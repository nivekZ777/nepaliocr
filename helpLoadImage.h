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
	/// Summary for helpLoadImage
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public __gc class helpLoadImage : public System::Windows::Forms::Form
	{
	public: 
		helpLoadImage(void)
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
	private: System::Windows::Forms::PictureBox *  pictureBox1;
	private: System::Windows::Forms::Label *  label1;
	private: System::Windows::Forms::PictureBox *  pictureBox2;
	private: System::Windows::Forms::Label *  label2;
	private: System::Windows::Forms::Button *  button1;

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
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(OCR::helpLoadImage));
			this->pictureBox1 = new System::Windows::Forms::PictureBox();
			this->label1 = new System::Windows::Forms::Label();
			this->pictureBox2 = new System::Windows::Forms::PictureBox();
			this->label2 = new System::Windows::Forms::Label();
			this->button1 = new System::Windows::Forms::Button();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (__try_cast<System::Drawing::Image *  >(resources->GetObject(S"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(16, 16);
			this->pictureBox1->Name = S"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(160, 48);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// label1
			// 
			this->label1->Location = System::Drawing::Point(200, 16);
			this->label1->Name = S"label1";
			this->label1->Size = System::Drawing::Size(168, 32);
			this->label1->TabIndex = 1;
			this->label1->Text = S"Load Image from the File menu";
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (__try_cast<System::Drawing::Image *  >(resources->GetObject(S"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(32, 80);
			this->pictureBox2->Name = S"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(120, 40);
			this->pictureBox2->TabIndex = 2;
			this->pictureBox2->TabStop = false;
			// 
			// label2
			// 
			this->label2->Location = System::Drawing::Point(192, 80);
			this->label2->Name = S"label2";
			this->label2->Size = System::Drawing::Size(168, 32);
			this->label2->TabIndex = 3;
			this->label2->Text = S"or Load from the mouse click menu";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(168, 152);
			this->button1->Name = S"button1";
			this->button1->Size = System::Drawing::Size(56, 24);
			this->button1->TabIndex = 4;
			this->button1->Text = S"Close";
			this->button1->Click += new System::EventHandler(this, button1_Click);
			// 
			// helpLoadImage
			// 
			this->AutoScale = false;
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->AutoScroll = true;
			this->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->ClientSize = System::Drawing::Size(416, 182);
			this->ControlBox = false;
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox1);
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->Name = S"helpLoadImage";
			this->Text = S"Help: Load Image";
			this->ResumeLayout(false);

		}		
	private: System::Void button1_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 this->Hide();
			 }

	};
}