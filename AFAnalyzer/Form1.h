#pragma once

namespace AFAnalyzer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Xml;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			initFile("afanalyzer.xml");
			//timer->Enable=true;
			timer->Start();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::StatusStrip^  statusStrip;
	private: System::Windows::Forms::ToolStripStatusLabel^  status;
	protected: 

	private: System::Windows::Forms::MenuStrip^  menuStrip;
	private: System::Windows::Forms::ToolStripMenuItem^  menuItemFile;

	private: System::Windows::Forms::ToolStripMenuItem^  menuLoad;
	private: System::Windows::Forms::ToolStripMenuItem^  menuUnload;
	private: System::Windows::Forms::ToolStripSeparator^  menuSeparator1;




	private: System::Windows::Forms::ToolStripMenuItem^  menuExit;
	private: System::Windows::Forms::ToolStripMenuItem^  menuItemSetup;


	private: System::Windows::Forms::ToolStripMenuItem^  loadFilterToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  signaturesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  captureColumnsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  menuSeparator2;
	private: System::Windows::Forms::ToolStripMenuItem^  menuResolve;



	private: System::Windows::Forms::ToolStripMenuItem^  menuItemFlow;

	private: System::Windows::Forms::ToolStripMenuItem^  menuSelectAll;
	private: System::Windows::Forms::ToolStripMenuItem^  menuSelectNone;
	private: System::Windows::Forms::ToolStripMenuItem^  menuDelete;
	private: System::Windows::Forms::ToolStripMenuItem^  menuAnalyze;
	private: System::Windows::Forms::ToolStripMenuItem^  menuConvert;





	private: System::Windows::Forms::ToolStripSeparator^  menuSeparator3;
	private: System::Windows::Forms::ToolStripMenuItem^  menuItemAbout;
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

		static const int FORM_STAT_ERROR = 0;
		static const int FORM_STAT_READY = 1;
		static const int FORM_STAT_LOAD = 2;
		static const int FORM_STAT_GENANA = 3;
		static const int FORM_STAT_GENAFA = 4;
		static const int FORM_STAT_GENAFC = 5;
	private: System::Windows::Forms::OpenFileDialog^  loadFileDialog;
	private: System::Windows::Forms::ToolStripMenuItem^  listeningToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  startListeningToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  companyToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  stopListeningToolStripMenuItem;
	private: System::Windows::Forms::Panel^  panel;
	private: System::Windows::Forms::TabControl^  tabControl;
	private: System::Windows::Forms::TabPage^  flowListPage;

	private: array<DataGridViewColumn ^>^ FLColumm;
	private: System::Windows::Forms::DataGridView^  dataGridView;
	private: System::Windows::Forms::Timer^  timer;
	private: System::Windows::Forms::TabPage^  analysisPage;
	private: System::Windows::Forms::ToolStripMenuItem^  menuInvertSelection;





		static array<String ^>^ form_stat={"Critical Error: ", 
													 "Ready ", 
												  "Loading: ", 
												  "Generating Capture Analysis...",
												  "Generating AppFlow Analysis...",
												  "Generating AppFlow Capture...",};

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->statusStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->status = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->menuItemFile = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuLoad = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuUnload = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->menuExit = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuItemSetup = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadFilterToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->signaturesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->captureColumnsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->listeningToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->menuResolve = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuItemFlow = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuSelectAll = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuSelectNone = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuInvertSelection = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuDelete = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->startListeningToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->stopListeningToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuAnalyze = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuConvert = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuItemAbout = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->companyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->panel = (gcnew System::Windows::Forms::Panel());
			this->tabControl = (gcnew System::Windows::Forms::TabControl());
			this->flowListPage = (gcnew System::Windows::Forms::TabPage());
			this->dataGridView = (gcnew System::Windows::Forms::DataGridView());
			this->analysisPage = (gcnew System::Windows::Forms::TabPage());
			this->timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->statusStrip->SuspendLayout();
			this->menuStrip->SuspendLayout();
			this->panel->SuspendLayout();
			this->tabControl->SuspendLayout();
			this->flowListPage->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView))->BeginInit();
			this->SuspendLayout();
			// 
			// statusStrip
			// 
			this->statusStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->status});
			this->statusStrip->Location = System::Drawing::Point(0, 540);
			this->statusStrip->Name = L"statusStrip";
			this->statusStrip->Size = System::Drawing::Size(964, 22);
			this->statusStrip->TabIndex = 0;
			this->statusStrip->Text = L"statusStrip";
			// 
			// status
			// 
			this->status->Name = L"status";
			this->status->Size = System::Drawing::Size(39, 17);
			this->status->Text = L"Ready";
			// 
			// menuStrip
			// 
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->menuItemFile, this->menuItemSetup, 
				this->menuItemFlow, this->menuItemAbout});
			this->menuStrip->Location = System::Drawing::Point(0, 0);
			this->menuStrip->Name = L"menuStrip";
			this->menuStrip->Size = System::Drawing::Size(964, 24);
			this->menuStrip->TabIndex = 1;
			this->menuStrip->Text = L"menuStrip";
			// 
			// menuItemFile
			// 
			this->menuItemFile->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->menuLoad, 
				this->menuUnload, this->menuSeparator1, this->menuExit});
			this->menuItemFile->Name = L"menuItemFile";
			this->menuItemFile->Size = System::Drawing::Size(37, 20);
			this->menuItemFile->Text = L"&File";
			// 
			// menuLoad
			// 
			this->menuLoad->Name = L"menuLoad";
			this->menuLoad->Size = System::Drawing::Size(112, 22);
			this->menuLoad->Text = L"&Load";
			this->menuLoad->Click += gcnew System::EventHandler(this, &Form1::menuLoad_Click);
			// 
			// menuUnload
			// 
			this->menuUnload->Enabled = false;
			this->menuUnload->Name = L"menuUnload";
			this->menuUnload->Size = System::Drawing::Size(112, 22);
			this->menuUnload->Text = L"&Unload";
			this->menuUnload->Click += gcnew System::EventHandler(this, &Form1::menuUnload_Click);
			// 
			// menuSeparator1
			// 
			this->menuSeparator1->Name = L"menuSeparator1";
			this->menuSeparator1->Size = System::Drawing::Size(109, 6);
			// 
			// menuExit
			// 
			this->menuExit->Name = L"menuExit";
			this->menuExit->Size = System::Drawing::Size(112, 22);
			this->menuExit->Text = L"&Exit";
			this->menuExit->Click += gcnew System::EventHandler(this, &Form1::menuExit_Click);
			// 
			// menuItemSetup
			// 
			this->menuItemSetup->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->loadFilterToolStripMenuItem, 
				this->signaturesToolStripMenuItem, this->captureColumnsToolStripMenuItem, this->listeningToolStripMenuItem, this->menuSeparator2, 
				this->menuResolve});
			this->menuItemSetup->Name = L"menuItemSetup";
			this->menuItemSetup->Size = System::Drawing::Size(49, 20);
			this->menuItemSetup->Text = L"&Setup";
			// 
			// loadFilterToolStripMenuItem
			// 
			this->loadFilterToolStripMenuItem->Name = L"loadFilterToolStripMenuItem";
			this->loadFilterToolStripMenuItem->Size = System::Drawing::Size(167, 22);
			this->loadFilterToolStripMenuItem->Text = L"Load &Filter";
			// 
			// signaturesToolStripMenuItem
			// 
			this->signaturesToolStripMenuItem->Name = L"signaturesToolStripMenuItem";
			this->signaturesToolStripMenuItem->Size = System::Drawing::Size(167, 22);
			this->signaturesToolStripMenuItem->Text = L"&Signatures";
			// 
			// captureColumnsToolStripMenuItem
			// 
			this->captureColumnsToolStripMenuItem->Name = L"captureColumnsToolStripMenuItem";
			this->captureColumnsToolStripMenuItem->Size = System::Drawing::Size(167, 22);
			this->captureColumnsToolStripMenuItem->Text = L"&Capture Columns";
			// 
			// listeningToolStripMenuItem
			// 
			this->listeningToolStripMenuItem->Name = L"listeningToolStripMenuItem";
			this->listeningToolStripMenuItem->Size = System::Drawing::Size(167, 22);
			this->listeningToolStripMenuItem->Text = L"&Listening";
			// 
			// menuSeparator2
			// 
			this->menuSeparator2->Name = L"menuSeparator2";
			this->menuSeparator2->Size = System::Drawing::Size(164, 6);
			// 
			// menuResolve
			// 
			this->menuResolve->CheckOnClick = true;
			this->menuResolve->Name = L"menuResolve";
			this->menuResolve->Size = System::Drawing::Size(167, 22);
			this->menuResolve->Text = L"&Resolve Names";
			// 
			// menuItemFlow
			// 
			this->menuItemFlow->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(9) {this->menuSelectAll, 
				this->menuSelectNone, this->menuInvertSelection, this->menuDelete, this->menuSeparator3, this->startListeningToolStripMenuItem, 
				this->stopListeningToolStripMenuItem, this->menuAnalyze, this->menuConvert});
			this->menuItemFlow->Name = L"menuItemFlow";
			this->menuItemFlow->Size = System::Drawing::Size(44, 20);
			this->menuItemFlow->Text = L"Flo&w";
			// 
			// menuSelectAll
			// 
			this->menuSelectAll->Enabled = false;
			this->menuSelectAll->Name = L"menuSelectAll";
			this->menuSelectAll->Size = System::Drawing::Size(155, 22);
			this->menuSelectAll->Text = L"Select &all";
			this->menuSelectAll->Click += gcnew System::EventHandler(this, &Form1::menuSelectAll_Click);
			// 
			// menuSelectNone
			// 
			this->menuSelectNone->Enabled = false;
			this->menuSelectNone->Name = L"menuSelectNone";
			this->menuSelectNone->Size = System::Drawing::Size(155, 22);
			this->menuSelectNone->Text = L"Select &none";
			this->menuSelectNone->Click += gcnew System::EventHandler(this, &Form1::menuSelectNone_Click);
			// 
			// menuInvertSelection
			// 
			this->menuInvertSelection->Enabled = false;
			this->menuInvertSelection->Name = L"menuInvertSelection";
			this->menuInvertSelection->Size = System::Drawing::Size(155, 22);
			this->menuInvertSelection->Text = L"&Invert Selection";
			this->menuInvertSelection->Click += gcnew System::EventHandler(this, &Form1::menuInvertSelection_Click);
			// 
			// menuDelete
			// 
			this->menuDelete->Enabled = false;
			this->menuDelete->Name = L"menuDelete";
			this->menuDelete->Size = System::Drawing::Size(155, 22);
			this->menuDelete->Text = L"&Delete";
			this->menuDelete->Click += gcnew System::EventHandler(this, &Form1::menuDelete_Click);
			// 
			// menuSeparator3
			// 
			this->menuSeparator3->Name = L"menuSeparator3";
			this->menuSeparator3->Size = System::Drawing::Size(152, 6);
			// 
			// startListeningToolStripMenuItem
			// 
			this->startListeningToolStripMenuItem->Name = L"startListeningToolStripMenuItem";
			this->startListeningToolStripMenuItem->Size = System::Drawing::Size(155, 22);
			this->startListeningToolStripMenuItem->Text = L"Start &Listening";
			// 
			// stopListeningToolStripMenuItem
			// 
			this->stopListeningToolStripMenuItem->Enabled = false;
			this->stopListeningToolStripMenuItem->Name = L"stopListeningToolStripMenuItem";
			this->stopListeningToolStripMenuItem->Size = System::Drawing::Size(155, 22);
			this->stopListeningToolStripMenuItem->Text = L"&Stop Listening";
			// 
			// menuAnalyze
			// 
			this->menuAnalyze->Enabled = false;
			this->menuAnalyze->Name = L"menuAnalyze";
			this->menuAnalyze->Size = System::Drawing::Size(155, 22);
			this->menuAnalyze->Text = L"Analy&ze";
			this->menuAnalyze->Click += gcnew System::EventHandler(this, &Form1::menuAnalyze_Click);
			// 
			// menuConvert
			// 
			this->menuConvert->Enabled = false;
			this->menuConvert->Name = L"menuConvert";
			this->menuConvert->Size = System::Drawing::Size(155, 22);
			this->menuConvert->Text = L"&Convert";
			// 
			// menuItemAbout
			// 
			this->menuItemAbout->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->helpToolStripMenuItem, 
				this->companyToolStripMenuItem});
			this->menuItemAbout->Name = L"menuItemAbout";
			this->menuItemAbout->Size = System::Drawing::Size(52, 20);
			this->menuItemAbout->Text = L"&About";
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(126, 22);
			this->helpToolStripMenuItem->Text = L"&Help";
			// 
			// companyToolStripMenuItem
			// 
			this->companyToolStripMenuItem->Name = L"companyToolStripMenuItem";
			this->companyToolStripMenuItem->Size = System::Drawing::Size(126, 22);
			this->companyToolStripMenuItem->Text = L"&Company";
			// 
			// loadFileDialog
			// 
			this->loadFileDialog->FileName = L"*.pcap";
			// 
			// panel
			// 
			this->panel->BackColor = System::Drawing::SystemColors::AppWorkspace;
			this->panel->Controls->Add(this->tabControl);
			this->panel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel->Location = System::Drawing::Point(0, 24);
			this->panel->Name = L"panel";
			this->panel->Size = System::Drawing::Size(964, 516);
			this->panel->TabIndex = 2;
			// 
			// tabControl
			// 
			this->tabControl->Controls->Add(this->flowListPage);
			this->tabControl->Controls->Add(this->analysisPage);
			this->tabControl->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl->Location = System::Drawing::Point(0, 0);
			this->tabControl->Name = L"tabControl";
			this->tabControl->SelectedIndex = 0;
			this->tabControl->Size = System::Drawing::Size(964, 516);
			this->tabControl->TabIndex = 0;
			this->tabControl->Visible = false;
			// 
			// flowListPage
			// 
			this->flowListPage->Controls->Add(this->dataGridView);
			this->flowListPage->Location = System::Drawing::Point(4, 22);
			this->flowListPage->Name = L"flowListPage";
			this->flowListPage->Padding = System::Windows::Forms::Padding(3);
			this->flowListPage->Size = System::Drawing::Size(956, 490);
			this->flowListPage->TabIndex = 1;
			this->flowListPage->Text = L"Flow List";
			this->flowListPage->UseVisualStyleBackColor = true;
			// 
			// dataGridView
			// 
			this->dataGridView->AllowUserToAddRows = false;
			this->dataGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dataGridView->EditMode = System::Windows::Forms::DataGridViewEditMode::EditOnEnter;
			this->dataGridView->Location = System::Drawing::Point(3, 3);
			this->dataGridView->Name = L"dataGridView";
			this->dataGridView->Size = System::Drawing::Size(950, 484);
			this->dataGridView->TabIndex = 0;
			this->dataGridView->Visible = false;
			this->dataGridView->CellStateChanged += gcnew System::Windows::Forms::DataGridViewCellStateChangedEventHandler(this, &Form1::dataGridView_CellStateChanged);
			this->dataGridView->CellValueChanged += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::dataGridView_CellContentClick);
			// 
			// analysisPage
			// 
			this->analysisPage->Location = System::Drawing::Point(4, 22);
			this->analysisPage->Name = L"analysisPage";
			this->analysisPage->Padding = System::Windows::Forms::Padding(3);
			this->analysisPage->Size = System::Drawing::Size(956, 490);
			this->analysisPage->TabIndex = 2;
			this->analysisPage->Text = L"Analysis";
			this->analysisPage->UseVisualStyleBackColor = true;
			// 
			// timer
			// 
			this->timer->Enabled = true;
			this->timer->Interval = 1000;
			this->timer->Tick += gcnew System::EventHandler(this, &Form1::timer_Event);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(964, 562);
			this->Controls->Add(this->panel);
			this->Controls->Add(this->statusStrip);
			this->Controls->Add(this->menuStrip);
			this->MainMenuStrip = this->menuStrip;
			this->Name = L"Form1";
			this->Text = L"AppFlow Analyzer";
			this->statusStrip->ResumeLayout(false);
			this->statusStrip->PerformLayout();
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			this->panel->ResumeLayout(false);
			this->tabControl->ResumeLayout(false);
			this->flowListPage->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void menuLoad_Click(System::Object^  sender, System::EventArgs^  e) { 
				 //this->status->Text=this->form_stat[FORM_STAT_LOAD];
				 bool hasRows=false;
				 this->status->Text="Please select PCAP files to load.";
				 loadFileDialog->Filter = "PCAP files|*.pcap|AppFlow files|*.apf";
				 loadFileDialog->RestoreDirectory = true;
				 if(loadFileDialog->ShowDialog()==System::Windows::Forms::DialogResult::OK)
				 {
					int row=0;
					if (loadFileDialog->CheckFileExists == true)
					{
						this->status->Text="Processing "+loadFileDialog->FileName+" ...";
						try
						{
							// Create an instance of StreamReader to read from a file.
							// The using statement also closes the StreamReader.
							StreamReader^ sr = gcnew StreamReader(loadFileDialog->FileName);
							String^ line;
							// Read and display lines from the file until the end of
							// the file is reached.
							while ((line = sr->ReadLine()) != nullptr)
							{
								if(line->Length > 2)
								{
									hasRows=true;
									this->dataGridView->Rows->Add();
									this->dataGridView->Rows[row]->Cells[2]->Value=line;
									this->dataGridView->Rows[row]->Cells[0]->Value=false;
									row++;
								}
							}
							sr->Close();
							this->tabControl->Visible=true;
							this->Text = "AppFlow Analyzer - "+loadFileDialog->FileName;
							if(hasRows)
							{
							  this->dataGridView->Visible=true;
							  this->menuSelectAll->Enabled = true;
							}
							this->menuUnload->Enabled = true;
							this->startListeningToolStripMenuItem->Enabled = false;
							this->menuLoad->Enabled = false;
						}
						catch (Exception^ e)
						{
							// Let the user know what went wrong.
							this->status->Text="Critical Error: "+e->Message;
						}
					}
					else
					{
						this->status->Text="Critical Error: File "+loadFileDialog->FileName+" does not exist.";
					}
				 } else this->status->Text="Ready.";
	}
