#include "stdafx.h"
#include "Form1.h"
#include "Capture.h"
//#include "Logics.h"
//#include "EngineCategorization.h"

using namespace System;
using namespace System::Threading;
using namespace System::Net;
using namespace System::Collections::Generic;
//using namespace ContentFlow;
using namespace capture;
//using namespace EngineCategorization;
//using namespace LogicsSpace;
using namespace System::Xml;


//using namespace System::Text::RegularExpressions;
//using namespace System::Text;

#include "CFEngine.h"
#include "tcpip_structs.h"



void CFEngine::init()
{
	capture->refreshInterfaces();
	//for(int i=0; i<capture->getTotalInterfaces(); i++)
		//this->view->cf_addInterface(gcnew String(capture->getNextInterface()), i);
	//Tokenizer::init();
	XmlTextReader ^reader=gcnew XmlTextReader("contentflow.conf.xml");
	try {
		String ^context="";
		while (reader->Read())
		{
			
			switch (reader->NodeType)
			{
				case XmlNodeType::Comment:
                break;
				case XmlNodeType::Element:
					context+=reader->Name;
					if(context->Equals("ContentFlowNetworkActiveInterface"))
					{
						if(reader->HasAttributes)
						{
							//Console::WriteLine("autostart: [{0}]",);
							if(reader->GetAttribute("autostart")->Equals("enable"))
								this->autostart=true;
						}
					}
				break;
				case XmlNodeType::Text:
					if(context->Equals("ContentFlowNetworkActiveInterface"))
					{
						Console::WriteLine("ActiveInterface: [{0}]",reader->Value);
						//try {
						//	//this->view->cf_setInterface(Convert::ToInt32(reader->Value));
						//}
						////catch(System::FormatException ^sfe)
						//catch(...)
						//{
						//	//try use interface names instead
						//}
					}
				break;
				case XmlNodeType::EndElement:
					//Console::WriteLine("Key:[{0}] Value:[{1}]", reader->Name, reader->Value);
					context=context->Replace(reader->Name, "");
				break;


			}
			//Console::WriteLine("Context: [{0}]", context);
		}
		reader->Close();
		//view->cf_setStatus(gcnew String("Config loaded. System Ready."));
	}
	catch(System::Xml::XmlException ^xmle)
	{
		//view->cf_setStatus("Config contentflow.conf.xml warning: "+xmle->Message+" System Ready.");
	}
	//catch(System::IO::FileNotFoundException ^fnfe)
	catch(...)
	{
		//Console::WriteLine("No config contentflow.conf.xml file found. System Ready.");
		//view->cf_setStatus(gcnew String("System Ready."));
	}


}

IntPtr CFEngine::getPacketListener()
{
  return Marshal::GetFunctionPointerForDelegate(this->pl);
}

void CFEngine::start() 
{ 
	if(this->activeIface>=0)
	{
		this->running=true;
		this->activeIfaceChanged=true;
		//view->cf_setStatus(gcnew String("Running network capture."));
	}
	else if(this->captureFile==nullptr)
	{
		//view->cf_setStatus(gcnew String("No Active Interface has been selected. Please select one at Network->Active Interfaces."));
	}
	else
	{
		this->running=true;
		this->activeIfaceChanged=true;
		//view->cf_setStatus(gcnew String("Processing source file."));
	}
}

void CFEngine::stop() 
{ 
	if(this->running)
	{
	   this->running=false;
	   capture->closeInterface();
	   //view->cf_setStatus(gcnew String("Network capture has been stopped."));

	}
}

void CFEngine::setActiveIface(int i) 
{
	this->activeIface=i;
	if(i>=0) this->activeIfaceChanged=true;
	else  this->activeIfaceChanged=false;
}
void CFEngine::setCaptureFile(String ^captureFile)
{	this->captureFile=captureFile; }

String ^CFEngine::getCaptureFile()
{	return this->captureFile; }

