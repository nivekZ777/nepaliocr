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
			 Bitmap* cropImage;
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
			 	 Line* LineInfo;
int linecount;
			static int lineno=0;
			static int charno=0;
			static int wordno=0;

	private: System::Windows::Forms::Button *  btnOpen;
	private: System::Windows::Forms::Button *  btnSave;
	private: System::Windows::Forms::Button *  btnExit;
	private: System::Windows::Forms::Panel *  panel1;
	private: System::Windows::Forms::PictureBox *  pictureBox1;
	private: System::Windows::Forms::OpenFileDialog *  myDialog;
	private: System::Windows::Forms::Label *  lbl1;
	private: System::Windows::Forms::Label *  lbl2;


	private: System::Windows::Forms::SaveFileDialog *  saveImage;
	private: System::Windows::Forms::Button *  Ne;
	private: System::Windows::Forms::Panel *  panel2;
	private: System::Windows::Forms::PictureBox *  SmallImage;
	private: System::Windows::Forms::Label *  WidthLabel;
	private: System::Windows::Forms::Label *  label2;
	private: System::Windows::Forms::Panel *  panel3;

	private: System::Windows::Forms::Panel *  panel4;

	private: System::Windows::Forms::Label *  label1;
	private: System::Windows::Forms::PictureBox *  Part1;
	private: System::Windows::Forms::PictureBox *  Part2;
	private: System::Windows::Forms::Label *  label3;



		


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
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(Headliner_ver_103::Form1));
			this->btnOpen = new System::Windows::Forms::Button();
			this->btnSave = new System::Windows::Forms::Button();
			this->btnExit = new System::Windows::Forms::Button();
			this->panel1 = new System::Windows::Forms::Panel();
			this->pictureBox1 = new System::Windows::Forms::PictureBox();
			this->myDialog = new System::Windows::Forms::OpenFileDialog();
			this->lbl1 = new System::Windows::Forms::Label();
			this->lbl2 = new System::Windows::Forms::Label();
			this->saveImage = new System::Windows::Forms::SaveFileDialog();
			this->Ne = new System::Windows::Forms::Button();
			this->panel2 = new System::Windows::Forms::Panel();
			this->SmallImage = new System::Windows::Forms::PictureBox();
			this->WidthLabel = new System::Windows::Forms::Label();
			this->label2 = new System::Windows::Forms::Label();
			this->panel3 = new System::Windows::Forms::Panel();
			this->Part1 = new System::Windows::Forms::PictureBox();
			this->panel4 = new System::Windows::Forms::Panel();
			this->Part2 = new System::Windows::Forms::PictureBox();
			this->label1 = new System::Windows::Forms::Label();
			this->label3 = new System::Windows::Forms::Label();
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->panel3->SuspendLayout();
			this->panel4->SuspendLayout();
			this->SuspendLayout();
			// 
			// btnOpen
			// 
			this->btnOpen->Location = System::Drawing::Point(16, 8);
			this->btnOpen->Name = S"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(64, 23);
			this->btnOpen->TabIndex = 0;
			this->btnOpen->Text = S"Open";
			this->btnOpen->Click += new System::EventHandler(this, btnOpen_Click);
			// 
			// btnSave
			// 
			this->btnSave->Location = System::Drawing::Point(16, 40);
			this->btnSave->Name = S"btnSave";
			this->btnSave->Size = System::Drawing::Size(64, 23);
			this->btnSave->TabIndex = 1;
			this->btnSave->Text = S"Save";
			this->btnSave->Click += new System::EventHandler(this, btnSave_Click);
			// 
			// btnExit
			// 
			this->btnExit->Location = System::Drawing::Point(16, 240);
			this->btnExit->Name = S"btnExit";
			this->btnExit->Size = System::Drawing::Size(64, 23);
			this->btnExit->TabIndex = 2;
			this->btnExit->Text = S"Exit";
			this->btnExit->Click += new System::EventHandler(this, button3_Click);
			// 
			// panel1
			// 
			this->panel1->AutoScroll = true;
			this->panel1->Controls->Add(this->pictureBox1);
			this->panel1->Location = System::Drawing::Point(88, 48);
			this->panel1->Name = S"panel1";
			this->panel1->Size = System::Drawing::Size(272, 184);
			this->panel1->TabIndex = 3;
			this->panel1->Paint += new System::Windows::Forms::PaintEventHandler(this, panel1_Paint);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(15, 15);
			this->pictureBox1->Name = S"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(248, 160);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += new System::EventHandler(this, pictureBox1_Click);
			// 
			// lbl1
			// 
			this->lbl1->Enabled = false;
			this->lbl1->Location = System::Drawing::Point(376, 8);
			this->lbl1->Name = S"lbl1";
			this->lbl1->Size = System::Drawing::Size(64, 32);
			this->lbl1->TabIndex = 4;
			// 
			// lbl2
			// 
			this->lbl2->Enabled = false;
			this->lbl2->Location = System::Drawing::Point(456, 8);
			this->lbl2->Name = S"lbl2";
			this->lbl2->Size = System::Drawing::Size(56, 32);
			this->lbl2->TabIndex = 5;
			// 
			// Ne
			// 
			this->Ne->Location = System::Drawing::Point(376, 56);
			this->Ne->Name = S"Ne";
			this->Ne->Size = System::Drawing::Size(56, 23);
			this->Ne->TabIndex = 6;
			this->Ne->Text = S"Next";
			this->Ne->Click += new System::EventHandler(this, button1_Click);
			// 
			// panel2
			// 
			this->panel2->AutoScroll = true;
			this->panel2->Controls->Add(this->SmallImage);
			this->panel2->Location = System::Drawing::Point(384, 88);
			this->panel2->Name = S"panel2";
			this->panel2->Size = System::Drawing::Size(144, 80);
			this->panel2->TabIndex = 7;
			// 
			// SmallImage
			// 
			this->SmallImage->Location = System::Drawing::Point(8, 8);
			this->SmallImage->Name = S"SmallImage";
			this->SmallImage->Size = System::Drawing::Size(128, 64);
			this->SmallImage->TabIndex = 0;
			this->SmallImage->TabStop = false;
			this->SmallImage->Click += new System::EventHandler(this, pictureBox2_Click);
			// 
			// WidthLabel
			// 
			this->WidthLabel->Enabled = false;
			this->WidthLabel->Location = System::Drawing::Point(632, 72);
			this->WidthLabel->Name = S"WidthLabel";
			this->WidthLabel->Size = System::Drawing::Size(32, 32);
			this->WidthLabel->TabIndex = 9;
			// 
			// label2
			// 
			this->label2->Enabled = false;
			this->label2->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->label2->Location = System::Drawing::Point(552, 72);
			this->label2->Name = S"label2";
			this->label2->Size = System::Drawing::Size(64, 32);
			this->label2->TabIndex = 8;
			this->label2->Text = S"Char Width";
			// 
			// panel3
			// 
			this->panel3->AutoScroll = true;
			this->panel3->Controls->Add(this->Part1);
			this->panel3->Location = System::Drawing::Point(432, 176);
			this->panel3->Name = S"panel3";
			this->panel3->Size = System::Drawing::Size(88, 56);
			this->panel3->TabIndex = 8;
			// 
			// Part1
			// 
			this->Part1->Location = System::Drawing::Point(8, 8);
			this->Part1->Name = S"Part1";
			this->Part1->Size = System::Drawing::Size(72, 40);
			this->Part1->TabIndex = 0;
			this->Part1->TabStop = false;
			this->Part1->Click += new System::EventHandler(this, pictureBox2_Click_1);
			// 
			// panel4
			// 
			this->panel4->AutoScroll = true;
			this->panel4->Controls->Add(this->Part2);
			this->panel4->Location = System::Drawing::Point(528, 176);
			this->panel4->Name = S"panel4";
			this->panel4->Size = System::Drawing::Size(88, 56);
			this->panel4->TabIndex = 10;
			// 
			// Part2
			// 
			this->Part2->Location = System::Drawing::Point(8, 8);
			this->Part2->Name = S"Part2";
			this->Part2->Size = System::Drawing::Size(72, 40);
			this->Part2->TabIndex = 0;
			this->Part2->TabStop = false;
			// 
			// label1
			// 
			this->label1->Location = System::Drawing::Point(432, 240);
			this->label1->Name = S"label1";
			this->label1->Size = System::Drawing::Size(88, 23);
			this->label1->TabIndex = 11;
			this->label1->Text = S"P1";
			// 
			// label3
			// 
			this->label3->Location = System::Drawing::Point(528, 240);
			this->label3->Name = S"label3";
			this->label3->Size = System::Drawing::Size(88, 23);
			this->label3->TabIndex = 12;
			this->label3->Text = S"P2";
			// 
			// Form1
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(680, 278);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->panel4);
			this->Controls->Add(this->WidthLabel);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->Ne);
			this->Controls->Add(this->lbl2);
			this->Controls->Add(this->lbl1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->btnExit);
			this->Controls->Add(this->btnSave);
			this->Controls->Add(this->btnOpen);
			this->Controls->Add(this->panel3);
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->Name = S"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = S"Headliner Ver 1.03";
			this->Load += new System::EventHandler(this, Form1_Load);
			this->panel1->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->panel3->ResumeLayout(false);
			this->panel4->ResumeLayout(false);
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
					im=NULL;
					this->ImageLoaded = true;
					this->BinaryDone=false;
					// creating a bitmap
					im = new Bitmap(this->myDialog->OpenFile());
					this->pictureBox1->Image = im;
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
							this->separateChar();	
							this->pictureBox1->Image=sp->output;//separate Characters					
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
			 } catch (System::Exception *x ) {
				 System::Windows::Forms::MessageBox::Show(x->Message->ToString(),"Failed to Apply Mean Removal!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
			 }

		 }


 private: void saveImageFile()
			{

					saveImage->Filter= "PNG files (*.jpg)|*.jpg|PNG files (*.png)|*.png|All valid files (*.jpg/*.png)|*.jpg/*.png" ;
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
private: System::Void panel1_Paint(System::Object *  sender, System::Windows::Forms::PaintEventArgs *  e)
		 {
		 }
private: int MultiFactorialAnalysis(Bitmap *connected)
		 {
			int i,j;
			ThresholedValue* ts = new ThresholedValue(connected);
			float fLevel;
			fLevel= ts->GetThresholed();
			int levl;
			levl = int(fLevel*255);
			rgbConvert* rgbC = new rgbConvert(connected);
			int **BinArray;
			int height;
			bool **tempArray;
			tempArray=rgbC->GetBinaryArray(levl);
			BinArray= rgbC->GetImageArray();
			bool flag=false;
			int width;
			width=connected->Width;
			int *top;
			int *bottom;
			int down,up;
			int count=0;
			bool temp,temp1;
			float *Fic,*Fmt,*Fdm,*Fdmc,*Summation;;
						
			top=new int[width];
			bottom=new int[width];
			Fic=new float[width];
			Fmt=new float[width];
			Summation=new float[width];
			Fdm=new float[width];
			Fdmc=new float[width];

			/*for(i=0;i<=connected->Width-1;i++)
			{
				top[i]=0;
				bottom[i]=0;
				Fic[i]=0;
				Fmt[i]=0;
				Summation[i]=0;
				Fdm[i]=0;
				Fdmc[i]=0;
			}*/
			for(i=0;i<=connected->Width-1;i++)
			{
				top[i]=0;
				bottom[i]=0;
				Fic[i]=0;
				Fmt[i]=0;
				Summation[i]=0;
				Fdm[i]=0;
				Fdmc[i]=0;
				flag=false;
				for(j=0;j<=connected->Height-1;j++)
				{
					if(BinArray[j][i]==0)
					{
						if(flag==false)
						{
							top[i]=j;
						//	System::Windows::Forms::MessageBox::Show(top[i].ToString(),"Top Value");
							flag=true;
						}
						else
						{
							bottom[i]=j;
						}
					}
				}
			}
			
			up=minimum(top,width);
			down=maximum(bottom,width);
			height=down-up;
			System::Windows::Forms::MessageBox::Show(up.ToString(),"Up");
			System::Windows::Forms::MessageBox::Show(down.ToString(),"Down");
			System::Windows::Forms::MessageBox::Show(height.ToString(),"Height");

			for(j=0;j<width;j++)
			{
                count=0;
				for(i=0;i<height;i++)
				{
					temp=tempArray[i][j];
					temp1=tempArray[i+1][j];
					if(temp!=temp1)
					{
						count++;
					}
				}
				if(count!=0)
				{
					Fic[j]=(float)1/(float)count;
				}
				else
				{
                    Fic[j]=-1;
				}
			}
			float inccount;
			
			for(i=0;i<width;i++)
			{
				inccount=0;
				for(j=0;j<height;j++)
				{
					if(BinArray[j][i]==0)
					{
						inccount++;
					}
				}
				System::Windows::Forms::MessageBox::Show(inccount.ToString(),"blob size");
			//	System::Windows::Forms::MessageBox::Show(height.ToString(),"Bigger T");
				Fmt[i]=1-inccount/(float)height;
			}
			float mid=(float)width/2;

			for(i=0;i<width;i++)
			{
				int l1=top[i]-up;
				int l2=down-bottom[i];
				int mn,mx;
				if(l1>=l2)
				{
					mn=l2;
					mx=l1;
				}
				else
				{
					mn=l1;
					mx=l2;
				}
				if(mx==0)
				{
					Fdm[i]=-10;
				}	
				else
				{
					Fdm[i]=(float)mn/(float)mx;
				}
				int ll1=i;
				int ll2=width-i-1;
				int mmn,mmx;
				if(ll1>=ll2)
				{
					mmn=ll2;
					mmx=ll1;
				}
				else
				{
					mmn=ll1;
					mmx=ll2;
				}
				if(mmx==0)
				{
					Fdmc[i]=-10;
				}
				else
				{
					Fdmc[i]=(float)mmn/(float)mmx;
				}
			}
				
			for(i=0;i<width;i++)
			{
				float sum=0.0;
				sum=Fic[i]+Fmt[i]+Fdm[i]+Fdmc[i];
				System::Windows::Forms::MessageBox::Show(sum.ToString(),"Sum");
				Summation[i]=sum/4;
			}
			
			int cutcolumn=maximum(Summation,width);
			return cutcolumn;
		 }

private: int minimum(int *num,int width)
		 {
			int mini=num[0];
			for (int i=1;i<=width-1;i++)
			{
				System::Windows::Forms::MessageBox::Show(mini.ToString(),"Mini Value");
				System::Windows::Forms::MessageBox::Show(num[i].ToString(),"Num Value");
				if(mini>=num[i] && num[i]>=0)
				{
					mini=num[i];
					System::Windows::Forms::MessageBox::Show(mini.ToString(),"Mini Value");
				}
			}
			return mini;
		 }

private: int maximum(float *num,int width)
		 {
			float maxi=num[0];
			int maxcol;
			for (int i=1;i<width;i++)
			{
				System::Windows::Forms::MessageBox::Show(maxi.ToString(),"Maxi");
				System::Windows::Forms::MessageBox::Show(num[i].ToString(),"Column Value");
				if(maxi<=num[i])
				{
					maxcol=i;
					maxi=num[i];
				}
				//System::Windows::Forms::MessageBox::Show(maxcol.ToString(),"MaxCol");
			}
			return maxcol;
		 }
private: int maximum(int *num,int width)
		 {
			int maxi=num[0];
			for (int i=1;i<width;i++)
			{
				if(maxi<=num[i])
				{
					maxi=num[i];
				}
			}
			return maxi;
		 }
private: void display(int lineno,int wordno,int charno)
		{
			int x1,x2,y1,y2;

			x1=this->LineInfo[lineno].Words[wordno].Units[charno].getStartColumn(); //Equivalent to :: left_x
			x2=this->LineInfo[lineno].Words[wordno].Units[charno].getEndColumn();	//Equivalent to :: right_x
			y1=this->LineInfo[lineno].getStartRow();		//Equivalent to :: top_y
			y2=this->LineInfo[lineno].getEndRow();			 //Equivalent to :: bottom_y
			
			int xsize=x2-x1+1;
			int ysize=y2-y1+1;
			this->WidthLabel->Text=xsize.ToString();
			this->cropImage=new Bitmap(xsize,ysize,Imaging::PixelFormat::Format24bppRgb);
				for(int i=y1;i<=y2;i++)//traverse through y
				{
					for(int j=x1;j<=x2;j++)//traverse through x
					{
						if(this->BArray[i][j])
						{
							this->cropImage->SetPixel(j-x1,i-y1,Color::Beige);
						}
						else
						{
							this->cropImage->SetPixel(j-x1,i-y1,Color::Black);
						}
					}
				}
			if (xsize>=2 && xsize<=11)
			{
			 	this->SmallImage->Image=cropImage;
			}
			else
			{
				Bitmap *cutImage1,*cutImage2;
				int col=this->MultiFactorialAnalysis(cropImage);
				cutImage1=new Bitmap(xsize,ysize,Imaging::PixelFormat::Format24bppRgb);
				cutImage2=new Bitmap(xsize,ysize,Imaging::PixelFormat::Format24bppRgb);

				System::Windows::Forms::MessageBox::Show("Cut Column:",col.ToString());
				for(int i=y1;i<=y2;i++)//traverse throughy
				{
					for(int j=x1;j<=x2;j++)//traverse through x
					{
						if((j-x1)<=col)
						{
							if(this->BArray[i][j])
							{
								cutImage1->SetPixel(j-x1,i-y1,Color::White);
								cutImage2->SetPixel(j-x1,i-y1,Color::White);

							}
							else
							{
								cutImage1->SetPixel(j-x1,i-y1,Color::Black);
								cutImage2->SetPixel(j-x1,i-y1,Color::White);
							}
						}
						else
						{
							if(this->BArray[i][j])
							{
								cutImage2->SetPixel(j-x1,i-y1,Color::White);
								cutImage1->SetPixel(j-x1,i-y1,Color::White);
							}
							else
							{
								cutImage2->SetPixel(j-x1,i-y1,Color::Black);
								cutImage1->SetPixel(j-x1,i-y1,Color::White);
							}
						}
					}
				}
				this->SmallImage->Image=cropImage;
				this->Part1->Image=cutImage1;
				this->Part2->Image=cutImage2;
			}
			//this->singleRecognize(x1,x2,y1,y2,0);
		}
private: System::Void button1_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 if(this->ImageLoaded && this->BinaryDone)
			 {
				linecount=this->numberOfLines;
				LineInfo=Lines;
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
						if(lineno<this->linecount-1)
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
				 this->display(this->lineno,this->wordno,this->charno);
				 this->Update();
			 }
		 }

private: System::Void Form1_Load(System::Object *  sender, System::EventArgs *  e)
		 {
		 }

private: System::Void pictureBox2_Click(System::Object *  sender, System::EventArgs *  e)
		 {
		 }

private: System::Void pictureBox2_Click_1(System::Object *  sender, System::EventArgs *  e)
		 {
		 }



private: System::Void pictureBox1_Click(System::Object *  sender, System::EventArgs *  e)
		 {
		 }

};
}


