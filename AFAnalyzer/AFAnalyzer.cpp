// AFAnalyzer.cpp : main project file.

#include "stdafx.h"
#include "Form1.h"

#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "pcap.h"
#include "Windows.h"
#include "Capture.h"
#using <system.dll>

#include <iostream>

using namespace System;
//using namespace System::IO;
//using namespace System::Text;
//using namespace ContentFlow;
using namespace AFAnalyzer;
//using namespace System;
using namespace System::Threading;
using namespace capture;
#include "CFEngine.h"
[STAThreadAttribute]



int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	CFEngine^ cfe=gcnew CFEngine();
		AttachConsole(ATTACH_PARENT_PROCESS);
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 
	Console::WriteLine( "\n\nContentFlow Prototype v0.2");
	// Create the main window and run it
	Application::Run(gcnew Form1());
	return 0;
}
