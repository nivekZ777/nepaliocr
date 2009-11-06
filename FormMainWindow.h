
/**
 *   OCR
 *
 *
 * Requirements:
 *  
 * win2k or later\n
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
#include "TrainingForm.h"
#include "RecognitionForm.h"
#include "RecognitionProcess.h"
#include "ThresholedValue.h"
#include "rgbConvert.h"
#include "Separate.h"
#include "Convolution.h"
#include "Deskew.h"
#include "myWindow.h"
#include "Resegment.h"
#include "RemoveNoise.h"


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
			this->TouchingCharIdentified=false;

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
			//this->MdiChildren = OCR::myWindow ;
			//this->MdiChildren = OCR::TrainingForm;
			//
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
	private: Bitmap *im,*backup;
			 
	private: Bitmap* BinaryImage;
	private: Bitmap *selectedImage;
	private: Graphics* g;
	private: int intLevel;
	private: int **ImgArray;
			 int **BackupImgArray;
			 int **HeadBottom;

	private: bool **BArray;
			 bool **BackupBArray;
			 bool **tmpBArray;
	private: bool BinaryDone;
	private: bool ImageLoaded;
			 bool SeparateDone;
			 bool ContrastDone;
			 bool meanDone;
			 bool deskewDone;
			 bool rtbOutputShowing;
			 bool imageSelection;
			 bool TouchingCharIdentified;
			 bool dragEnabled;
			 



	private: int numberOfLines;
			 //new variables
			 int SizeThreshold;
			 int totalUnits;
			 int *WStore;
			 
	private: Line* Lines; 

	private: String* applicationPath;
			 String* modelTrainDBPath;
			 String* scriptFilePath;
			 String* characterDBPath;

	
	private: System::Collections::SortedList* slForCharacters;
	private: System::Collections::SortedList* slModelTranscription;	// for storing the model transcriptions
	private: System::Collections::ArrayList* alModelRec;			// for models that already recognized
			 System::Collections::ArrayList *aakarList;
			 System::Collections::ArrayList *rassoEEkarList;


	
	
			 
	
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
private: System::Windows::Forms::MenuItem *  mnuStart;
private: System::Windows::Forms::MenuItem *  mnuLoadImage2;
private: System::Windows::Forms::MenuItem *  mnuSaveImage;
private: System::Windows::Forms::MenuItem *  mnuFastRecognize;
private: System::Windows::Forms::MenuItem *  mnuExit;
private: System::Windows::Forms::MenuItem *  mnuOCR;
private: System::Windows::Forms::MenuItem *  mnuFastRecognize2;
private: System::Windows::Forms::MenuItem *  mnuRecognize;
private: System::Windows::Forms::MenuItem *  mnuAdvanced;
private: System::Windows::Forms::MenuItem *  mnuBinarize;
private: System::Windows::Forms::MenuItem *  menuItem2;
private: System::Windows::Forms::MenuItem *  mnuSeparate;
private: System::Windows::Forms::MenuItem *  mnuTrain;
private: System::Windows::Forms::MenuItem *  mnuRecognize2;
private: System::Windows::Forms::MenuItem *  menuItem3;
private: System::Windows::Forms::MenuItem *  mnuMeanRemoval;
private: System::Windows::Forms::MenuItem *  mnuContrast;
private: System::Windows::Forms::MenuItem *  mnuContrastAndBinarize;
private: System::Windows::Forms::MenuItem *  mnuNoiseRemoval;
private: System::Windows::Forms::MenuItem *  mnuImage;
private: System::Windows::Forms::MenuItem *  mnuLoadImage;
private: System::Windows::Forms::MenuItem *  mnuDeskew;
private: System::Windows::Forms::MenuItem *  mnuRotate;
private: System::Windows::Forms::MenuItem *  mnuCropper;
private: System::Windows::Forms::MenuItem *  menuItem1;
private: System::Windows::Forms::MenuItem *  mnuMagnification;
private: System::Windows::Forms::ProgressBar *  pbOCR;
private: System::Windows::Forms::StatusBar *  statusBar1;
private: System::Windows::Forms::Panel *  panel1;

private: System::Windows::Forms::RichTextBox *rtbOutput;
private: System::Windows::Forms::MenuItem *  mnuResegment;
private: int pointX1,pointX2,pointY1,pointY2,xMouseDistance,yMouseDistance; //for capturing the points
private: System::Windows::Forms::MenuItem *  mnuAbout;
private: System::Windows::Forms::MenuItem *  mnuVersionInfo;

private: System::Windows::Forms::MenuItem *  menuItem4;
private: System::Windows::Forms::PictureBox *  crobPictureBox;
private: System::Windows::Forms::RichTextBox *  rtbMainOutput;
private: System::Windows::Forms::SaveFileDialog *  saveOutputDialog;
private: System::Windows::Forms::MenuItem *  mnuSaveOutput;










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
			this->crobPictureBox = new System::Windows::Forms::PictureBox();
			this->pbOCR = new System::Windows::Forms::ProgressBar();
			this->openImageDialog = new System::Windows::Forms::OpenFileDialog();
			this->saveImageDialog = new System::Windows::Forms::SaveFileDialog();
			this->myInfo = new System::Windows::Forms::Label();
			this->myInfo1 = new System::Windows::Forms::Label();
			this->ocrMenu = new System::Windows::Forms::MainMenu();
			this->mnuStart = new System::Windows::Forms::MenuItem();
			this->mnuLoadImage2 = new System::Windows::Forms::MenuItem();
			this->mnuSaveImage = new System::Windows::Forms::MenuItem();
			this->mnuFastRecognize = new System::Windows::Forms::MenuItem();
			this->mnuSaveOutput = new System::Windows::Forms::MenuItem();
			this->mnuExit = new System::Windows::Forms::MenuItem();
			this->mnuOCR = new System::Windows::Forms::MenuItem();
			this->mnuFastRecognize2 = new System::Windows::Forms::MenuItem();
			this->mnuRecognize = new System::Windows::Forms::MenuItem();
			this->mnuAdvanced = new System::Windows::Forms::MenuItem();
			this->mnuBinarize = new System::Windows::Forms::MenuItem();
			this->menuItem2 = new System::Windows::Forms::MenuItem();
			this->mnuSeparate = new System::Windows::Forms::MenuItem();
			this->mnuTrain = new System::Windows::Forms::MenuItem();
			this->mnuRecognize2 = new System::Windows::Forms::MenuItem();
			this->menuItem3 = new System::Windows::Forms::MenuItem();
			this->mnuMeanRemoval = new System::Windows::Forms::MenuItem();
			this->mnuContrast = new System::Windows::Forms::MenuItem();
			this->mnuContrastAndBinarize = new System::Windows::Forms::MenuItem();
			this->mnuNoiseRemoval = new System::Windows::Forms::MenuItem();
			this->mnuResegment = new System::Windows::Forms::MenuItem();
			this->mnuImage = new System::Windows::Forms::MenuItem();
			this->mnuLoadImage = new System::Windows::Forms::MenuItem();
			this->mnuDeskew = new System::Windows::Forms::MenuItem();
			this->mnuRotate = new System::Windows::Forms::MenuItem();
			this->mnuCropper = new System::Windows::Forms::MenuItem();
			this->menuItem1 = new System::Windows::Forms::MenuItem();
			this->mnuMagnification = new System::Windows::Forms::MenuItem();
			this->mnuAbout = new System::Windows::Forms::MenuItem();
			this->mnuVersionInfo = new System::Windows::Forms::MenuItem();
			this->menuItem4 = new System::Windows::Forms::MenuItem();
			this->panel1 = new System::Windows::Forms::Panel();
			this->rtbMainOutput = new System::Windows::Forms::RichTextBox();
			this->rtbOutput = new System::Windows::Forms::RichTextBox();
			this->saveOutputDialog = new System::Windows::Forms::SaveFileDialog();
			this->picture_panel->SuspendLayout();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// picture_panel
			// 
			this->picture_panel->AllowDrop = true;
			this->picture_panel->AutoScroll = true;
			this->picture_panel->BackColor = System::Drawing::Color::AliceBlue;
			this->picture_panel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->picture_panel->Controls->Add(this->statusBar1);
			this->picture_panel->Controls->Add(this->pictureBox1);
			this->picture_panel->Controls->Add(this->crobPictureBox);
			this->picture_panel->Location = System::Drawing::Point(0, 8);
			this->picture_panel->Name = S"picture_panel";
			this->picture_panel->Size = System::Drawing::Size(992, 568);
			this->picture_panel->TabIndex = 1;
			this->picture_panel->DragEnter += new System::Windows::Forms::DragEventHandler(this, picture_panel_DragEnter);
			this->picture_panel->MouseUp += new System::Windows::Forms::MouseEventHandler(this, picture_panel_MouseUp);
			this->picture_panel->DragDrop += new System::Windows::Forms::DragEventHandler(this, picture_panel_DragDrop);
			// 
			// statusBar1
			// 
			this->statusBar1->Location = System::Drawing::Point(0, 548);
			this->statusBar1->Name = S"statusBar1";
			this->statusBar1->Size = System::Drawing::Size(988, 16);
			this->statusBar1->TabIndex = 18;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(5, 12);
			this->pictureBox1->Name = S"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(100, 100);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->MouseUp += new System::Windows::Forms::MouseEventHandler(this, pictureBox1_MouseUp);
			this->pictureBox1->MouseMove += new System::Windows::Forms::MouseEventHandler(this, pictureBox1_MouseMove);
			this->pictureBox1->MouseDown += new System::Windows::Forms::MouseEventHandler(this, pictureBox1_MouseDown);
			// 
			// crobPictureBox
			// 
			this->crobPictureBox->Location = System::Drawing::Point(872, 8);
			this->crobPictureBox->Name = S"crobPictureBox";
			this->crobPictureBox->Size = System::Drawing::Size(104, 96);
			this->crobPictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->crobPictureBox->TabIndex = 2;
			this->crobPictureBox->TabStop = false;
			this->crobPictureBox->Visible = false;
			// 
			// pbOCR
			// 
			this->pbOCR->Location = System::Drawing::Point(8, 696);
			this->pbOCR->Name = S"pbOCR";
			this->pbOCR->Size = System::Drawing::Size(992, 8);
			this->pbOCR->Step = 100;
			this->pbOCR->TabIndex = 17;
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
			this->myInfo->Location = System::Drawing::Point(256, 8);
			this->myInfo->Name = S"myInfo";
			this->myInfo->Size = System::Drawing::Size(72, 8);
			this->myInfo->TabIndex = 11;
			// 
			// myInfo1
			// 
			this->myInfo1->Location = System::Drawing::Point(384, 0);
			this->myInfo1->Name = S"myInfo1";
			this->myInfo1->Size = System::Drawing::Size(72, 24);
			this->myInfo1->TabIndex = 12;
			// 
			// ocrMenu
			// 
			System::Windows::Forms::MenuItem* __mcTemp__1[] = new System::Windows::Forms::MenuItem*[5];
			__mcTemp__1[0] = this->mnuStart;
			__mcTemp__1[1] = this->mnuOCR;
			__mcTemp__1[2] = this->mnuAdvanced;
			__mcTemp__1[3] = this->mnuImage;
			__mcTemp__1[4] = this->mnuAbout;
			this->ocrMenu->MenuItems->AddRange(__mcTemp__1);
			// 
			// mnuStart
			// 
			this->mnuStart->Index = 0;
			System::Windows::Forms::MenuItem* __mcTemp__2[] = new System::Windows::Forms::MenuItem*[5];
			__mcTemp__2[0] = this->mnuLoadImage2;
			__mcTemp__2[1] = this->mnuSaveImage;
			__mcTemp__2[2] = this->mnuFastRecognize;
			__mcTemp__2[3] = this->mnuSaveOutput;
			__mcTemp__2[4] = this->mnuExit;
			this->mnuStart->MenuItems->AddRange(__mcTemp__2);
			this->mnuStart->Text = S"&File";
			// 
			// mnuLoadImage2
			// 
			this->mnuLoadImage2->Index = 0;
			this->mnuLoadImage2->Shortcut = System::Windows::Forms::Shortcut::CtrlN;
			this->mnuLoadImage2->Text = S"&New Image";
			this->mnuLoadImage2->Click += new System::EventHandler(this, mnuLoadImage2_Click);
			// 
			// mnuSaveImage
			// 
			this->mnuSaveImage->Enabled = false;
			this->mnuSaveImage->Index = 1;
			this->mnuSaveImage->Shortcut = System::Windows::Forms::Shortcut::CtrlS;
			this->mnuSaveImage->Text = S"&Save Image";
			this->mnuSaveImage->Click += new System::EventHandler(this, mnuSaveImage_Click);
			// 
			// mnuFastRecognize
			// 
			this->mnuFastRecognize->Enabled = false;
			this->mnuFastRecognize->Index = 2;
			this->mnuFastRecognize->Text = S"Fast Recognize";
			this->mnuFastRecognize->Click += new System::EventHandler(this, mnuFastRecognize_Click);
			// 
			// mnuSaveOutput
			// 
			this->mnuSaveOutput->Index = 3;
			this->mnuSaveOutput->Shortcut = System::Windows::Forms::Shortcut::CtrlD;
			this->mnuSaveOutput->Text = S"Save Output";
			this->mnuSaveOutput->Click += new System::EventHandler(this, mnuSaveOutput_Click);
			// 
			// mnuExit
			// 
			this->mnuExit->Index = 4;
			this->mnuExit->Shortcut = System::Windows::Forms::Shortcut::CtrlW;
			this->mnuExit->Text = S"&Exit";
			this->mnuExit->Click += new System::EventHandler(this, mnuExit_Click);
			// 
			// mnuOCR
			// 
			this->mnuOCR->Enabled = false;
			this->mnuOCR->Index = 1;
			System::Windows::Forms::MenuItem* __mcTemp__3[] = new System::Windows::Forms::MenuItem*[2];
			__mcTemp__3[0] = this->mnuFastRecognize2;
			__mcTemp__3[1] = this->mnuRecognize;
			this->mnuOCR->MenuItems->AddRange(__mcTemp__3);
			this->mnuOCR->Text = S"OCR";
			// 
			// mnuFastRecognize2
			// 
			this->mnuFastRecognize2->Checked = true;
			this->mnuFastRecognize2->Enabled = false;
			this->mnuFastRecognize2->Index = 0;
			this->mnuFastRecognize2->Shortcut = System::Windows::Forms::Shortcut::CtrlO;
			this->mnuFastRecognize2->Text = S"&OCR";
			this->mnuFastRecognize2->Click += new System::EventHandler(this, mnuFastRecognize2_Click);
			// 
			// mnuRecognize
			// 
			this->mnuRecognize->Enabled = false;
			this->mnuRecognize->Index = 1;
			this->mnuRecognize->Text = S"Recognize";
			this->mnuRecognize->Click += new System::EventHandler(this, mnuRecognize_Click);
			// 
			// mnuAdvanced
			// 
			this->mnuAdvanced->Enabled = false;
			this->mnuAdvanced->Index = 2;
			System::Windows::Forms::MenuItem* __mcTemp__4[] = new System::Windows::Forms::MenuItem*[11];
			__mcTemp__4[0] = this->mnuBinarize;
			__mcTemp__4[1] = this->menuItem2;
			__mcTemp__4[2] = this->mnuSeparate;
			__mcTemp__4[3] = this->mnuTrain;
			__mcTemp__4[4] = this->mnuRecognize2;
			__mcTemp__4[5] = this->menuItem3;
			__mcTemp__4[6] = this->mnuMeanRemoval;
			__mcTemp__4[7] = this->mnuContrast;
			__mcTemp__4[8] = this->mnuContrastAndBinarize;
			__mcTemp__4[9] = this->mnuNoiseRemoval;
			__mcTemp__4[10] = this->mnuResegment;
			this->mnuAdvanced->MenuItems->AddRange(__mcTemp__4);
			this->mnuAdvanced->Text = S"&Advanced";
			// 
			// mnuBinarize
			// 
			this->mnuBinarize->Enabled = false;
			this->mnuBinarize->Index = 0;
			this->mnuBinarize->Shortcut = System::Windows::Forms::Shortcut::CtrlB;
			this->mnuBinarize->Text = S"Binarize";
			this->mnuBinarize->Click += new System::EventHandler(this, mnuBinarize_Click);
			// 
			// menuItem2
			// 
			this->menuItem2->Index = 1;
			this->menuItem2->Text = S"-";
			// 
			// mnuSeparate
			// 
			this->mnuSeparate->Enabled = false;
			this->mnuSeparate->Index = 2;
			this->mnuSeparate->Shortcut = System::Windows::Forms::Shortcut::CtrlP;
			this->mnuSeparate->Text = S"Separate";
			this->mnuSeparate->Click += new System::EventHandler(this, mnuSeparate_Click);
			// 
			// mnuTrain
			// 
			this->mnuTrain->Enabled = false;
			this->mnuTrain->Index = 3;
			this->mnuTrain->Shortcut = System::Windows::Forms::Shortcut::CtrlT;
			this->mnuTrain->Text = S"Train";
			this->mnuTrain->Click += new System::EventHandler(this, mnuTrain_Click);
			// 
			// mnuRecognize2
			// 
			this->mnuRecognize2->Enabled = false;
			this->mnuRecognize2->Index = 4;
			this->mnuRecognize2->Shortcut = System::Windows::Forms::Shortcut::CtrlE;
			this->mnuRecognize2->Text = S"Recognize";
			this->mnuRecognize2->Click += new System::EventHandler(this, mnuRecognize2_Click);
			// 
			// menuItem3
			// 
			this->menuItem3->Index = 5;
			this->menuItem3->Text = S"-";
			// 
			// mnuMeanRemoval
			// 
			this->mnuMeanRemoval->Enabled = false;
			this->mnuMeanRemoval->Index = 6;
			this->mnuMeanRemoval->Text = S"Mean Removal";
			this->mnuMeanRemoval->Click += new System::EventHandler(this, mnuMeanRemoval_Click);
			// 
			// mnuContrast
			// 
			this->mnuContrast->Enabled = false;
			this->mnuContrast->Index = 7;
			this->mnuContrast->Text = S"Contrast Only";
			this->mnuContrast->Click += new System::EventHandler(this, mnuContrast_Click);
			// 
			// mnuContrastAndBinarize
			// 
			this->mnuContrastAndBinarize->Enabled = false;
			this->mnuContrastAndBinarize->Index = 8;
			this->mnuContrastAndBinarize->Text = S"Contrast and Binarize";
			this->mnuContrastAndBinarize->Click += new System::EventHandler(this, mnuContrastAndBinarize_Click);
			// 
			// mnuNoiseRemoval
			// 
			this->mnuNoiseRemoval->Index = 9;
			this->mnuNoiseRemoval->Text = S"Noise Removal";
			this->mnuNoiseRemoval->Click += new System::EventHandler(this, mnuNoiseRemoval_Click);
			// 
			// mnuResegment
			// 
			this->mnuResegment->Index = 10;
			this->mnuResegment->Text = S"Resegment";
			this->mnuResegment->Click += new System::EventHandler(this, mnuResegment_Click);
			// 
			// mnuImage
			// 
			this->mnuImage->Index = 3;
			System::Windows::Forms::MenuItem* __mcTemp__5[] = new System::Windows::Forms::MenuItem*[6];
			__mcTemp__5[0] = this->mnuLoadImage;
			__mcTemp__5[1] = this->mnuDeskew;
			__mcTemp__5[2] = this->mnuRotate;
			__mcTemp__5[3] = this->mnuCropper;
			__mcTemp__5[4] = this->menuItem1;
			__mcTemp__5[5] = this->mnuMagnification;
			this->mnuImage->MenuItems->AddRange(__mcTemp__5);
			this->mnuImage->Text = S"&Image";
			// 
			// mnuLoadImage
			// 
			this->mnuLoadImage->Index = 0;
			this->mnuLoadImage->Shortcut = System::Windows::Forms::Shortcut::CtrlN;
			this->mnuLoadImage->Text = S"Load Image";
			this->mnuLoadImage->Click += new System::EventHandler(this, mnuLoadImage_Click);
			// 
			// mnuDeskew
			// 
			this->mnuDeskew->Enabled = false;
			this->mnuDeskew->Index = 1;
			this->mnuDeskew->Text = S"Deskew";
			this->mnuDeskew->Click += new System::EventHandler(this, mnuDeskew_Click);
			// 
			// mnuRotate
			// 
			this->mnuRotate->Enabled = false;
			this->mnuRotate->Index = 2;
			this->mnuRotate->Shortcut = System::Windows::Forms::Shortcut::CtrlR;
			this->mnuRotate->Text = S"Rotate Right";
			this->mnuRotate->Click += new System::EventHandler(this, mnuRotate_Click);
			// 
			// mnuCropper
			// 
			this->mnuCropper->Enabled = false;
			this->mnuCropper->Index = 3;
			this->mnuCropper->Text = S"Image Cropper";
			// 
			// menuItem1
			// 
			this->menuItem1->Index = 4;
			this->menuItem1->Text = S"-";
			// 
			// mnuMagnification
			// 
			this->mnuMagnification->Enabled = false;
			this->mnuMagnification->Index = 5;
			this->mnuMagnification->Text = S"Magnification";
			this->mnuMagnification->Click += new System::EventHandler(this, mnuMagnification_Click);
			// 
			// mnuAbout
			// 
			this->mnuAbout->Index = 4;
			System::Windows::Forms::MenuItem* __mcTemp__6[] = new System::Windows::Forms::MenuItem*[2];
			__mcTemp__6[0] = this->mnuVersionInfo;
			__mcTemp__6[1] = this->menuItem4;
			this->mnuAbout->MenuItems->AddRange(__mcTemp__6);
			this->mnuAbout->Text = S"&About";
			// 
			// mnuVersionInfo
			// 
			this->mnuVersionInfo->Index = 0;
			this->mnuVersionInfo->Text = S"Version &Info";
			this->mnuVersionInfo->Click += new System::EventHandler(this, mnuVersionInfo_Click);
			// 
			// menuItem4
			// 
			this->menuItem4->Index = 1;
			this->menuItem4->Text = S"-";
			// 
			// panel1
			// 
			this->panel1->AutoScroll = true;
			this->panel1->Controls->Add(this->picture_panel);
			this->panel1->Controls->Add(this->rtbMainOutput);
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = S"panel1";
			this->panel1->Size = System::Drawing::Size(1000, 696);
			this->panel1->TabIndex = 19;
			// 
			// rtbMainOutput
			// 
			this->rtbMainOutput->Location = System::Drawing::Point(8, 584);
			this->rtbMainOutput->Name = S"rtbMainOutput";
			this->rtbMainOutput->Size = System::Drawing::Size(976, 96);
			this->rtbMainOutput->TabIndex = 19;
			this->rtbMainOutput->Text = S"";
			this->rtbMainOutput->MouseUp += new System::Windows::Forms::MouseEventHandler(this, rtbMainOutput_MouseUp);
			// 
			// rtbOutput
			// 
			this->rtbOutput->Location = System::Drawing::Point(0, 0);
			this->rtbOutput->Name = S"rtbOutput";
			this->rtbOutput->TabIndex = 0;
			this->rtbOutput->Text = S"";
			// 
			// FormMainWindow
			// 
			this->AccessibleRole = System::Windows::Forms::AccessibleRole::Application;
			this->AllowDrop = true;
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->BackColor = System::Drawing::Color::WhiteSmoke;
			this->ClientSize = System::Drawing::Size(1006, 711);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->myInfo1);
			this->Controls->Add(this->myInfo);
			this->Controls->Add(this->pbOCR);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->IsMdiContainer = true;
			this->Menu = this->ocrMenu;
			this->Name = S"FormMainWindow";
			this->Text = S"OCR (Sept)";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += new System::EventHandler(this, FormMainWindow_Load);
			this->picture_panel->ResumeLayout(false);
			this->panel1->ResumeLayout(false);
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
			
			this->Cursor = System::Windows::Forms::Cursors::WaitCursor;
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
			this->Cursor = System::Windows::Forms::Cursors::Default;
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
			this->Cursor = System::Windows::Forms::Cursors::WaitCursor;
			/*

				This method increases the contrast of the image. 
				Thus making the image more visible. 

			*/
			if(this->im->PixelFormat != System::Drawing::Imaging::PixelFormat::Format24bppRgb){
				this->statusBar1->Text = ("Pixelformat is not 24 bytes per pixel RGB \(Format24bppRgb\)");
				//System::Windows::Forms::MessageBox::Show("Pixelformat is not 24 bytes per pixel RGB","Format24bppRgb");
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
				  if(this->rtbOutputShowing == true) this->delRTB();

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
						this->BackupBArray=this->BArray;
						ImgArray = rgbC->GetImageArray();
						this->pbOCR->Value+= 5;
					   	this->BackupImgArray=this->ImgArray;

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
					this->Cursor = System::Windows::Forms::Cursors::Default;
				 this->Update();
				 this->statusBar1->Text = "Binarization Done.";
				 this->setResetMenu(this->ImageLoaded,this->BinaryDone,this->SeparateDone);

				 }// if(this->ImageLoaded)
	}// end of function 


		 	private: void openImageFile()
			{
				if(this->rtbOutputShowing == true) this->delRTB();
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
					
					this->setResetMenu(this->ImageLoaded,this->BinaryDone,this->SeparateDone);
					

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
									}// for(int i=0;i<this->numberOfLines;i++)
									this->statusBar1->Text = "Character Separation Done";
									if(this->pbOCR->Value <50) this->pbOCR->Value +=10;

				 }
		private: void separate()
				 {
			if(this->rtbOutputShowing == true) this->delRTB();
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
								this->HeadBottom=sp->getHeadBottom();
								this->SeparateDone=true;
								this->separateChar();				//separate Characters					
								this->pbOCR->Value =60;
							}
							else
							{
								this->separateChar();			//separate Characters
								this->pbOCR->Value =60;
							}
							this->WidthStore();
                            this->SizeThreshold=this->ThresholdSize();
							Resegment* rsg=new Resegment(im,BinaryDone,ImageLoaded,SeparateDone,BArray,this->numberOfLines,this->Lines,g,this->totalUnits,this->SizeThreshold,this->intLevel,this->HeadBottom);
