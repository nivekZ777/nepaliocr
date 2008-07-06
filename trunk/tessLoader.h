#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Threading;

namespace NepaliOCR
{
	/// <summary> 
	/// Summary for tessLoader
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public __gc class tessLoader : public System::Windows::Forms::Form
	{
	public: 
		tessLoader(void)
		{
			InitializeComponent();
		}
        
	protected: 
		void Dispose(Boolean disposing)
		{
			if (disposing && components)
			{
				components->Dispose();
			}
			__super::Dispose(disposing);
		}
	private: System::Windows::Forms::Button *  button3;
	private: System::Windows::Forms::Button *  button2;
	private: System::Windows::Forms::RichTextBox *  rtb_output;
	private: System::Windows::Forms::Button *  button1;
	public: String* applicationPath;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container* components;

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button3 = new System::Windows::Forms::Button();
			this->button2 = new System::Windows::Forms::Button();
			this->rtb_output = new System::Windows::Forms::RichTextBox();
			this->button1 = new System::Windows::Forms::Button();
			this->SuspendLayout();
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(348, 27);
			this->button3->Name = S"button3";
			this->button3->Size = System::Drawing::Size(72, 24);
			this->button3->TabIndex = 11;
			this->button3->Text = S"delete files";
			this->button3->Click += new System::EventHandler(this, button3_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(216, 24);
			this->button2->Name = S"button2";
			this->button2->TabIndex = 10;
			this->button2->Text = S"tess";
			this->button2->Click += new System::EventHandler(this, button2_Click);
			// 
			// rtb_output
			// 
			this->rtb_output->Location = System::Drawing::Point(44, 67);
			this->rtb_output->Name = S"rtb_output";
			this->rtb_output->Size = System::Drawing::Size(408, 240);
			this->rtb_output->TabIndex = 9;
			this->rtb_output->Text = S"";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(88, 24);
			this->button1->Name = S"button1";
			this->button1->Size = System::Drawing::Size(64, 24);
			this->button1->TabIndex = 8;
			this->button1->Text = S"Output";
			this->button1->Click += new System::EventHandler(this, button1_Click);
			// 
			// tessLoader
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(496, 334);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->rtb_output);
			this->Controls->Add(this->button1);
			this->Name = S"tessLoader";
			this->Text = S"tessLoader";
			this->Closed += new System::EventHandler(this, tessLoader_Closed);
			this->ResumeLayout(false);

		}		
	private: System::Void button1_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 this->showFile("output.txt");
				 this->showFile("tesseract.log");
			 }

	private: System::Void button2_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				  this->tryTesseract();
			 }

	private: System::Void button3_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				  this->delFile("output.txt");
				 this->delFile("tesseract.log");
			 }


	
public: void showFile(String *fileName){
			try{
				//this->rtb_output->Text = "";
					System::IO::StreamReader *outPutReader = new System::IO::StreamReader(fileName);
					while(String* myline = outPutReader->ReadLine()){
						this->rtb_output->AppendText(myline);
					}
			}
			catch(System::Exception *ex){
				this->rtb_output->AppendText(ex->ToString());
			}
		}

public: void delFile(String *fileName){
			this->rtb_output->Text = "";
			try{
			if(System::IO::File::Exists(fileName)){
				  System::IO::File::Delete(fileName);
			  }
			 else{
				 this->rtb_output->AppendText("\n -- File not found");
				 this->rtb_output->AppendText(fileName);
				 this->rtb_output->AppendText("--\n");
			  }
			}
			catch(System::Exception *ex){
				this->rtb_output->AppendText(ex->ToString());
			}
			 
	}


	public: void tryTesseract()
	{
				this->applicationPath=Application::StartupPath->ToString();
			//remove an extra slash "/" in the filepath
			int len = this->applicationPath->Length -1;			
			
			if(this->applicationPath->Substring(len)->Equals("\\"))
			{
				this->applicationPath = this->applicationPath->Substring(0,len);				
			}

			 
		
				/////////////////// paths here ////////////////
			//tesseract will be provided to the user in a folder called tesseract
			System::String* tesseractPath="";
			System::String* invComa="\"";
			tesseractPath =  tesseractPath->Concat(invComa,this->applicationPath, "\\" ,"tesseract.exe");
			tesseractPath =  tesseractPath->Concat(tesseractPath,invComa);
			//tesseractPath = "tesseract.exe";
			//tesseractPath = tesseractPath->Concat("\"",tesseractPath,"\"");
			
			System::String *imagePath  = " eurotext.tif ";
			System::String* langId = " -l eng ";
			System::String* outPutFileName = " outputfile ";
			
			System::String *fullParameters = "";
			fullParameters = fullParameters->Concat(fullParameters,imagePath);
			fullParameters = fullParameters->Concat(fullParameters,outPutFileName,langId);
		
			
		
			try{
				System::Diagnostics::Process *q = new System::Diagnostics::Process();
				//q->StartInfo->FileName = this->applicationPath\\"hello.exe";//tesseractPath;
				
				//Working stuff
				////q->Start("tesseract.exe"," eurotext.tif output");
				//working stuff
				
				//Produce Output
				if(System::IO::File::Exists("output.txt"))
							System::IO::File::Delete("output.txt");
				if(System::IO::File::Exists("tesseract.log"))
							System::IO::File::Delete("tesseract.log");

				q->Start("tesseract.exe"," eurotext.tif output" );
				
				this->Cursor = System::Windows::Forms::Cursors::WaitCursor;
				//q->WaitForExit();
				this->Cursor = System::Windows::Forms::Cursors::Default;
				
				//try reading output
				try{
					System::IO::StreamReader *outPutReader = new System::IO::StreamReader("output.txt");
					while(String* myline = outPutReader->ReadLine()){
					this->rtb_output->AppendText(myline);

					}
					//Try deleting temporary file
					try{
						q->WaitForExit();
						MessageBox::Show("sleeping");
						while(q->HasExited == false){
							
							
							Thread::Sleep(200);
						}
						
					}
					catch(System::Exception *ex2){
						this->rtb_output->AppendText("\n -- File could not be deleted \n");
					}
					
				}
				catch(System::Exception *ex){
					this->rtb_output->AppendText("\n --- Error Reading Output --\n");
				}
				q->StartInfo->UseShellExecute = false;
				q->StartInfo->CreateNoWindow = true; 
				q->StartInfo->RedirectStandardInput = true; 
				q->StartInfo->RedirectStandardOutput = true;
				q->StartInfo->RedirectStandardError = true;
				
				//this->rtb_output->AppendText(q->StandardError->ToString());
				//this->rtb_output->AppendText(q->StandardInput->ToString());
				//this->rtb_output->AppendText(q->StandardOutput->ToString());
			}
			catch(System::Exception *excp){

				this->rtb_output->AppendText("\n ==  Error running tesseract  == \n");
				System::String *excep2;
			//	excep2 = excep2->Concat(excep2,tesseractPath," \n", excp->Message->ToString());
				this->rtb_output->AppendText(excp->ToString());
				

			}
		


		}







	private: System::Void tessLoader_Closed(System::Object *  sender, System::EventArgs *  e)
			 {
				 Application::Exit();
			 }

};
}