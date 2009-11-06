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
	/// Summary for helpOCR
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public __gc class helpOCR : public System::Windows::Forms::Form
	{
	public: 
		helpOCR(void)
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
	private: System::Windows::Forms::Button *  btnClose;


	private: System::Windows::Forms::PictureBox *  pictureBox3;
	private: System::Windows::Forms::PictureBox *  pictureBoxDeskew;
	private: System::Windows::Forms::PictureBox *  pictureBoxHelpOCR;
	private: System::Windows::Forms::PictureBox *  pictureBoxHelpOCR2;
	private: System::Windows::Forms::PictureBox *  pictureBoxHelpRemoveNoise;
	private: System::Windows::Forms::PictureBox *  pictureBoxHelpBinarize;
	private: System::Windows::Forms::PictureBox *  pictureBoxHelpSeparate;
	private: System::Windows::Forms::PictureBox *  pictureBoxHelpContrast;
	private: System::Windows::Forms::PictureBox *  pictureBoxContrastAdded;
	private: System::Windows::Forms::PictureBox *  pictureBoxHelpCropper;
	private: System::Windows::Forms::PictureBox *  pictureBoxHelpSaveImage;
	private: System::Windows::Forms::PictureBox *  pictureBoxHelpSaveOutput;
	private: System::Windows::Forms::PictureBox *  pictureBoxHelpRotateLeft;
	private: System::Windows::Forms::PictureBox *  pictureBoxHelpImageRotateRight;
	private: System::Windows::Forms::PictureBox *  pictureBoxHelpRotateUpright;






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
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(OCR::helpOCR));
			this->btnClose = new System::Windows::Forms::Button();
			this->pictureBoxHelpOCR = new System::Windows::Forms::PictureBox();
			this->pictureBoxHelpOCR2 = new System::Windows::Forms::PictureBox();
			this->pictureBox3 = new System::Windows::Forms::PictureBox();
			this->pictureBoxDeskew = new System::Windows::Forms::PictureBox();
			this->pictureBoxHelpRemoveNoise = new System::Windows::Forms::PictureBox();
			this->pictureBoxHelpBinarize = new System::Windows::Forms::PictureBox();
			this->pictureBoxHelpSeparate = new System::Windows::Forms::PictureBox();
			this->pictureBoxHelpContrast = new System::Windows::Forms::PictureBox();
			this->pictureBoxContrastAdded = new System::Windows::Forms::PictureBox();
			this->pictureBoxHelpCropper = new System::Windows::Forms::PictureBox();
			this->pictureBoxHelpSaveImage = new System::Windows::Forms::PictureBox();
			this->pictureBoxHelpSaveOutput = new System::Windows::Forms::PictureBox();
			this->pictureBoxHelpRotateLeft = new System::Windows::Forms::PictureBox();
			this->pictureBoxHelpImageRotateRight = new System::Windows::Forms::PictureBox();
			this->pictureBoxHelpRotateUpright = new System::Windows::Forms::PictureBox();
			this->SuspendLayout();
			// 
			// btnClose
			// 
			this->btnClose->Location = System::Drawing::Point(96, 8);
			this->btnClose->Name = S"btnClose";
			this->btnClose->Size = System::Drawing::Size(72, 24);
			this->btnClose->TabIndex = 0;
			this->btnClose->Text = S"Close";
			this->btnClose->Click += new System::EventHandler(this, btnClose_Click);
			// 
			// pictureBoxHelpOCR
			// 
			this->pictureBoxHelpOCR->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->pictureBoxHelpOCR->Image = (__try_cast<System::Drawing::Image *  >(resources->GetObject(S"pictureBoxHelpOCR.Image")));
			this->pictureBoxHelpOCR->Location = System::Drawing::Point(16, 56);
			this->pictureBoxHelpOCR->Name = S"pictureBoxHelpOCR";
			this->pictureBoxHelpOCR->Size = System::Drawing::Size(280, 200);
			this->pictureBoxHelpOCR->TabIndex = 1;
			this->pictureBoxHelpOCR->TabStop = false;
			this->pictureBoxHelpOCR->Visible = false;
			// 
			// pictureBoxHelpOCR2
			// 
			this->pictureBoxHelpOCR2->Image = (__try_cast<System::Drawing::Image *  >(resources->GetObject(S"pictureBoxHelpOCR2.Image")));
			this->pictureBoxHelpOCR2->Location = System::Drawing::Point(320, 80);
			this->pictureBoxHelpOCR2->Name = S"pictureBoxHelpOCR2";
			this->pictureBoxHelpOCR2->Size = System::Drawing::Size(200, 136);
			this->pictureBoxHelpOCR2->TabIndex = 2;
			this->pictureBoxHelpOCR2->TabStop = false;
			this->pictureBoxHelpOCR2->Visible = false;
			// 
			// pictureBox3
			// 
			this->pictureBox3->Image = (__try_cast<System::Drawing::Image *  >(resources->GetObject(S"pictureBox3.Image")));
			this->pictureBox3->Location = System::Drawing::Point(16, 64);
			this->pictureBox3->Name = S"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(336, 192);
			this->pictureBox3->TabIndex = 3;
			this->pictureBox3->TabStop = false;
			this->pictureBox3->Visible = false;
			// 
			// pictureBoxDeskew
			// 
			this->pictureBoxDeskew->Image = (__try_cast<System::Drawing::Image *  >(resources->GetObject(S"pictureBoxDeskew.Image")));
			this->pictureBoxDeskew->Location = System::Drawing::Point(16, 56);
			this->pictureBoxDeskew->Name = S"pictureBoxDeskew";
			this->pictureBoxDeskew->Size = System::Drawing::Size(344, 184);
			this->pictureBoxDeskew->TabIndex = 4;
			this->pictureBoxDeskew->TabStop = false;
			this->pictureBoxDeskew->Visible = false;
			// 
			// pictureBoxHelpRemoveNoise
			// 
			this->pictureBoxHelpRemoveNoise->BackgroundImage = (__try_cast<System::Drawing::Image *  >(resources->GetObject(S"pictureBoxHelpRemoveNoise.BackgroundImage")));
			this->pictureBoxHelpRemoveNoise->Location = System::Drawing::Point(40, 56);
			this->pictureBoxHelpRemoveNoise->Name = S"pictureBoxHelpRemoveNoise";
			this->pictureBoxHelpRemoveNoise->Size = System::Drawing::Size(224, 216);
			this->pictureBoxHelpRemoveNoise->TabIndex = 5;
			this->pictureBoxHelpRemoveNoise->TabStop = false;
			this->pictureBoxHelpRemoveNoise->Visible = false;
			// 
			// pictureBoxHelpBinarize
			// 
			this->pictureBoxHelpBinarize->BackgroundImage = (__try_cast<System::Drawing::Image *  >(resources->GetObject(S"pictureBoxHelpBinarize.BackgroundImage")));
			this->pictureBoxHelpBinarize->Location = System::Drawing::Point(16, 64);
			this->pictureBoxHelpBinarize->Name = S"pictureBoxHelpBinarize";
			this->pictureBoxHelpBinarize->Size = System::Drawing::Size(280, 160);
			this->pictureBoxHelpBinarize->TabIndex = 6;
			this->pictureBoxHelpBinarize->TabStop = false;
			this->pictureBoxHelpBinarize->Visible = false;
			// 
			// pictureBoxHelpSeparate
			// 
			this->pictureBoxHelpSeparate->Image = (__try_cast<System::Drawing::Image *  >(resources->GetObject(S"pictureBoxHelpSeparate.Image")));
			this->pictureBoxHelpSeparate->Location = System::Drawing::Point(16, 64);
			this->pictureBoxHelpSeparate->Name = S"pictureBoxHelpSeparate";
			this->pictureBoxHelpSeparate->Size = System::Drawing::Size(312, 152);
			this->pictureBoxHelpSeparate->TabIndex = 7;
			this->pictureBoxHelpSeparate->TabStop = false;
			this->pictureBoxHelpSeparate->Visible = false;
			// 
			// pictureBoxHelpContrast
			// 
			this->pictureBoxHelpContrast->Image = (__try_cast<System::Drawing::Image *  >(resources->GetObject(S"pictureBoxHelpContrast.Image")));
			this->pictureBoxHelpContrast->Location = System::Drawing::Point(16, 40);
			this->pictureBoxHelpContrast->Name = S"pictureBoxHelpContrast";
			this->pictureBoxHelpContrast->Size = System::Drawing::Size(312, 288);
			this->pictureBoxHelpContrast->TabIndex = 8;
			this->pictureBoxHelpContrast->TabStop = false;
			this->pictureBoxHelpContrast->Visible = false;
			// 
			// pictureBoxContrastAdded
			// 
			this->pictureBoxContrastAdded->Image = (__try_cast<System::Drawing::Image *  >(resources->GetObject(S"pictureBoxContrastAdded.Image")));
			this->pictureBoxContrastAdded->Location = System::Drawing::Point(376, 112);
			this->pictureBoxContrastAdded->Name = S"pictureBoxContrastAdded";
			this->pictureBoxContrastAdded->Size = System::Drawing::Size(216, 192);
			this->pictureBoxContrastAdded->TabIndex = 9;
			this->pictureBoxContrastAdded->TabStop = false;
			this->pictureBoxContrastAdded->Visible = false;
			// 
			// pictureBoxHelpCropper
			// 
			this->pictureBoxHelpCropper->Image = (__try_cast<System::Drawing::Image *  >(resources->GetObject(S"pictureBoxHelpCropper.Image")));
			this->pictureBoxHelpCropper->Location = System::Drawing::Point(16, 40);
			this->pictureBoxHelpCropper->Name = S"pictureBoxHelpCropper";
			this->pictureBoxHelpCropper->Size = System::Drawing::Size(504, 360);
			this->pictureBoxHelpCropper->TabIndex = 10;
			this->pictureBoxHelpCropper->TabStop = false;
			this->pictureBoxHelpCropper->Visible = false;
			// 
			// pictureBoxHelpSaveImage
			// 
			this->pictureBoxHelpSaveImage->Image = (__try_cast<System::Drawing::Image *  >(resources->GetObject(S"pictureBoxHelpSaveImage.Image")));
			this->pictureBoxHelpSaveImage->Location = System::Drawing::Point(16, 40);
			this->pictureBoxHelpSaveImage->Name = S"pictureBoxHelpSaveImage";
			this->pictureBoxHelpSaveImage->Size = System::Drawing::Size(240, 208);
			this->pictureBoxHelpSaveImage->TabIndex = 11;
			this->pictureBoxHelpSaveImage->TabStop = false;
			this->pictureBoxHelpSaveImage->Visible = false;
			// 
			// pictureBoxHelpSaveOutput
			// 
			this->pictureBoxHelpSaveOutput->Image = (__try_cast<System::Drawing::Image *  >(resources->GetObject(S"pictureBoxHelpSaveOutput.Image")));
			this->pictureBoxHelpSaveOutput->Location = System::Drawing::Point(16, 64);
			this->pictureBoxHelpSaveOutput->Name = S"pictureBoxHelpSaveOutput";
			this->pictureBoxHelpSaveOutput->Size = System::Drawing::Size(336, 136);
			this->pictureBoxHelpSaveOutput->TabIndex = 12;
			this->pictureBoxHelpSaveOutput->TabStop = false;
			this->pictureBoxHelpSaveOutput->Visible = false;
			// 
			// pictureBoxHelpRotateLeft
			// 
			this->pictureBoxHelpRotateLeft->Image = (__try_cast<System::Drawing::Image *  >(resources->GetObject(S"pictureBoxHelpRotateLeft.Image")));
			this->pictureBoxHelpRotateLeft->Location = System::Drawing::Point(16, 48);
			this->pictureBoxHelpRotateLeft->Name = S"pictureBoxHelpRotateLeft";
			this->pictureBoxHelpRotateLeft->Size = System::Drawing::Size(248, 256);
			this->pictureBoxHelpRotateLeft->TabIndex = 13;
			this->pictureBoxHelpRotateLeft->TabStop = false;
			// 
			// pictureBoxHelpImageRotateRight
			// 
			this->pictureBoxHelpImageRotateRight->Image = (__try_cast<System::Drawing::Image *  >(resources->GetObject(S"pictureBoxHelpImageRotateRight.Image")));
			this->pictureBoxHelpImageRotateRight->Location = System::Drawing::Point(16, 40);
			this->pictureBoxHelpImageRotateRight->Name = S"pictureBoxHelpImageRotateRight";
			this->pictureBoxHelpImageRotateRight->Size = System::Drawing::Size(272, 280);
			this->pictureBoxHelpImageRotateRight->TabIndex = 14;
			this->pictureBoxHelpImageRotateRight->TabStop = false;
			this->pictureBoxHelpImageRotateRight->Visible = false;
			// 
			// pictureBoxHelpRotateUpright
			// 
			this->pictureBoxHelpRotateUpright->Image = (__try_cast<System::Drawing::Image *  >(resources->GetObject(S"pictureBoxHelpRotateUpright.Image")));
			this->pictureBoxHelpRotateUpright->Location = System::Drawing::Point(16, 40);
			this->pictureBoxHelpRotateUpright->Name = S"pictureBoxHelpRotateUpright";
			this->pictureBoxHelpRotateUpright->Size = System::Drawing::Size(272, 264);
			this->pictureBoxHelpRotateUpright->TabIndex = 15;
			this->pictureBoxHelpRotateUpright->TabStop = false;
			this->pictureBoxHelpRotateUpright->Visible = false;
			// 
			// helpOCR
			// 
			this->AutoScale = false;
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->ClientSize = System::Drawing::Size(296, 334);
			this->ControlBox = false;
			this->Controls->Add(this->pictureBoxHelpRotateUpright);
			this->Controls->Add(this->pictureBoxHelpImageRotateRight);
			this->Controls->Add(this->pictureBoxHelpRotateLeft);
			this->Controls->Add(this->pictureBoxHelpSaveOutput);
			this->Controls->Add(this->pictureBoxHelpSaveImage);
			this->Controls->Add(this->pictureBoxHelpCropper);
			this->Controls->Add(this->pictureBoxContrastAdded);
			this->Controls->Add(this->pictureBoxHelpContrast);
			this->Controls->Add(this->pictureBoxHelpSeparate);
			this->Controls->Add(this->pictureBoxHelpBinarize);
			this->Controls->Add(this->pictureBoxHelpRemoveNoise);
			this->Controls->Add(this->pictureBoxDeskew);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->pictureBoxHelpOCR2);
			this->Controls->Add(this->pictureBoxHelpOCR);
			this->Controls->Add(this->btnClose);
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->Name = S"helpOCR";
			this->Text = S"Help";
			this->ResumeLayout(false);

		}		
	private: System::Void btnClose_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 this->Hide();
			 }
	public: void ShowHelpOCR(){
 
				this->enableDisable(this->pictureBoxHelpOCR,System::Drawing::Size(576, 328)," Help : OCR");
				this->pictureBoxHelpOCR2->Visible = true;
			}
			
		public: void ShowHelpTrain(){
 
				this->enableDisable(this->pictureBox3,System::Drawing::Size(400, 320)," Help : Training");
			}
				
			public: void ShowHelpDeskew(){
 
				this->enableDisable(this->pictureBoxDeskew,System::Drawing::Size(424, 320)," Help : Deskewing a tilted image");
			}
			public: void ShowHelpNoiseRemoval(){
 
				this->enableDisable(this->pictureBoxHelpRemoveNoise,System::Drawing::Size(344, 344)," Help : Removing Noise from an Image");
			}

			public: void ShowHelpBinarize(){
				this->enableDisable(this->pictureBoxHelpBinarize,System::Drawing::Size(344, 272)," Help : Binarizing an image");
			}
			
			
			public: void ShowHelpSeparate(){
				this->enableDisable(this->pictureBoxHelpSeparate,System::Drawing::Size(344, 296)," Help : Separating A binarized image");
			}
						
			public: void ShowHelpContrast(){
					this->enableDisable(this->pictureBoxHelpContrast,System::Drawing::Size(656, 416)," Help : Adding Contrast to a Picture");
					this->pictureBoxContrastAdded->Visible = true;
			}
			
									
			public: void ShowHelpCropper(){
				 this->enableDisable(this->pictureBoxHelpCropper,System::Drawing::Size(648, 512)," Help : Adding Cropping a Picture");
					
			}
		
			public: void ShowHelpSaveImage(){
				this->enableDisable(this->pictureBoxHelpSaveImage,System::Drawing::Size(224, 232)," Help : Saving image");				
			}
	
				 
			public: void ShowHelpSaveOutput(){
				this->enableDisable(this->pictureBoxHelpSaveOutput,System::Drawing::Size(376, 240)," Help : Saving Output text");				
			}
			public: void ShowHelpRotateLeft(){
				this->enableDisable(this->pictureBoxHelpRotateLeft,System::Drawing::Size(304, 368)," Help : Rotating the Image to left");				
			}
			public: void ShowHelpRotateRight(){
				this->enableDisable(this->pictureBoxHelpImageRotateRight,System::Drawing::Size(304, 368)," Help : Rotating the Image to right");				
			}
				

				public: void ShowHelpRotateUpright(){
				this->enableDisable(this->pictureBoxHelpRotateUpright,System::Drawing::Size(304, 368)," Help : Rotating the Image upright");				
			}
			void enableDisable(System::Windows::Forms::PictureBox *pb,System::Drawing::Size size,System::String *titleBarString){
				this->pictureBoxHelpOCR->Visible = false;
				this->pictureBoxHelpOCR2->Visible =  false;
				this->pictureBoxHelpBinarize->Visible  = false;
				this->pictureBoxHelpRemoveNoise->Visible = false;
				this->pictureBoxHelpSeparate->Visible  =false;
				this->pictureBoxHelpContrast->Visible = false;
				this->pictureBoxContrastAdded->Visible = false;
				this->pictureBoxHelpCropper->Visible = false;
				this->pictureBoxHelpSaveImage->Visible =false;			
				this->pictureBoxHelpSaveOutput->Visible =false;
				this->pictureBoxHelpRotateLeft->Visible =false;
				this->pictureBoxHelpImageRotateRight->Visible =false;
				this->pictureBoxHelpRotateUpright->Visible =false;

				this->pictureBox3->Visible = false;
				this->pictureBoxDeskew->Visible = false;

				pb->Visible = true;
				this->Size = size;
				this->Text = titleBarString;
				int closeButton_x = Math::Abs ((int)(this->Width/2));
				
				int closeButton_y = (int)this->btnClose->Location.Y;
				this->btnClose->Location = System::Drawing::Size(closeButton_x,closeButton_y);
				 
		}
	};
}