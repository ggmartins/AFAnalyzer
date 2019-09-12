#include "stdafx.h"
#include <winsock2.h>

#include <string.h>
#include <vcclr.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <list>
#include <iostream>
#include <time.h>
#include "pcap.h"
#include "tcpip_structs.h"

using namespace System;
using namespace System::Collections;
using namespace System::Threading;
using namespace System::Net;

using namespace std;

#include "Capture.h"

namespace capture {

void FlowBlock::setFlowBlockInit(void (*callback)(FlowBlock ^fblk))
{ FlowBlock::flowBlockInit=gcnew FlowBlockInit(callback); }
void FlowBlock::setFlowBlockFin(void (*callback)(FlowBlock ^fblk))
{ FlowBlock::flowBlockFin=gcnew FlowBlockFin(callback); }

Hashtable ^FlowBlock::getHashtable()
{
	if(FlowBlock::hashtable==nullptr) FlowBlock::hashtable=Hashtable::Synchronized(gcnew Hashtable());
	return FlowBlock::hashtable;
}

void FlowBlock::addFlowBlock(FlowPacket ^fpkt)
{
	FlowBlock ^fblk=gcnew FlowBlock(fpkt);
	Hashtable ^hashtable=FlowBlock::getHashtable();
	hashtable->Add(fblk->getHash(), fblk);
	if(FlowBlock::flowBlockInit!=nullptr)
		FlowBlock::flowBlockInit->Invoke(fblk);
}


void FlowBlock::removeFlowBlock(FlowBlock ^fblk)
{
	Hashtable ^hashtable=FlowBlock::getHashtable();
	hashtable->Remove(fblk->getHash());
}

bool FlowBlock::hasExpired(DateTime now)
{
	TimeSpan delta=now.Subtract(this->timestamp);
	if(((delta.Minutes*60)+delta.Seconds)>FlowBlock::exptime) return true; 

	return false;
}

void FlowBlock::showFlowList()
{
	DateTime now=DateTime::Now;
	Hashtable ^hashtable=dynamic_cast<Hashtable^> ((FlowBlock::getHashtable())->Clone());
	IEnumerator^ ie=hashtable->GetEnumerator();
	while ( ie->MoveNext() )
	{
		DictionaryEntry de=*safe_cast<DictionaryEntry ^>(ie->Current);
		FlowBlock ^flowblock=dynamic_cast<FlowBlock^>(de.Value);
		if(flowblock->hasExpired(now))
		{
			if(FlowBlock::flowBlockFin!=nullptr)
				FlowBlock::flowBlockFin->Invoke(flowblock);
		}
		//Console::WriteLine("{0} Exp:{1}", flowblock->ToString(), ((flowblock->hasExpired(now))?"1":"0"));
		array<Byte>^ pldsig=gcnew array<Byte>(6);
		
		String ^pldstr=nullptr;
		if(flowblock->pldsig!=nullptr)
		{
			Array::Copy(flowblock->pldsig, pldsig, 6);
			pldstr=System::Text::Encoding::ASCII->GetString(pldsig);
		}
		//Console::WriteLine("{0}[{1}]", flowblock->ToString(),pldstr);
	}
	hashtable=nullptr;
	GC::Collect();
}

FlowBlock^ FlowBlock::getFlowBlock(int index)
{
	FlowBlock ^flowblock=nullptr;
	return flowblock;
}

Int32 FlowBlock::CompareTo( Object^ obj ) 
{
	if ( obj->GetType() == FlowBlock::typeid ) 
	{
		FlowBlock ^flowblock=dynamic_cast<FlowBlock^>(obj);
		return (this->hash==flowblock->hash)?0:((this->hash<flowblock->hash)?-1:1);
	}
	if ( obj->GetType() == FlowPacket::typeid ) 
	{
		FlowPacket ^flowpacket=dynamic_cast<FlowPacket^>(obj);
		return (this->hash==flowpacket->getHash())?0:((this->hash<flowpacket->getHash())?-1:1);
		//return this->fp->CompareTo(flowpacket);
	}
	throw gcnew ArgumentException(  "Object is not a FlowBlock/FlowPacket" );
}

FlowBlock^ FlowBlock::searchFlowPacket(Object ^fpktobj)
{
	Hashtable ^hashtable=FlowBlock::getHashtable();
	FlowPacket ^fpkt=nullptr;
	if ( hashtable == nullptr ) return nullptr;
	if ( fpktobj == nullptr ) return nullptr;
	if ( fpktobj->GetType() != FlowPacket::typeid ) return nullptr;
	fpkt=dynamic_cast<FlowPacket^>  (fpktobj);
	FlowBlock ^fblk=dynamic_cast<FlowBlock^> (hashtable[fpkt->getHash()]);
	return fblk;
}

int FlowPacket::decode(const u_char *pkt_data, int length)
{
	mac_header *mh;
	ip_header *ih;
    udp_header *uh;
	tcp_header *th;
	unsigned char *pld=NULL;
	mh=(mac_header *)pkt_data;
	if(mh->type==TYPEMAC_IP)
	{
	  ih=(ip_header *)(pkt_data+sizeof(mac_header));	
	  ih->ver_ihl=ih->ver_ihl & 0x0F;
	  this->iphlen=(ih->ver_ihl*4);
	  this->type=ih->proto;
	  if(ih->proto==TYPEIP_UDP) 
	  {
		  uh=(udp_header *)(pkt_data+sizeof(mac_header)+this->iphlen);
		  this->hdrlen=sizeof(udp_header);
		  pld=(unsigned char *)(pkt_data+sizeof(mac_header)+this->iphlen+sizeof(udp_header));
		  this->endsrc=gcnew IPEndPoint((__int64)ih->saddr, uh->sport);//ntohs(uh->sport)); //danger converting __int64
		  this->enddst=gcnew IPEndPoint((__int64)ih->daddr, uh->dport);//ntohs(uh->dport)); //danger converting __int64
		  this->pldlen=length-sizeof(mac_header)-this->iphlen-this->hdrlen;
		  if(this->pldlen>1500)
		  {
			this->pldlen=0;
			return 0;
		  }
		  Marshal::Copy(IntPtr(pld),this->payload, 0, this->pldlen);
		 // Console::WriteLine("UDP[{0}][{1}][{2:X}][{3:X}]", endsrc, enddst, this->payload[0], this->payload[1] );
	  }
	  else if(ih->proto==TYPEIP_TCP)
	  {
		  u_char th_size;
		  th=(tcp_header *)(pkt_data+sizeof(mac_header)+this->iphlen);
		  th_size=th->th_off;
		  this->hdrlen=(th_size>>4)*4;
		  pld=(unsigned char *)(pkt_data+sizeof(mac_header)+this->iphlen+this->hdrlen);
		  //this->endsrc=gcnew IPEndPoint((__int64)ih->saddr, ntohs(th->sport)); //danger converting __int64
		  //this->enddst=gcnew IPEndPoint((__int64)ih->daddr, ntohs(th->dport)); //danger converting __int64
		  this->cwr=((th->flags&0x80)==0x80);
		  this->ecn=((th->flags&0x40)==0x40);
		  this->urg=((th->flags&0x20)==0x20);
		  this->ack=((th->flags&0x10)==0x10);
		  this->psh=((th->flags&0x08)==0x08);
		  this->rst=((th->flags&0x04)==0x04);
		  this->syn=((th->flags&0x02)==0x02);
		  this->fin=((th->flags&0x01)==0x01);
		  this->pldlen=length-sizeof(mac_header)-this->iphlen-this->hdrlen;
		  if(this->pldlen>1500)
		  {
			this->pldlen=0;
			return 0;
		  }
		  Marshal::Copy(IntPtr(pld),this->payload, 0, this->pldlen);
		  //Console::WriteLine("syn:{0} ack:{1} psh:{2} rst:{3} fin:{4} urg:{5} len:{6}", 
			////  this->syn, this->ack, this->psh, this->rst, this->fin, this->urg, this->pldlen);
		  //Console::WriteLine("TCP[{0}][{1}][{2:X}][{3:X}]->{4}", endsrc, enddst, this->payload[0], this->payload[1],length );
		 // for(int i=0; i<this->pldlen; i++) Console::Write("[{0:X}]", this->payload[i]);
		 // Console::WriteLine("");
	  }
	  else { /*Console::WriteLine("Received: non tcp/udp packet");*/  return 1; }

	}

	return 0;
}

Int32 FlowPacket::CompareTo( Object^ obj ) {
	if ( obj->GetType() == FlowPacket::typeid ) 
	{
		FlowPacket ^flowpacket=dynamic_cast<FlowPacket^>(obj);
		if(this->endsrc->Equals(flowpacket->endsrc)&&this->enddst->Equals(flowpacket->enddst)) return 0;
		if(this->endsrc->Equals(flowpacket->enddst)&&this->enddst->Equals(flowpacket->endsrc)) return 0;
		if(this->endsrc->GetHashCode()<this->enddst->GetHashCode()) //do not use this, not trustworthy
		{
			if(flowpacket->endsrc->GetHashCode()<flowpacket->enddst->GetHashCode())
				 return (this->endsrc->GetHashCode()<flowpacket->endsrc->GetHashCode())?-1:1;
			else return (this->endsrc->GetHashCode()<flowpacket->enddst->GetHashCode())?-1:1;
		}
		else
		{
			if(flowpacket->enddst->GetHashCode()<flowpacket->endsrc->GetHashCode())
				 return (this->enddst->GetHashCode()<flowpacket->enddst->GetHashCode())?-1:1;
			else return (this->enddst->GetHashCode()<flowpacket->endsrc->GetHashCode())?-1:1;
		}
	}
	throw gcnew ArgumentException(  "Object is not a FlowPacket" );
	return 0;
}

int FlowPacket::getHash()
{
	//check null for endsrc enddst
	//return (this->enddst->GetHashCode()<this->endsrc->GetHashCode())?
		//this->enddst->GetHashCode():
		//this->endsrc->GetHashCode();
	return ((int)this->enddst->GetHashCode() ^ (int)this->endsrc->GetHashCode());
}

void pkt_handler(u_char *user, const struct pcap_pkthdr *pkt_header, const u_char *pkt_data)
{
	int i=1,j=2;
	FlowPacket ^pkt=gcnew FlowPacket();
	Capture *capture=(Capture *)user;
	//pkt->decode(pkt_data, pkt_header->len);
	capture->runPacketListener(pkt);
}


void Capture::init() 
{ 
	callback=(IntPtr)nullptr;
	//refreshInterfaces();
	//FlowBlock::setFlowBlockInit(&Capture::flowBlockInit);
	//FlowBlock::setFlowBlockFin(&Capture::flowBlockFin);
}


int runPHCallBack(packetHandler ph, FlowPacket ^pkt)
{
   return ph(pkt); //access violation exception
}


int Capture::runPacketListener(FlowPacket ^pkt)
{
   //packetHandler cb = static_cast<packetHandler>(this->callback.ToPointer());
   if(this->pktHandler!=nullptr)
	   return runPHCallBack(this->pktHandler, pkt);
   else
		return 0;
}

void Capture::setPacketListener(IntPtr listener)
{
   this->callback=listener;
   this->pktHandler = static_cast<packetHandler>(this->callback.ToPointer());
}


int Capture::refreshInterfaces() {
	pcap_if_t *alldevs;
    pcap_if_t *d;
	devlist.clear();

	if (pcap_findalldevs(&alldevs, errbuf) == -1) return 1;
	for(d= alldevs; d != NULL; d= d->next)
	{
		if (d->description)
		{
			char ifacename[200];
			if(d->addresses)
			{
				struct in_addr  interface_addr;
				interface_addr = ((struct sockaddr_in *)d->addresses->addr)->sin_addr;
				//sprintf_s(ifacename,200, "(%s) %s", inet_ntoa(interface_addr), d->description);
			}
			else sprintf_s(ifacename,200, "(unnamed) %s", d->description);
			devlist.push_back((std::string)ifacename);
		}
		//else
	}
	pcap_freealldevs((pcap_if_t *)(alldevs));
	deviter=devlist.begin();
	return 0;
}

int Capture::openInterface(String ^captureFile)
{
  pin_ptr<const wchar_t> cap = PtrToStringChars(captureFile);
  size_t origsize = wcslen(cap) + 1;
  size_t convertedChars = 0;
  char capFile[250];
  wcstombs_s(&convertedChars, capFile, origsize, cap, _TRUNCATE);

  this->cap=pcap_open_offline(capFile,errbuf);
  if(this->cap == NULL) return 1; 
  return 0;
}


int Capture::openInterface(int activeIface)
{
  int i=0;
  if (pcap_findalldevs(&alldevs, errbuf) == -1) return 1;
  for(d= alldevs; ((d != NULL)&&(i<(activeIface-1))); d= d->next) i++;
  if(d==NULL) 
  { 
	   sprintf_s(errbuf, PCAP_ERRBUF_SIZE, "Invalid interface number %d.", activeIface); 
	   this->cap=NULL; 
	   return 1;
  }
  this->cap=pcap_open_live(d->name, 65536, 1,-1,errbuf);
  pcap_freealldevs((pcap_if_t *)(alldevs));
  if(this->cap == NULL) return 1; 

  return 0;
}

int Capture::runInterface()
{
	int r;
	struct pcap_pkthdr *pkt_header;
	//pcap_loop(this->cap, 0, pkt_handler, (u_char *)this);
	const u_char *packet;
	
	while((r=pcap_next_ex(this->cap, &pkt_header, &packet))>=0) //access violation exception
	{
		if(r==0)
		{
		  continue; //timeout
		}
		//Console::WriteLine("HERE");
		capture::pkt_handler((u_char *)this, pkt_header, packet);
		//Thread::Sleep(10);	
	}
	Console::WriteLine("Leaving here");
	return 0;
}

int Capture::closeInterface()
{
  if(this->cap != NULL) pcap_breakloop(this->cap);
  return 0;
}

int  Capture::getTotalInterfaces()
{
  return this->devlist.size ();
}
const char * Capture::getNextInterface()
{
  if(deviter != devlist.end()) 
  {
	  return (*(deviter++)).c_str(); 
  }
  return nullptr;
}

const char* Capture::getErrorMsg(){ return this->errbuf; }

}