//							rsg->PrepareTouchingCharIndex();
							rsg->Do_Segmentation();

						}// if(this->BinaryDone==true) //If binarization is done
					
					this->setResetMenu(this->ImageLoaded,this->BinaryDone,this->SeparateDone);
					this->statusBar1->Text = "Separation done"; 	
					this->Update();
					this->pbOCR->Value =70;
				 }//end try 
				catch(System::Exception *ex){
						 this->statusBar1->Text = "!!!!! Separate Failed !!!!";
						 MessageBox::Show( "Cannot Separate line, words and characters","Error!!");
				}//end Catch

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
						if(this->BinaryDone){
							this->resetVariablesAfterRotation();
						}
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
						this->Cursor = System::Windows::Forms::Cursors::WaitCursor;
						RecognitionProcess* rp = new RecognitionProcess(this->applicationPath,this->ImgArray);
						// load the transcription of the models
						this->statusBar1->Text = "Loading Models ....";

						//aakarList added 
						aakarList = new System::Collections::ArrayList();
						this->slModelTranscription = rp->LoadModelTranscriptions(this->modelTrainDBPath);

						this->aakarList =  rp->aakarsList;
						this->rassoEEkarList = rp->rassoEEkarList;
						
						
						int lineCount = this->numberOfLines;
						int wordCount = 0;
						int totalUnit = 0;
						int unitCount = 0;
						int left_x,right_x,top_y,bottom_y;
						System::String* wordToRec;
						System::String* dirOfRecFile = rp->recognitionTempFileDir;
						this->statusBar1->Text = "Searching database directories ..";

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
									this->statusBar1->Text = "Setting Image Boundaries ..";
									rp->SetImageBoundary(left_x,right_x,top_y,bottom_y);
									totalUnit++;
									wordToRec = wordToRec->Concat(dirOfRecFile,totalUnit.ToString(),".txt");	
									this->statusBar1->Text = "Preparing word datas.. ";
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
						this->statusBar1->Text = "Recognisation process in progress.. Please wait..";
						
						this->alModelRec = rp->RecognizeByHTK();
						this->statusBar1->Text = "Recognition process complete..";




						this->statusBar1->Text = "Showing Output...";						
						this->ProvideOutput();
						this->statusBar1->Text = " Done.";

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
						this->Cursor = System::Windows::Forms::Cursors::Default;
					//	this->statusBar1->Text = "Output window closed";
						this->pbOCR->Value = 100;
						this->Cursor = System::Windows::Forms::Cursors::Default;
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

			System::Collections::IEnumerator *AakarEnum =   aakarList->GetEnumerator();
			System::Collections::IEnumerator *rassoEEkarEnum = rassoEEkarList->GetEnumerator();
			
			//System::Collections::IEnumerator *ehhEEkarEnum = 
			bool aaKarFound = false;
			bool rassoEEkarFound = false;
			int aaKarCounter = 0;
			int rassoEEkarCounter = 0;
			
			int tempcount=0;	//Added for postprocessor : Multifactorial added
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
							{// Block Start
								ucodeStr = "";									
								System::Collections::IEnumerator* ENum;
								ENum=this->alModelRec->GetEnumerator();
								System::String* tempStr="";
								System::String* tempStr1="";
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
								 

								tempStr1=tempStr; //multifactorial added

								index = this->slModelTranscription->IndexOfKey(tempStr);
								ind++;
								tempAl = (System::Collections::ArrayList*)slModelTranscription->GetByIndex(index);
								System::Collections::IEnumerator* tempNum=tempAl->GetEnumerator();

								int tcount=0; //multifactorial added

								while(tempNum->MoveNext())
								{
									tempStr = (String*)tempNum->Current;
									ucodeStr = ucodeStr->Concat(ucodeStr,slForCharacters->GetKey(slForCharacters->IndexOfValue(tempStr)));

									tcount++; //multifactorial added
								}
								//Normal Processing Complete here 
								//tempStr contains the model name
								//ucodeStr contains the Unicode value
								//Just append 
								/*
									//Original before multifactorial :- 
									text = text->Concat(text,ucodeStr);
								*/
				
//Sanjeev's Post Processing Codes for extra aakar 
							 
							bool aakarNew = false;
							while(AakarEnum->MoveNext()){
								//String *abc = ehh->Current->ToString();
								if(tempStr1->Equals(AakarEnum->Current->ToString())){
									aakarNew = true;
								}
																
							}
							if(aakarNew) {
								aaKarCounter++;
							}
							else{
								aaKarCounter = 0;
							}

							while(rassoEEkarEnum->MoveNext()){
								if(tempStr->Equals(rassoEEkarEnum->Current->ToString())){
									rassoEEkarFound = true;
								}

							}
							//aaKarFound

			
								//multifactorial added
								if(aaKarCounter<=1) //multifactorial added
								{
										//multifactorial added
										text = text->Concat(text,ucodeStr);			//multifactorial added
									  
								}	//endif multifact								//multifactorial added
								tempcount=tcount;
								if(aakarNew) {aaKarFound = true;}
								else { aaKarFound = false; }
																
							} //end if

