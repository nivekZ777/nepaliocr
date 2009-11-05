#include "Line.h"
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
			InitializeComponent();
			this->pictureBox_myWindow->Image = receivedImageFromMainForm;
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
	private: System::Windows::Forms::PictureBox *  pictureBox1;


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
			this->pictureBox_myWindow = new System::Windows::Forms::PictureBox();
			this->pictureBox1 = new System::Windows::Forms::PictureBox();
			this->panel_myWindow->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel_myWindow
			// 
			this->panel_myWindow->AutoScroll = true;
			this->panel_myWindow->Controls->Add(this->pictureBox1);
			this->panel_myWindow->Controls->Add(this->pictureBox_myWindow);
			this->panel_myWindow->Location = System::Drawing::Point(8, 80);
			this->panel_myWindow->Name = S"panel_myWindow";
			this->panel_myWindow->Size = System::Drawing::Size(504, 256);
			this->panel_myWindow->TabIndex = 1;
			// 
			// pictureBox_myWindow
			// 
			this->pictureBox_myWindow->Location = System::Drawing::Point(16, 16);
			this->pictureBox_myWindow->Name = S"pictureBox_myWindow";
			this->pictureBox_myWindow->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox_myWindow->TabIndex = 0;
			this->pictureBox_myWindow->TabStop = false;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(208, 16);
			this->pictureBox1->Name = S"pictureBox1";
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// myWindow
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(520, 342);
			this->Controls->Add(this->panel_myWindow);
			this->Name = S"myWindow";
			this->Text = S"Image Viewer";
			this->panel_myWindow->ResumeLayout(false);
			this->ResumeLayout(false);

		}		
	public:
		void defineVar(int** ImgArray,bool** BArray,Line* Lines,int numberOfLines)
			{
				this->ImageArray=ImgArray;
				this->BinArray=BArray;
				this->LineInfo=Lines;
				this->lineCount=numberOfLines;
				this->display(this->lineno,this->wordno,this->charno);
				//this->LoadComboBoxFromFile();
			}


	private:
	void display(int lineno,int wordno,int charno)
		{
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
		}


	
	};
}