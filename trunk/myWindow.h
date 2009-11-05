#include "Line.h"
#include "RecognitionProcess.h"
#include "RecognitionForm.h"
#include "ThresholedValue.h"
//#include "Separate.h"


//#include "Separate.h"
//#include "myWindowSeparate.h"

#include "rgbConvert.h"

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
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public __gc class myWindow : public System::Windows::Forms::Form
	{
	public: 
		
		//myWindow(void)
		myWindow(System::Drawing::Bitmap *receivedImageFromMainForm )
		{
			this->imageReceivedToForm = receivedImageFromMainForm;
			InitializeComponent();
			
			//display the image
			this->pictureBox_myWindow->Image = receivedImageFromMainForm;
			//removed image that was passed in default

			label1->Text = receivedImageFromMainForm->Height.ToString();
			label7->Text = receivedImageFromMainForm->Width.ToString();
			
		

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
	private: System::Windows::Forms::Panel *  panel_myWindow;
	private: System::Windows::Forms::PictureBox *  pictureBox_myWindow;
	
	private: 
		bool** BinArray;
		int **ImageArray;
		
		Line* LineInfo;
		int lineCount;
		static int lineno=0;
		static int wordno=0;
		static int charno=0;
		private: int x1,x2,y1,y2;
		Bitmap* cropImage;
		private: int **ImgArray;
		private: int intLevel;
		Bitmap* imageReceivedToForm;
		String* meroText;
		private: static float counterForAveragingHeightWeight=0;

	private: int numberOfLines;
	private: Line* Lines; 

		private: String* applicationPath;
				 String* modelTrainDBPath;
                 String* scriptFilePath;
                 String* characterDBPath;
	 	
	private: System::Collections::SortedList* slForCharacters;
	private: System::Collections::SortedList* slModelTranscription;	// for storing the model transcriptions
	private: System::Collections::ArrayList* alModelRec;			// for models that already recognized
	


	private: System::Windows::Forms::PictureBox *  pictureBox1;
	private: System::Windows::Forms::GroupBox *  groupBox1;
	private: System::Windows::Forms::GroupBox *  groupBox2;
	private: System::Windows::Forms::Label *  label1;
	private: System::Windows::Forms::Label *  label2;
	private: System::Windows::Forms::Label *  label3;
	private: System::Windows::Forms::Label *  label4;
	private: System::Windows::Forms::Label *  label5;
	private: System::Windows::Forms::Label *  label6;
	private: System::Windows::Forms::Label *  label8;
	private: System::Windows::Forms::Label *  label7;
	private: System::Windows::Forms::Button *  button1;
	private: System::Windows::Forms::Button *  button2;
	private: System::Windows::Forms::Label *  label9;
	private: System::Windows::Forms::Label *  label10;
	private: System::Windows::Forms::Label *  label11;
	private: System::Windows::Forms::Label *  label12;
	private: System::Windows::Forms::Button *  avgButton;
	private: System::Windows::Forms::Label *  label13;
	private: System::Windows::Forms::RichTextBox *  myRTB;






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
			this->panel_myWindow = new System::Windows::Forms::Panel();
			this->myRTB = new System::Windows::Forms::RichTextBox();
			this->groupBox2 = new System::Windows::Forms::GroupBox();
			this->label12 = new System::Windows::Forms::Label();
			this->label11 = new System::Windows::Forms::Label();
			this->label10 = new System::Windows::Forms::Label();
			this->label9 = new System::Windows::Forms::Label();
			this->button2 = new System::Windows::Forms::Button();
			this->button1 = new System::Windows::Forms::Button();
			this->label8 = new System::Windows::Forms::Label();
			this->label6 = new System::Windows::Forms::Label();
			this->label4 = new System::Windows::Forms::Label();
			this->label2 = new System::Windows::Forms::Label();
			this->pictureBox1 = new System::Windows::Forms::PictureBox();
			this->groupBox1 = new System::Windows::Forms::GroupBox();
			this->label13 = new System::Windows::Forms::Label();
			this->avgButton = new System::Windows::Forms::Button();
			this->label7 = new System::Windows::Forms::Label();
			this->label5 = new System::Windows::Forms::Label();
			this->label3 = new System::Windows::Forms::Label();
			this->pictureBox_myWindow = new System::Windows::Forms::PictureBox();
			this->label1 = new System::Windows::Forms::Label();
			this->panel_myWindow->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel_myWindow
			// 
			this->panel_myWindow->AutoScroll = true;
			this->panel_myWindow->Controls->Add(this->myRTB);
			this->panel_myWindow->Controls->Add(this->groupBox2);
			this->panel_myWindow->Controls->Add(this->groupBox1);
			this->panel_myWindow->Location = System::Drawing::Point(8, 16);
			this->panel_myWindow->Name = S"panel_myWindow";
			this->panel_myWindow->Size = System::Drawing::Size(928, 456);
			this->panel_myWindow->TabIndex = 1;
			// 
			// myRTB
			// 
			this->myRTB->Location = System::Drawing::Point(656, 32);
			this->myRTB->Name = S"myRTB";
			this->myRTB->Size = System::Drawing::Size(256, 400);
			this->myRTB->TabIndex = 6;
			this->myRTB->Text = S"";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->label12);
			this->groupBox2->Controls->Add(this->label11);
			this->groupBox2->Controls->Add(this->label10);
			this->groupBox2->Controls->Add(this->label9);
			this->groupBox2->Controls->Add(this->button2);
			this->groupBox2->Controls->Add(this->button1);
			this->groupBox2->Controls->Add(this->label8);
			this->groupBox2->Controls->Add(this->label6);
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Controls->Add(this->pictureBox1);
			this->groupBox2->Location = System::Drawing::Point(312, 16);
			this->groupBox2->Name = S"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(312, 384);
			this->groupBox2->TabIndex = 5;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = S"Sliced single Image";
			// 
			// label12
			// 
			this->label12->Location = System::Drawing::Point(176, 144);
			this->label12->Name = S"label12";
			this->label12->TabIndex = 11;
			// 
			// label11
			// 
			this->label11->Location = System::Drawing::Point(56, 144);
			this->label11->Name = S"label11";
			this->label11->TabIndex = 10;
			this->label11->Text = S"Avg Height";
			// 
			// label10
			// 
			this->label10->Location = System::Drawing::Point(176, 104);
			this->label10->Name = S"label10";
			this->label10->TabIndex = 9;
			// 
			// label9
			// 
			this->label9->Location = System::Drawing::Point(56, 104);
			this->label9->Name = S"label9";
			this->label9->Size = System::Drawing::Size(96, 16);
			this->label9->TabIndex = 8;
			this->label9->Text = S"Avg width";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(208, 216);
			this->button2->Name = S"button2";
			this->button2->Size = System::Drawing::Size(96, 96);
			this->button2->TabIndex = 7;
			this->button2->Text = S"Exit";
			this->button2->Click += new System::EventHandler(this, button2_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(96, 264);
			this->button1->Name = S"button1";
			this->button1->Size = System::Drawing::Size(72, 40);
			this->button1->TabIndex = 6;
			this->button1->Text = S"Next";
			this->button1->Click += new System::EventHandler(this, button1_Click);
			// 
			// label8
			// 
			this->label8->Location = System::Drawing::Point(176, 64);
			this->label8->Name = S"label8";
			this->label8->Size = System::Drawing::Size(104, 24);
			this->label8->TabIndex = 5;
			// 
			// label6
			// 
			this->label6->Location = System::Drawing::Point(56, 72);
			this->label6->Name = S"label6";
			this->label6->Size = System::Drawing::Size(72, 24);
			this->label6->TabIndex = 4;
			this->label6->Text = S"Image width";
			// 
			// label4
			// 
			this->label4->Location = System::Drawing::Point(56, 40);
			this->label4->Name = S"label4";
			this->label4->Size = System::Drawing::Size(80, 16);
			this->label4->TabIndex = 3;
			this->label4->Text = S"image height";
			// 
			// label2
			// 
			this->label2->Location = System::Drawing::Point(176, 40);
			this->label2->Name = S"label2";
			this->label2->Size = System::Drawing::Size(104, 16);
			this->label2->TabIndex = 2;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(56, 200);
			this->pictureBox1->Name = S"pictureBox1";
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label13);
			this->groupBox1->Controls->Add(this->avgButton);
			this->groupBox1->Controls->Add(this->label7);
			this->groupBox1->Controls->Add(this->label5);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->pictureBox_myWindow);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Location = System::Drawing::Point(16, 16);
			this->groupBox1->Name = S"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(280, 384);
			this->groupBox1->TabIndex = 4;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = S"Input Image ";
			// 
			// label13
			// 
			this->label13->Location = System::Drawing::Point(32, 280);
			this->label13->Name = S"label13";
			this->label13->Size = System::Drawing::Size(112, 32);
			this->label13->TabIndex = 7;
			// 
			// avgButton
			// 
			this->avgButton->Location = System::Drawing::Point(104, 336);
			this->avgButton->Name = S"avgButton";
			this->avgButton->Size = System::Drawing::Size(72, 24);
			this->avgButton->TabIndex = 6;
			this->avgButton->Text = S"Average";
			this->avgButton->Click += new System::EventHandler(this, avgButton_Click);
			// 
			// label7
			// 
			this->label7->Location = System::Drawing::Point(128, 48);
			this->label7->Name = S"label7";
			this->label7->Size = System::Drawing::Size(88, 16);
			this->label7->TabIndex = 5;
			// 
			// label5
			// 
			this->label5->Location = System::Drawing::Point(16, 48);
			this->label5->Name = S"label5";
			this->label5->Size = System::Drawing::Size(88, 24);
			this->label5->TabIndex = 4;
			this->label5->Text = S"Image width";
			// 
			// label3
			// 
			this->label3->Location = System::Drawing::Point(16, 16);
			this->label3->Name = S"label3";
			this->label3->Size = System::Drawing::Size(100, 16);
			this->label3->TabIndex = 3;
			this->label3->Text = S"image height";
			// 
			// pictureBox_myWindow
			// 
			this->pictureBox_myWindow->Location = System::Drawing::Point(24, 104);
			this->pictureBox_myWindow->Name = S"pictureBox_myWindow";
			this->pictureBox_myWindow->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox_myWindow->TabIndex = 0;
			this->pictureBox_myWindow->TabStop = false;
			// 
			// label1
			// 
			this->label1->Location = System::Drawing::Point(128, 16);
			this->label1->Name = S"label1";
			this->label1->Size = System::Drawing::Size(72, 16);
			this->label1->TabIndex = 2;
			// 
			// myWindow
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(944, 478);
			this->Controls->Add(this->panel_myWindow);
			this->Name = S"myWindow";
			this->Text = S"Image Viewer";
			this->panel_myWindow->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->ResumeLayout(false);

		}		
	public:
		void defineVar(int** ImgArray,bool** BArray,Line* Lines,int numberOfLines)
			{
				//System::Windows::Forms::MessageBox::Show( numberOfLines.ToString(),"number of lines");
				this->ImageArray=ImgArray;
				this->BinArray=BArray;
				this->LineInfo=Lines;
				this->lineCount=numberOfLines;
				this->numberOfLines = numberOfLines;
				this->display(this->lineno,this->wordno,this->charno);
//				this->LoadComboBoxFromFile();
			}


	private:
	void display(int lineno,int wordno,int charno)
		{
			static float widthCount=0;
			static float heightCount=0;
			static float avgWidthCount=0;
			static float avgHeightCount=0;
			

			x1=this->LineInfo[lineno].Words[wordno].Units[charno].getStartColumn();
			x2=this->LineInfo[lineno].Words[wordno].Units[charno].getEndColumn();
			y1=this->LineInfo[lineno].getStartRow();
			y2=this->LineInfo[lineno].getEndRow();
			
			/*



			[x1,y1]-------[x2,y1]
				|			|
				|			|
				|		(ysize)
				|			|
			[x1,y2]-(xsize)-[x2,y2] 

			x1 = startColumn (unit)
			x2 = endColumn	 (unit)
			y1 = startRow  (line)
			y2 = EndRow		(line)

			*/


			 //System::Windows::Forms::MessageBox::Show("Please Load the image first","Image not loaded");

			///System::Windows::Forms::MessageBox::Show(x1.ToString(),"x1");
			///System::Windows::Forms::MessageBox::Show(x2.ToString(),"x2");
			///System::Windows::Forms::MessageBox::Show(y1.ToString(),"y1");
			///System::Windows::Forms::MessageBox::Show(y2.ToString(),"y2");
			int xsize=x2-x1+1;
			int ysize=y2-y1+1;
			
			//xsize=400;
			//ysize=400;
			
			this->cropImage=new Bitmap(xsize,ysize,Imaging::PixelFormat::Format24bppRgb);
			
			for(int i=y1;i<=y2;i++)//traverse through y
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
			this->pictureBox1->Image=cropImage;
			 
			
			this->label2->Text = cropImage->Height.ToString();
			this->label8->Text = cropImage->Width.ToString();
			widthCount +=cropImage->Height;
			heightCount +=cropImage->Width;
			counterForAveragingHeightWeight++;
		
			//Now the same values will be the average
			avgWidthCount=widthCount/counterForAveragingHeightWeight;
			avgHeightCount=heightCount/counterForAveragingHeightWeight;
			
			this->label10->Text = avgWidthCount.ToString();
			this->meroText= this->meroText->Concat(this->meroText,"\n Average width : ",avgWidthCount.ToString());
			

			this->label12->Text = avgHeightCount.ToString();
			this->meroText= this->meroText->Concat(this->meroText,"\n Average Height : ",avgHeightCount.ToString());
			
		
			this->label13->Text = counterForAveragingHeightWeight.ToString();

			//this->myRTB->AppendText("\n ");
			this->myRTB->AppendText(this->meroText);


		}


	
	private: System::Void button2_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 this->Hide();
			 }