///////////////// Whole Block 
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
		  
			this->rtbMainOutput->Text = text;
			this->createRTB();
			
			
			System::String* notepadOutputFileName = notepadOutputFileName->Concat(this->applicationPath, "\\" ,"output.txt");
			System::IO::StreamWriter* notepadOutSw = new System::IO::StreamWriter(notepadOutputFileName);
			notepadOutSw->Write(text);
			notepadOutSw->Close();
			 
			//OCR::RecognitionForm* rw=new OCR::RecognitionForm();
			//
			////rw->showText(text);
			////rw->MdiParent = this;
			//rw->showText(text);
			//rw->ShowDialog();
			

		 
			// 
			// rtbOutput
			// 
			
			/*this->createRTB();*/
			this->pbOCR->Value = 100;
			this->statusBar1->Text = "Recognition Complete";
			
			/*this->rtbOutput->Text = text;*/
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

 

		 

 
 
 
//Try magnify function
		 
private: void tryMagnify(){
			  
				this->Contrast(10);
				this->ContrastDone=true;
				this->Update();
				
				//mean removal
				//this->MeanRemoval(9);
				//this->meanDone= true;
				//this->Update();

				//Binarization
				this->makeBinary();
				
				//separation
				this->SeparateDone=false;
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
					//mw->MdiParent = this;
					//mw->Show();
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

private: System::Void FormMainWindow_Load(System::Object *  sender, System::EventArgs *  e)
		 {
		 }


int Truncate(int val)
{
	float temp=float(3*val)/2;
	int ttemp=3*val/2;
	float x= temp- float(ttemp);
	//System::Windows::Forms::MessageBox::Show(temp.ToString(),"Threshold Size float value");
	if(x>=0.5)
	{
		ttemp++;
	}
	//System::Windows::Forms::MessageBox::Show(ttemp.ToString(),"Threshold Size After Truncate");
	return ttemp;
}
void TotalUnitCount()
{
	this->totalUnits=0;
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
				if((x2-x1+1)>2)			// Avoiding the "Aakar"
				{
					this->totalUnits++;
				}
			}
		}
	}
}

