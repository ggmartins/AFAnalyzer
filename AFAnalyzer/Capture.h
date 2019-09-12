#pragma once

//using namespace System::Collections::Generic;
#include <string.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <list>
#include <iostream>
#include <time.h>
//#include <winsock.h>
#include "pcap.h"

namespace capture {
	using namespace System;
	using namespace System::Net;
	using namespace System::Runtime::InteropServices;
	using namespace System::Collections;
	using namespace System::ComponentModel;




	//this is basically an ip packet (udp/tcp) with parameters dissected
	//we dont care about icmp, arp, stp packets for now
public ref class FlowPacket : public IComparable {
public:
	int type;
	IPEndPoint ^endsrc;
	IPEndPoint ^enddst;
	u_int iphlen; //ok
	u_int tcpseq;
	u_int tcpack;
	u_int tcpwin;
	u_int tcpurg;
	u_int tcpopt;
	u_int hdrlen; //ok (udp & tcp)
	u_int pldlen; //ok
	u_int chksum;
	bool cwr; //congestion win reduced;
	bool ecn; //Explicit Congestion Notification ecn echo
	bool syn;
	bool ack;
	bool psh;
	bool rst;
	bool fin;
	bool urg;
	array<Byte>^ payload;
	FlowPacket() { payload=gcnew array<Byte>(1500); }
	int decode(const u_char *pkt_data, int length);
	virtual Int32 CompareTo( Object^ obj);
	virtual  String ^ToString() override
	{ 
		return "["+endsrc+"+"+enddst+"] s:"+((syn)?"1":"0")+" a:"+((ack)?"1":"0")+
	         " p:"+((psh)?"1":"0")+" r:"+((rst)?"1":"0")+" f:"+((fin)?"1":"0")+" u:"+((urg)?"1":"0")+" l:"+pldlen; 
	}
	int getHash();

}; 


ref class FlowBlock;
	delegate  void FlowBlockInit(FlowBlock ^fblk);
	delegate  void FlowBlockFin(FlowBlock ^fblk);


public ref class FlowBlock : public IComparable{
private:
	int hash;
	FlowPacket ^fp;
	//static ArrayList ^flowBlockList=nullptr;
	static Hashtable ^hashtable=nullptr;
	DateTime timestamp;
	static FlowBlockInit ^flowBlockInit=nullptr;
	static FlowBlockFin ^flowBlockFin=nullptr;
	int exptime;
	array<Byte>^ pldsig;
public:
	int lastpos;
	FlowBlock(FlowPacket ^fp)
	{
		this->hash=fp->getHash();
		this->fp=fp;
		timestamp=DateTime::Now;
		exptime=30;
		if(fp->pldlen>0) pldsig=fp->payload;
		else pldsig=nullptr;
	}
	virtual Int32 CompareTo( Object^ obj);
	virtual String ^ToString() override { return this->fp->ToString(); }
	//static ArrayList ^getFlowList();
	static Hashtable ^getHashtable();
	static void showFlowList();
	static FlowBlock^ getFlowBlock(int index);
	static FlowBlock^ searchFlowPacket(Object ^fpktobj);
	static void addFlowBlock(FlowPacket ^fpkt);
	static void removeFlowBlock(FlowBlock ^fblk);
	void setTimeout(int timeout) { exptime=timeout; }
	bool hasExpired(DateTime now);
	FlowPacket^ getFlowPacket() { return fp; }
	int getHash() { return hash; }
	
	void updateTimestamp() { timestamp=DateTime::Now; }
	void updateSignature(FlowPacket ^fp) { if(this->pldsig==nullptr) if(fp->pldlen>0) pldsig=fp->payload; }
	static void setFlowBlockInit(void (*callback)(FlowBlock ^fblk));
	static void setFlowBlockFin(void (*callback)(FlowBlock ^fblk));

};




}



#pragma managed(push, off)

//unamnaged callback func
void pkt_handler(u_char *user, const struct pcap_pkthdr *pkt_header, const u_char *pkt_data);



namespace capture {
	using namespace std;	
//unmanaged callback signature
typedef int (__stdcall *packetHandler)(FlowPacket ^pkt);
//unmanaged callback linker
int runPHCallBack(packetHandler ph, FlowPacket ^pkt);

public  class Capture {
public:
	Capture(){ sprintf_s(errbuf, PCAP_ERRBUF_SIZE, "Unknown error."); }
	void init();
	int getTotalInterfaces();
	int refreshInterfaces();
	//void setPacketHandler(Object ^packetHandlerObj);
	const char *getNextInterface();
	int openInterface(int activeIface);
	int openInterface(String ^captureFile);
	int Capture::runInterface();
	int closeInterface();
	const char* getErrorMsg();
	int runPacketListener(FlowPacket ^pkt);
	void setPacketListener(IntPtr callback);
	pcap_t *cap;
private:
	std::list <string> devlist;
	std::list <string>::iterator deviter;
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_if_t *alldevs;
	pcap_if_t *d;
	IntPtr callback; //pkt handler call back
	packetHandler pktHandler;
	//void *(*pkthandler)(FlowPacket ^pkt);



};

#pragma managed(pop)

}