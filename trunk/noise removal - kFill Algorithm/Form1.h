#include "ThresholedValue.h"
#include "rgbConvert.h"
//#include "whiteConvert.h"
//#include "invertImage.h"
//#include "invertImageSecond.h"
#include "removeNoise.h"
#pragma once


namespace binarizationTest
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
	private: System::Windows::Forms::Button *  button1;
	private: System::Windows::Forms::Panel *  panel1;
	private: System::Windows::Forms::PictureBox *  pictureBox1;
	private: System::Windows::Forms::OpenFileDialog *  openFileDialog1;

	Bitmap *im;
	private: Bitmap* BinaryImage;
	private: Bitmap* WhiteImage;
	private:Bitmap* InvertedImage;
	private:Bitmap* ClearImage;
	int x;
	int y;

	
	private: int **ImgArray; 
	private: bool **BArray; 

	private: int intLevel; //Threshold Value

	private: System::Windows::Forms::Label *  label1;
	private: System::Windows::Forms::Label *  label2;
	private: System::Windows::Forms::Button *  button2;










	private: System::Windows::Forms::Button *  button7;
	private: System::Windows::Forms::Button *  button3;
	private: System::Windows::Forms::SaveFileDialog *  saveImageDialog;


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
			this->button1 = new System::Windows::Forms::Button();
			this->panel1 = new System::Windows::Forms::Panel();
			this->pictureBox1 = new System::Windows::Forms::PictureBox();
			this->openFileDialog1 = new System::Windows::Forms::OpenFileDialog();
			this->label1 = new System::Windows::Forms::Label();
			this->label2 = new System::Windows::Forms::Label();
			this->button2 = new System::Windows::Forms::Button();
			this->button7 = new System::Windows::Forms::Button();
			this->button3 = new System::Windows::Forms::Button();
			this->saveImageDialog = new System::Windows::Forms::SaveFileDialog();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(16, 8);
			this->button1->Name = S"button1";
			this->button1->Size = System::Drawing::Size(80, 32);
			this->button1->TabIndex = 0;
			this->button1->Text = S"open";
			this->button1->Click += new System::EventHandler(this, button1_Click);
			// 
			// panel1
			// 
			this->panel1->AutoScroll = true;
			this->panel1->Controls->Add(this->pictureBox1);
			this->panel1->Location = System::Drawing::Point(8, 144);
			this->panel1->Name = S"panel1";
			this->panel1->Size = System::Drawing::Size(496, 152);
			this->panel1->TabIndex = 1;
			this->panel1->Paint += new System::Windows::Forms::PaintEventHandler(this, panel1_Paint);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(8, 8);
			this->pictureBox1->Name = S"pictureBox1";
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// label1
			// 
			this->label1->Location = System::Drawing::Point(200, 16);
			this->label1->Name = S"label1";
			this->label1->Size = System::Drawing::Size(136, 24);
			this->label1->TabIndex = 2;
			// 
			// label2
			// 
			this->label2->Location = System::Drawing::Point(344, 16);
			this->label2->Name = S"label2";
			this->label2->TabIndex = 3;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(104, 8);
			this->button2->Name = S"button2";
			this->button2->Size = System::Drawing::Size(72, 32);
			this->button2->TabIndex = 4;
			this->button2->Text = S"binarize";
			this->button2->Click += new System::EventHandler(this, button2_Click);
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(16, 56);
			this->button7->Name = S"button7";
			this->button7->Size = System::Drawing::Size(80, 32);
			this->button7->TabIndex = 14;
			this->button7->Text = S"remove noise";
			this->button7->Click += new System::EventHandler(this, button7_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(16, 104);
			this->button3->Name = S"button3";
			this->button3->Size = System::Drawing::Size(80, 23);
			this->button3->TabIndex = 15;
			this->button3->Text = S"save";
			this->button3->Click += new System::EventHandler(this, button3_Click);
			// 
			// Form1
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(512, 302);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->button1);
			this->Name = S"Form1";
			this->Text = S"Binarization Test";
			this->panel1->ResumeLayout(false);
			this->ResumeLayout(false);

		}	
	private: System::Void button1_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 this->grrFunctionToOpenImage();				 

			 }
			 void grrFunctionToOpenImage(){
				//opening function 
				 System::Windows::Forms::DialogResult d = this->openFileDialog1->ShowDialog();
				 if(d == System::Windows::Forms::DialogResult::OK){
					 

					im = new Bitmap(this->openFileDialog1->OpenFile());
					this->pictureBox1->Image = im;
					
				 }
			 }
			 void grrShortOpenFunction(){

				 System::Windows::Forms::DialogResult d = this->openFileDialog1->ShowDialog();
				 if(d == System::Windows::Forms::DialogResult::OK){
					
					 this->pictureBox1->Image = new Bitmap(this->openFileDialog1->OpenFile());
				 }
			 }
			 void b2Binarization(){

				  // calculating Thresholed Value for binary image	
				 ThresholedValue* ts = new ThresholedValue(im);
				 float fLevel = ts->GetThresholed();
				 intLevel = int(fLevel*255);
				 //Threshold value is intlevel
				 
				 this->label1->Text = "Threshold value";
				 this->label2->Text = intLevel.ToString();

				  // getting an binary array of image and store into BArray[][] = **BArray 					 
					rgbConvert* rgbC = new rgbConvert(im);
					
					BArray = rgbC->GetBinaryArray(intLevel);
					ImgArray = rgbC->GetImageArray( );

					// Showing the binary image
					 this->BinaryImage = rgbC->GetBinaryImage();
					 this->pictureBox1->Image = this->BinaryImage;

			 }
	private: System::Void button2_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 this->b2Binarization();
			 }



private: System::Void panel1_Paint(System::Object *  sender, System::Windows::Forms::PaintEventArgs *  e)
		 {
		 }



private: System::Void button7_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 this->makeClear();
		 }
		 void makeClear()
		 {
			 removeNoise* rN = new removeNoise( this ->BinaryImage, this->ImgArray);
			 this->ClearImage = rN->GetClearImage();
			 this->pictureBox1->Image = this->ClearImage;
		 }


private: System::Void button3_Click(System::Object *  sender, System::EventArgs *  e)
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
							Bitmap* save;
							save=new Bitmap(this->pictureBox1->Image);
							save->Save(saveImageDialog->FileName);
							
							}
							 
			}

};
}


