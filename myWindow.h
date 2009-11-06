#include "Separate.h"
#include "Line.h"
#include "ThresholedValue.h"
#include "rgbConvert.h"
#include "RecognitionForm.h"
#include "RecognitionProcess.h"

#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace OCR
{
	/// <summary> 
	/// Summary for myWindow
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Othe rwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public __gc class myWindow : public System::Windows::Forms::Form
	{
	public: 
		myWindow(
						Bitmap* im,
						Bitmap* BinaryImage,
						Graphics* g,
						int intLevel,
						int **ImgArray,
						bool **BArray,
						bool **tmpBArray,
						bool BinaryDone,
						bool ImageLoaded,
						bool SeparateDone,
						bool ContrastDone,
						bool meanDone,
						bool deskewDone,
						int numberOfLines,
						Line* Lines, 
						String* applicationPath,
						String* modelTrainDBPath,
						String* scriptFilePath,
						String* characterDBPath,
						System::Collections::SortedList* slForCharacters,
						System::Collections::SortedList* slModelTranscription,	// for storing the model transcriptions
						System::Collections::ArrayList* alModelRec
						
	){

			InitializeComponent();
			this->im = im;
			this->BinaryImage = BinaryImage;
			this->g =g;
			this->intLevel=intLevel;
			this->ImgArray=ImgArray;
			this->BArray=BArray;
			this->tmpBArray=tmpBArray;
			this->BinaryDone=BinaryDone;
			this->ImageLoaded=ImageLoaded;
			this->SeparateDone=SeparateDone;
			this->ContrastDone=ContrastDone;
			this->meanDone=meanDone;
			this->deskewDone=deskewDone;
			this->numberOfLines=numberOfLines;
			this->Lines=Lines;
			this->applicationPath=applicationPath;
			this->modelTrainDBPath=modelTrainDBPath;
			this->scriptFilePath=scriptFilePath;
			this->characterDBPath=characterDBPath;
			this->slForCharacters=slForCharacters;
			this->slModelTranscription=slModelTranscription;	// for storing the model transcriptions
			this->alModelRec=alModelRec;
			this->pictureBox_myWindow->Image = this->im;
			this->bigHeightLabel->Text = this->im->Height.ToString();
			this->bigWidthLabel->Text = this->im->Width.ToString();
			



			
			//application path
			this->applicationPath=Application::StartupPath->ToString();
			int len = this->applicationPath->Length -1;			
			if(this->applicationPath->Substring(len)->Equals("\\"))
			{
				this->applicationPath = this->applicationPath->Substring(0,len);				
			}
			
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
	private: System::Windows::Forms::Panel *  panel1;
	private: System::Windows::Forms::Button *  singleRecog;
	private: System::Windows::Forms::GroupBox *  groupBox1;
	private: System::Windows::Forms::GroupBox *  groupBox2;
	private: System::Windows::Forms::GroupBox *  groupBox3;
	private: System::Windows::Forms::PictureBox *  pictureBox_myWindow;
	private: System::Windows::Forms::Button *  myWindowRecognizeButton;
	private: System::Windows::Forms::Button *  myWindowSeparateButton;
	private: System::Windows::Forms::RichTextBox *  myRTB;
	private: System::Windows::Forms::PictureBox *  pictureBoxSmall;
	private: System::Windows::Forms::Label *  label1;
	private: System::Windows::Forms::Label *  bigHeightLabel;
	private: System::Windows::Forms::Label *  label2;
	private: System::Windows::Forms::Label *  bigWidthLabel;
	private: System::Windows::Forms::Label *  label4;
	private: System::Windows::Forms::Label *  smallHeightLabel;
	private: System::Windows::Forms::Label *  smallWidthLabel;
	private: System::Windows::Forms::Label *  label3;
	private: System::Windows::Forms::Button *  nextButton;
	private: System::Windows::Forms::Button *  exitButton;
	private: System::Windows::Forms::Label *  label5;
	private: System::Windows::Forms::Label *  avgWidthLabel;
	private: System::Windows::Forms::Label *  label6;
	private: System::Windows::Forms::Label *  avgHeightLabel;

	private: Bitmap* im;
	private: Bitmap* BinaryImage;

	bool** BinArray;

	private: Graphics* g;
	private: int intLevel;
	private: int **ImgArray;

	int **ImageArray;

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

	Line* LineInfo;
	int lineCount;
	static int lineno=0;
	static int wordno=0;
	static int charno=0;
	private: int x1,x2,y1,y2;
	Bitmap* cropImage;
	
		
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
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(OCR::myWindow));
			this->panel1 = new System::Windows::Forms::Panel();
			this->pictureBox_myWindow = new System::Windows::Forms::PictureBox();
			this->groupBox1 = new System::Windows::Forms::GroupBox();
			this->bigWidthLabel = new System::Windows::Forms::Label();
			this->label2 = new System::Windows::Forms::Label();
			this->bigHeightLabel = new System::Windows::Forms::Label();
			this->label1 = new System::Windows::Forms::Label();
			this->groupBox2 = new System::Windows::Forms::GroupBox();
			this->singleRecog = new System::Windows::Forms::Button();
			this->myWindowRecognizeButton = new System::Windows::Forms::Button();
			this->myWindowSeparateButton = new System::Windows::Forms::Button();
			this->avgHeightLabel = new System::Windows::Forms::Label();
			this->label6 = new System::Windows::Forms::Label();
			this->avgWidthLabel = new System::Windows::Forms::Label();
			this->label5 = new System::Windows::Forms::Label();
			this->exitButton = new System::Windows::Forms::Button();
			this->nextButton = new System::Windows::Forms::Button();
			this->label3 = new System::Windows::Forms::Label();
			this->smallWidthLabel = new System::Windows::Forms::Label();
			this->smallHeightLabel = new System::Windows::Forms::Label();
			this->label4 = new System::Windows::Forms::Label();
			this->pictureBoxSmall = new System::Windows::Forms::PictureBox();
			this->groupBox3 = new System::Windows::Forms::GroupBox();
			this->myRTB = new System::Windows::Forms::RichTextBox();
			this->panel1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->AutoScroll = true;
			this->panel1->Controls->Add(this->pictureBox_myWindow);
			this->panel1->Location = System::Drawing::Point(8, 80);
			this->panel1->Name = S"panel1";
			this->panel1->Size = System::Drawing::Size(312, 360);
			this->panel1->TabIndex = 0;
			// 
			// pictureBox_myWindow
			// 
			this->pictureBox_myWindow->Location = System::Drawing::Point(56, 32);
			this->pictureBox_myWindow->Name = S"pictureBox_myWindow";
			this->pictureBox_myWindow->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox_myWindow->TabIndex = 0;
			this->pictureBox_myWindow->TabStop = false;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->bigWidthLabel);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->bigHeightLabel);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->panel1);
			this->groupBox1->Location = System::Drawing::Point(24, 24);
			this->groupBox1->Name = S"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(336, 448);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = S"Input Image";
			// 
			// bigWidthLabel
			// 
			this->bigWidthLabel->Location = System::Drawing::Point(136, 48);
			this->bigWidthLabel->Name = S"bigWidthLabel";
			this->bigWidthLabel->Size = System::Drawing::Size(120, 24);
			this->bigWidthLabel->TabIndex = 4;
			// 
			// label2
			// 
			this->label2->Location = System::Drawing::Point(24, 48);
			this->label2->Name = S"label2";
			this->label2->Size = System::Drawing::Size(88, 24);
			this->label2->TabIndex = 3;
			this->label2->Text = S"Image Width";
			// 
			// bigHeightLabel
			// 
			this->bigHeightLabel->Location = System::Drawing::Point(136, 24);
			this->bigHeightLabel->Name = S"bigHeightLabel";
			this->bigHeightLabel->Size = System::Drawing::Size(120, 16);
			this->bigHeightLabel->TabIndex = 2;
			// 
			// label1
			// 
			this->label1->Location = System::Drawing::Point(24, 24);
			this->label1->Name = S"label1";
			this->label1->Size = System::Drawing::Size(96, 24);
			this->label1->TabIndex = 1;
			this->label1->Text = S"Image Height";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->singleRecog);
			this->groupBox2->Controls->Add(this->myWindowRecognizeButton);
			this->groupBox2->Controls->Add(this->myWindowSeparateButton);
			this->groupBox2->Controls->Add(this->avgHeightLabel);
			this->groupBox2->Controls->Add(this->label6);
			this->groupBox2->Controls->Add(this->avgWidthLabel);
			this->groupBox2->Controls->Add(this->label5);
			this->groupBox2->Controls->Add(this->exitButton);
			this->groupBox2->Controls->Add(this->nextButton);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->smallWidthLabel);
			this->groupBox2->Controls->Add(this->smallHeightLabel);
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Controls->Add(this->pictureBoxSmall);
			this->groupBox2->Location = System::Drawing::Point(368, 32);
			this->groupBox2->Name = S"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(280, 448);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = S"Sliced Single Image";
			// 
			// singleRecog
			// 
			this->singleRecog->Location = System::Drawing::Point(160, 304);
			this->singleRecog->Name = S"singleRecog";
			this->singleRecog->Size = System::Drawing::Size(88, 24);
			this->singleRecog->TabIndex = 13;
			this->singleRecog->Text = S"Single Recog";
			this->singleRecog->Click += new System::EventHandler(this, singleRecog_Click);
			// 
			// myWindowRecognizeButton
			// 
			this->myWindowRecognizeButton->Location = System::Drawing::Point(152, 272);
			this->myWindowRecognizeButton->Name = S"myWindowRecognizeButton";
			this->myWindowRecognizeButton->Size = System::Drawing::Size(80, 24);
			this->myWindowRecognizeButton->TabIndex = 12;
			this->myWindowRecognizeButton->Text = S"RecognizeAll";
			this->myWindowRecognizeButton->Click += new System::EventHandler(this, myWindowRecognizeButton_Click);
			// 
			// myWindowSeparateButton
			// 
			this->myWindowSeparateButton->Location = System::Drawing::Point(48, 296);
			this->myWindowSeparateButton->Name = S"myWindowSeparateButton";
			this->myWindowSeparateButton->Size = System::Drawing::Size(72, 48);
			this->myWindowSeparateButton->TabIndex = 11;
			this->myWindowSeparateButton->Text = S"Separate";
			this->myWindowSeparateButton->Click += new System::EventHandler(this, myWindowSeparateButton_Click);
			// 
			// avgHeightLabel
			// 
			this->avgHeightLabel->Location = System::Drawing::Point(120, 112);
			this->avgHeightLabel->Name = S"avgHeightLabel";
			this->avgHeightLabel->Size = System::Drawing::Size(128, 24);
			this->avgHeightLabel->TabIndex = 10;
			// 
			// label6
			// 
			this->label6->Location = System::Drawing::Point(17, 112);
			this->label6->Name = S"label6";
			this->label6->Size = System::Drawing::Size(88, 24);
			this->label6->TabIndex = 9;
			this->label6->Text = S"Average Height";
			// 
			// avgWidthLabel
			// 
			this->avgWidthLabel->Location = System::Drawing::Point(120, 88);
			this->avgWidthLabel->Name = S"avgWidthLabel";
			this->avgWidthLabel->Size = System::Drawing::Size(128, 24);
			this->avgWidthLabel->TabIndex = 8;
			// 
			// label5
			// 
			this->label5->Location = System::Drawing::Point(16, 88);
			this->label5->Name = S"label5";
			this->label5->Size = System::Drawing::Size(80, 24);
			this->label5->TabIndex = 7;
			this->label5->Text = S"Average width";
			// 
			// exitButton
			// 
			this->exitButton->Location = System::Drawing::Point(152, 344);
			this->exitButton->Name = S"exitButton";
			this->exitButton->Size = System::Drawing::Size(112, 72);
			this->exitButton->TabIndex = 6;
			this->exitButton->Text = S"Exit";
			this->exitButton->Click += new System::EventHandler(this, exitButton_Click);
			// 
			// nextButton
			// 
			this->nextButton->Location = System::Drawing::Point(48, 360);
			this->nextButton->Name = S"nextButton";
			this->nextButton->Size = System::Drawing::Size(72, 48);
			this->nextButton->TabIndex = 5;
			this->nextButton->Text = S"Next";
			this->nextButton->Click += new System::EventHandler(this, nextButton_Click);
			// 
			// label3
			// 
			this->label3->Location = System::Drawing::Point(34, 56);
			this->label3->Name = S"label3";
			this->label3->Size = System::Drawing::Size(56, 16);
			this->label3->TabIndex = 4;
			this->label3->Text = S"Width";
			// 
			// smallWidthLabel
			// 
			this->smallWidthLabel->Location = System::Drawing::Point(120, 56);
			this->smallWidthLabel->Name = S"smallWidthLabel";
			this->smallWidthLabel->Size = System::Drawing::Size(128, 16);
			this->smallWidthLabel->TabIndex = 3;
			// 
			// smallHeightLabel
			// 
			this->smallHeightLabel->Location = System::Drawing::Point(120, 24);
			this->smallHeightLabel->Name = S"smallHeightLabel";
			this->smallHeightLabel->Size = System::Drawing::Size(120, 16);
			this->smallHeightLabel->TabIndex = 2;
			// 
			// label4
			// 
			this->label4->Location = System::Drawing::Point(32, 24);
			this->label4->Name = S"label4";
			this->label4->Size = System::Drawing::Size(56, 16);
			this->label4->TabIndex = 1;
			this->label4->Text = S"Height";
			// 
			// pictureBoxSmall
			// 
			this->pictureBoxSmall->Location = System::Drawing::Point(80, 176);
			this->pictureBoxSmall->Name = S"pictureBoxSmall";
			this->pictureBoxSmall->TabIndex = 0;
			this->pictureBoxSmall->TabStop = false;
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->myRTB);
			this->groupBox3->Location = System::Drawing::Point(656, 32);
			this->groupBox3->Name = S"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(240, 448);
			this->groupBox3->TabIndex = 2;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = S"Logs";
			// 
			// myRTB
			// 
			this->myRTB->Location = System::Drawing::Point(16, 40);
			this->myRTB->Name = S"myRTB";
			this->myRTB->Size = System::Drawing::Size(208, 392);
			this->myRTB->TabIndex = 0;
			this->myRTB->Text = S"";
			// 
			// myWindow
			// 
			this->AllowDrop = true;
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(912, 494);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->Name = S"myWindow";
			this->Text = S"Image Viewer";
			this->Load += new System::EventHandler(this, myWindow_Load);
			this->panel1->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->groupBox3->ResumeLayout(false);
			this->ResumeLayout(false);

		}		



	
