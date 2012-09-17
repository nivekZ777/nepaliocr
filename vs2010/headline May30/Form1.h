#include "ThresholedValue.h"
#include "rgbConvert.h"
#include "Separate.h"

#pragma once


namespace Headliner_ver_103
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary> 
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public __gc class Form1 : public System::Windows::Forms::Form
	{	
	public:
		Form1(void)
		{
			this->BinaryDone=false;
			this->ImageLoaded=false;
			this->SeparateDone=false;
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

	private: Bitmap* im;
	private: Bitmap* BinaryImage;
	private: Graphics* g;
    private: int intLevel;
	private: int **ImgArray;

	private: bool **BArray;
			 bool **tmpBArray;

	private: bool BinaryDone;
	private: bool ImageLoaded;
			 bool SeparateDone;

    private: int numberOfLines;
	private: Line* Lines; 

	private: System::Windows::Forms::Button *  btnOpen;
	private: System::Windows::Forms::Button *  btnSave;
	private: System::Windows::Forms::Button *  btnExit;
	private: System::Windows::Forms::Panel *  panel1;
	private: System::Windows::Forms::PictureBox *  pictureBox1;
	private: System::Windows::Forms::OpenFileDialog *  myDialog;
	private: System::Windows::Forms::Label *  lbl1;
	private: System::Windows::Forms::Label *  lbl2;


	private: System::Windows::Forms::SaveFileDialog *  saveImage;




	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container * components;

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btnOpen = new System::Windows::Forms::Button();
			this->btnSave = new System::Windows::Forms::Button();
			this->btnExit = new System::Windows::Forms::Button();
			this->panel1 = new System::Windows::Forms::Panel();
			this->pictureBox1 = new System::Windows::Forms::PictureBox();
			this->myDialog = new System::Windows::Forms::OpenFileDialog();
			this->lbl1 = new System::Windows::Forms::Label();
			this->lbl2 = new System::Windows::Forms::Label();
			this->saveImage = new System::Windows::Forms::SaveFileDialog();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// btnOpen
			// 
			this->btnOpen->Location = System::Drawing::Point(16, 8);
			this->btnOpen->Name = S"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(40, 23);
			this->btnOpen->TabIndex = 0;
			this->btnOpen->Text = S"Open";
			this->btnOpen->Click += new System::EventHandler(this, btnOpen_Click);
			// 
			// btnSave
			// 
			this->btnSave->Location = System::Drawing::Point(64, 8);
			this->btnSave->Name = S"btnSave";
			this->btnSave->Size = System::Drawing::Size(48, 23);
			this->btnSave->TabIndex = 1;
			this->btnSave->Text = S"Save";
			this->btnSave->Click += new System::EventHandler(this, btnSave_Click);
			// 
			// btnExit
			// 
			this->btnExit->Location = System::Drawing::Point(208, 232);
			this->btnExit->Name = S"btnExit";
			this->btnExit->TabIndex = 2;
			this->btnExit->Text = S"Exit";
			this->btnExit->Click += new System::EventHandler(this, button3_Click);
			// 
			// panel1
			// 
			this->panel1->AutoScroll = true;
			this->panel1->Controls->Add(this->pictureBox1);
			this->panel1->Location = System::Drawing::Point(9, 40);
			this->panel1->Name = S"panel1";
			this->panel1->Size = System::Drawing::Size(272, 184);
			this->panel1->TabIndex = 3;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(15, 15);
			this->pictureBox1->Name = S"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(248, 160);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// lbl1
			// 
			this->lbl1->Enabled = false;
			this->lbl1->Location = System::Drawing::Point(120, 8);
			this->lbl1->Name = S"lbl1";
			this->lbl1->TabIndex = 4;
			// 
			// lbl2
			// 
			this->lbl2->Enabled = false;
			this->lbl2->Location = System::Drawing::Point(232, 8);
			this->lbl2->Name = S"lbl2";
			this->lbl2->Size = System::Drawing::Size(56, 23);
			this->lbl2->TabIndex = 5;
			// 
			// Form1
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(296, 266);
			this->Controls->Add(this->lbl2);
			this->Controls->Add(this->lbl1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->btnExit);
			this->Controls->Add(this->btnSave);
			this->Controls->Add(this->btnOpen);
			this->Name = S"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = S"Headliner Ver 1.03";
			this->panel1->ResumeLayout(false);
			this->ResumeLayout(false);

		}	
	private: System::Void button3_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 this->Close();
			 }

	private: System::Void btnOpen_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 this->OpenImage();
				 this->DoBinary();
				 this->DoSeparate();
			 }

private: void OpenImage(void)
			 {
				 System::Windows::Forms::DialogResult myDialog = this->myDialog->ShowDialog();
				 if (myDialog == System::Windows::Forms::DialogResult::OK)				 
				 {			 
					this->ImageLoaded = true;
					this->BinaryDone=false;
					 // creating a bitmap
					 im = new Bitmap(this->myDialog->OpenFile());
					this->pictureBox1->Image = im;
					//g = Graphics::FromImage(im);
					g=this->pictureBox1->CreateGraphics();
					 	
					//System::Windows::Forms::MessageBox::Show("Image successfully loaded","Success");
				 }
				this->Update();
				//this->Refresh();
				 
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
						this->pictureBox1->Image = this->BinaryImage;
						
					 // set the cursor to Default.... 
						this->Cursor = System::Windows::Forms::Cursors::Default;
						//System::Windows::Forms::MessageBox::Show(this->intLevel.ToString()/*fLevel.ToString()*/,"Threshold Value");
						
						lbl1->Text = "Threshold Value";
						lbl2->Text = this->intLevel.ToString();
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
					 lbl1->Text = "Image Height";
					 lbl2->Text = im->Height.ToString();
					 //this->tmpBArray=this->BArray;
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

private: System::Void btnSave_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 try {

			 this->saveImageFile();
			 } catch (Exception *x ) {
				 System::Windows::Forms::MessageBox::Show(x->Message->ToString(),"Failed to Apply Mean Removal!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
			 }

		 }


 private: void saveImageFile()
			{

					saveImage->Filter= "Jpeg files (*.jpg)|*.jpg|PNG files (*.png)|*.png|All valid files (*.jpg/*.png)|*.jpg/*.png" ;
					saveImage->FilterIndex = 1 ;
					saveImage->RestoreDirectory = true ;

					System::Windows::Forms::DialogResult d = this->saveImage->ShowDialog();
						if (d == System::Windows::Forms::DialogResult::OK)				 
							{			 
							// creating a bitmap
							Bitmap* save;
							save=new Bitmap(this->pictureBox1->Image);
							save->Save(saveImage->FileName);
							
							}
				
				 
			}
	 
};
}


