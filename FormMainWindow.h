	#include "TrainingForm.h"
#include "RecognitionForm.h"
#include "RecognitionProcess.h"
#include "ThresholedValue.h"
#include "rgbConvert.h"
#include "Separate.h"
#include "Convolution.h"
#include "Deskew.h"
#include "myWindow.h"


#pragma once


namespace OCR
{
	using namespace System;
	using namespace System::IO;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::ComponentModel;
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
	
/*
 
		The main Class of the program.
		This program initiates the start dialog box. This class control other classes and initiates them.
 
*/

	public __gc class Form1 : public System::Windows::Forms::Form
	{	
	public:
		Form1(void)
		{
			//user declarations
			this->BinaryDone=false;
			this->ImageLoaded=false;
			this->SeparateDone=false;
			this->ContrastDone=false;
			this->meanDone=false;
			this->deskewDone=false;

			InitializeComponent();

			this->applicationPath=Application::StartupPath->ToString();
			
			int len = this->applicationPath->Length -1;			
			if(this->applicationPath->Substring(len)->Equals("\\"))
			{
				this->applicationPath = this->applicationPath->Substring(0,len);				
			}

			// getting the character database path
			//System::Windows::Forms::MessageBox::Show(this->applicationPath,"Path of characterDB path");

//			this->characterDBPath=this->characterDBPath->Concat(this->applicationPath ,"\\htk\\DataBaseFile\\characters.txt");	
			//System::Windows::Forms::MessageBox::Show(this->characterDBPath,"Path of characterDB path");
			
			this->modelTrainDBPath = this->modelTrainDBPath->Concat(this->applicationPath , "\\htk\\DataBaseFile\\modelTrainDataBase.txt");
			
			this->alModelRec = new System::Collections::ArrayList();
			this->characterDBPath=this->characterDBPath->Concat(this->applicationPath ,"\\htk\\DataBaseFile\\characters.txt");	
			this->scriptFilePath = this->scriptFilePath->Concat(this->applicationPath ,"\\htk\\recognizer\\script.txt");

			this->LoadFromFile();
			
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



	//user variable start 
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
			 bool ContrastDone;
			 bool meanDone;
			 bool deskewDone;


	private: int numberOfLines;
	private: Line* Lines; 

	private: String* applicationPath;
			 String* modelTrainDBPath;
			 String* scriptFilePath;
			 String* characterDBPath;

	
	private: System::Collections::SortedList* slForCharacters;
	private: System::Collections::SortedList* slModelTranscription;	// for storing the model transcriptions
	private: System::Collections::ArrayList* alModelRec;			// for models that already recognized
	
			 
	
	//private: Graphics* g;	
//    private: BinaryImgProcessor* bim;
    //user variable end 
	
	private: System::Windows::Forms::Panel *  picture_panel;
	private: System::Windows::Forms::PictureBox *  pictureBox1;
	private: System::Windows::Forms::Button *  convertToBinary_button;
	private: System::Windows::Forms::Button *  openImage;
	private: System::Windows::Forms::OpenFileDialog *  openImageDialog;
	private: System::Windows::Forms::Button *  separate_button;
	private: System::Windows::Forms::SaveFileDialog *  saveImageDialog;
	private: System::Windows::Forms::Button *  saveImage;
	private: System::Windows::Forms::Button *  imContrast;
	private: System::Windows::Forms::Button *  meanRemoval;
	private: System::Windows::Forms::Button *  deSkew;
	private: System::Windows::Forms::Button *  train;
	private: System::Windows::Forms::Button *  recognize;
	private: System::Windows::Forms::Button *  fastRecognizeButton;
	private: System::Windows::Forms::Label *  myInfo;
	private: System::Windows::Forms::Label *  myInfo1;
	private: System::Windows::Forms::Button *  findMagnification;






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
			this->convertToBinary_button = new System::Windows::Forms::Button();
			this->picture_panel = new System::Windows::Forms::Panel();
			this->pictureBox1 = new System::Windows::Forms::PictureBox();
			this->openImage = new System::Windows::Forms::Button();
			this->openImageDialog = new System::Windows::Forms::OpenFileDialog();
			this->separate_button = new System::Windows::Forms::Button();
			this->saveImageDialog = new System::Windows::Forms::SaveFileDialog();
			this->saveImage = new System::Windows::Forms::Button();
			this->imContrast = new System::Windows::Forms::Button();
			this->meanRemoval = new System::Windows::Forms::Button();
			this->deSkew = new System::Windows::Forms::Button();
			this->train = new System::Windows::Forms::Button();
			this->recognize = new System::Windows::Forms::Button();
			this->fastRecognizeButton = new System::Windows::Forms::Button();
			this->myInfo = new System::Windows::Forms::Label();
			this->myInfo1 = new System::Windows::Forms::Label();
			this->findMagnification = new System::Windows::Forms::Button();
			this->picture_panel->SuspendLayout();
			this->SuspendLayout();
			// 
			// convertToBinary_button
			// 
			this->convertToBinary_button->Cursor = System::Windows::Forms::Cursors::Hand;
			this->convertToBinary_button->Location = System::Drawing::Point(232, 96);
			this->convertToBinary_button->Name = S"convertToBinary_button";
			this->convertToBinary_button->Size = System::Drawing::Size(72, 24);
			this->convertToBinary_button->TabIndex = 5;
			this->convertToBinary_button->Text = S"BINARY";
			this->convertToBinary_button->Click += new System::EventHandler(this, close_button_Click_1);
			// 
			// picture_panel
			// 
			this->picture_panel->AutoScroll = true;
			this->picture_panel->BackColor = System::Drawing::Color::AliceBlue;
			this->picture_panel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->picture_panel->Controls->Add(this->pictureBox1);
			this->picture_panel->Location = System::Drawing::Point(8, 128);
			this->picture_panel->Name = S"picture_panel";
			this->picture_panel->Size = System::Drawing::Size(776, 384);
			this->picture_panel->TabIndex = 1;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(5, 12);
			this->pictureBox1->Name = S"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(100, 100);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// openImage
			// 
			this->openImage->BackColor = System::Drawing::Color::Transparent;
			this->openImage->Cursor = System::Windows::Forms::Cursors::Hand;
			this->openImage->Location = System::Drawing::Point(32, 8);
			this->openImage->Name = S"openImage";
			this->openImage->Size = System::Drawing::Size(112, 48);
			this->openImage->TabIndex = 1;
			this->openImage->Text = S"OPEN IMAGE";
			this->openImage->Click += new System::EventHandler(this, openImage_Click);
			// 
			// openImageDialog
			// 
			this->openImageDialog->Filter = S"Image Files(*.BMP;*.JPG;*.GIF;*.png)|*.BMP;*.JPG;*.GIF;*.PNG|All files (*.*)|*.*";
			// 
			// separate_button
			// 
			this->separate_button->Cursor = System::Windows::Forms::Cursors::Hand;
			this->separate_button->Location = System::Drawing::Point(320, 96);
			this->separate_button->Name = S"separate_button";
			this->separate_button->TabIndex = 6;
			this->separate_button->Text = S"SEPARATE";
			this->separate_button->Click += new System::EventHandler(this, separate_button_Click);
			// 
			// saveImageDialog
			// 
			this->saveImageDialog->DefaultExt = S"*.jpg";
			// 
			// saveImage
			// 
			this->saveImage->BackColor = System::Drawing::Color::WhiteSmoke;
			this->saveImage->Cursor = System::Windows::Forms::Cursors::Hand;
			this->saveImage->Location = System::Drawing::Point(264, 8);
			this->saveImage->Name = S"saveImage";
			this->saveImage->Size = System::Drawing::Size(112, 48);
			this->saveImage->TabIndex = 2;
			this->saveImage->Text = S"SAVE IMAGE";
			this->saveImage->Click += new System::EventHandler(this, saveImage_Click);
			// 
			// imContrast
			// 
			this->imContrast->BackColor = System::Drawing::Color::Transparent;
			this->imContrast->Cursor = System::Windows::Forms::Cursors::Hand;
			this->imContrast->Location = System::Drawing::Point(64, 96);
			this->imContrast->Name = S"imContrast";
			this->imContrast->TabIndex = 3;
			this->imContrast->Text = S"CONTRAST";
			this->imContrast->Click += new System::EventHandler(this, imContrast_Click);
			// 
			// meanRemoval
			// 
			this->meanRemoval->Cursor = System::Windows::Forms::Cursors::Hand;
			this->meanRemoval->Location = System::Drawing::Point(144, 96);
			this->meanRemoval->Name = S"meanRemoval";
			this->meanRemoval->TabIndex = 4;
			this->meanRemoval->Text = S"MEAN";
			this->meanRemoval->Click += new System::EventHandler(this, meanRemoval_Click);
			// 
			// deSkew
			// 
			this->deSkew->Cursor = System::Windows::Forms::Cursors::Hand;
			this->deSkew->Location = System::Drawing::Point(8, 72);
			this->deSkew->Name = S"deSkew";
			this->deSkew->TabIndex = 7;
			this->deSkew->Text = S"DE-SKEW";
			this->deSkew->Click += new System::EventHandler(this, deSkew_Click);
			// 
			// train
			// 
			this->train->Cursor = System::Windows::Forms::Cursors::Hand;
			this->train->Location = System::Drawing::Point(600, 88);
			this->train->Name = S"train";
			this->train->TabIndex = 8;
			this->train->Text = S"TRAIN";
			this->train->Click += new System::EventHandler(this, train_Click);
			// 
			// recognize
			// 
			this->recognize->Cursor = System::Windows::Forms::Cursors::Hand;
			this->recognize->Location = System::Drawing::Point(688, 88);
			this->recognize->Name = S"recognize";
			this->recognize->Size = System::Drawing::Size(88, 23);
			this->recognize->TabIndex = 9;
			this->recognize->Text = S"RECOGNIZE";
			this->recognize->Click += new System::EventHandler(this, recognize_Click);
			// 
			// fastRecognizeButton
			// 
			this->fastRecognizeButton->Location = System::Drawing::Point(160, 8);
			this->fastRecognizeButton->Name = S"fastRecognizeButton";
			this->fastRecognizeButton->Size = System::Drawing::Size(88, 48);
			this->fastRecognizeButton->TabIndex = 10;
			this->fastRecognizeButton->Text = S"Fast Recognize";
			this->fastRecognizeButton->Click += new System::EventHandler(this, fastRecognizeButton_Click);
			// 
			// myInfo
			// 
			this->myInfo->Location = System::Drawing::Point(520, 16);
			this->myInfo->Name = S"myInfo";
			this->myInfo->Size = System::Drawing::Size(264, 24);
			this->myInfo->TabIndex = 11;
			// 
			// myInfo1
			// 
			this->myInfo1->Location = System::Drawing::Point(440, 16);
			this->myInfo1->Name = S"myInfo1";
			this->myInfo1->Size = System::Drawing::Size(72, 24);
			this->myInfo1->TabIndex = 12;
			// 
			// findMagnification
			// 
			this->findMagnification->Location = System::Drawing::Point(392, 64);
			this->findMagnification->Name = S"findMagnification";
			this->findMagnification->Size = System::Drawing::Size(88, 24);
			this->findMagnification->TabIndex = 13;
			this->findMagnification->Text = S"Magnification";
			this->findMagnification->Click += new System::EventHandler(this, findMagnification_Click);
			// 
			// Form1
			// 
			this->AccessibleRole = System::Windows::Forms::AccessibleRole::Application;
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->AutoScroll = true;
			this->BackColor = System::Drawing::Color::WhiteSmoke;
			this->ClientSize = System::Drawing::Size(794, 518);
			this->Controls->Add(this->findMagnification);
			this->Controls->Add(this->myInfo1);
			this->Controls->Add(this->myInfo);
			this->Controls->Add(this->fastRecognizeButton);
			this->Controls->Add(this->recognize);
			this->Controls->Add(this->train);
			this->Controls->Add(this->meanRemoval);
			this->Controls->Add(this->imContrast);
			this->Controls->Add(this->saveImage);
			this->Controls->Add(this->separate_button);
			this->Controls->Add(this->openImage);
			this->Controls->Add(this->picture_panel);
			this->Controls->Add(this->convertToBinary_button);
			this->Controls->Add(this->deSkew);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->MaximizeBox = false;
			this->Name = S"Form1";
			this->Text = S" Image Processing Part Of Nepali OCR";
			this->picture_panel->ResumeLayout(false);
			this->ResumeLayout(false);

		}	


		
		/*

			The InitializeComponent method initializes the application. 

			

		*/

		public: void Conv3x3(ConvMatrix* m)
		{
			this->Cursor = System::Windows::Forms::Cursors::WaitCursor;
			
			try{
			// Avoid divide by zero errors
			if (0 == m->Factor) return;

			Bitmap* bSrc = (Bitmap*)im->Clone(); 

			// GDI+ still lies to us - the return format is BGR, NOT RGB.
			BitmapData* bmData = im->LockBits(Rectangle(0, 0, im->Width, im->Height), ImageLockMode::ReadWrite, PixelFormat::Format24bppRgb);
			BitmapData* bmSrc = bSrc->LockBits(Rectangle(0, 0, bSrc->Width, bSrc->Height), ImageLockMode::ReadWrite, PixelFormat::Format24bppRgb);

			int stride = bmData->Stride;
			int stride2 = stride * 2;
			IntPtr Scan0 = bmData->Scan0;
			IntPtr SrcScan0 = bmSrc->Scan0;

				Byte * p = (Byte *)(void *)Scan0;
				Byte * pSrc = (Byte *)(void *)SrcScan0;

				int nOffset = stride - im->Width*3;
				int nWidth = im->Width - 2;
				int nHeight = im->Height - 2;

				int nPixel;

				for(int y=0;y < nHeight;++y)
				{
					for(int x=0; x < nWidth; ++x )
					{
						nPixel = ( ( ( (pSrc[2] * m->TopLeft) + (pSrc[5] * m->TopMid) + (pSrc[8] * m->TopRight) +
							(pSrc[2 + stride] * m->MidLeft) + (pSrc[5 + stride] * m->Pixel) + (pSrc[8 + stride] * m->MidRight) +
							(pSrc[2 + stride2] * m->BottomLeft) + (pSrc[5 + stride2] * m->BottomMid) + (pSrc[8 + stride2] * m->BottomRight)) / m->Factor) + m->Offset); 

						if (nPixel < 0) nPixel = 0;
						if (nPixel > 255) nPixel = 255;

						p[5 + stride]= (Byte)nPixel;

						nPixel = ( ( ( (pSrc[1] * m->TopLeft) + (pSrc[4] * m->TopMid) + (pSrc[7] * m->TopRight) +
							(pSrc[1 + stride] * m->MidLeft) + (pSrc[4 + stride] * m->Pixel) + (pSrc[7 + stride] * m->MidRight) +
							(pSrc[1 + stride2] * m->BottomLeft) + (pSrc[4 + stride2] * m->BottomMid) + (pSrc[7 + stride2] * m->BottomRight)) / m->Factor) + m->Offset); 

						if (nPixel < 0) nPixel = 0;
						if (nPixel > 255) nPixel = 255;
							
						p[4 + stride] = (Byte)nPixel;

						nPixel = ( ( ( (pSrc[0] * m->TopLeft) + (pSrc[3] * m->TopMid) + (pSrc[6] * m->TopRight) +
							(pSrc[0 + stride] * m->MidLeft) + (pSrc[3 + stride] * m->Pixel) + (pSrc[6 + stride] * m->MidRight) +
							(pSrc[0 + stride2] * m->BottomLeft) + (pSrc[3 + stride2] * m->BottomMid) + (pSrc[6 + stride2] * m->BottomRight)) / m->Factor) + m->Offset); 

						if (nPixel < 0) nPixel = 0;
						if (nPixel > 255) nPixel = 255;

						p[3 + stride] = (Byte)nPixel;

						p += 3;
						pSrc += 3;
					}
					p += nOffset;
					pSrc += nOffset;
				}
			
			im->UnlockBits(bmData);
			bSrc->UnlockBits(bmSrc);

			this->pictureBox1->Image = im;
			g=this->pictureBox1->CreateGraphics();
			//System::Windows::Forms::MessageBox::Show("Mean Removal Done!!!!"/*fLevel.ToString()*/,"Threshold Value");
			}
		catch(Exception* ex)
			{
				System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"Failed to Apply Mean Removal!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
			}
		this->Cursor = System::Windows::Forms::Cursors::Default;
			
		}
		
		private: void MeanRemoval(int nWeight)
		{
			
			/*

				This method does the mean removal of the image, before it is binarized. 
				Yhis is an essentinal part of the Image Preprocessing part. 

			*/

			ConvMatrix* m=new ConvMatrix();
			//ConvMatrix* h1[];
			//h1=new ConvMatrix* [20];
			//h1=this->GetTopValR();
			
			m->SetAll(-1);
			m->Pixel=nWeight;
			m->Factor=nWeight-8;
			this->Conv3x3(m);
		}

		/*private: ConvMatrix* GetTopValR()[]
				 {
					ConvMatrix* h1[];
					h1=new ConvMatrix* [20];
			
					return h1;
				 }
		 */
		private: void Contrast(int nContrast)
		{

			/*

				This method increases the contrast of the image. 
				Thus making the image more visible. 

			*/
			this->Cursor = System::Windows::Forms::Cursors::WaitCursor;
			try{
			double pixel = 0, contrast = (100.0+nContrast)/100.0;

			contrast *= contrast;

			int red, green, blue;
			
			// GDI+ still lies to us - the return format is BGR, NOT RGB.
			BitmapData* bmData = im->LockBits(Rectangle(0, 0, im->Width, im->Height), ImageLockMode::ReadWrite, PixelFormat::Format24bppRgb);
			int stride = bmData->Stride;
			IntPtr Scan0 = bmData->Scan0;
			
			//System::Byte p;
			Byte* p = (Byte*)(void *)Scan0;
			
			
				//Color clr = b->GetPixel(i,j);
				//int p= clr.ToArgb();				
			
				int nOffset = stride - im->Width*3;

				for(int y=0;y<im->Height;++y)
				{
					for(int x=0; x < im->Width; ++x )
					{
						blue = p[0];
						green = p[1];
						red = p[2];
				
						pixel = red/255.0;
						pixel -= 0.5;
						pixel *= contrast;
						pixel += 0.5;
						pixel *= 255;
						if (pixel < 0) pixel = 0;
						if (pixel > 255) pixel = 255;
						p[2] = (Byte) pixel;

						pixel = green/255.0;
						pixel -= 0.5;
						pixel *= contrast;
						pixel += 0.5;
						pixel *= 255;
						if (pixel < 0) pixel = 0;
						if (pixel > 255) pixel = 255;
						p[1] = (Byte) pixel;

						pixel = blue/255.0;
						pixel -= 0.5;
						pixel *= contrast;
						pixel += 0.5;
						pixel *= 255;
						if (pixel < 0) pixel = 0;
						if (pixel > 255) pixel = 255;
						p[0] = (Byte) pixel;					

						p += 3;
					}
					p += nOffset;
				}
			

			im->UnlockBits(bmData);
			
			this->pictureBox1->Image = im;
			g=this->pictureBox1->CreateGraphics();
			//System::Windows::Forms::MessageBox::Show("Contrast Done!!!!"/*fLevel.ToString()*/,"Threshold Value");
			}
		catch(Exception* ex)
			{
				System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"Failed to Improve the Contrast!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
			}
		this->Cursor = System::Windows::Forms::Cursors::Default;
	

//			return true;
		}
		private: void makeBinary()
			 {
				/*

				This method binarizes the image. 
				The binarized image is used during the recognition process and training process.
 
				*/

				 if(this->ImageLoaded)
				 {
					//if (this->BinaryDone)
					//	return;
				 
					
					
					try{
					 // set the cursor to wait.... 
						this->Cursor = System::Windows::Forms::Cursors::WaitCursor;

					 
					 // calculating Thresholed Value for binary image					 
						ThresholedValue* ts = new ThresholedValue(im);
						float fLevel = ts->GetThresholed();
						intLevel = int(fLevel*255);
					
					 
					 
					 // getting an binary array of 					 
						rgbConvert* rgbC = new rgbConvert(im);
						BArray = rgbC->GetBinaryArray(200);
						ImgArray = rgbC->GetImageArray( );
					   	
					 // Showing the binary image
						this->BinaryImage = rgbC->GetBinaryImage();
						this->pictureBox1->Image = this->BinaryImage;
						
					 // set the cursor to Default.... 
						this->Cursor = System::Windows::Forms::Cursors::Default;
						//System::Windows::Forms::MessageBox::Show(this->intLevel.ToString()/*fLevel.ToString()*/,"Threshold Value");
						myInfo1->Text = "Threshold Value";
						myInfo->Text = this->intLevel.ToString();
						this->BinaryDone=true;
					}
				 catch(System::Exception* ex)
					{
					System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"Failed to Binarize the Image!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
					this->Update();
					}
				 this->Update();
				 }
	}// end of function 


		private: void openImageFile()
			{
				System::Windows::Forms::DialogResult d = this->openImageDialog->ShowDialog();
				if (d == System::Windows::Forms::DialogResult::OK)				 
				 {			 
					

					//reset all flags after successfull image loading
					this->ImageLoaded = true;
					
					this->BinaryDone=false;
					this->SeparateDone=false;
					this->ContrastDone=false;
					this->meanDone=false;
					this->deskewDone=false;
					// creating a bitmap
					im = new Bitmap(this->openImageDialog->OpenFile());
					this->pictureBox1->Image = im;
					g=this->pictureBox1->CreateGraphics();
					myInfo->Text="";
					myInfo1->Text="";
					
					
					//System::Windows::Forms::MessageBox::Show("Image successfully loaded","Success");
				 }
				this->Update();
				 
			}
		private: void saveImageFile()
			{

			/*

			This method is used to save the image file after certain image processing portion is complete.
			In case we need the file in future.

			*/


				if(this->BinaryDone)
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
				else{
					System::Windows::Forms::MessageBox::Show("The file was not saved because \n the image processing is not completed", "Action Incomplete");
					
				}
				 
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

														g->DrawLine(p,x1,y1,x1,y2);
														g->DrawLine(p,x2,y1,x2,y2);
													}
											}
									}

				 }
		private: void separate()
				 {

				/*
				This method is used to separate the words and lines after binarization.
				*/

					 this->tmpBArray=new bool*[im->Height];
					 //System::Windows::Forms::MessageBox::Show(im->Height.ToString(),"Height");
					 myInfo1->Text = "Image Height";
					 myInfo->Text = im->Height.ToString();
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



		private: void doDeSkew()
				  {
				/*
				If the lines in the image is tilted or slanted, this method is used to deskew the image. 
				*/		 
				 
					Deskew* ds=new Deskew(im);
					double skewAngle=ds->GetSkewAngle();
					
					myInfo1->Text = "Skew Angle:";
					myInfo->Text = skewAngle.ToString();

					

   				    //System::Windows::Forms::MessageBox::Show(skewAngle.ToString(),"Skew Angle");

					if(skewAngle !=0){
						im=this->RotateImage(-skewAngle); 
						this->pictureBox1->Image = im;
						}
					//System::Windows::Forms::MessageBox::Show(" Image rotated successfully","Action Complete");

				 
					
					
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
		
		
		private: void Recognize()
		{
/*
		This method is used to recognize the text in the image.
*/	 
						RecognitionProcess* rp = new RecognitionProcess(this->applicationPath,this->ImgArray);

						// load the transcription of the models
						this->slModelTranscription = rp->LoadModelTranscriptions(this->modelTrainDBPath);
						 
						int lineCount = this->numberOfLines;
						int wordCount = 0;
						int totalUnit = 0;
						int unitCount = 0;
						int left_x,right_x,top_y,bottom_y;
						System::String* wordToRec;
						System::String* dirOfRecFile = rp->recognitionTempFileDir;

						for(int i=0; i<lineCount;i++)
						{				 
							top_y = this->Lines[i].getStartRow();//line start
							bottom_y = this->Lines[i].getEndRow();//line end

							wordCount = this->Lines[i].getTotalWord();
							for(int j=0;j<wordCount;j++)
							{					 
								unitCount = this->Lines[i].Words[j].getTotalUnit();					 
								for(int k=0; k<unitCount; k++)
								{
									left_x = this->Lines[i].Words[j].Units[k].getStartColumn();//wrod start
									right_x = this->Lines[i].Words[j].Units[k].getEndColumn();//word end

									// setting the actual image boundary
									rp->SetImageBoundary(left_x,right_x,top_y,bottom_y);
									totalUnit++;
									wordToRec = wordToRec->Concat(dirOfRecFile,totalUnit.ToString(),".txt");	
									rp->PrepareWordData(wordToRec);
								} 
							}//wordcount
						}
						  
						// preparing the script file to be recognized
						try
						{
							System::IO::StreamWriter* sw = System::IO::File::AppendText(rp->scriptFilePath);	
							for(int i=1;i<=totalUnit;i++)	
							{
								System::String* tmp=tmp->Concat((String*)"\"",dirOfRecFile,i.ToString(),(String*)".txt",(String*)"\"");
								sw->WriteLine(tmp);
								sw->Flush();
								//sw->WriteLine("\"" + dirOfRecFile+i + ".txt" + "\"");
							}
							sw->Close();
						}
						catch(System::Exception* ex)
						{
							System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"Failed to prepare the script file!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
							exit(0);
						}

						// recognize the words from the features file using the Viterbi decoder of the HTK Toolkit HVite
						// then read the Master Labeled File(MLF) and fetch the output models
						this->alModelRec = rp->RecognizeByHTK();
						
						 

						 
						this->ProvideOutput();

						/* after recognizing is done remove the script file and also the associated image features files */
						// remove the script file
						 
						System::IO::File::Delete(rp->scriptFilePath);

						// remove all the temporary word image feature files
						for(int i=1;i<=totalUnit;i++)	
						{
							System::String* tmp=tmp->Concat(dirOfRecFile,i.ToString(),".txt");
							//System::IO::File::Delete(dirOfRecFile+i+".txt");
							System::IO::File::Delete(tmp);
						}

		}


		private: void LoadFromFile()
		 {
			System::IO::StreamReader* sr = System::IO::StreamReader::Null;
			System::String* tempStr;
			System::String* charStr;
			System::String* unicodeStr;
			int index;

			try
			{
				this->slForCharacters = new System::Collections::SortedList();
				// read the characters and store
				sr = new System::IO::StreamReader(this->characterDBPath);
				tempStr = sr->ReadLine();
				while (tempStr->Length!=0)
				{
					index = tempStr->IndexOf(" ");
					charStr = tempStr->Substring(0,index);
					unicodeStr = tempStr->Substring(index+1);
					slForCharacters->Add(charStr,unicodeStr);
					tempStr = sr->ReadLine();
				}
				sr->Close();
			}
			catch(System::Exception* ex)
			{
				System::String* errorString1="";
				errorString1 = ex->Message->ToString();
				errorString1 = errorString1->Concat("Database file access error \n\nThe system generated the following error:\n",errorString1);
				System::Windows::Forms::MessageBox::Show( errorString1,"Error");
				
				exit(0);
			}
		 }

		private: void ProvideOutput()
		 {
/*
		This method prints the output in a new dialog box.
 */
			 
		    System::String* tempStr = "";
			System::String* text = "";
			System::Collections::ArrayList* tempAl;	// temporary working array list
			System::String* ucodeStr;	

			try
			{	
				int index = 0;
				int ind = 0;
				for (int i = 0; i < this->numberOfLines; i++  )
				{
					for (int j = 0; j < this->Lines[i].getTotalWord(); j++)
					{
						for (int k = 0; k < this->Lines[i].Words[j].getTotalUnit(); k++)
						{
							if ( ind < this->alModelRec->Count)
							{
								ucodeStr = "";
									
							System::Collections::IEnumerator* ENum;
							ENum=this->alModelRec->GetEnumerator();
							System::String* tempStr="";
							int tempCount=0;
               				while(ENum->MoveNext())
								{
									if(ind==tempCount)
									{
									tempStr=ENum->Current->ToString();
									break;
									}
									tempCount++;
									
								}
								 

								index = this->slModelTranscription->IndexOfKey(tempStr);
								ind++;
								tempAl = (System::Collections::ArrayList*)slModelTranscription->GetByIndex(index);
								System::Collections::IEnumerator* tempNum=tempAl->GetEnumerator();
								while(tempNum->MoveNext())
								{
									tempStr = (String*)tempNum->Current;
									ucodeStr = ucodeStr->Concat(ucodeStr,slForCharacters->GetKey(slForCharacters->IndexOfValue(tempStr)));
								}
												
								text = text->Concat(text,ucodeStr);
							}// end if
						}
						text = text->Concat(text,(String*)" ");						
					}
					text = text->Concat(text,(String*)"\n");
				}
			}
			catch(System::Exception* ex)
			{
				System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"Failed to provide the output!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
				exit(0);
			}
		 
			OCR::RecognitionForm* rw=new OCR::RecognitionForm();
			rw->showText(text);
			rw->ShowDialog();

		 }

private: System::Void close_button_Click_1(System::Object *  sender, System::EventArgs *  e)
			 {
				//this->Dispose(true);
				this->makeBinary();
			
					
			 }


private: System::Void openImage_Click(System::Object *  sender, System::EventArgs *  e)
			{
				this->openImageFile();
				
				
			}

private: System::Void separate_button_Click(System::Object *  sender, System::EventArgs *  e)
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

private: System::Void saveImage_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 this->saveImageFile();
		 }

private: System::Void imContrast_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			if(this->ImageLoaded==true){
			this->Contrast(10);
			this->ContrastDone=true;
			this->Update();
			 }
			 else{
				 System::Windows::Forms::MessageBox::Show("Please load the image first","Image not loaded");
			 }
		 }