//	private: void separateChar();
//`	private: void separate();

	private: System::Void exitButton_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 this->Hide();
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
		 }//End LoadFromFile

	private: void makeBinary()
			 {
				 if(this->ImageLoaded)
				 {
 				
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
						this->pictureBox_myWindow->Image = this->BinaryImage;
						
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
	}// end of function MakeBinary

		 private: void separateChar()
				 {
					 float myPenSum=0;
					 int myPenCount = 0;
					 
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
														 myPenSum+=(y2-y1)/(x2-x1);
														 myPenCount++;
														 //System::Windows::Forms::MessageBox::Show((myPenSum/myPenCount).ToString(),"Transformation Factor");
														g->DrawLine(p,x1,y1,x1,y2);
														g->DrawLine(p,x2,y1,x2,y2);
													}
											}
									}

				 }//End SeparateChar
	private: void separate()
				 {
					 this->tmpBArray=new bool*[im->Height]; 
					  
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
				 }//End Separate
	private: System::Void nextButton_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 if(charno<this->LineInfo[lineno].Words[wordno].getTotalUnit()-1)
				 {
					 this->myRTB->AppendText("\n--------within first if ---total units ----------");
					 this->myRTB->AppendText(this->LineInfo[lineno].Words[wordno].getTotalUnit().ToString());

					 this->charno++;
 				 

				 }
				 else
				 {
					 //this->charno=0;
					 if(wordno< this->LineInfo[lineno].getTotalWord()-1)
					 {
						 this->wordno++;
						 this->charno=0;
						 this->myRTB->AppendText("\n else if -----------total units ----------");
						 this->myRTB->AppendText(this->LineInfo[lineno].Words[wordno].getTotalUnit().ToString());
						 
							}


					 else
					 {
						 this->wordno=0;
						 this->charno=0;
						 if(lineno<this->lineCount-1)
						 {
							 this->lineno++;
							 this->myRTB->AppendText("------else else if -----total units ----------");
							 this->myRTB->AppendText(this->LineInfo[lineno].Words[wordno].getTotalUnit().ToString());
 							 
									}
						 else
						 {
							 this->lineno=0;
							 this->wordno=0;
							 this->charno=0;
							 this->myRTB->AppendText("------else else else -----total units ----------");
							 this->myRTB->AppendText(this->LineInfo[lineno].Words[wordno].getTotalUnit().ToString());
							
						 }
					 }
				 }
				 this->display(this->lineno,this->wordno,this->charno);
				 this->Update();


				 this->myRTB->AppendText("\n x1:");
				 this->myRTB->AppendText(x1.ToString());
				 this->myRTB->AppendText(" x2:");
				 this->myRTB->AppendText(x2.ToString());
				 this->myRTB->AppendText(" y1:");
				 this->myRTB->AppendText(y1.ToString());
				 this->myRTB->AppendText(" y2:");
				 this->myRTB->AppendText(y2.ToString());
				 this->myRTB->AppendText(" Charno:");
				 this->myRTB->AppendText(this->charno.ToString());
				 x1=this->LineInfo[lineno].Words[wordno].Units[charno].getStartColumn(); //Equivalent to :: left_x
				 x2=this->LineInfo[lineno].Words[wordno].Units[charno].getEndColumn();	//Equivalent to :: right_x
				 y1=this->LineInfo[lineno].getStartRow();		//Equivalent to :: top_y
				 y2=this->LineInfo[lineno].getEndRow();	
				// singleRecognize(x1,x2,y1,y2,1) ;

				 //Cuzz charno starts from 0, we need to increment charno by 1, before recognizing
				// singleRecognize(x1,x2,y1,y2,charno) ;
				
				 
				 
			 
		 }
	public: 
		void defineVar(int** ImgArray,bool** BArray,Line* Lines,int numberOfLines)
			{
				this->ImageArray=ImgArray;
				this->BinArray=BArray;
				this->LineInfo=Lines;
				this->lineCount=numberOfLines;
				this->display(this->lineno,this->wordno,this->charno);
				
			}
 	void display(int lineno,int wordno,int charno)
		{
			
			x1=this->LineInfo[lineno].Words[wordno].Units[charno].getStartColumn(); //Equivalent to :: left_x
			x2=this->LineInfo[lineno].Words[wordno].Units[charno].getEndColumn();	//Equivalent to :: right_x
			y1=this->LineInfo[lineno].getStartRow();		//Equivalent to :: top_y
			y2=this->LineInfo[lineno].getEndRow();			 //Equivalent to :: bottom_y
			
			int xsize=x2-x1+1;
			int ysize=y2-y1+1;
			 
			this->cropImage=new Bitmap(xsize,ysize,Imaging::PixelFormat::Format24bppRgb);
			
			for(int i=y1;i<=y2;i++)//traverse throughy
			{
				for(int j=x1;j<=x2;j++)//traverse through x
				{
					if(this->BinArray[i][j])
					{
						 
						this->cropImage->SetPixel(j-x1,i-y1,Color::White);
					}
					else
					{
						this->cropImage->SetPixel(j-x1,i-y1,Color::Black);
					}
			    }
			}
			this->pictureBoxSmall->Image=cropImage;
			this->smallHeightLabel->Text = this->cropImage->Height.ToString();
			this->smallWidthLabel->Text = this->cropImage->Width.ToString();
			//this->singleRecognize(x1,x2,y1,y2,0);
		}
	
	private: void singleRecognize(int left_x,int right_x,int top_y,int bottom_y,int charno){
				 //Assumption: int left_x  :::word start
				 //int right_x				::: word end
				 //int top_y ~ equivalent to :: int top_x :::Line start
				 //int bottom_y ~ equivalent to :: int bottom_y :::Line end
			
			System::String* wordToRec;
			RecognitionProcess* rp = new RecognitionProcess(this->applicationPath,this->ImgArray);
			
			System::String* dirOfRecFile = rp->recognitionTempFileDir;
			this->slModelTranscription = rp->LoadModelTranscriptions(this->modelTrainDBPath);
			rp->SetImageBoundary(left_x,right_x,top_y,bottom_y);
			int totalUnit =charno;
			
			//rp->PrepareWordData(wordToRec);
			//Assumption : totalunit for single recognize is 1

				wordToRec = wordToRec->Concat(dirOfRecFile,totalUnit.ToString(),".txt");	
			
				if(this->SeparateDone){			
				rp->PrepareWordData(wordToRec);
				}
				else{
					System::Windows::Forms::MessageBox::Show("The words are not separated. \n Cannot Process for recognition","Error");
					exit(0);
				}

				try
				{
					System::IO::StreamWriter* sw = System::IO::File::AppendText(rp->scriptFilePath);	
					for(int i=1;i<=totalUnit;i++)	
					{
						System::String* tmp=tmp->Concat((String*)"\"",dirOfRecFile,i.ToString(),(String*)".txt",(String*)"\"");
						sw->WriteLine(tmp);
						sw->Flush();
					}
					sw->Close();
				}
				catch(System::Exception* ex)
				{
					System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"Failed to prepare the script file!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
					exit(0);
				}
			
				this->alModelRec = rp->RecognizeByHTK();
				this->ProvideOutput();
				System::IO::File::Delete(rp->scriptFilePath);
				for(int i=1;i<=totalUnit;i++)	
				{
					System::String* tmp=tmp->Concat(dirOfRecFile,i.ToString(),".txt");
					System::IO::File::Delete(tmp);
				}

			
			 

}	 //End singleRecognize
	
	private: void Recognize()
		{		 
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
									left_x = this->Lines[i].Words[j].Units[k].getStartColumn();//word start
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
							}
							sw->Close();
						}
						catch(System::Exception* ex)
						{
							System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"Failed to prepare the script file!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
							exit(0);
						}
						this->alModelRec = rp->RecognizeByHTK();
						this->ProvideOutput();
						System::IO::File::Delete(rp->scriptFilePath);
						for(int i=1;i<=totalUnit;i++)	
						{
							System::String* tmp=tmp->Concat(dirOfRecFile,i.ToString(),".txt");
							System::IO::File::Delete(tmp);
						}
		}//End Function Recognize
	private: void ProvideOutput()
		 {
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
		 }//End ProvideOutput

private: System::Void myWindowSeparateButton_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 this->makeBinary();
			 this->separate();
		 }//End myWindowSeparateButton_Click

private: System::Void myWindowRecognizeButton_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 this->Recognize();
		 }//End myWindowRecognizeButton_Click

private: System::Void singleRecog_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 singleRecognize(x1,x2,y1,y2,1) ;
		 }

private: System::Void myWindow_Load(System::Object *  sender, System::EventArgs *  e)
		 {
		 }

};
}