private: System::Void menuUnload_Click(System::Object^  sender, System::EventArgs^  e) {
			this->Text = "AppFlow Analyzer";
			this->menuAnalyze->Enabled = false;
			this->menuConvert->Enabled = false;
			this->menuSelectAll->Enabled = false;
			this->menuSelectNone->Enabled = false;
			this->menuInvertSelection->Enabled=false;
            this->menuDelete->Enabled = false;
			this->tabControl->Visible = false;
			this->menuUnload->Enabled = false;
			this->menuLoad->Enabled = true;
			this->startListeningToolStripMenuItem->Enabled = true;
			this->dataGridView->Visible=false;
			this->dataGridView->Rows->Clear();
			this->status->Text="Ready.";
		 }
private: System::Void menuExit_Click(System::Object^  sender, System::EventArgs^  e) {
		 }

private: System::Void initFile(String ^fname) {
				XmlTextReader ^xtr;
				XmlTextWriter ^xtw;
				bool ifexists = true;
				int size=0;
				int width=0, ind=0; String ^name=nullptr;
				System::Windows::Forms::DataGridViewCheckBoxColumn ^current=nullptr;
				try
				{
					xtr = gcnew XmlTextReader(fname);
					xtr->Read(); //skip 
				}
				catch (Exception^  )
				{
					ifexists = false;
				}
				

				if(!ifexists)
				{
					try
					{
						  xtw = gcnew XmlTextWriter(fname, System::Text::Encoding::UTF8);
						  xtw->Formatting = Formatting::Indented;
						  xtw->Indentation = 4;
						  xtw->WriteStartDocument();
						  xtw->WriteComment("AppFlow Analyzer INI file");
						  xtw->WriteStartElement("AFAnalyzer_INI");
						  xtw->WriteStartElement("FLOWLIST");
						  xtw->WriteAttributeString("size", "12");
						  xtw->WriteStartElement("COLUMN");
						  xtw->WriteAttributeString("name", "Select");
						  xtw->WriteAttributeString("ind", "1");
						  xtw->WriteAttributeString("width", "42");
						  xtw->WriteString("Checkbox");
						  xtw->WriteEndElement();
						  xtw->WriteStartElement("COLUMN");
						  xtw->WriteAttributeString("name", "NumPkts");
						  xtw->WriteAttributeString("ind", "2");
						  xtw->WriteAttributeString("width", "60");
						  xtw->WriteString("Field");
						  xtw->WriteEndElement();

						  xtw->WriteStartElement("COLUMN");
						  xtw->WriteAttributeString("name", "IPSrc");
						  xtw->WriteAttributeString("ind", "3");
						  xtw->WriteAttributeString("width", "150");
						  xtw->WriteString("Field");
						  xtw->WriteEndElement();

						  xtw->WriteStartElement("COLUMN");
						  xtw->WriteAttributeString("name", "PortSrc");
						  xtw->WriteAttributeString("ind", "4");
						  xtw->WriteAttributeString("width", "60");
						  xtw->WriteString("Field");
						  xtw->WriteEndElement();

						  xtw->WriteStartElement("COLUMN");
						  xtw->WriteAttributeString("name", "IPDst");
						  xtw->WriteAttributeString("ind", "5");
						  xtw->WriteAttributeString("width", "150");
						  xtw->WriteString("Field");
						  xtw->WriteEndElement();

						  xtw->WriteStartElement("COLUMN");
						  xtw->WriteAttributeString("name", "PortDst");
						  xtw->WriteAttributeString("ind", "6");
						  xtw->WriteAttributeString("width", "60");
						  xtw->WriteString("Field");
						  xtw->WriteEndElement();

						  xtw->WriteStartElement("COLUMN");
						  xtw->WriteAttributeString("name", "Stack");
						  xtw->WriteAttributeString("ind", "7");
						  xtw->WriteAttributeString("width", "60");
						  xtw->WriteString("Field");
						  xtw->WriteEndElement();

						  xtw->WriteStartElement("COLUMN");
						  xtw->WriteAttributeString("name", "Signature");
						  xtw->WriteAttributeString("ind", "8");
						  xtw->WriteAttributeString("width", "60");
						  xtw->WriteString("Field");
						  xtw->WriteEndElement();

						  xtw->WriteStartElement("COLUMN");
						  xtw->WriteAttributeString("name", "PayloadStart");
						  xtw->WriteAttributeString("ind", "9");
						  xtw->WriteAttributeString("width", "100");
						  xtw->WriteString("Field");
						  xtw->WriteEndElement();

						  xtw->WriteStartElement("COLUMN");
						  xtw->WriteAttributeString("name", "Size");
						  xtw->WriteAttributeString("ind", "10");
						  xtw->WriteAttributeString("width", "60");
						  xtw->WriteString("Field");
						  xtw->WriteEndElement();

						  xtw->WriteStartElement("COLUMN");
						  xtw->WriteAttributeString("name", "Complete");
						  xtw->WriteAttributeString("ind", "11");
						  xtw->WriteAttributeString("width", "60");
						  xtw->WriteString("Field");
						  xtw->WriteEndElement();

						  xtw->WriteStartElement("COLUMN");
						  xtw->WriteAttributeString("name", "Type");
						  xtw->WriteAttributeString("ind", "12");
						  xtw->WriteAttributeString("width", "60");
						  xtw->WriteString("Field");
						  xtw->WriteEndElement();

						  xtw->WriteEndElement();
						  xtw->WriteEndElement();
						  xtw->WriteEndDocument();
						  xtw->Flush();
						  xtw->Close();
						  this->status->Text="Created AFAnalyzer.xml INI file.";
					}
					catch (Exception^ e)
					{
						ifexists = false;
						this->status->Text="Critical Error (Writing AFAnalyzer.xml): "+e->Message;
					}				
				}

				try
				{
					xtr = gcnew XmlTextReader(fname);
					while(xtr->Read())
					{
					  if(xtr->NodeType == XmlNodeType::EndElement)
					  {
						  if(String::Compare(xtr->Name, "COLUMN", true)==0)
						  {
					        width=0; ind=0;
						  }
						  if(String::Compare(xtr->Name, "FLOWLIST", true)==0)
						  {
							  for(int i=0; i<size; i++)
							  {
								if(FLColumm[i]!=nullptr)
							      dataGridView->Columns->Add(FLColumm[i]);
							  }
						  }
					  }
					  else if(xtr->NodeType == XmlNodeType::Text)
					  {
						  if(ind>0)
						  {
						  	  if(String::Compare(xtr->Value, "Checkbox", true)==0)
							  {  
								  FLColumm[ind -1]= (gcnew System::Windows::Forms::DataGridViewCheckBoxColumn());
								  FLColumm[ind -1]->HeaderText = name;
								  FLColumm[ind -1]->Name = name;
								  FLColumm[ind -1]->Width = width;
								  
							  }
							  else if(String::Compare(xtr->Value, "Field", true)==0)
							  {  
								  FLColumm[ind -1]= (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
								  FLColumm[ind -1]->HeaderText = name;
								  FLColumm[ind -1]->Name = name;
								  FLColumm[ind -1]->Width = width;
								  FLColumm[ind -1]->ReadOnly = true;
							  }
							  else{ this->status->Text="Error parsing AFAnalyzer.ini: Invalid COLUMN Value ("+xtr->Value+")"; return; }
						  }
					  }
					  else if(xtr->NodeType == XmlNodeType::Element)
					  {
						  if(String::Compare(xtr->Name, "FLOWLIST", true)==0)
						  {  
							  try 
							  { 
								  size = Convert::ToInt32(xtr->GetAttribute("size")); 
								  if(size <= 0 || size > 18) throw (gcnew Exception("Invalid FLOWLIST Size"));
							  }
							  catch (Exception^ )
							  { this->status->Text="Error parsing AFAnalyzer.ini: FLOWLIST SIZE"; return; }

							  FLColumm= (gcnew array<DataGridViewColumn^>(size));

						  }
						  if(String::Compare(xtr->Name, "COLUMN", true)==0)
						  {
							  
						      if(!size)
							  {  this->status->Text="Error parsing AFAnalyzer.ini: Missing FLOWLIST SIZE"; return; }

							  try 
							  { 
								  width = Convert::ToInt32(xtr->GetAttribute("width")); 
								  ind = Convert::ToInt32(xtr->GetAttribute("ind"));
								  name = xtr->GetAttribute("name");
								  if(width <= 0 || width > 800) throw (gcnew Exception("Invalid FLOWLIST width "+width));
								  if(ind <= 0 || ind > size) throw (gcnew Exception("Invalid FLOWLIST ind "+ind));
							  }
							  catch (Exception^ e)
							  { 
								  this->status->Text="Warning parsing AFAnalyzer.xml: "+e->Message; 
								  ind = 0;
							  }
						  }
					  }

					}
					xtr->Close();
				}
				catch (Exception^ e)
				{
					this->status->Text="Critical Error (Reading AFAnalyzer.xml): "+e->Message;
				}

		 }
private: System::Void dataGridView_CellContentClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
			 //dataGridView->ClearSelection();
			 //dataGridView->CurrentCell=nullptr;
		 }