private: System::Void meanRemoval_Click(System::Object *  sender, System::EventArgs *  e)
		 {

			 if( (this->ImageLoaded==true) && (this->ContrastDone==true) ){
				this->MeanRemoval(9);
				this->meanDone= true;
				this->Update();
				
			 }
			 else if( (this->ImageLoaded==true) && (this->ContrastDone==false ) ){
				 System::Windows::Forms::MessageBox::Show("Please set the contrast first","Contrast not done");
			 }
			 else if( this->ImageLoaded==false){
				 System::Windows::Forms::MessageBox::Show("Please Load the image first","Image not loaded");
			 }

		 }

private: System::Void deSkew_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 if(this->ImageLoaded==true){
			 this->doDeSkew();
			 }
			 else{
				 System::Windows::Forms::MessageBox::Show("Please Load the image first","Image not loaded");
			 }
		 }

private: System::Void train_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 if(this->ImageLoaded){

			 OCR::TrainingForm* tw=new OCR::TrainingForm();
			 tw->defineVar(this->ImgArray,this->tmpBArray,this->Lines,this->numberOfLines);
			 tw->ShowDialog();

				}
			 else{
				 System::Windows::Forms::MessageBox::Show("Image not loaded, Please load image first ","Image Not loaded");
			 }
			 
			
		 }

