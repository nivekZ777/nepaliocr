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
	/// Summary for croper
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public __gc class croper : public System::Windows::Forms::Form
	{
	public: 
		croper(Bitmap *im2,bool** BinArray)
		{
			InitializeComponent();
			this->im2 = im2;
			this->pictureBox1->Image = im2;
			g=this->pictureBox1->CreateGraphics();
			this->BinArray = BinArray;


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
	private: System::Windows::Forms::Button *  button1;
	private: System::Windows::Forms::PictureBox *  pictureBox1;

	public: Bitmap* im2;
	public:	bool** BinArray;
	//public: int **ImgArray;

	private: System::Windows::Forms::Panel *  panel2;
	private: System::Windows::Forms::PictureBox *  pictureBox2;
	private: int x1,x2,y1,y2,xMouseDistance,yMouseDistance;
			 Graphics *g;

	

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
			this->button1 = new System::Windows::Forms::Button();
			this->panel2 = new System::Windows::Forms::Panel();
			this->pictureBox2 = new System::Windows::Forms::PictureBox();
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->AutoScroll = true;
			this->panel1->Controls->Add(this->pictureBox1);
			this->panel1->Location = System::Drawing::Point(8, 72);
			this->panel1->Name = S"panel1";
			this->panel1->Size = System::Drawing::Size(264, 344);
			this->panel1->TabIndex = 0;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(16, 16);
			this->pictureBox1->Name = S"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(168, 152);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 2;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Paint += new System::Windows::Forms::PaintEventHandler(this, pictureBox1_Paint);
			this->pictureBox1->MouseUp += new System::Windows::Forms::MouseEventHandler(this, pictureBox1_MouseUp);
			this->pictureBox1->MouseDown += new System::Windows::Forms::MouseEventHandler(this, pictureBox1_MouseDown);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(440, 16);
			this->button1->Name = S"button1";
			this->button1->Size = System::Drawing::Size(80, 40);
			this->button1->TabIndex = 1;
			this->button1->Text = S"Clickme";
			this->button1->Click += new System::EventHandler(this, button1_Click);
			// 
			// panel2
			// 
			this->panel2->AutoScroll = true;
			this->panel2->Controls->Add(this->pictureBox2);
			this->panel2->Location = System::Drawing::Point(288, 72);
			this->panel2->Name = S"panel2";
			this->panel2->Size = System::Drawing::Size(288, 336);
			this->panel2->TabIndex = 2;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(24, 16);
			this->pictureBox2->Name = S"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(128, 152);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox2->TabIndex = 0;
			this->pictureBox2->TabStop = false;
			// 
			// croper
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(592, 422);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->panel1);
			this->Name = S"croper";
			this->Text = S"croper";
			this->Closed += new System::EventHandler(this, croper_Closed);
			this->panel1->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->ResumeLayout(false);

		}		
	private: System::Void button1_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 this->cropThisImage();
			 }

	private: System::Void croper_Closed(System::Object *  sender, System::EventArgs *  e)
			 {
				 Application::Exit();
                 
			 }



	private: void cropThisImage(){
				 Bitmap *croppedImage;
				 croppedImage = new Bitmap(im2);
				 this->pictureBox2->Image = croppedImage;


			 }
	private: System::Void pictureBox1_MouseDown(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
			 {
				  
				 this->x1 = e->X;
				 this->y1 = e->Y;
			 }



private: System::Void pictureBox1_MouseUp(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		 {
			 this->find_xy_MouseDistance(e);
		    			 
		//int mouse_dragged_Image_width = System::Math::Abs(this->x2 - this->x1) ;
			int mouse_dragged_Image_width = (this->x2 - this->x1) ;
		//int mouse_dragged_Image_height = System::Math::Abs(this->y2 - this->y1);
			int mouse_dragged_Image_height = (this->y2 - this->y1);

		 Bitmap *cropImage = new Bitmap( mouse_dragged_Image_width+1,mouse_dragged_Image_height+1,Imaging::PixelFormat::Format24bppRgb);
		 for(int cropRow=0;  cropRow<(cropImage->Height); cropRow++){
			 for(int cropColumn=0;cropColumn<(cropImage->Width) ;cropColumn++){
				cropImage->SetPixel(cropColumn,cropRow,System::Drawing::Color::White);
				} // for(int cropRow=0;  cropRow<(cropImage->Height); cropRow++){for(int cropColumn=0;cropColumn<(cropImage->Width) ;cropColumn++)
          } // for(int cropRow=0;  cropRow<(cropImage->Height); cropRow++)


		  for(int i=this->y1, int cropRow=0;  i<this->y2,cropRow<(cropImage->Height)-1; i++,cropRow++){
			 for(int cropColumn=0,j=this->x1; j<this->x2,cropColumn<(cropImage->Width)-1 ; j++,cropColumn++){
				 
				 if(this->BinArray[i][j]==true)
					 cropImage->SetPixel(cropColumn,cropRow,System::Drawing::Color::White);
				 else
					 cropImage->SetPixel(cropColumn,cropRow,System::Drawing::Color::Black);
				 
			 } // for(int i=0;i<cropImage->Height;i++){for(int j=0;j<cropImage->Width;j++)
		 } // for(int i=0;i<cropImage->Height;i++)

		 this->g->DrawRectangle(Pens::Blue, Rectangle(this->x1,this->y1,(this->x2-this->x1),(this->y2-this->y1)));
		 this->g->Flush();
		
		 this->pictureBox2->Image = cropImage;

	 
		}


private: System::Void pictureBox1_Paint(System::Object *  sender, System::Windows::Forms::PaintEventArgs *  e)
		 {			 
			 e->Graphics->DrawRectangle(Pens::Blue, Rectangle(this->x1,this->y1,(this->x2-this->x1),(this->y2-this->y1)));
		 }

private: void find_xy_MouseDistance(System::Windows::Forms::MouseEventArgs *  e){
			
			 //end preserving

			 this->x2 = e->X;
			 this->y2 = e->Y;
			 int temp;


			 if(this->x1 != this->x2 && this->y1 != this->y2)
			 {
				if(this->x1>this->x2)
				{
					temp=this->x1;
					this->x1=this->x2;
					this->x2=temp;
				} // if(this->x1>this->x2)
                
				if(this->y1>this->y2)
				{
					temp=this->y1;
					this->y1=this->y2;
					this->y2=temp;
				} // if(this->y1>this->y2) 
                
			 } // if(this->x1 != this->x2 && this->y1 != this->y2)
			 else{
				 MessageBox::Show("Unable to crop");
			 }
		 }
};
}










 





