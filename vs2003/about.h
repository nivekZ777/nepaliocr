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
	/// Summary for about
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public __gc class about : public System::Windows::Forms::Form
	{
	public: 
		about(void)
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
	private: System::Windows::Forms::Label *  label2;




	private: System::Windows::Forms::Button *  btnCloseAboutForm;
	private: System::Windows::Forms::Label *  label4;
	private: System::Windows::Forms::LinkLabel *  linkLabel1;


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
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(OCR::about));
			this->pictureBox1 = new System::Windows::Forms::PictureBox();
			this->label1 = new System::Windows::Forms::Label();
			this->label2 = new System::Windows::Forms::Label();
			this->btnCloseAboutForm = new System::Windows::Forms::Button();
			this->label4 = new System::Windows::Forms::Label();
			this->linkLabel1 = new System::Windows::Forms::LinkLabel();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImage = (__try_cast<System::Drawing::Image *  >(resources->GetObject(S"pictureBox1.BackgroundImage")));
			this->pictureBox1->Location = System::Drawing::Point(40, 8);
			this->pictureBox1->Name = S"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(136, 120);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// label1
			// 
			this->label1->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->label1->Location = System::Drawing::Point(232, 24);
			this->label1->Name = S"label1";
			this->label1->Size = System::Drawing::Size(200, 16);
			this->label1->TabIndex = 1;
			this->label1->Text = S"Nepali OCR (Beta Version)";
			// 
			// label2
			// 
			this->label2->Location = System::Drawing::Point(232, 80);
			this->label2->Name = S"label2";
			this->label2->Size = System::Drawing::Size(200, 40);
			this->label2->TabIndex = 2;
			this->label2->Text = S"Developed by :                                                  Madan Puraskar Pu" 
				S"stakalaya ";
			// 
			// btnCloseAboutForm
			// 
			this->btnCloseAboutForm->Location = System::Drawing::Point(184, 168);
			this->btnCloseAboutForm->Name = S"btnCloseAboutForm";
			this->btnCloseAboutForm->Size = System::Drawing::Size(88, 24);
			this->btnCloseAboutForm->TabIndex = 4;
			this->btnCloseAboutForm->Text = S"Close";
			this->btnCloseAboutForm->Click += new System::EventHandler(this, btnCloseAboutForm_Click);
			// 
			// label4
			// 
			this->label4->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->label4->Location = System::Drawing::Point(232, 48);
			this->label4->Name = S"label4";
			this->label4->Size = System::Drawing::Size(200, 16);
			this->label4->TabIndex = 1;
			this->label4->Text = S"Released : December 15,2008";
			// 
			// linkLabel1
			// 
			this->linkLabel1->Location = System::Drawing::Point(232, 120);
			this->linkLabel1->Name = S"linkLabel1";
			this->linkLabel1->Size = System::Drawing::Size(160, 32);
			this->linkLabel1->TabIndex = 6;
			this->linkLabel1->TabStop = true;
			this->linkLabel1->Text = S"www.madanpuraskar.org";
			this->linkLabel1->Click += new System::EventHandler(this, linkLabel1_Click);
			// 
			// about
			// 
			this->AutoScale = false;
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->ClientSize = System::Drawing::Size(456, 214);
			this->ControlBox = false;
			this->Controls->Add(this->linkLabel1);
			this->Controls->Add(this->btnCloseAboutForm);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label4);
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->Name = S"about";
			this->Text = S"About: Nepali OCR";
			this->ResumeLayout(false);

		}		
	private: System::Void btnCloseAboutForm_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 this->Hide();
			 }

private: System::Void linkLabel1_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 System::Diagnostics::Process::Start("IExplore"," http://www.madanpuraskar.org");

		 }

};
}