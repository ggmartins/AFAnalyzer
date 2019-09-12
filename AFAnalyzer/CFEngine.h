

using namespace System::Collections::Generic;

public interface class Engine {
	public:
	virtual void start()=0;
	virtual void stop()=0;
	virtual void setActiveIface(int i)=0;
	virtual void setCaptureFile(String ^captureFile)=0;
};

ref class CFEngine: public Engine
{
public:
	delegate int PacketListener(FlowPacket ^pkt);
private:
	Capture *capture;
	//Form1 ^view;
	int activeIface;
	bool activeIfaceChanged;
	bool running;
	bool autostart;
	String ^captureFile;
	Thread ^captureRun;
	int processorSize;
	array<Thread ^> ^processorRun;
	PacketListener ^pl;
	ArrayList ^flowBlockList;
	Hashtable ^hashtable;
	array<System::Collections::Queue^> ^packetQueue; 
public:
	int packetHandler(FlowPacket ^pkt);
	CFEngine()
	{
		activeIface=-1;
		activeIfaceChanged=false;	
		running=false;
		autostart=false;
		captureFile=nullptr;
		pl = gcnew PacketListener(this, &CFEngine::packetHandler);
		//flowBlockList=FlowBlock::getFlowList();
		processorSize=3;
		processorRun=gcnew array<Thread ^>(processorSize);
		packetQueue=gcnew array<System::Collections::Queue ^>(processorSize);
		for(int i=0; i<processorSize; i++)
			packetQueue[i]=System::Collections::Queue::Synchronized(gcnew System::Collections::Queue());
	}
	//void setView(Form1 ^form){ this->view=form; this->view->cf_setEngine(this); };
	void setCapture(Capture *capture) { this->capture=capture; /*this->capture->setPacketHandler(this);*/ }
	
public:
	IntPtr getPacketListener ();
	void init();
	void ThreadCore();
	void ThreadCaptureRun();
	void ThreadProcessorRun();
	//void packetHandler(FlowPacket ^pkt);
	virtual void start();
	virtual void stop();
	virtual void setActiveIface(int i);
	virtual void setCaptureFile(String ^captureFile);
	virtual String ^getCaptureFile();
	static void flowBlockInit(FlowBlock ^fblk);
	static void flowBlockFin(FlowBlock ^fblk);

};