private: System::Void dataGridView_CellStateChanged(System::Object^  sender, System::Windows::Forms::DataGridViewCellStateChangedEventArgs^  e) {

			// dataGridView->ClearSelection();
			// dataGridView->CurrentCell=nullptr;
		 }
private: System::Void timer_Event(System::Object^  sender, System::EventArgs^  e) {
			 int i=0;
			 int c=0;

			 if(dataGridView->IsCurrentCellDirty == true)
			    dataGridView->CommitEdit(DataGridViewDataErrorContexts::Commit);


			 if(dataGridView->RowCount>0)
			 {
			      this->menuSelectAll->Enabled = true;
			      this->menuInvertSelection->Enabled = true;
			 }
			 else
			 {
			      this->menuSelectAll->Enabled = false;
			      this->menuInvertSelection->Enabled = false;
			 }
			 for(i=0; i<dataGridView->RowCount; i++)
			 {
			      if((dataGridView->Rows[i]->Cells[0]->Value+"")=="True") c++;
				  if(!this->menuInvertSelection->Enabled) this->menuInvertSelection->Enabled=true;
			 }
			 if(c>0) 
			 {
				 this->status->Text="Selected "+c+" Flow(s).";
				 this->menuDelete->Enabled = true;
				 this->menuSelectNone->Enabled = true;
				 this->menuAnalyze->Enabled = true;
				 this->menuConvert->Enabled = true;
			 }
			 else
			 {
				 this->status->Text="Ready.";
				 this->menuDelete->Enabled = false;
				 this->menuSelectNone->Enabled = false;
				 this->menuAnalyze->Enabled = false;
				 this->menuConvert->Enabled = false;
			 }

		 }