private: System::Void recognize_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 if(this->ImageLoaded){
				 if(this->SeparateDone){
					 //if the image is loaded and words are separated.. recognition process is started
						this->Recognize();

				 }
				 else{
					 System::Windows::Forms::MessageBox::Show("First Complete the preprocessing steps, words are not separated","Preprocessing steps not complete");
				 }
			 }
			 else{
				 //Image is not loaded
				 System::Windows::Forms::MessageBox::Show("Image not loaded, Please load the image first","Image not loaded");
			 }
			 //OCR::RecognitionForm* rw=new OCR::RecognitionForm();
			 //rw->ShowDialog();
		 }

private: System::Void fastRecognizeButton_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 if(this->ImageLoaded==true){
				 
				//contrast
				this->Contrast(10);
				this->ContrastDone=true;
				this->Update();
				
				//mean removal
				this->MeanRemoval(9);
				this->meanDone= true;
				this->Update();

				//Binarization
				this->makeBinary();
				
				//separation
				this->separate();

				//Recognition
				 this->Recognize();


			 }
			 else{
				 System::Windows::Forms::MessageBox::Show("Please load the image first","Image not loaded");

			 }

		 }//End function recognize button
//Try magnify function
		 
private: void tryMagnify(){
			  
				this->Contrast(10);
				this->ContrastDone=true;
				this->Update();
				
				//mean removal
				this->MeanRemoval(9);
				this->meanDone= true;
				this->Update();

				//Binarization
				this->makeBinary();
				
				//separation
				this->separate();
				

					OCR::myWindow* mw = new OCR::myWindow(this->im,
					this->BinaryImage,
						this->g,
						this->intLevel,
						this->ImgArray,
						this->BArray,
						this->tmpBArray,
						this->BinaryDone,
						this->ImageLoaded,
						this->SeparateDone,
						this->ContrastDone,
						this->meanDone,
						this->deskewDone,
						this->numberOfLines,
						this->Lines, 
						this->applicationPath,
						this->modelTrainDBPath,
						this->scriptFilePath,
						this->characterDBPath,
						this->slForCharacters,
						this->slModelTranscription,	// for storing the model transcriptions
						this->alModelRec
						);
				
				 
				mw->defineVar(this->ImgArray,this->tmpBArray,this->Lines,this->numberOfLines);
				mw->ShowDialog();
			 	  }

private: System::Void findMagnification_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 if(this->ImageLoaded){ 
			tryMagnify();		
			 }
			 else{
				 System::Windows::Forms::MessageBox::Show("Please load the image first","Image not loaded");
			 }

		 }

};




}