void WidthStore()
{
	this->TotalUnitCount();
	this->WStore=new int[this->totalUnits];
	int count=0;
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
				int wth=x2-x1+1;
			
				if(wth>2)
				{
					this->WStore[count]=wth;
					count++;
				}
			}
		}
	}
}

int ThresholdSize()
{
	this->sortWidth();
	int sz;
	sz=(this->totalUnits+1)/2;
	int val;
	val= this->WStore[sz];
	val= this->Truncate(val);
	return val;

}
void sortWidth()
{
	int temp;
	for(int i=0;i<this->totalUnits;i++)
	{
		for(int j=i+1;j<this->totalUnits;j++)
		{
			if(this->WStore[i]>this->WStore[j])
			{
				temp=this->WStore[i];
				this->WStore[i]=this->WStore[j];
				this->WStore[j]=temp;
			}
		}
	}
}
 

private: System::Void mnuLoadImage2_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			  //Load image
			  this->openImageFile();
		 }

private: System::Void mnuSaveImage_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 this->saveImageFile();
		 }

private: System::Void mnuFastRecognize_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 
			 if(this->ImageLoaded==true){
				 
				//contrast
				this->Contrast(10);
				this->ContrastDone=true;
				this->Update();
				
				//mean removal
				//this->MeanRemoval(9);
				//this->meanDone= true;
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

private: System::Void mnuExit_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 Application::Exit();
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
				//this->MeanRemoval(9);
				//this->meanDone= true;
				//this->Update();

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

private: System::Void mnuBinarize_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 this->makeBinary();
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

				}
		 }