void CFEngine::ThreadCaptureRun()
{
	capture->runInterface();
}

void CFEngine::ThreadProcessorRun()
{
	int index=Convert::ToInt32(Thread::CurrentThread->Name);
	Console::WriteLine("Processor started "+index);
	while(this->running)
	{
		FlowPacket ^pkt;
		try
		{
			//Console::Write("->1");
			pkt=static_cast<FlowPacket^>(this->packetQueue[index]->Dequeue());
			//Console::Write("->2");
		}
		catch(...){Thread::Sleep(500); continue; }
		switch(pkt->type)
		{
			case TYPEIP_UDP: 
				//Console::WriteLine("UDP[{0}][{1}][{2:X}][{3:X}]", pkt->endsrc, pkt->enddst, pkt->payload[0], pkt->payload[1] );
			break;
			case TYPEIP_TCP: 
				{
					//CLEANNED 
				}
				break;
		}

	}
}

void CFEngine::flowBlockInit(FlowBlock ^fblk)
{
	//Console::WriteLine("FLOWBLOCK INIT");
	
}

void CFEngine::flowBlockFin(FlowBlock ^fblk)
{
	//Console::WriteLine("FLOWBLOCK FIN");
	FlowBlock::removeFlowBlock(fblk);
}


int CFEngine::packetHandler(FlowPacket ^pkt) 
{
	switch(pkt->type)
	{
		case TYPEIP_UDP:
		case TYPEIP_TCP:
			{
				FlowBlock ^fblk=FlowBlock::searchFlowPacket(pkt);
				if(fblk==nullptr)
				{
					//Console::WriteLine("FlowBlock not found for {0}. Inserting...", pkt);
					FlowBlock::addFlowBlock(pkt);
				}
				else
				{
					//Console::WriteLine("MATCH[{0}]", fblk);	
					fblk->updateTimestamp();
					fblk->updateSignature(pkt);
				}
			}
			this->packetQueue[(((unsigned int)pkt->getHash())%this->processorSize)]->Enqueue(pkt);
		break;
	}
	return 0;
}



void CFEngine::ThreadCore()
{
	if(this->autostart)
	{
		this->start();
		Console::WriteLine("Auto Starting...");
	}
	while(true)
	{
		//Console::WriteLine( "ActiveInterface: {0}", this->activeIface );
		//Console::WriteLine( "ActiveInterfaceChange: {0}", this->activeIfaceChanged );

		if(!this->running)
		{
		  // Console::WriteLine( "stopped" );
		   Thread::Sleep(1000);
		   continue;
		}

		if(this->activeIfaceChanged)
		{
		   this->activeIfaceChanged=false;
		   //insert pcap bind code here
		   if(this->captureFile)
		   {
			   if(capture->openInterface(this->captureFile))
			   {
				  this->running=false;
				  //view->cf_setStatus(gcnew String(capture->getErrorMsg()));
				  capture->closeInterface();
				  continue;
			   }
			   this->captureFile=nullptr;
		   }
		   else if(capture->openInterface(this->activeIface))
		   {
			  this->running=false;
			  //view->cf_setStatus(gcnew String(capture->getErrorMsg()));
			  capture->closeInterface();
			  continue;
		   }
		   
			//nothing
		   { 
			    Console::WriteLine( "Content Flow Engine initialized..." );
				for(int i=0; i<this->processorSize; i++)
				{
					processorRun[i] = gcnew Thread(gcnew ThreadStart(this, &CFEngine::ThreadProcessorRun));
					processorRun[i]->Name = ""+i;
					processorRun[i]->Start();
				}

			   	captureRun = gcnew Thread(gcnew ThreadStart(this, &CFEngine::ThreadCaptureRun));
				captureRun->Name = "CFEngine runCapture";
				captureRun->Start();
	
		   }

		}
		Thread::Sleep(1000);
		//Console::WriteLine( "Flow List" );
		FlowBlock::showFlowList();

	} //while
}//thread core



