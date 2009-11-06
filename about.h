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
	private: System::Windows::Forms::Label *  label3;
	private: System::Windows::Forms::Label *  label4;
	private: System::Windows::Forms::Label *  label5;
	private: System::Windows::Forms::Label *  label6;
	private: System::Windows::Forms::Button *  btnCloseAboutForm;

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
			this->label3 = new System::Windows::Forms::Label();
			this->label4 = new System::Windows::Forms::Label();
			this->label5 = new System::Windows::Forms::Label();
			this->label6 = new System::Windows::Forms::Label();
			this->btnCloseAboutForm = new System::Windows::Forms::Button();
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
			this->label1->TabIndex = 1;
			this->label1->Text = S"Nepali OCR ";
			// 
			// label2
			// 
			this->label2->Location = System::Drawing::Point(224, 64);
			this->label2->Name = S"label2";
			this->label2->Size = System::Drawing::Size(200, 40);
			this->label2->TabIndex = 2;
			this->label2->Text = S"Developed by :                                                  Madan Puraskar Pu" 
				S"stakalaya ";
			// 
			// label3
			// 
			this->label3->Location = System::Drawing::Point(24, 192);
			this->label3->Name = S"label3";
			this->label3->Size = System::Drawing::Size(560, 136);
			this->label3->TabIndex = 3;
			this->label3->Text = S"The Madan Puraskar Pustakalaya (MPP) is the principal archive of books and period" 
				S"icals in the nepali language, the mother tongue (or lingua franca) of a little o" 
				S"ver 30 million people of South Asia. The Library is a not-for profit, non-govern" 
				S"mental institution that is run by a trust whose members are eminent men and wome" 
				S"n of letters of Nepal. In addition to the archival collection which is at the ce" 
				S"nter of its focus, the Library is well known for its continuing work in the area" 
				S"s of publishing, education and training. It also manages two of Nepal\'s most pre" 
				S"stigious literary prizes, the Madan Puraskar and the Jagadamba Shree. The first " 
				S"four decades of the Library\'s existence have been devoted to accessions and cata" 
				S"loguing (using the Dewey System). With beginnings as a private collection in the" 
				S" mid-1940s, the Library has expanded continuously over the decades, keeping pace" 
				S" with the development of the Nepali language in the modernizing nation state of " 
				S"Nepal, and in the hills of North India.";
			// 
			// label4
			// 
			this->label4->Location = System::Drawing::Point(24, 344);
			this->label4->Name = S"label4";
			this->label4->Size = System::Drawing::Size(568, 64);
			this->label4->TabIndex = 3;
			this->label4->Text = S"The first acquisitions for what was later to become the Madan Puraskar Pustakalay" 
				S"a (MPP) were made in the mid-1940s by a Kathmandu schoolboy, with pennies that c" 
				S"ame from his lunch allowance. As the personal collection grew, it attracted gift" 
				S"s in kind from several important literary personalities, statesmen and scholars " 
				S"of Nepal and India.";
			// 
			// label5
			// 
			this->label5->Location = System::Drawing::Point(24, 424);
			this->label5->Name = S"label5";
			this->label5->Size = System::Drawing::Size(568, 64);
			this->label5->TabIndex = 3;
			this->label5->Text = S"In 1956, the collection received an endowment from Rani Jagadamba Kumari Devi Ran" 
				S"a. Madan Puraskar Pustakalaya was officially registered in 1985, under Organizat" 
				S"ions Registration Act of 1977. The foundations of the Library were even more sec" 
				S"ure when in 1986, it was gifted land and a building worth over NRs 10 million (a" 
				S"bout US$ 200,000) by that schoolboy, Kamal Mani Dixit, presently Chairman of the" 
				S" Library.";
			// 
			// label6
			// 
			this->label6->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->label6->Location = System::Drawing::Point(136, 152);
			this->label6->Name = S"label6";
			this->label6->Size = System::Drawing::Size(232, 24);
			this->label6->TabIndex = 3;
			this->label6->Text = S" About: Madan Puraskar Pustakalaya";
			// 
			// btnCloseAboutForm
			// 
			this->btnCloseAboutForm->Location = System::Drawing::Point(240, 496);
			this->btnCloseAboutForm->Name = S"btnCloseAboutForm";
			this->btnCloseAboutForm->Size = System::Drawing::Size(88, 24);
			this->btnCloseAboutForm->TabIndex = 4;
			this->btnCloseAboutForm->Text = S"Close";
			this->btnCloseAboutForm->Click += new System::EventHandler(this, btnCloseAboutForm_Click);
			// 
			// about
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->ClientSize = System::Drawing::Size(624, 526);
			this->Controls->Add(this->btnCloseAboutForm);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label6);
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->Name = S"about";
			this->Text = S"About: Nepali OCR";
			this->ResumeLayout(false);

		}		
	private: System::Void btnCloseAboutForm_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 this->Hide();
			 }

};
}