private: System::Void mnuTrain_Click(System::Object *  sender, System::EventArgs *  e)
		{
			 if(this->rtbOutputShowing == true) this->delRTB();
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
  
		private: void createRTB(){
			  //this function is used to create the richtextbox used producing output after recognition
				this->rtbMainOutput->Visible = true;
			  if(this->rtbOutputShowing == false){
				  
				this->picture_panel->Size = System::Drawing::Size((this->picture_panel->Width),(this->picture_panel->Height-96));
				
				this->rtbOutputShowing = true;
			  }
			  else{
				 return;
			  }
		  }
  private: void delRTB(){
		    //this function is used to remove the unnecessary richtextbox, which was used for producing output after recognition
			
			
			this->picture_panel->Size = System::Drawing::Size((this->picture_panel->Width),(this->picture_panel->Height+96));
			this->rtbMainOutput->Visible = false;
			//this->rtbOutput->Container->Dispose();
			this->rtbOutputShowing = false;
			 
			
		   }

private: System::Void mnuResegment_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			if(this->ImageLoaded && this->BinaryDone && this->SeparateDone)
			{
				Resegment* rsg=new Resegment(im,BinaryDone,ImageLoaded,SeparateDone,BArray,this->numberOfLines,this->Lines,g,this->totalUnits,this->SizeThreshold,this->intLevel,this->HeadBottom);
			//	rsg->PrepareTouchingCharIndex();
				rsg->Do_Segmentation();
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

private: System::Void mnuMeanRemoval_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			
			 if( (this->ImageLoaded==true) ){
				this->MeanRemoval(9);
				this->meanDone= true;
				this->Update();
				
			 }
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

private: System::Void mnuNoiseRemoval_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			  this->makeClear();

		 }
void makeClear()
		 {
			 removeNoise* rN = new removeNoise( this ->BinaryImage, this->ImgArray);
			 this->im  = rN->GetClearImage();
			 this->pictureBox1->Image = im;
		 }


private: void enableCropper(System::Windows::Forms::ContextMenu *ocrCMenu){
			
			System::Windows::Forms::MenuItem *mnuCropSelected = new System::Windows::Forms::MenuItem();
			mnuCropSelected->Text = "Crop Selected";
			mnuCropSelected->Click+= new System::EventHandler(this,mnuCropSelected_Click);
			ocrCMenu->MenuItems->Add(mnuCropSelected);
			this->g->DrawRectangle(Pens::Blue, Rectangle(this->pointX1,this->pointY1,(this->pointX2-this->pointX1),(this->pointY2-this->pointY1)));
			this->imageSelection = true;
			
			
			

}

public: void mnuCropSelected_Click(System::Object *  sender, System::EventArgs *  e){
			
			
			if(this->xMouseDistance < this->im->Width && this->yMouseDistance < this->im->Height){
			
			Bitmap *cropImage1 = new Bitmap( this->xMouseDistance+1,this->yMouseDistance+1,Imaging::PixelFormat::Format24bppRgb);
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
		 this->pictureBox1->Image = cropImage1;
		 this->im = cropImage1;
		 this->ImageLoaded = true;
		 //this->makeBinary();
		 this->BinaryDone = false;
		 this->SeparateDone = false;
		 
		 } // if(this->xMouseDistance < this->im->Width && this->yMouseDistance < this->im->Height)
			else{
				MessageBox::Show("Image cropped must be smaller than the original image ","Crop Again");
			}
	}

private: void find_xy_MouseDistance(System::Windows::Forms::MouseEventArgs *  e){
			
			 //end preserving

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
				} // if(this->x1>this->x2)
                
				if(this->pointX1>this->pointY2)
				{
					temp=this->pointY1;
					this->pointY1=this->pointY2;
					this->pointY2=temp;
				} // if(this->pointY1>this->pointY2) 
                
			 } // if(this->x1 != this->x2 && this->y1 != this->y2)
			 else{
				 this->statusBar1->Text = "Unable to crop";
			 }

			 this->xMouseDistance = System::Math::Abs(this->pointX2 - this->pointX1);
			 this->yMouseDistance = System::Math::Abs(this->pointY2 - this->pointY1);
		 }

 private:	void setResetMenu(bool ImageLoaded, bool BinaryDone,bool SeparateDone){
				 //set reset menus depending upon the flags
					 
						
			 if(ImageLoaded){

				 this->mnuLoadImage->Visible = true;
				 this->mnuLoadImage->Enabled = true;
				 this->mnuMagnification->Enabled = true;
				 
				 
				 this->mnuBinarize->Enabled = true;
				 this->mnuBinarize->DefaultItem = true;
				// this->mnuBinarize->Visible = true;

				 this->mnuFastRecognize->Enabled = true;
				 this->mnuFastRecognize->DefaultItem = true;
				 this->mnuFastRecognize->Visible = true;
				 
				 this->mnuFastRecognize2->Enabled = true;
				 this->mnuFastRecognize2->DefaultItem = true;
				 this->mnuFastRecognize2->Visible = true;
				 
				 			 
				this->mnuContrast->Enabled = true;
				this->mnuMeanRemoval->Enabled = true;
				this->mnuContrastAndBinarize->Enabled =true;

				this->mnuCropper->Enabled = true;
				this->mnuRotate->Enabled = true;
				this->mnuSaveImage->Enabled = true;
				this->mnuDeskew->Enabled = true;
				

				this->mnuAdvanced->Enabled = true;
				this->mnuOCR->Enabled = true;
				this->mnuImage->Enabled = true;

				 if(BinaryDone){
					   this->mnuNoiseRemoval->Enabled = true;
					   this->mnuBinarize->DefaultItem = false;
					   this->mnuFastRecognize->DefaultItem = false;
					   
					 
						this->mnuSeparate->Enabled = true;
						this->mnuSeparate->DefaultItem = true;
						//this->mnuSeparate->Visible = true;

						if(SeparateDone){
							this->mnuBinarize->DefaultItem = false;
							this->mnuSeparate->DefaultItem = false;
							this->mnuFastRecognize->DefaultItem = false;
							
							this->mnuRecognize->Enabled = true;
							this->mnuRecognize->DefaultItem = true;
							this->mnuRecognize2->DefaultItem = true;

							this->mnuTrain->Enabled = true;
						

							this->mnuRecognize->Enabled = true;
							this->mnuRecognize2->Enabled = true;

						} // if(SeparateDone)

						else{
							this->mnuRecognize->Enabled = false;
							this->mnuTrain->Enabled = false;
						}

				 } // if(BinaryDone)
				 else{
					 this->mnuBinarize->Enabled = true;
					 this->mnuBinarize->DefaultItem = true;
					 this->mnuBinarize->Visible = true;

					 this->mnuSeparate->Enabled = false;
					 

				 }

			 } // if(ImageLoaded)

			 else{
				this->mnuLoadImage->Enabled = true;
				this->mnuLoadImage->Visible = true;
				this->mnuLoadImage->DefaultItem = true;
				//
				
				 
				this->mnuNoiseRemoval->Enabled = false;
				this->mnuBinarize->Enabled = false;
				this->mnuContrast->Enabled = false;
				this->mnuMeanRemoval->Enabled = false;
				this->mnuContrastAndBinarize->Enabled =false;
				this->mnuSeparate->Enabled = false;

				this->mnuRecognize->Enabled= false;
				this->mnuTrain->Enabled = false;
				this->mnuRecognize2->Enabled = false;
				this->mnuFastRecognize->Enabled = false;
				this->mnuFastRecognize2->Enabled = false;
				this->mnuMagnification->Enabled = false;

				this->mnuCropper->Enabled = false;
				this->mnuRotate->Enabled = false;
				this->mnuSaveImage->Enabled = false;
				this->mnuDeskew->Enabled = false;
				

				this->mnuAdvanced->Enabled = false;
				this->mnuOCR->Enabled = false;
				this->mnuImage->Enabled = true;

			 }

					 
		 }
