#include "Line.h"

#pragma once

	using namespace System;
	using namespace System::Data;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Drawing::Imaging;



namespace OCR
{
	/// <summary> 
	/// Summary for TrainingForm
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public __gc class TrainingForm : public System::Windows::Forms::Form
	{
	public: 
		TrainingForm(void)
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

	
	private: 
		bool** BinArray;
		Line* LineInfo;
		int lineCount;
		Bitmap* cropImage;
		static int lineno=0;
		static int wordno=0;
		static int charno=0;


	public: 
		
		void defineVar(bool** BArray,Line* Lines,int numberOfLines)
			{
				this->BinArray=BArray;
				this->LineInfo=Lines;
				this->lineCount=numberOfLines;
				this->display(this->lineno,this->wordno,this->charno);
			}


		void display(int lineno,int wordno,int charno)
		{
			int x1=this->LineInfo[lineno].Words[wordno].Units[charno].getStartColumn();
			int x2=this->LineInfo[lineno].Words[wordno].Units[charno].getEndColumn();
			int y1=this->LineInfo[lineno].getStartRow();
			int y2=this->LineInfo[lineno].getEndRow();

			int xsize=x2-x1+1;
			int ysize=y2-y1+1;
			
			//xsize=400;
			//ysize=400;

			this->cropImage=new Bitmap(xsize,ysize,Imaging::PixelFormat::Format24bppRgb);
			
			for(int i=y1;i<=y2;i++)
			{
				for(int j=x1;j<=x2;j++)
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

	private: System::Windows::Forms::Panel *  panel1;
	private: System::Windows::Forms::PictureBox *  pictureBox1;
	private: System::Windows::Forms::ComboBox *  LineNo;
	private: System::Windows::Forms::ComboBox *  WordNo;
	private: System::Windows::Forms::ComboBox *  CharNo;
	private: System::Windows::Forms::Label *  label1;
	private: System::Windows::Forms::Label *  label2;
	private: System::Windows::Forms::Label *  label3;
	private: System::Windows::Forms::Button *  nextButton;
	private: System::Windows::Forms::Button *  prevButton;
	private: System::Windows::Forms::ComboBox *  characterBox;
	private: System::Windows::Forms::Button *  trainButton;

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
			this->panel1 = new System::Windows::Forms::Panel();
			this->pictureBox1 = new System::Windows::Forms::PictureBox();
			this->LineNo = new System::Windows::Forms::ComboBox();
			this->WordNo = new System::Windows::Forms::ComboBox();
			this->CharNo = new System::Windows::Forms::ComboBox();
			this->label1 = new System::Windows::Forms::Label();
			this->label2 = new System::Windows::Forms::Label();
			this->label3 = new System::Windows::Forms::Label();
			this->nextButton = new System::Windows::Forms::Button();
			this->prevButton = new System::Windows::Forms::Button();
			this->characterBox = new System::Windows::Forms::ComboBox();
			this->trainButton = new System::Windows::Forms::Button();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->AutoScroll = true;
			this->panel1->Controls->Add(this->pictureBox1);
			this->panel1->Location = System::Drawing::Point(8, 8);
			this->panel1->Name = S"panel1";
			this->panel1->Size = System::Drawing::Size(128, 128);
			this->panel1->TabIndex = 0;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(16, 8);
			this->pictureBox1->Name = S"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(104, 112);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// LineNo
			// 
			this->LineNo->Location = System::Drawing::Point(208, 24);
			this->LineNo->Name = S"LineNo";
			this->LineNo->Size = System::Drawing::Size(72, 21);
			this->LineNo->TabIndex = 1;
			this->LineNo->Text = S"Line No.";
			// 
			// WordNo
			// 
			this->WordNo->Location = System::Drawing::Point(208, 64);
			this->WordNo->Name = S"WordNo";
			this->WordNo->Size = System::Drawing::Size(72, 21);
			this->WordNo->TabIndex = 2;
			this->WordNo->Text = S"Word No.";
			// 
			// CharNo
			// 
			this->CharNo->Location = System::Drawing::Point(208, 104);
			this->CharNo->Name = S"CharNo";
			this->CharNo->Size = System::Drawing::Size(72, 21);
			this->CharNo->TabIndex = 3;
			this->CharNo->Text = S"Char No.";
			// 
			// label1
			// 
			this->label1->Location = System::Drawing::Point(144, 27);
			this->label1->Name = S"label1";
			this->label1->Size = System::Drawing::Size(56, 23);
			this->label1->TabIndex = 4;
			this->label1->Text = S"LINE:";
			// 
			// label2
			// 
			this->label2->Location = System::Drawing::Point(144, 67);
			this->label2->Name = S"label2";
			this->label2->Size = System::Drawing::Size(56, 23);
			this->label2->TabIndex = 5;
			this->label2->Text = S"WORD:";
			// 
			// label3
			// 
			this->label3->Location = System::Drawing::Point(144, 107);
			this->label3->Name = S"label3";
			this->label3->Size = System::Drawing::Size(56, 23);
			this->label3->TabIndex = 6;
			this->label3->Text = S"CHAR:";
			// 
			// nextButton
			// 
			this->nextButton->Location = System::Drawing::Point(160, 160);
			this->nextButton->Name = S"nextButton";
			this->nextButton->Size = System::Drawing::Size(56, 24);
			this->nextButton->TabIndex = 7;
			this->nextButton->Text = S"NEXT>>";
			this->nextButton->Click += new System::EventHandler(this, nextButton_Click);
			// 
			// prevButton
			// 
			this->prevButton->Location = System::Drawing::Point(80, 160);
			this->prevButton->Name = S"prevButton";
			this->prevButton->Size = System::Drawing::Size(56, 24);
			this->prevButton->TabIndex = 8;
			this->prevButton->Text = S"<<PREV";
			this->prevButton->Click += new System::EventHandler(this, prevButton_Click);
			// 
			// characterBox
			// 
			this->characterBox->Location = System::Drawing::Point(16, 224);
			this->characterBox->Name = S"characterBox";
			this->characterBox->Size = System::Drawing::Size(121, 21);
			this->characterBox->TabIndex = 9;
			this->characterBox->Text = S"Characters";
			// 
			// trainButton
			// 
			this->trainButton->Location = System::Drawing::Point(176, 224);
			this->trainButton->Name = S"trainButton";
			this->trainButton->TabIndex = 10;
			this->trainButton->Text = S"TRAIN";
			// 
			// TrainingForm
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(292, 266);
			this->Controls->Add(this->trainButton);
			this->Controls->Add(this->characterBox);
			this->Controls->Add(this->prevButton);
			this->Controls->Add(this->nextButton);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->CharNo);
			this->Controls->Add(this->WordNo);
			this->Controls->Add(this->LineNo);
			this->Controls->Add(this->panel1);
			this->Name = S"TrainingForm";
			this->Text = S"TrainingForm";
			this->panel1->ResumeLayout(false);
			this->ResumeLayout(false);

		}	

		

	
	private: System::Void nextButton_Click(System::Object *  sender, System::EventArgs *  e)
			 {
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
				 this->display(this->lineno,this->wordno,this->charno);
				 this->Update;
			 }

private: System::Void prevButton_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 if(charno > 0) //this->LineInfo[lineno].Words[wordno].getTotalUnit()-1)
				 {
					this->charno--;
				 }
				 else
				 {
					 //this->charno=0;
					 if(wordno > 0)// this->LineInfo[lineno].getTotalWord()-1)
					 {
						 this->wordno--;
						 this->charno=this->LineInfo[lineno].Words[wordno].getTotalUnit()-1;
					 }


					 else
					 {
						 if(lineno > 0)
						 {
							 this->lineno--;
							 this->wordno=this->LineInfo[lineno].getTotalWord()-1;
							 this->charno=this->LineInfo[lineno].Words[wordno].getTotalUnit()-1;
						 
						 }
						 else
						 {
							 this->lineno=this->lineCount-1;
							 this->wordno=this->LineInfo[lineno].getTotalWord()-1;
							 this->charno=this->LineInfo[lineno].Words[wordno].getTotalUnit()-1;
						 }
					 }
				 }
				 this->display(this->lineno,this->wordno,this->charno);
				 this->Update;

		 }

};
}