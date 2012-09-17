
#pragma once
#include "rgbConvert.h"
//#include "Separate.h"
//#include "Convolution.h"
#include "Deskew.h"


namespace tryDeskew
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Drawing::Imaging;

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
			this->ContrastDone=false;
			this->meanDone=false;
			this->deskewDone=false;

			InitializeComponent();
			//this->openImageFile();
			//this->doDeskew();
			
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
	private: System::Windows::Forms::Button *  openImage;
	private: System::Windows::Forms::Button *  saveImage;

	private: System::Windows::Forms::PictureBox *  pictureBox1;
	private: System::Windows::Forms::Panel *  picture_panel;
	private: System::Windows::Forms::OpenFileDialog *  openImageDialog;
	private: Bitmap* im;
    private: Graphics* g;
	private: System::Windows::Forms::Button *  deSkew;
	private: bool **BArray;
			 bool **tmpBArray;
			 bool BinaryDone;
			 bool ImageLoaded;
			 bool SeparateDone;
			 bool ContrastDone;
			 bool meanDone;
			 bool deskewDone;
	private: System::Windows::Forms::TextBox *  fileTextBar;

	private: System::Windows::Forms::TextBox *  angleBar;
	private: System::Windows::Forms::Label *  angleLabel;
	public: System::Windows::Forms::RichTextBox *  myBar;
	private: System::Windows::Forms::SaveFileDialog *  saveImageDialog;
	private: System::Windows::Forms::Label *  label1;
	private: System::Windows::Forms::Label *  label2;




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
			this->openImage = new System::Windows::Forms::Button();
			this->saveImage = new System::Windows::Forms::Button();
			this->picture_panel = new System::Windows::Forms::Panel();
			this->pictureBox1 = new System::Windows::Forms::PictureBox();
			this->openImageDialog = new System::Windows::Forms::OpenFileDialog();
			this->deSkew = new System::Windows::Forms::Button();
			this->fileTextBar = new System::Windows::Forms::TextBox();
			this->angleBar = new System::Windows::Forms::TextBox();
			this->angleLabel = new System::Windows::Forms::Label();
			this->myBar = new System::Windows::Forms::RichTextBox();
			this->saveImageDialog = new System::Windows::Forms::SaveFileDialog();
			this->label1 = new System::Windows::Forms::Label();
			this->label2 = new System::Windows::Forms::Label();
			this->picture_panel->SuspendLayout();
			this->SuspendLayout();
			// 
			// openImage
			// 
			this->openImage->Location = System::Drawing::Point(144, 8);
			this->openImage->Name = S"openImage";
			this->openImage->Size = System::Drawing::Size(128, 32);
			this->openImage->TabIndex = 0;
			this->openImage->Text = S"open Image";
			this->openImage->Click += new System::EventHandler(this, openImage_Click);
			// 
			// saveImage
			// 
			this->saveImage->Location = System::Drawing::Point(312, 8);
			this->saveImage->Name = S"saveImage";
			this->saveImage->Size = System::Drawing::Size(104, 32);
			this->saveImage->TabIndex = 1;
			this->saveImage->Text = S"Save New Image As";
			this->saveImage->Click += new System::EventHandler(this, saveImage_Click);
			// 
			// picture_panel
			// 
			this->picture_panel->BackColor = System::Drawing::Color::AliceBlue;
			this->picture_panel->Controls->Add(this->pictureBox1);
			this->picture_panel->Location = System::Drawing::Point(8, 80);
			this->picture_panel->Name = S"picture_panel";
			this->picture_panel->Size = System::Drawing::Size(632, 480);
			this->picture_panel->TabIndex = 2;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(8, 8);
			this->pictureBox1->Name = S"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(152, 144);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 3;
			this->pictureBox1->TabStop = false;
			// 
			// deSkew
			// 
			this->deSkew->Location = System::Drawing::Point(24, 16);
			this->deSkew->Name = S"deSkew";
			this->deSkew->Size = System::Drawing::Size(88, 16);
			this->deSkew->TabIndex = 3;
			this->deSkew->Text = S"Deskew";
			this->deSkew->Click += new System::EventHandler(this, deSkew_Click);
			// 
			// fileTextBar
			// 
			this->fileTextBar->Location = System::Drawing::Point(520, 16);
			this->fileTextBar->Name = S"fileTextBar";
			this->fileTextBar->Size = System::Drawing::Size(328, 20);
			this->fileTextBar->TabIndex = 4;
			this->fileTextBar->Text = S" ";
			// 
			// angleBar
			// 
			this->angleBar->Location = System::Drawing::Point(520, 40);
			this->angleBar->Name = S"angleBar";
			this->angleBar->Size = System::Drawing::Size(112, 20);
			this->angleBar->TabIndex = 6;
			this->angleBar->Text = S"";
			// 
			// angleLabel
			// 
			this->angleLabel->Location = System::Drawing::Point(440, 40);
			this->angleLabel->Name = S"angleLabel";
			this->angleLabel->Size = System::Drawing::Size(80, 16);
			this->angleLabel->TabIndex = 7;
			this->angleLabel->Text = S"Deskew Angle";
			// 
			// myBar
			// 
			this->myBar->Location = System::Drawing::Point(664, 136);
			this->myBar->Name = S"myBar";
			this->myBar->Size = System::Drawing::Size(200, 280);
			this->myBar->TabIndex = 8;
			this->myBar->Text = S"";
			// 
			// label1
			// 
			this->label1->Location = System::Drawing::Point(456, 16);
			this->label1->Name = S"label1";
			this->label1->Size = System::Drawing::Size(56, 16);
			this->label1->TabIndex = 9;
			this->label1->Text = S"File Path";
			// 
			// label2
			// 
			this->label2->Location = System::Drawing::Point(664, 80);
			this->label2->Name = S"label2";
			this->label2->Size = System::Drawing::Size(200, 48);
			this->label2->TabIndex = 10;
			this->label2->Text = S"Action";
			// 
			// Form1
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(880, 566);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->myBar);
			this->Controls->Add(this->angleLabel);
			this->Controls->Add(this->angleBar);
			this->Controls->Add(this->fileTextBar);
			this->Controls->Add(this->deSkew);
			this->Controls->Add(this->picture_panel);
			this->Controls->Add(this->saveImage);
			this->Controls->Add(this->openImage);
			this->Name = S"Form1";
			this->Text = S"Deskew Portion";
			this->picture_panel->ResumeLayout(false);
			this->ResumeLayout(false);

		}	
	private: System::Void openImage_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 myBar->AppendText("\n opening file :\n         ");
				 this->openImageFile();
				 
			 }

			 private: void openImageFile(){
				 
						  System::Windows::Forms::DialogResult d = this->openImageDialog->ShowDialog();
						  if(d== System::Windows::Forms::DialogResult::OK){
							  //openImageDialog->FileName ="C:\\Documents\ and\ Settings\\Administrator\\Desktop\\OCR\\Daily\\Aug13\\Aug13\\Sample\ Images\\skewed\.jpg";
							  im = new Bitmap(this->openImageDialog->OpenFile());

							  this->pictureBox1->Image = im;
							  //openImageDialog->FileName ="C:\\Documents\ and\ Settings\\Administrator\\Desktop\\OCR\\Daily\\Aug13\\Aug13\\Sample\ Images\\skewed\.jpg";
							  //System::Windows::Forms::MessageBox::Show(openImageDialog->FileName ,"string");
							  fileTextBar->AppendText(openImageDialog->FileName);
							  //fileTextBar->Text=openImageDialog->FileName;
								  //AppendText(openImageDialog->FileName);
							  myBar->AppendText(openImageDialog->FileName);
							  myBar->AppendText("\n");
							  g = this->pictureBox1->CreateGraphics();
							  this->ImageLoaded=true;
							  angleBar->Text = "";
							  
						  }
						  this->Update();
				 
			 }
	 