private: System::Void menuSelectAll_Click(System::Object^  sender, System::EventArgs^  e) {
			 int i=0;
			 for(i=0; i<dataGridView->RowCount; i++)
			 {
			     dataGridView->Rows[i]->Cells[0]->Value=true;
			 }
			 dataGridView->ClearSelection();
			 dataGridView->CurrentCell=nullptr;
		 }
private: System::Void menuSelectNone_Click(System::Object^  sender, System::EventArgs^  e) {
			 int i=0;
			 for(i=0; i<dataGridView->RowCount; i++)
			 {
			     dataGridView->Rows[i]->Cells[0]->Value=false;
			 }
			 dataGridView->ClearSelection();
			 dataGridView->CurrentCell=nullptr;			 
		 }
private: System::Void menuInvertSelection_Click(System::Object^  sender, System::EventArgs^  e) {
			 int i=0;
			 for(i=0; i<dataGridView->RowCount; i++)
			 {
			     dataGridView->Rows[i]->Cells[0]->Value=!(bool)dataGridView->Rows[i]->Cells[0]->Value;
			 }
			 dataGridView->ClearSelection();
			 dataGridView->CurrentCell=nullptr;		
		 }
private: System::Void menuDelete_Click(System::Object^  sender, System::EventArgs^  e) {
			 int i=0;
			 for(i=0; i<dataGridView->RowCount; i++)
			 {
			     if((bool)dataGridView->Rows[i]->Cells[0]->Value)
				 {
				   dataGridView->Rows->RemoveAt(i);
				   i--;
				 }
			 }
			 dataGridView->ClearSelection();
			 dataGridView->CurrentCell=nullptr;		
		 }
