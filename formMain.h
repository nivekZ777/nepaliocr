#include "tessLoader.h"
#include "ThresholedValue.h"
#include "rgbConvert.h"
#include "Separate.h"
#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;	


namespace NepaliOCR
{
	/// <summary> 
	/// Summary for formMain
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public __gc class formMain : public System::Windows::Forms::Form
	{
	public: 
		formMain(void)
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
	private: System::Windows::Forms::Button *  btnTessLoader;
	private: System::Windows::Forms::OpenFileDialog *  dlgOpenImage;
	private: System::Windows::Forms::Button *  btnOpen;
	private: System::Windows::Forms::Panel *  pnlDisplay;
	private: System::Windows::Forms::PictureBox *  pbImage;
	public: System::Drawing::Bitmap *im;
	public: System::Drawing::Graphics *g;

	private: Bitmap* BinaryImage;
	
    private: int intLevel;
	private: int **ImgArray;

	private: bool **BArray;
			 bool **tmpBArray;

	private: bool BinaryDone;
	private: bool ImageLoaded;
			 bool SeparateDone;

    private: int numberOfLines;
	private: Line* Lines; 


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
			this->btnTessLoader = new System::Windows::Forms::Button();
			this->dlgOpenImage = new System::Windows::Forms::OpenFileDialog();
			this->btnOpen = new System::Windows::Forms::Button();
			this->pnlDisplay = new System::Windows::Forms::Panel();
			this->pbImage = new System::Windows::Forms::PictureBox();
			this->pnlDisplay->SuspendLayout();
			this->SuspendLayout();
			// 
			// btnTessLoader
			// 
			this->btnTessLoader->Location = System::Drawing::Point(216, 11);
			this->btnTessLoader->Name = S"btnTessLoader";
			this->btnTessLoader->TabIndex = 5;
			this->btnTessLoader->Text = S"Tess";
			this->btnTessLoader->Click += new System::EventHandler(this, btnTessLoader_Click);
			// 
			// btnOpen
			// 
			this->btnOpen->Location = System::Drawing::Point(24, 11);
			this->btnOpen->Name = S"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(80, 24);
			this->btnOpen->TabIndex = 4;
			this->btnOpen->Text = S"Open";
			this->btnOpen->Click += new System::EventHandler(this, btnOpen_Click);
			// 
			// pnlDisplay
			// 
			this->pnlDisplay->AutoScroll = true;
			this->pnlDisplay->Controls->Add(this->pbImage);
			this->pnlDisplay->Location = System::Drawing::Point(16, 59);
			this->pnlDisplay->Name = S"pnlDisplay";
			this->pnlDisplay->Size = System::Drawing::Size(512, 256);
			this->pnlDisplay->TabIndex = 3;
			this->pnlDisplay->DragEnter += new System::Windows::Forms::DragEventHandler(this, pnlDisplay_DragEnter);
			this->pnlDisplay->DragDrop += new System::Windows::Forms::DragEventHandler(this, pnlDisplay_DragDrop);
			// 
			// pbImage
			// 
			this->pbImage->Location = System::Drawing::Point(8, 8);
			this->pbImage->Name = S"pbImage";
			this->pbImage->Size = System::Drawing::Size(120, 64);
			this->pbImage->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pbImage->TabIndex = 0;
			this->pbImage->TabStop = false;
			// 
			// formMain
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(544, 326);
			this->Controls->Add(this->btnOpen);
			this->Controls->Add(this->pnlDisplay);
			this->Controls->Add(this->btnTessLoader);
			this->Name = S"formMain";
			this->Text = S"Nepali OCR Tesseract Loader";
			this->DragDrop += new System::Windows::Forms::DragEventHandler(this, formMain_DragDrop);
			this->DragEnter += new System::Windows::Forms::DragEventHandler(this, formMain_DragEnter);
			this->pnlDisplay->ResumeLayout(false);
			this->ResumeLayout(false);

		}		
	private: System::Void btnOpen_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 this->openImageFunction();
			 }

	private: System::Void btnTessLoader_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 this->runTesseractLoader();
			 }

	public: void  openImageFunction(){
				System::Windows::Forms::DialogResult d = this->dlgOpenImage->ShowDialog();
				if(d == System::Windows::Forms::DialogResult::OK){
					im = new Bitmap(this->dlgOpenImage->OpenFile());
					this->pbImage->Image = im;
					this->ImageLoaded = true;
					this->BinaryDone=false;
					g = this->pbImage->CreateGraphics();
				}
				this->DoBinary();
				this->separate();
			}
	 
	public: void runTesseractLoader(){
				
				tessLoader *mytessLoader = new tessLoader();
				mytessLoader->Show();
				this->Dispose(false);
			
				//todo system.exit
			}

	
