
/**
 *   OCR
 *
 *
 * Requirements:
 *  
 * win2k or later
 * .NET FrameWork 1.1 or later 
 *
 * Version 1.0
 * first version
 *
 * Date 07-01-2008
 *
 * Author Rajesh Pandey
 *
 * license
 * This code is absolutely free to use and modify. The code is provided "as is" with
 * no expressed or implied warranty. The author accepts no liability if it causes
 * any damage to your computer, causes your pet to fall ill, increases baldness
 * or makes your car start emitting strange noises when you start it up.
 * This code has no bugs, just undocumented features!
 * 
 *  
 *
 *  
 *
 */
#include "croper.h"
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
	/// Summary for FormMainWindow
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

	public __gc class FormMainWindow : public System::Windows::Forms::Form
	{	
	public:
		FormMainWindow(void)
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


	private: System::Windows::Forms::OpenFileDialog *  openImageDialog;

	private: System::Windows::Forms::SaveFileDialog *  saveImageDialog;







	private: System::Windows::Forms::Label *  myInfo;
	private: System::Windows::Forms::Label *  myInfo1;




private: System::Windows::Forms::MainMenu *  ocrMenu;
private: System::Windows::Forms::MenuItem *  menuItem1;
private: System::Windows::Forms::MenuItem *  mnuLoadImage;
private: System::Windows::Forms::MenuItem *  mnuFastRecognize;
private: System::Windows::Forms::MenuItem *  mnuOCR;
private: System::Windows::Forms::MenuItem *  mnuBinarize;
private: System::Windows::Forms::MenuItem *  mnuSeparate;
private: System::Windows::Forms::MenuItem *  mnuRecognize;
private: System::Windows::Forms::MenuItem *  mnuAdvanced;
private: System::Windows::Forms::MenuItem *  mnuTrain;
private: System::Windows::Forms::MenuItem *  menuItem2;


private: System::Windows::Forms::MenuItem *  mnuSaveImage;
private: System::Windows::Forms::MenuItem *  mnuDeskew;
private: System::Windows::Forms::MenuItem *  menuItem3;


private: System::Windows::Forms::Splitter *  splitter1;
private: System::Windows::Forms::MenuItem *  mnuContrastAndBinarize;
private: System::Windows::Forms::MenuItem *  mnuContrast;
private: System::Windows::Forms::MenuItem *  mnuMeanRemoval;
private: System::Windows::Forms::MenuItem *  mnuMagnification;
private: System::Windows::Forms::MenuItem *  mnuRotate;
private: System::Windows::Forms::MenuItem *  mnuRecognize2;
private: System::Windows::Forms::MenuItem *  mnuCropper;
private: System::Windows::Forms::StatusBar *  statusBar1;
private: System::Windows::Forms::MenuItem *  mnuFastRecognize2;
private: System::Windows::Forms::MenuItem *  menuItem5;
private: System::Windows::Forms::ContextMenu *  ocrCntMenu;
private: System::Windows::Forms::MenuItem *  cMenuLoadImage;
private: System::Windows::Forms::MenuItem *  cMenuFastRecognize;
private: System::Windows::Forms::ProgressBar *  pbOCR; 
private: System::Windows::Forms::MenuItem *  cropperEnabler; 

private: int pointX1,pointX2,pointY1,pointY2; //for capturing the points






















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
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(OCR::FormMainWindow));
			this->picture_panel = new System::Windows::Forms::Panel();
			this->statusBar1 = new System::Windows::Forms::StatusBar();
			this->pictureBox1 = new System::Windows::Forms::PictureBox();
			this->openImageDialog = new System::Windows::Forms::OpenFileDialog();
			this->saveImageDialog = new System::Windows::Forms::SaveFileDialog();
			this->myInfo = new System::Windows::Forms::Label();
			this->myInfo1 = new System::Windows::Forms::Label();
			this->ocrMenu = new System::Windows::Forms::MainMenu();
			this->menuItem1 = new System::Windows::Forms::MenuItem();
			this->mnuLoadImage = new System::Windows::Forms::MenuItem();
			this->mnuFastRecognize = new System::Windows::Forms::MenuItem();
			this->mnuMagnification = new System::Windows::Forms::MenuItem();
			this->mnuOCR = new System::Windows::Forms::MenuItem();
			this->mnuFastRecognize2 = new System::Windows::Forms::MenuItem();
			this->menuItem5 = new System::Windows::Forms::MenuItem();
			this->mnuBinarize = new System::Windows::Forms::MenuItem();
			this->mnuSeparate = new System::Windows::Forms::MenuItem();
			this->mnuRecognize = new System::Windows::Forms::MenuItem();
			this->menuItem3 = new System::Windows::Forms::MenuItem();
			this->mnuContrastAndBinarize = new System::Windows::Forms::MenuItem();
			this->mnuContrast = new System::Windows::Forms::MenuItem();
			this->mnuMeanRemoval = new System::Windows::Forms::MenuItem();
			this->mnuAdvanced = new System::Windows::Forms::MenuItem();
			this->mnuTrain = new System::Windows::Forms::MenuItem();
			this->mnuRecognize2 = new System::Windows::Forms::MenuItem();
			this->menuItem2 = new System::Windows::Forms::MenuItem();
			this->mnuSaveImage = new System::Windows::Forms::MenuItem();
			this->mnuDeskew = new System::Windows::Forms::MenuItem();
			this->mnuRotate = new System::Windows::Forms::MenuItem();
			this->mnuCropper = new System::Windows::Forms::MenuItem();
			this->cropperEnabler = new System::Windows::Forms::MenuItem();
			this->splitter1 = new System::Windows::Forms::Splitter();
			this->ocrCntMenu = new System::Windows::Forms::ContextMenu();
			this->cMenuLoadImage = new System::Windows::Forms::MenuItem();
			this->cMenuFastRecognize = new System::Windows::Forms::MenuItem();
			this->pbOCR = new System::Windows::Forms::ProgressBar();
			this->picture_panel->SuspendLayout();
			this->SuspendLayout();
			// 
			// picture_panel
			// 
			this->picture_panel->AllowDrop = true;
			this->picture_panel->AutoScroll = true;
			this->picture_panel->BackColor = System::Drawing::Color::White;
			this->picture_panel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->picture_panel->Controls->Add(this->statusBar1);
			this->picture_panel->Controls->Add(this->pictureBox1);
			this->picture_panel->Location = System::Drawing::Point(8, 32);
			this->picture_panel->Name = S"picture_panel";
			this->picture_panel->Size = System::Drawing::Size(728, 360);
			this->picture_panel->TabIndex = 1;
			this->picture_panel->Click += new System::EventHandler(this, picture_panel_Click);
			this->picture_panel->DragEnter += new System::Windows::Forms::DragEventHandler(this, picture_panel_DragEnter);
			this->picture_panel->MouseUp += new System::Windows::Forms::MouseEventHandler(this, picture_panel_MouseUp);
			this->picture_panel->DragDrop += new System::Windows::Forms::DragEventHandler(this, picture_panel_DragDrop);
			// 
			// statusBar1
			// 
			this->statusBar1->Location = System::Drawing::Point(0, 340);
			this->statusBar1->Name = S"statusBar1";
			this->statusBar1->Size = System::Drawing::Size(724, 16);
			this->statusBar1->TabIndex = 1;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(5, 12);
			this->pictureBox1->Name = S"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(100, 100);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Paint += new System::Windows::Forms::PaintEventHandler(this, pictureBox1_Paint);
			this->pictureBox1->MouseUp += new System::Windows::Forms::MouseEventHandler(this, pictureBox1_MouseUp);
			this->pictureBox1->MouseDown += new System::Windows::Forms::MouseEventHandler(this, pictureBox1_MouseDown);
			// 
			// openImageDialog
			// 
			this->openImageDialog->Filter = S"Image Files(*.BMP;*.JPG;*.GIF;*.png)|*.BMP;*.JPG;*.GIF;*.PNG|All files (*.*)|*.*";
			// 
			// saveImageDialog
			// 
			this->saveImageDialog->DefaultExt = S"*.jpg";
			// 
			// myInfo
			// 
			this->myInfo->Location = System::Drawing::Point(440, 8);
			this->myInfo->Name = S"myInfo";
			this->myInfo->Size = System::Drawing::Size(264, 24);
			this->myInfo->TabIndex = 11;
			// 
			// myInfo1
			// 
			this->myInfo1->Location = System::Drawing::Point(360, 8);
			this->myInfo1->Name = S"myInfo1";
			this->myInfo1->Size = System::Drawing::Size(72, 24);
			this->myInfo1->TabIndex = 12;
			// 
			// ocrMenu
			// 
			System::Windows::Forms::MenuItem* __mcTemp__1[] = new System::Windows::Forms::MenuItem*[4];
			__mcTemp__1[0] = this->menuItem1;
			__mcTemp__1[1] = this->mnuOCR;
			__mcTemp__1[2] = this->mnuAdvanced;
			__mcTemp__1[3] = this->menuItem2;
			this->ocrMenu->MenuItems->AddRange(__mcTemp__1);
			// 
			// menuItem1
			// 
			this->menuItem1->Index = 0;
			System::Windows::Forms::MenuItem* __mcTemp__2[] = new System::Windows::Forms::MenuItem*[3];
			__mcTemp__2[0] = this->mnuLoadImage;
			__mcTemp__2[1] = this->mnuFastRecognize;
			__mcTemp__2[2] = this->mnuMagnification;
			this->menuItem1->MenuItems->AddRange(__mcTemp__2);
			this->menuItem1->Text = S"Start";
			// 
			// mnuLoadImage
			// 
			this->mnuLoadImage->Index = 0;
			this->mnuLoadImage->Text = S"Load Image";
			this->mnuLoadImage->Click += new System::EventHandler(this, mnuLoadImage_Click);
			// 
			// mnuFastRecognize
			// 
			this->mnuFastRecognize->Index = 1;
			this->mnuFastRecognize->Text = S"Fast Recognize";
			this->mnuFastRecognize->Click += new System::EventHandler(this, mnuFastRecognize_Click);
			// 
			// mnuMagnification
			// 
			this->mnuMagnification->Index = 2;
			this->mnuMagnification->Text = S"Magnification";
			this->mnuMagnification->Click += new System::EventHandler(this, mnuMagnification_Click);
			// 
			// mnuOCR
			// 
			this->mnuOCR->Index = 1;
			System::Windows::Forms::MenuItem* __mcTemp__3[] = new System::Windows::Forms::MenuItem*[9];
			__mcTemp__3[0] = this->mnuFastRecognize2;
			__mcTemp__3[1] = this->menuItem5;
			__mcTemp__3[2] = this->mnuBinarize;
			__mcTemp__3[3] = this->mnuSeparate;
			__mcTemp__3[4] = this->mnuRecognize;
			__mcTemp__3[5] = this->menuItem3;
			__mcTemp__3[6] = this->mnuContrastAndBinarize;
			__mcTemp__3[7] = this->mnuContrast;
			__mcTemp__3[8] = this->mnuMeanRemoval;
			this->mnuOCR->MenuItems->AddRange(__mcTemp__3);
			this->mnuOCR->Text = S"OCR";
			// 
			// mnuFastRecognize2
			// 
			this->mnuFastRecognize2->Index = 0;
			this->mnuFastRecognize2->Text = S"Fast Recognize";
			this->mnuFastRecognize2->Click += new System::EventHandler(this, mnuFastRecognize2_Click);
			// 
			// menuItem5
			// 
			this->menuItem5->Index = 1;
			this->menuItem5->Text = S"-";
			// 
			// mnuBinarize
			// 
			this->mnuBinarize->Index = 2;
			this->mnuBinarize->Text = S"Binarize";
			this->mnuBinarize->Click += new System::EventHandler(this, mnuBinarize_Click);
			// 
			// mnuSeparate
			// 
			this->mnuSeparate->Index = 3;
			this->mnuSeparate->Text = S"Separate";
			this->mnuSeparate->Click += new System::EventHandler(this, mnuSeparate_Click);
			// 
			// mnuRecognize
			// 
			this->mnuRecognize->Index = 4;
			this->mnuRecognize->Text = S"Recognize";
			this->mnuRecognize->Click += new System::EventHandler(this, mnuRecognize_Click);
			// 
			// menuItem3
			// 
			this->menuItem3->Index = 5;
			this->menuItem3->Text = S"-";
			// 
			// mnuContrastAndBinarize
			// 
			this->mnuContrastAndBinarize->Index = 6;
			this->mnuContrastAndBinarize->Text = S"Contrast and Binarize";
			this->mnuContrastAndBinarize->Click += new System::EventHandler(this, mnuContrastAndBinarize_Click);
			// 
			// mnuContrast
			// 
			this->mnuContrast->Index = 7;
			this->mnuContrast->Text = S"Contrast Only";
			this->mnuContrast->Click += new System::EventHandler(this, mnuContrast_Click);
			// 
			// mnuMeanRemoval
			// 
			this->mnuMeanRemoval->Index = 8;
			this->mnuMeanRemoval->Text = S"Mean Removal";
			this->mnuMeanRemoval->Click += new System::EventHandler(this, mnuMeanRemoval_Click);
			// 
			// mnuAdvanced
			// 
			this->mnuAdvanced->Index = 2;
			System::Windows::Forms::MenuItem* __mcTemp__4[] = new System::Windows::Forms::MenuItem*[2];
			__mcTemp__4[0] = this->mnuTrain;
			__mcTemp__4[1] = this->mnuRecognize2;
			this->mnuAdvanced->MenuItems->AddRange(__mcTemp__4);
			this->mnuAdvanced->Text = S"Advanced";
			// 
			// mnuTrain
			// 
			this->mnuTrain->Index = 0;
			this->mnuTrain->Text = S"Train";
			this->mnuTrain->Click += new System::EventHandler(this, mnuTrain_Click);
			// 
			// mnuRecognize2
			// 
			this->mnuRecognize2->Index = 1;
			this->mnuRecognize2->Text = S"Recognize";
			this->mnuRecognize2->Click += new System::EventHandler(this, mnuRecognize2_Click);
			// 
			// menuItem2
			// 
			this->menuItem2->Index = 3;
			System::Windows::Forms::MenuItem* __mcTemp__5[] = new System::Windows::Forms::MenuItem*[5];
			__mcTemp__5[0] = this->mnuSaveImage;
			__mcTemp__5[1] = this->mnuDeskew;
			__mcTemp__5[2] = this->mnuRotate;
			__mcTemp__5[3] = this->mnuCropper;
			__mcTemp__5[4] = this->cropperEnabler;
			this->menuItem2->MenuItems->AddRange(__mcTemp__5);
			this->menuItem2->Text = S"Image";
			// 
			// mnuSaveImage
			// 
			this->mnuSaveImage->Index = 0;
			this->mnuSaveImage->Text = S"Save Imae";
			this->mnuSaveImage->Click += new System::EventHandler(this, mnuSaveImage_Click);
			// 
			// mnuDeskew
			// 
			this->mnuDeskew->Index = 1;
			this->mnuDeskew->Text = S"Deskew";
			this->mnuDeskew->Click += new System::EventHandler(this, mnuDeskew_Click);
			// 
			// mnuRotate
			// 
			this->mnuRotate->Index = 2;
			this->mnuRotate->Text = S"Rotate Right";
			this->mnuRotate->Click += new System::EventHandler(this, mnuRotate_Click);
			// 
			// mnuCropper
			// 
			this->mnuCropper->Index = 3;
			this->mnuCropper->Text = S"Image Cropper";
			this->mnuCropper->Click += new System::EventHandler(this, mnuCropper_Click);
			// 
			// cropperEnabler
			// 
			this->cropperEnabler->Index = 4;
			this->cropperEnabler->Text = S"Crop";
			// 
			// splitter1
			// 
			this->splitter1->Location = System::Drawing::Point(0, 0);
			this->splitter1->Name = S"splitter1";
			this->splitter1->Size = System::Drawing::Size(3, 399);
			this->splitter1->TabIndex = 17;
			this->splitter1->TabStop = false;
			// 
			// ocrCntMenu
			// 
			System::Windows::Forms::MenuItem* __mcTemp__6[] = new System::Windows::Forms::MenuItem*[2];
			__mcTemp__6[0] = this->cMenuLoadImage;
			__mcTemp__6[1] = this->cMenuFastRecognize;
			this->ocrCntMenu->MenuItems->AddRange(__mcTemp__6);
			// 
			// cMenuLoadImage
			// 
			this->cMenuLoadImage->Index = 0;
			this->cMenuLoadImage->Text = S"Load Image";
			this->cMenuLoadImage->Click += new System::EventHandler(this, cMenuLoadImage_Click);
			// 
			// cMenuFastRecognize
			// 
			this->cMenuFastRecognize->Index = 1;
			this->cMenuFastRecognize->Text = S"Fast Recognize";
			this->cMenuFastRecognize->Click += new System::EventHandler(this, cMenuFastRecognize_Click);
			// 
			// pbOCR
			// 
			this->pbOCR->Location = System::Drawing::Point(8, 8);
			this->pbOCR->Name = S"pbOCR";
			this->pbOCR->Size = System::Drawing::Size(120, 8);
			this->pbOCR->Step = 100;
			this->pbOCR->TabIndex = 0;
			// 
			// FormMainWindow
			// 
			this->AccessibleRole = System::Windows::Forms::AccessibleRole::Application;
			this->AllowDrop = true;
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->AutoScroll = true;
			this->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->ClientSize = System::Drawing::Size(750, 399);
			this->Controls->Add(this->splitter1);
			this->Controls->Add(this->myInfo1);
			this->Controls->Add(this->myInfo);
			this->Controls->Add(this->picture_panel);
			this->Controls->Add(this->pbOCR);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->MaximizeBox = false;
			this->Menu = this->ocrMenu;
			this->Name = S"FormMainWindow";
			this->Text = S"Nepali OCR";
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
				Yhis is an essentinal part of the ` part. 

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
			if(this->im->PixelFormat != System::Drawing::Imaging::PixelFormat::Format24bppRgb){
				System::Windows::Forms::MessageBox::Show("Pixelformat is not 24 bytes per pixel RGB","Format24bppRgb");
				return;
			}
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
				 this->pbOCR->Value = 0;
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
						this->pbOCR->Value+= 5;
					 
					 // calculating Thresholed Value for binary image					 
						ThresholedValue* ts = new ThresholedValue(im);
						float fLevel = ts->GetThresholed();
						intLevel = int(fLevel*255);
					
						 this->pbOCR->Value+= 5;
						 
					 // getting an binary array of 					 
						rgbConvert* rgbC = new rgbConvert(im);
						BArray = rgbC->GetBinaryArray(intLevel);
						ImgArray = rgbC->GetImageArray( );

						this->pbOCR->Value+= 5;
					   	
					 // Showing the binary image
						this->BinaryImage = rgbC->GetBinaryImage();
						this->pictureBox1->Image = this->BinaryImage;
						
						this->pbOCR->Value+= 5;

					 // set the cursor to Default.... 
						this->Cursor = System::Windows::Forms::Cursors::Default;
						//System::Windows::Forms::MessageBox::Show(this->intLevel.ToString()/*fLevel.ToString()*/,"Threshold Value");
						
						myInfo1->Text = "Threshold Value";
						myInfo->Text = this->intLevel.ToString();
						this->BinaryDone=true;
						this->pbOCR->Value+= 5;
					}
				 catch(System::Exception* ex)
					{
					System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"Failed to Binarize the Image!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
					this->Update();
					}
				 this->Update();
				 this->statusBar1->Text = "Binarization Done.";
				 }
	}// end of function 


		private: void openImageFile()
			{
				this->pbOCR->Value =30;
				
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
					im = new System::Drawing::Bitmap(this->openImageDialog->OpenFile());
					this->pbOCR->Value =40;
					this->pictureBox1->Image = im;
					this->pbOCR->Value =70;
					g=this->pictureBox1->CreateGraphics();
					this->pbOCR->Value =80;
					myInfo->Text="";
					myInfo1->Text="";
					
					
					//System::Windows::Forms::MessageBox::Show("Image successfully loaded","Success");
				 } // if (d == System::Windows::Forms::DialogResult::OK)
				 this->pbOCR->Value = 99;
				this->Update();
				this->pbOCR->Value = 0; //reset value in progressbar
				 
			}
		private: void saveImageFile()
			{

			/*

			This method is used to save the image file after certain image processing portion is complete.
			In case we need the file in future.

			*/


				//if(this->BinaryDone)
				//{	
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
							this->statusBar1->Text = "Image Saved Successfully";
							
							}
				//}
				//else{
			//		System::Windows::Forms::MessageBox::Show("The file was not saved because \n the image processing is not completed", "Action Incomplete");
					
			//	}
				 
			}

		
		private: void separateChar()
				 {
/*

	This method is used to separate the characters, or the connected units  after the words are separated.

	*/				this->statusBar1->Text = "Separating Characters... ";
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
									} // for(int i=0;i<this->numberOfLines;i++)
									this->statusBar1->Text = "Character Separation Done";
									if(this->pbOCR->Value <50) this->pbOCR->Value +=10;

				 }
		private: void separate()
				 {
					 
					 try{
					 this->pbOCR->Value = 40;
					 this->statusBar1->Text  = "Separating lines and Words...";
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
							this->pbOCR->Value =50;

							this->numberOfLines=sp->getNumberOfLines(); //Get Number of Lines
							this->Lines=sp->getLines();			//Get Lines
							this->SeparateDone=true;
							this->separateChar();				//separate Characters	
							this->pbOCR->Value =60;
							}

							else
							{
								this->separateChar();			//separate Characters
								this->pbOCR->Value =60;
							}

							 
						}
						this->statusBar1->Text = "Separation done"; 	
					this->Update();
					this->pbOCR->Value =70;
					 
					 }//end try 
					 catch(System::Exception *ex){
						 this->statusBar1->Text = "!!!!! Separate Failed !!!!";
						 MessageBox::Show( "Cannot Separate line, words and characters","Error!!");
					 }



				 }
 
		private: void doDeSkew()
				  {
				
				//If the lines in the image is tilted or slanted, this method is used to deskew the image. 
					  this->pbOCR->Value = 0;
				 
					Deskew* ds=new Deskew(im);
						this->pbOCR->Value +=10;
					double skewAngle=ds->GetSkewAngle();
						this->pbOCR->Value +=10;
					
					myInfo1->Text = "Skew Angle:";
					myInfo->Text = skewAngle.ToString();

					

   				    //System::Windows::Forms::MessageBox::Show(skewAngle.ToString(),"Skew Angle");

					if(skewAngle !=0){
						im=this->RotateImage(-skewAngle); 
							this->pbOCR->Value +=30;
						this->pictureBox1->Image = im;
							this->pbOCR->Value +=30;
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
						this->statusBar1->Text = "Recognition Complete ";
						this->pbOCR->Value = 100;
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
			
			/*
			Adding just in time box
			System::Windows::Forms::RichTextBox *  rtbOutput;
			rtbOutput->AutoWordSelection = true;
			rtbOutput->Location = System::Drawing::Point(8, 40);
			rtbOutput->Name = S"charRecBox";
			rtbOutput->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Vertical;
			rtbOutput->Size = System::Drawing::Size(424, 296);
			rtbOutput->TabIndex = 0;
			rtbOutput->Text = text;
			*/

			OCR::RecognitionForm* rw=new OCR::RecognitionForm();
			this->pbOCR->Value = 100;
			this->statusBar1->Text = "Recognition Complete";
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

			 if( (this->ImageLoaded==true) ){
				this->MeanRemoval(9);
				this->meanDone= true;
				this->Update();
				
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
			 //Check If the image is loaded or not.
			 if(this->ImageLoaded){
			
				 //Check If the image is binarized first or not.

				 if(this->BinaryDone){
						OCR::TrainingForm* tw=new OCR::TrainingForm();
						tw->defineVar(this->ImgArray,this->tmpBArray,this->Lines,this->numberOfLines);
						tw->ShowDialog();
				 }
					//If not binarized print an error message				
				 else{
					 System::Windows::Forms::MessageBox::Show("Image is not Binarized","Please Binarize first");
				 }
				
				}
			 //If an Image is not loaded, Print an error message to load the image.
			 else{
				 //Please Browse for image and Load the image
				 System::Windows::Forms::MessageBox::Show("Image not loaded, Please Browse for image and load image first ","Image Not loaded");
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
			 this->pbOCR->Value = 5;
			 if(this->ImageLoaded==true){
				 
				//contrast
				this->Contrast(10);
				 this->pbOCR->Value = 10;
				this->ContrastDone=true;
				 this->pbOCR->Value = 15;
				this->Update();
				 this->statusBar1->Text = "Contrast added.";
				
				//mean removal
				this->MeanRemoval(9);
				 this->pbOCR->Value = 20;
				this->meanDone= true;
				 this->statusBar1->Text = "Mean removed";

				this->Update();

				//Binarization
				 this->statusBar1->Text = "Binarizing Image...";
				this->makeBinary();
				 this->pbOCR->Value = 30;
				  this->statusBar1->Text = "Binarization Complete";
				
				//separation
				   this->statusBar1->Text = "Separating Images... ";
				this->separate();
				 this->pbOCR->Value = 50;
				  this->statusBar1->Text = "Separation of Line, words and characters complete";

				//Recognition
				   this->statusBar1->Text = "Recognition Started.";
				    this->statusBar1->Text = "Recognizing... ";
				 this->Recognize();
				  this->pbOCR->Value = 100;
				  this->statusBar1->Text = "Recognition Complete";


			 }
			 else{
				 System::Windows::Forms::MessageBox::Show("Please load the image first","Image not loaded");

			 }
			 this->pbOCR->Value = 0;

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


private: System::Void cb_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			if(this->ImageLoaded==true){
			this->Contrast(10);
			this->ContrastDone=true;
			this->makeBinary();
			this->Update();
			 }
			 else{
				 System::Windows::Forms::MessageBox::Show("Please load the image first","Image not loaded");
			 }
		 }

private: System::Void picture_panel_DragDrop(System::Object *  sender, System::Windows::Forms::DragEventArgs *  e)
		 {
			 bool allowFlag = true;
			 String* fileName[];
			  
			fileName = (String *[]) e->Data->GetData(DataFormats::FileDrop, false);
			  
			
			// for(int a=0;a<fileName->Length;a++){
//				 String *ext = Path::GetExtension(fileName)::tolower();
				 //  if( (ext != ".jpg")|| (ext != ".jpeg")|| (ext != ".gif")|| (ext != ".png")|| (ext != ".tif")|| (ext != ".tiff")|| (ext != ".bmp") ) allow = false;

			// }
			 if(e->Data->GetDataPresent(DataFormats::FileDrop))
							e->Effect = DragDropEffects::All;
			 else
					e->Effect = DragDropEffects::None;

			 
			   
			   
			  fileName = (String *[]) e->Data->GetData(DataFormats::FileDrop, false);
			  
			  for(int a=0;a<fileName->Length;a++){
				  
				this->ImageLoaded = true;
				this->BinaryDone=false;
				this->SeparateDone=false;
				this->ContrastDone=false;
				this->meanDone=false;
				this->deskewDone=false;
				im = new Bitmap(fileName[a]);
				this->pictureBox1->Image = im;
				g=this->pictureBox1->CreateGraphics();
				myInfo->Text="";
				myInfo1->Text="";
			  
			 }
  		 
		 }

private: System::Void picture_panel_DragEnter(System::Object *  sender, System::Windows::Forms::DragEventArgs *  e)
		 {
			if(e->Data->GetDataPresent(DataFormats::FileDrop))
							e->Effect = DragDropEffects::All;
			 else
					e->Effect = DragDropEffects::None;
		 }

private: System::Void btnRotate_right_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 //Function to rotate clockwise direction by 90 degrees
			 //Button_rotate_right : click event
 
			 im->RotateFlip(RotateFlipType::Rotate90FlipNone);
			 this->pictureBox1->Image = im;
		 }

private: void tryImageCropperLoad(){
			 if(this->BinaryDone ==false) 
						this->makeBinary(); //binarize before cropping

			 croper *myCroper = new croper(im,this->BArray);
			 myCroper->Show();
			 //myCroper->ImgArray = this->ImgArray;
			 //myCroper->BinArray  = this->BArray;
			 this->Hide();

			 


		 }
private: System::Void btnCrop_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 this->tryImageCropperLoad();
			 
		 }

private: System::Void mnuFastRecognize_Click(System::Object *  sender, System::EventArgs *  e)
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

		
		 }

private: System::Void mnuLoadImage_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 this->openImageFile();

		 }

private: System::Void mnuSaveImage_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 this->saveImageFile();
		 }

private: System::Void mnuDeskew_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 if(this->ImageLoaded==true){
			 this->doDeSkew();
			  }
			 else{
				 System::Windows::Forms::MessageBox::Show("Please Load the image first","Image not loaded");
			 }
			 
		 }

private: System::Void mnuContrastAndBinarize_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 if(this->ImageLoaded==true){
			this->Contrast(10);
			this->ContrastDone=true;
			this->makeBinary();
			this->Update();
			 }
			 else{
				 System::Windows::Forms::MessageBox::Show("Please load the image first","Image not loaded");
			 }
		 }

private: System::Void mnuContrast_Click(System::Object *  sender, System::EventArgs *  e)
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

private: System::Void mnuMeanRemoval_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 
			 if( (this->ImageLoaded==true) ){
				this->MeanRemoval(9);
				this->meanDone= true;
				this->Update();
				
			 }
		 }

private: System::Void mnuMagnification_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 if(this->ImageLoaded){ 
			tryMagnify();		
			
			 }
			 else{
				 System::Windows::Forms::MessageBox::Show("Please load the image first","Image not loaded");
			 }
		 }

private: System::Void mnuBinarize_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 this->makeBinary();

		 }

private: System::Void mnuRotate_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 
			 //Function to rotate clockwise direction by 90 degrees
			 //Button_rotate_right : click event
 
			 im->RotateFlip(RotateFlipType::Rotate90FlipNone);
			 this->pictureBox1->Image = im;

		 }

private: System::Void mnuSeparate_Click(System::Object *  sender, System::EventArgs *  e)
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
						 this->statusBar1->Text = "Please binarize the image first, Binarization not done";

				}
		 }

private: System::Void mnuTrain_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 //Check If the image is loaded or not.
			 if(this->ImageLoaded){
			
				 //Check If the image is binarized first or not.

				 if(this->BinaryDone){
						OCR::TrainingForm* tw=new OCR::TrainingForm();
						tw->defineVar(this->ImgArray,this->tmpBArray,this->Lines,this->numberOfLines);
						tw->ShowDialog();
				 }
					//If not binarized print an error message				
				 else{
					 System::Windows::Forms::MessageBox::Show("Image is not Binarized","Please Binarize first");
				 }
				
				}
			 //If an Image is not loaded, Print an error message to load the image.
			 else{
				 //Please Browse for image and Load the image
				 System::Windows::Forms::MessageBox::Show("Image not loaded, Please Browse for image and load image first ","Image Not loaded");
			 }
			 
		 }

private: System::Void mnuRecognize2_Click(System::Object *  sender, System::EventArgs *  e)
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



private: System::Void mnuCropper_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 this->tryImageCropperLoad();

		 }





private: System::Void mnuRecognize_Click(System::Object *  sender, System::EventArgs *  e)
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

private: System::Void mnuFastRecognize2_Click(System::Object *  sender, System::EventArgs *  e)
		 {
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

		 }
		 }

private: System::Void cMenuLoadImage_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 this->openImageFile();
			 //this->cMenuLoadImage->Enabled = false;
		 }

private: System::Void picture_panel_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 
			 
		 }

private: System::Void picture_panel_MouseUp(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		 {
			 this->drawContextMenu(e);
		 }

private: System::Void cMenuFastRecognize_Click(System::Object *  sender, System::EventArgs *  e)
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

		
		  

		 }

private: System::Void pictureBox1_MouseUp(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		 {

				 this->drawContextMenu(e);
				 if(this->BinaryDone == true) cropMe(e);

		 }

private: void drawContextMenu(System::Windows::Forms::MouseEventArgs *  e){

			 //Left Click
			 if(e->Button == MouseButtons::Left){ //Left Click
					System::Windows::Forms::ContextMenu *ocrCMenu = new System::Windows::Forms::ContextMenu();

				if(this->ImageLoaded ==false){//Left Click, If image not loaded, load image
					
					ocrCMenu->MenuItems->Add(this->mnuLoadImage);
					
				} // if(e->Button == MouseButtons::Left){if(this->ImageLoaded ==false)
				else{
					if(this->ImageLoaded ==true && this->BinaryDone==false){ //Left click, if image loaded, recognize it
						ocrCMenu->MenuItems->Add(this->mnuFastRecognize);
						ocrCMenu->MenuItems->Add(this->mnuBinarize);
						
					}
					if(this->ImageLoaded ==true && this->BinaryDone==true){ //Left click, if image loaded, and Binarized, separate it
						ocrCMenu->MenuItems->Add(this->mnuSeparate);
						ocrCMenu->MenuItems->Add(this->mnuFastRecognize);
					}
					

				}//end Else
				if(this->SeparateDone==true){
					ocrCMenu->MenuItems->Add(this->mnuRecognize);
					ocrCMenu->MenuItems->Add(this->mnuTrain);

				}

				ocrCMenu->Show(this,System::Drawing::Point(e->X,e->Y));
			} // if(e->Button == MouseButtons::Left) 


		 
		
			 //Right Click
			 if(e->Button == MouseButtons::Right){//Right Click
				 if(this->ImageLoaded==true){ //Rotate Image on right click
					System::Windows::Forms::ContextMenu *ocrCMenu = new System::Windows::Forms::ContextMenu();

					ocrCMenu->MenuItems->Add(this->mnuRotate);
					ocrCMenu->MenuItems->Add(this->mnuLoadImage);
					ocrCMenu->Show(this,System::Drawing::Point(e->X,e->Y));
				 }
			 } // if(e->Button == MouseButtons::Right)


		 }

private: System::Void pictureBox1_Paint(System::Object *  sender, System::Windows::Forms::PaintEventArgs *  e)
		 {
			 //e->Graphics->DrawRectangle(Pens::Blue, Rectangle(this->pointX1,this->pointY1,(this->pointX2-this->pointX1),(this->pointY2-this->pointY1)));
		 }

private: System::Void pictureBox1_MouseDown(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		 {
			 this->pointX1 = e->X;
			 this->pointY1 = e->Y;
		 }

private: void cropMe(System::Windows::Forms::MouseEventArgs *  e){
			
			 this->pointX2 = e->X;
			 this->pointY2 = e->Y;
			 int temp;


			 if(this->pointX1 != this->pointX2 && this->pointY1 != this->pointY2)
			 {
				if(this->pointX1>this->pointX2)
				{
					temp=this->pointX1;
					this->pointX1=this->pointX2;
					this->pointX2=temp;
				} // if(this->pointX1>this->pointX2)
                
				if(this->pointY1>this->pointY2)
				{
					temp=this->pointY1;
					this->pointY1=this->pointY2;
					this->pointY2=temp;
				} // if(this->pointY1>this->pointY2) 
                
			 } // if(this->pointX1 != this->pointX2 && this->pointY1 != this->pointY2)


			 //int mouse_dragged_Image_width = System::Math::Abs(this->x2 - this->x1) ;
			int mouse_dragged_Image_width = (this->pointX2 - this->pointX1) ;
		//int mouse_dragged_Image_height = System::Math::Abs(this->y2 - this->y1);
			int mouse_dragged_Image_height = (this->pointY2 - this->pointY1);

			 Bitmap *cropImage1 = new Bitmap( mouse_dragged_Image_width+1,mouse_dragged_Image_height+1,Imaging::PixelFormat::Format24bppRgb);
		 for(int cropRow=0;  cropRow<(cropImage1->Height); cropRow++){
			 for(int cropColumn=0;cropColumn<(cropImage1->Width) ;cropColumn++){
				cropImage1->SetPixel(cropColumn,cropRow,System::Drawing::Color::White);
				} // for(int cropRow=0;  cropRow<(cropImage->Height); cropRow++){for(int cropColumn=0;cropColumn<(cropImage->Width) ;cropColumn++)
          } // for(int cropRow=0;  cropRow<(cropImage->Height); cropRow++)

		 for(int i=this->pointY1, int cropRow=0;  i<this->pointY2,cropRow<(cropImage1->Height)-1; i++,cropRow++){
			 for(int cropColumn=0,j=this->pointX1; j<this->pointX2,cropColumn<(cropImage1->Width)-1 ; j++,cropColumn++){
				 
				 if(this->BArray[i][j]==true)
					 cropImage1->SetPixel(cropColumn,cropRow,System::Drawing::Color::White);
				 else
					 cropImage1->SetPixel(cropColumn,cropRow,System::Drawing::Color::Black);
				 
			 } // for(int i=0;i<cropImage->Height;i++){for(int j=0;j<cropImage->Width;j++)
		 } // for(int i=0;i<cropImage->Height;i++)

		 this->g->DrawRectangle(Pens::Blue, Rectangle(this->pointX1,this->pointY1,(this->pointX2-this->pointX1),(this->pointY2-this->pointY1)));
		 this->g->Flush();
		
		 this->pictureBox1->Image = cropImage1;



		 }

};




}