private: System::Void button1_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			this->meroText= this->meroText->Concat(this->meroText,"\n");
			
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
				 this->Update;
		 }
	
/* ///	Commented sept14
	private:
		void recognize(){//ImageArray
							
						//int** whymakeBinary;
						this->smallBinary();			
						
						
						RecognitionProcess* rp = new RecognitionProcess(this->applicationPath,ImgArray);
						
						//RecognitionProcess* rp = new RecognitionProcess(this->applicationPath,this->ImageArray);
						//from:: //	RecognitionProcess* rp = new RecognitionProcess(this->applicationPath,this->ImgArray);

						// load the transcription of the models
						this->slModelTranscription = rp->LoadModelTranscriptions(this->modelTrainDBPath);
						
						

						int lineCount = this->numberOfLines;
						
						if(this->ImgArray){
							System::Windows::Forms::MessageBox::Show(this->numberOfLines.ToString(),"image array exists");
						}
						int wordCount = 0;
						int totalUnit = 0;
						int unitCount = 0;
						int left_x,right_x,top_y,bottom_y;
						System::String* wordToRec;
						System::String* dirOfRecFile = rp->recognitionTempFileDir;

						for(int i=0; i<lineCount;i++)
						{		
							
							System::Windows::Forms::MessageBox::Show(i.ToString(),"I");
							
							top_y = this->Lines[i].getStartRow();//line start
							bottom_y = this->Lines[i].getEndRow();//line end

							wordCount = this->Lines[i].getTotalWord();
							for(int j=0;j<wordCount;j++)
							{		
								System::Windows::Forms::MessageBox::Show(j.ToString(),"J");
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
							//System::Windows::Forms::MessageBox::Show("ke bhayo","ke bhayo");
							System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"Failed to prepare the script file!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
							exit(0);
						}

						// recognize the words from the features file using the Viterbi decoder of the HTK Toolkit HVite
						// then read the Master Labeled File(MLF) and fetch the output models
						this->alModelRec = rp->RecognizeByHTK();
						
						 
						
						
						this->ProvideOutput();

						/* after recognizing is done remove the script file and also the associated image features files */
						// remove the script file
	/*	///	Commented sept14			 
						System::IO::File::Delete(rp->scriptFilePath);

						// remove all the temporary word image feature files
						for(int i=1;i<=totalUnit;i++)	
						{~
							System::String* tmp=tmp->Concat(dirOfRecFile,i.ToString(),".txt");
							//System::IO::File::Delete(dirOfRecFile+i+".txt");
							System::IO::File::Delete(tmp);
						}

		
		}

		*/ ///	Commented sept14
		private: void recognize(){
				 }
		private: void recognize_small_chars(){
						
				 }
		private: void ProvideOutput(){

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
											//System::Windows::Forms::MessageBox::Show(tempStr,"Keys",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
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
										/*for(int l=0;l<tempAl->Count;l++)
										{
											tempStr = tempAl[l]->ToString();
											ucodeStr = ucodeStr->Concat(ucodeStr,slForCharacters->GetKey(slForCharacters->IndexOfValue(tempStr)));
										}		*/					
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
				//System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"Can't load the Combo box!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
				//System::Windows::Forms::MessageBox::Show( ex->Message->ToString(),"Can't access database files");
				exit(0);
			}
		 }

	public: void smallBinary(){
				
				try{
					ThresholedValue* ts = new ThresholedValue(this->imageReceivedToForm);
						float fLevel = ts->GetThresholed();
						intLevel = int(fLevel*255);
						rgbConvert* rgbC = new rgbConvert(this->imageReceivedToForm);
						//BArray = rgbC->GetBinaryArray(200);
						ImgArray = rgbC->GetImageArray( );
				}
				catch(System::Exception* ex){
				}

			}
	private: void smallSeparate(){

			 }

	private: void checkParameters(){

			 this->myRTB->AppendText("\n Lineno is ");
			 this->myRTB->AppendText(lineno.ToString());
			 this->myRTB->AppendText("\n lineCount is ");
			 this->myRTB->AppendText(this->lineCount.ToString());


			 /*
			 if(charno<this->LineInfo[lineno].Words[wordno].getTotalUnit()-1)
				 {
					this->charno++;
				 }
				 else
				 {
					 //this->charno=0;
					 if(wordno< this->LineInfo[lineno].getTotalWord()-1)
					 {
						 this->wordno++;
						 this->charno=0;
					 }


					 else
					 {
						 this->wordno=0;
						 this->charno=0;
						 if(lineno<this->lineCount-1)
						 {
							 this->lineno++;
						 }
						 else
						 {
							 this->lineno=0;
							 this->wordno=0;
							 this->charno=0;
						 }
					 }
				 }
			
			*/

			int abc=0;

			for(int myI=0;(myI<= this->lineno) ;myI++){ //no of Lines
				this->myRTB->AppendText(" \n Number of lines :  ");
				this->myRTB->AppendText(this->lineno.ToString());
				this->myRTB->AppendText(myI.ToString());
				this->myRTB->AppendText(" \n ");

				 for(int myJ=0;myJ<=this->LineInfo[myI].getTotalWord();myJ++){
					 this->myRTB->AppendText("\nnumber of Words:");
					 this->myRTB->AppendText(this->LineInfo[myI].getTotalWord().ToString());
					 this->myRTB->AppendText("\nJ:");		
					 this->myRTB->AppendText(myJ.ToString());
					 this->myRTB->AppendText("\nK:    ");
					 for(int myK=0;(myK<this->LineInfo[myI].Words[myK].getTotalUnit());myK++){
						
						 abc++;
						 
						 
						 this->myRTB->AppendText(myK.ToString());
						 this->myRTB->AppendText("  ");

						 //this->myAverage(myI,myJ,myK);

					 }
				 
				 }

				 this->myRTB->AppendText("\n--------------------- Abc is ");
				 this->myRTB->AppendText(abc.ToString());
			 }
				 this->myAverage(this->lineno,this->wordno,this->charno);
			 
			 
				 this->Update;
		 }

	private:
	void myAverage(int lineno,int wordno,int charno)
		{
			static float widthCount=0;
			static float heightCount=0;
			static float avgWidthCount=0;
			static float avgHeightCount=0;
			static float counterForAveragingHeightWeight=0;

			x1=this->LineInfo[lineno].Words[wordno].Units[charno].getStartColumn();
			x2=this->LineInfo[lineno].Words[wordno].Units[charno].getEndColumn();
			y1=this->LineInfo[lineno].getStartRow();
			y2=this->LineInfo[lineno].getEndRow();
			int xsize=x2-x1+1;
			int ysize=y2-y1+1;
			
			this->cropImage=new Bitmap(xsize,ysize,Imaging::PixelFormat::Format24bppRgb);
			
			for(int i=y1;i<=y2;i++)//traverse through y
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
			//this->pictureBox1->Image=cropImage;
			this->label2->Text = cropImage->Height.ToString();
			this->label8->Text = cropImage->Width.ToString();
			widthCount +=cropImage->Height;
			heightCount +=cropImage->Width;
			counterForAveragingHeightWeight++;
			avgWidthCount=widthCount/counterForAveragingHeightWeight;
			avgHeightCount=heightCount/counterForAveragingHeightWeight;
			
			this->label10->Text = avgWidthCount.ToString();
			this->meroText= this->meroText->Concat(this->meroText,"\n Average width : ",avgWidthCount.ToString());
			this->label12->Text = avgHeightCount.ToString();
			this->meroText= this->meroText->Concat(this->meroText,"\n Average Height : ",avgHeightCount.ToString());
			this->label13->Text = counterForAveragingHeightWeight.ToString();
			this->myRTB->AppendText(this->meroText);


		}
private: System::Void avgButton_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			checkParameters();
		 }

};
}