private: void DoBinary()
		 {
			 if(this->ImageLoaded)
			 {
				try
				{
					 // set the cursor to wait.... 
						this->Cursor = System::Windows::Forms::Cursors::WaitCursor;
					 
					 // calculating Thresholed Value for binary image					 
						ThresholedValue* ts = new ThresholedValue(im);
						float fLevel = ts->GetThresholed();
						intLevel = int(fLevel*255);
								 
					// getting an binary array of 					 
						rgbConvert* rgbC = new rgbConvert(im);
						BArray = rgbC->GetBinaryArray(intLevel);
						ImgArray = rgbC->GetImageArray( );
					   	
					 // Showing the binary image
						this->BinaryImage = rgbC->GetBinaryImage();
						this->pbImage->Image = this->BinaryImage;
						
					 // set the cursor to Default.... 
						this->Cursor = System::Windows::Forms::Cursors::Default;
						//System::Windows::Forms::MessageBox::Show(this->intLevel.ToString()/*fLevel.ToString()*/,"Threshold Value");
						
						 
						this->BinaryDone=true;
				}
				catch(System::Exception* ex)
				{
					System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"Failed to Binarize the Image!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
					this->Update();
				}
				 this->Update();
			 }
		 }

private: void DoSeparate()
			 {
				 if( (this->ImageLoaded==true  ) && (this->BinaryDone==true) )
			 {
				this->separate();
			 }
			 else if( (this->ImageLoaded==false  ) )
			 {
				 System::Windows::Forms::MessageBox::Show("Please load the image first","Image not loaded");
			 }
			 else if(this->BinaryDone==false)
					 {
						 //System::Windows::Forms::Show("Please binarize the image before separating","Binarization not done");
						 System::Windows::Forms::MessageBox::Show("Please binarize the image first","Binarization not done");

				}
			 }

  private: void separate()
				 {
					 
				/*
				This method is used to separate the words and lines after binarization.
				*/

					 this->tmpBArray=new bool*[im->Height];
					 //System::Windows::Forms::MessageBox::Show(im->Height.ToString(),"Height");
					 
					 for(int i=0;i<im->Height;i++)
					 {
						 this->tmpBArray[i]=new bool[im->Width];
						 for(int j=0;j<im->Width;j++)
						 {
							 this->tmpBArray[i][j]=this->BArray[i][j];
						 }

					 }
					 if(this->BinaryDone==true) //If binarization is done
						{

							if(this->SeparateDone==false)
							{
							Separate* sp=new Separate(im,BArray,g);
							sp->applicationPathResolver(Application::StartupPath->ToString());
							sp->LineSeparate();						//Separate Lines from the image

							this->numberOfLines=sp->getNumberOfLines(); //Get Number of Lines
							this->Lines=sp->getLines();			//Get Lines
							this->SeparateDone=true;
							this->separateChar();				//separate Characters					
							}

							else
							{
								this->separateChar();			//separate Characters
							}
						}
					 
					this->Update();
				 }
  private: void separateChar()
				 {
/*

	This method is used to separate the characters, or the connected units  after the words are separated.

*/
					 Pen* p=new Pen(Color::Blue,1);
	
								for(int i=0;i<this->numberOfLines;i++)
									{
										for(int j=0;j<this->Lines[i].getTotalWord();j++)
											{
												for(int k=0;k<this->Lines[i].Words[j].getTotalUnit();k++)
													{
														int x1=this->Lines[i].Words[j].Units[k].getStartColumn();
														int x2=this->Lines[i].Words[j].Units[k].getEndColumn();
														int y1=this->Lines[i].getStartRow();
														int y2=this->Lines[i].getEndRow();
														
														//g->DrawLine(p,x1,y1,x1,y2);
														//g->DrawLine(p,x2,y1,x2,y2);
													}
											}
									}
								}

	private: System::Void pnlDisplay_DragEnter(System::Object *  sender, System::Windows::Forms::DragEventArgs *  e)
			 {
				 if(e->Data->GetDataPresent(DataFormats::FileDrop))
							e->Effect = DragDropEffects::All;
			 else
					e->Effect = DragDropEffects::None;
			 }

private: System::Void pnlDisplay_DragDrop(System::Object *  sender, System::Windows::Forms::DragEventArgs *  e)
		 {
			  if(e->Data->GetDataPresent(DataFormats::FileDrop))
							e->Effect = DragDropEffects::All;
			 else
					e->Effect = DragDropEffects::None;

			  String* fileName[];
			   
			   int a;
			  fileName = (String *[]) e->Data->GetData(DataFormats::FileDrop, false);
			  for(a=0;a<fileName->Length;a++){
				im = new Bitmap(fileName[a]);
				this->pbImage->Image = im;
				g=this->pbImage->CreateGraphics();
			  }

		 }

private: System::Void formMain_DragEnter(System::Object *  sender, System::Windows::Forms::DragEventArgs *  e)
		 {
			  if(e->Data->GetDataPresent(DataFormats::FileDrop))
							e->Effect = DragDropEffects::All;
			 else
					e->Effect = DragDropEffects::None;
		 }

private: System::Void formMain_DragDrop(System::Object *  sender, System::Windows::Forms::DragEventArgs *  e)
		 {
			 
			  if(e->Data->GetDataPresent(DataFormats::FileDrop))
					e->Effect = DragDropEffects::All;
			 else
					e->Effect = DragDropEffects::None;

			  String* fileName[];
			   
			   int a;
			  fileName = (String *[]) e->Data->GetData(DataFormats::FileDrop, false);
			  for(a=0;a<fileName->Length;a++){
				im = new Bitmap(fileName[a]);
				this->pbImage->Image = im;
				g=this->pbImage->CreateGraphics();
			  }
		 }

};
}