private: System::Void menuAnalyze_Click(System::Object^  sender, System::EventArgs^  e) {
			 int c=0, i=0;
			// array<TabPages ^>^ pages=this->tabControl->TabPages();



			 for(i=0; i<dataGridView->RowCount; i++)
			 {
				  if((dataGridView->Rows[i]->Cells[0]->Value+"")=="True")
				  {
						IEnumerator ^tpc=this->tabControl->TabPages->GetEnumerator();
						bool found=false;
						while(tpc->MoveNext())
						{
						   TabPage^ current=(TabPage ^)tpc->Current;
						   if(current->Name ==(dataGridView->Rows[i]->Cells[2]->Value+"+"+
											  dataGridView->Rows[i]->Cells[3]->Value+"_"+
											  dataGridView->Rows[i]->Cells[4]->Value+"+"+
                                              dataGridView->Rows[i]->Cells[5]->Value+"-TCP"))
						   {
						     found=true;
							 break;
						   }
						}
						if(found) continue;

						TabPage^ fanalysisPage = gcnew TabPage();
						fanalysisPage->Location = System::Drawing::Point(4, 22);
						fanalysisPage->Name = (dataGridView->Rows[i]->Cells[2]->Value+"+"+
											  dataGridView->Rows[i]->Cells[3]->Value+"_"+
											  dataGridView->Rows[i]->Cells[4]->Value+"+"+
                                              dataGridView->Rows[i]->Cells[5]->Value+"-TCP");
						fanalysisPage->Padding = System::Windows::Forms::Padding(3);
						fanalysisPage->Size = System::Drawing::Size(956, 490);
						fanalysisPage->TabIndex = 2+c;
						fanalysisPage->Text =(dataGridView->Rows[i]->Cells[2]->Value+"+"+
											  dataGridView->Rows[i]->Cells[3]->Value+"_"+
											  dataGridView->Rows[i]->Cells[4]->Value+"+"+
                                              dataGridView->Rows[i]->Cells[5]->Value+"-TCP");
						fanalysisPage->UseVisualStyleBackColor = true;																											
                        this->tabControl->Controls->Add(fanalysisPage);
						c++;																																
				  }
			 }
			 dataGridView->ClearSelection();
			 dataGridView->CurrentCell=nullptr;
		 }
};
}