private: System::Void picture_panel_MouseUp(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		 {
			 this->pointX2 = e->X;
			 this->pointY2 = e->Y;

			 this->drawContextMenu(e);
			 this->crobPictureBox->Visible = false;
			 
		 }

private: void drawContextMenu(System::Windows::Forms::MouseEventArgs *  e){			
			 try{
	//Left Click
			 if(e->Button == MouseButtons::Left){ //Left Click
					
					System::Windows::Forms::ContextMenu *ocrCMenu = new System::Windows::Forms::ContextMenu();
					System::Windows::Forms::MenuItem  *Cseparator = new System::Windows::Forms::MenuItem();
					Cseparator->Text = "-";
					
					//System::Windows::Forms::MenuItem *mnuNewCropper = new System::Windows::Forms::MenuItem();
					//mnuNewCropper->Text = "New Crop Selected";
					//mnuNewCropper->Click+= new System::EventHandler(this,mnuNewCrop_Click);
					//ocrCMenu->MenuItems->Add(mnuNewCropper);
					

				if(this->ImageLoaded ==false){//Left Click, If image not loaded, load image
	//Create Load Image Menu
					System::Windows::Forms::MenuItem  *CmnuLoadImage = new System::Windows::Forms::MenuItem();
					CmnuLoadImage->Text = "New Image";
					CmnuLoadImage->Click += new System::EventHandler(this, mnuLoadImage2_Click);
					//ocrCMenu->MenuItems->Add(this->mnuLoadImage);
					ocrCMenu->MenuItems->Add(CmnuLoadImage);
					

							
				} // if(e->Button == MouseButtons::Left){if(this->ImageLoaded ==false)
				else{
	//Create Fast Recognize menu
					System::Windows::Forms::MenuItem  *CmnuFastRecognize = new System::Windows::Forms::MenuItem();
					CmnuFastRecognize->Text = "OCR ";
					CmnuFastRecognize->DefaultItem = true;
					CmnuFastRecognize->Click += new System::EventHandler(this, mnuFastRecognize_Click);
	//Create Binarize menu
					if(this->ImageLoaded ==true && this->BinaryDone==false){ //Left click, if image loaded, recognize it

						//Finding the points 
						if(this->pointX1!=this->pointX2){
						this->find_xy_MouseDistance(e);	
						
						this->enableNewCropper(ocrCMenu);
						//System::Windows::Forms::MenuItem *mnuNewCropper = new System::Windows::Forms::MenuItem();
						//mnuNewCropper->Text = "New Crop Selected";
						//mnuNewCropper->Click+= new System::EventHandler(this,mnuNewCrop_Click);
						//ocrCMenu->MenuItems->Add(mnuNewCropper);
						}

						System::Windows::Forms::MenuItem  *CmnuBinarization = new System::Windows::Forms::MenuItem();
						CmnuBinarization->Text = "Binarize ";
						CmnuBinarization->Click += new System::EventHandler(this, mnuBinarize_Click);

						//ocrCMenu->MenuItems->Add(CmnuFastRecognize);
						//ocrCMenu->MenuItems->Add(this->mnuFastRecognize);

						ocrCMenu->MenuItems->Add(CmnuFastRecognize);
						ocrCMenu->MenuItems->Add(CmnuBinarization);
						
						//draw here

						//ocrCMenu->MenuItems->Add(this->mnuBinarize);
						this->mnuLoadImage->Enabled = true;

						//set reset menus
						this->mnuBinarize->Enabled = true;
						this->mnuContrast->Enabled = true;
						this->mnuContrastAndBinarize->Enabled =true;
						this->mnuCropper->Enabled = true;
						this->mnuRotate->Enabled = true;

						this->mnuSeparate->Enabled = false;
						this->mnuRecognize->Enabled= false;
						//this->mnuRecognize2->DefaultItem = true;
						this->mnuTrain->Enabled = false;
						//ENd set reset menus
						
					}
					if(this->ImageLoaded ==true && this->BinaryDone==true){ //Left click, if image loaded, and Binarized, separate it

						//this->mnuStart->MenuItems->Add(this->mnuLoadImage);
					 // Todo: add condition for checking this->xMouseDistance, this->yMouseDistance
					//	MessageBox::Show("ok");
					//	find_xy_MouseDistance
						if(this->pointX1!=this->pointX2){
							this->find_xy_MouseDistance(e);	
							this->enableCropper(ocrCMenu);
						}
						
					

				     // if((this->BinaryDone == true) && (this->xMouseDistance >0) )
						System::Windows::Forms::MenuItem  *CmnuSeparate = new System::Windows::Forms::MenuItem();
						CmnuSeparate->Text = "Separate";
						CmnuSeparate->Click += new System::EventHandler(this, mnuSeparate_Click);
						ocrCMenu->MenuItems->Add(CmnuSeparate);

						//ocrCMenu->MenuItems->Add(this->mnuSeparate);
						//ocrCMenu->MenuItems->Add(this->mnuFastRecognize);
						
						//set reset menus
						this->mnuSeparate->Enabled = true;
						

					}
					

				}//end Else
				if(this->SeparateDone==true){
					ocrCMenu->MenuItems->Add(Cseparator);	
					System::Windows::Forms::MenuItem  *CmnuRecognize = new System::Windows::Forms::MenuItem();
					CmnuRecognize->Text = "Recognize Separated Units";
					CmnuRecognize->Click += new System::EventHandler(this, mnuRecognize_Click);
					ocrCMenu->MenuItems->Add(CmnuRecognize);
					
					System::Windows::Forms::MenuItem  *CmnuTrain = new System::Windows::Forms::MenuItem();
					CmnuTrain->Text = "Train Separated Units";
					CmnuTrain->Click += new System::EventHandler(this, mnuTrain_Click);
					ocrCMenu->MenuItems->Add(CmnuTrain);
					

					

					//ocrCMenu->MenuItems->Add(this->mnuRecognize);
					//ocrCMenu->MenuItems->Add(this->mnuTrain);

						//set reset menus
						this->mnuRecognize->Enabled= true;
						this->mnuTrain->Enabled = true;
						//ENd set reset menus


				}
				

				ocrCMenu->Show(this,System::Drawing::Point(e->X,e->Y));
			} // if(e->Button == MouseButtons::Left) 


		 
		
			 //Right Click
			 if(e->Button == MouseButtons::Right){//Right Click
				 if(this->ImageLoaded==true){ //Rotate Image on right click
					System::Windows::Forms::ContextMenu *ocrCMenu = new System::Windows::Forms::ContextMenu();
					
					System::Windows::Forms::MenuItem  *CmnuLoadImage = new System::Windows::Forms::MenuItem();
					CmnuLoadImage->Text = "New Image";
					CmnuLoadImage->Click += new System::EventHandler(this, mnuLoadImage_Click);
					ocrCMenu->MenuItems->Add(CmnuLoadImage);

					System::Windows::Forms::MenuItem  *CmnuSeparator_rightClick = new System::Windows::Forms::MenuItem();
					CmnuSeparator_rightClick->Text = "-";
					ocrCMenu->MenuItems->Add(CmnuSeparator_rightClick);

					System::Windows::Forms::MenuItem  *CmnuRotateLeft = new System::Windows::Forms::MenuItem();
					CmnuRotateLeft->Text = "Rotate Right ";
					CmnuRotateLeft->Click += new System::EventHandler(this, mnuRotate_Click);
					ocrCMenu->MenuItems->Add(CmnuRotateLeft);
				
					System::Windows::Forms::MenuItem  *CmnuRotateRight = new System::Windows::Forms::MenuItem();
					CmnuRotateRight->Text = "Rotate Left ";
					CmnuRotateRight->Click += new System::EventHandler(this, rotateLeft);
					ocrCMenu->MenuItems->Add(CmnuRotateRight);


					System::Windows::Forms::MenuItem  *CmnuRotateUpright = new System::Windows::Forms::MenuItem();
					CmnuRotateUpright->Text = "Rotate Upright ";
					CmnuRotateUpright->Click += new System::EventHandler(this, rotateUpright);
					ocrCMenu->MenuItems->Add(CmnuRotateUpright);


					//ocrCMenu->MenuItems->Add(this->mnuRotate);
					//ocrCMenu->MenuItems->Add(this->mnuLoadImage);
					ocrCMenu->Show(this,System::Drawing::Point(e->X,e->Y));
				 }
			 } // if(e->Button == MouseButtons::Right)

		 }catch(System::Exception *mouseExceptions){
			// this->statusBar1->Text = "Don\'t mess much with mouse";
			 this->statusBar1->Text = "Left click for options, right Click for new Image";
		 }
		 }

private: System::Void mnuLoadImage_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			  this->openImageFile();
		 }