/*
private: void openImageFile1(){
						
						  ///System::Windows::Forms::DialogResult d = this->openImageDialog->ShowDialog();
						 /// if(d== System::Windows::Forms::DialogResult::OK){
							  openImageDialog->FileName ="C:\\Documents\ and\ Settings\\Administrator\\Desktop\\OCR\\Daily\\Aug13\\Aug13\\Sample\ Images\\skewed\.jpg";
							  im = new Bitmap(this->openImageDialog->OpenFile());

							  this->pictureBox1->Image = im;
							  openImageDialog->FileName ="C:\\Documents\ and\ Settings\\Administrator\\Desktop\\OCR\\Daily\\Aug13\\Aug13\\Sample\ Images\\skewed\.jpg";
							  //System::Windows::Forms::MessageBox::Show(openImageDialog->FileName ,"string");
							  fileTextBar->AppendText(openImageDialog->FileName);
							  //fileTextBar->Text=openImageDialog->FileName;
								  //AppendText(openImageDialog->FileName);
							  g = this->pictureBox1->CreateGraphics();
							  this->ImageLoaded=true;
							  angleBar->Text = "";	
						///  }
						  this->Update();
				 
			 }
		 */
	private: System::Void deSkew_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 if(this->ImageLoaded){
					 this->doDeskew();
					 //System::Windows::Forms::MessageBox::Show("inside deskew","inside deskew");
					
				 }

				 else{
					 System::Windows::Forms::MessageBox::Show("Image not loaded, Please load the image first","Image not loaded");
				 }

			 }
		
			private: void doDeskew(){
						Deskew* ds=new Deskew(im);
						double skewAngle=ds->GetSkewAngle();
						

						/* do this after fixing everything

						if (skewAngle >= 45.0) skewAngle -= 90.0;
						else if (skewAngle <= -45.0) skewAngle += 90.0;
						
						*/
						//System::Windows::Forms::MessageBox::Show(skewAngle.ToString(),"Skew Angle");
						angleBar->Text = skewAngle.ToString();
						//rangleBar->AppendText(skewAngle.ToString());
						//fileTextBar->AppendText(skewAngle.ToString());
						if(skewAngle !=0){
						im=this->RotateImage(-skewAngle); 
						this->pictureBox1->Image = im;
						}

				  }
			
		private: Bitmap* RotateImage(double angle)
					{
						Graphics* gr;
						Bitmap* tmp=new Bitmap(2*im->Width,2*im->Height,PixelFormat::Format24bppRgb);
						tmp->SetResolution(im->HorizontalResolution,im->VerticalResolution);
						gr=Graphics::FromImage(tmp);
						gr->FillRectangle(Brushes::White,0,0,2*im->Width,2*im->Height);
						gr->RotateTransform(angle);
						gr->DrawImage(im,15,0);
						gr->Dispose();
						return tmp;
					}


		
private: System::Void saveImage_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 this->saveImageFile();
		 }
	private: void saveImageFile()
			{
					saveImageDialog->Filter= "PNG files (*.jpg)|*.jpg|PNG files (*.png)|*.png|All valid files (*.jpg/*.png)|*.jpg/*.png" ;
					saveImageDialog->FilterIndex = 1 ;
					saveImageDialog->RestoreDirectory = true ;

					System::Windows::Forms::DialogResult d = this->saveImageDialog->ShowDialog();
						if (d == System::Windows::Forms::DialogResult::OK)				 
							{			 
							// creating a bitmap
							Bitmap* save;
							save=new Bitmap(this->pictureBox1->Image);
							save->Save(saveImageDialog->FileName);
							
							}
				
				
				 
			}

};




}