private: System::Void mnuRotate_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 
			 //Function to rotate clockwise direction by 90 degrees
			 //Button_rotate_right : click event
 
			 im->RotateFlip(RotateFlipType::Rotate90FlipNone);
			 this->pictureBox1->Image = im;
			 if(this->BinaryDone){
				this->resetVariablesAfterRotation();
			 }
		 }
 private: System::Void rotateLeft(System::Object *  sender, System::EventArgs *  e)
		 {
			 
			 //Function to rotate clockwise direction by 90 degrees
			 //Button_rotate_right : click event
 
			 im->RotateFlip(RotateFlipType::Rotate270FlipNone);
			 this->pictureBox1->Image = im;
			 if(this->BinaryDone){
				this->resetVariablesAfterRotation();
			 }
		 }
 private: System::Void rotateUpright(System::Object *  sender, System::EventArgs *  e)
		 {
			 
			 //Function to rotate clockwise direction by 90 degrees
			 //Button_rotate_right : click event
 
			 im->RotateFlip(RotateFlipType::Rotate180FlipNone);
			 this->pictureBox1->Image = im;
			 if(this->BinaryDone){
				this->resetVariablesAfterRotation();
			 }
		 }

 void resetVariablesAfterRotation(){
			 this->ImageLoaded = true;
			 
			 this->BinaryDone=false;
			 this->SeparateDone=false;
			 this->ContrastDone=false;
			 this->meanDone=false;
			 this->deskewDone=false;
			 this->makeBinary();
			 this->BinaryDone = true;

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

private: System::Void pictureBox1_MouseDown(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		 {
			 //reset variables x2 and y2 
			 //if already initialized
			 if(this->pointX1 && this->pointX2){
				this->pointX2 = this->pointX1;
				this->pointY2 = this->pointY1;
			 }
			 //
			 this->pointX1 = e->X;
			 this->pointY1 = e->Y;
			 this->crobPictureBox->Visible = false;
			 
		 }

private: System::Void pictureBox1_MouseUp(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		 {
			 this->pointX2 = e->X;
			 this->pointY2 = e->Y;
			 
			this->drawContextMenu(e);
			 
		 }

private: void drawMyMenu(System::Windows::Forms::MenuItem *abc, String *myMenuText){

			abc->Enabled = true;
			abc->Text = myMenuText;
			//abc->Click += new System::EventHandler(this, mnuSaveImage_Click);
			 //abc->set_siz = System::Drawing::Size(len, wid);
			 //abc->Text = myMenuText;
			 //
						 
		 }
private: System::Void mnuVersionInfo_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 System::Windows::Forms::MessageBox::Show("Build: September 12 2008","Nepali OCR ");
		 }

		 
		 private: System::Void mnuNewCrop_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 if(this->xMouseDistance < this->im->Width && this->yMouseDistance < this->im->Height){

			   

			
			this->im = this->selectedImage;
			this->pictureBox1->Image = im;

			this->ImageLoaded = true;
			this->BinaryDone = false;
			this->SeparateDone = false;
		 
			} // if(this->xMouseDistance < this->im->Width && this->yMouseDistance < this->im->Height)
			else{
				this->statusBar1->Text = "Image Cropped Must be Smaller than the original Image, Pls crop again";
				return;
				//MessageBox::Show("Image cropped must be smaller than the original image ","Crop Again");
			}


 

		 }
		
private: void enableNewCropper(System::Windows::Forms::ContextMenu *ocrCMenu){
			
			 
				
			System::Windows::Forms::MenuItem *mnuNewCropper = new System::Windows::Forms::MenuItem();
			mnuNewCropper->Text = "Crop Selected Image";
			mnuNewCropper->Click+= new System::EventHandler(this,mnuNewCrop_Click);
			ocrCMenu->MenuItems->Add(mnuNewCropper);
			try{
				//System::Windows::Forms::MessageBox::Show(String::Format("Image Size : {0} {1} ",im->Width,im->Height));
				selectedImage = new Bitmap((this->pointX2-this->pointX1),(this->pointY2-this->pointY1));
				Graphics *gr2 = Graphics::FromImage(selectedImage);
				//Graphics.DrawImage(newImage, destRect, srcRect, units);
				gr2->DrawImage(im,(Rectangle(0,0,(this->pointX2-this->pointX1),(this->pointY2-this->pointY1))),(Rectangle(this->pointX1,this->pointY1,(this->pointX2-this->pointX1),(this->pointY2-this->pointY1))),GraphicsUnit::Pixel);
				this->crobPictureBox->Visible = true;
				this->crobPictureBox->BringToFront();
				this->crobPictureBox->Image = selectedImage ;
				this->crobPictureBox->Location = System::Drawing::Point(872,8);
				//MessageBox::Show (String::Format("Height is {0} and Width is {1} ",im->Height.ToString(),im->Width.ToString()),"Original Image" );
				//MessageBox::Show (String::Format("Height is {0} and Width is {1} ",selectedImage->Height.ToString(),selectedImage->Width.ToString()),"Cropped image" );

			}
			catch(System::Exception *ex){
				return;
			}
			this->pictureBox1->Refresh();
			this->g->DrawRectangle(Pens::Black, Rectangle(this->pointX1,this->pointY1,(this->pointX2-this->pointX1),(this->pointY2-this->pointY1)));
			this->imageSelection = true;
					
}
private: System::Void pictureBox1_MouseMove(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		 {
			 //this->crobPictureBox->Visible = true;
			 //this->crobPictureBox->BringToFront();
			 //g->Flush();
			 //this->g->DrawRectangle(Pens::Black, Rectangle(this->pointX1,this->pointY1,(this->pointX2-this->pointX1),(this->pointY2-this->pointY1)));

		 }



private: System::Void rtbMainOutput_MouseUp(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		 {
			 try{
				if(e->Button == MouseButtons::Right){
					
					System::Windows::Forms::ContextMenu *rtbCMenu = new System::Windows::Forms::ContextMenu();
					System::Windows::Forms::MenuItem *rtbExit = new System::Windows::Forms::MenuItem();
					rtbExit->Text = "Hide Output";
					rtbExit->Click+= new System::EventHandler(this,rtbExit_Click);
					rtbCMenu->MenuItems->Add(rtbExit);
					rtbCMenu->Show(this,System::Drawing::Point(e->X,this->picture_panel->Height+e->Y));
				}
			 }
			 catch(System::Exception *ex){
				 return;
			 }
		 }
private: System::Void rtbExit_Click(System::Object *  sender, System::EventArgs *  e){
			 this->delRTB();
			 }
private: System::Void mnuSaveOutput_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 //Output Saving rajesh
			 if(this->rtbOutputShowing){
				// this->saveOutputDialog->Filter = "Text Files (*.txt)";
				 this->saveOutputDialog->RestoreDirectory = true;
				 this->saveOutputDialog->FilterIndex = 1;
				 System::Windows::Forms::DialogResult outputDialog = this->saveOutputDialog->ShowDialog();
				 if(outputDialog == System::Windows::Forms::DialogResult::OK){
					System::String* notepadOutputFileName = this->saveOutputDialog->FileName;
					System::IO::StreamWriter* notepadOutSw = new System::IO::StreamWriter(notepadOutputFileName);
					notepadOutSw->Write(this->rtbMainOutput->Text);
					notepadOutSw->Close();
					}
			 }
		 }

};




}


