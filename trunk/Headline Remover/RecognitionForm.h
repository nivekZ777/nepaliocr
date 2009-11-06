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
	/// Summary for RecognitionForm
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public __gc class RecognitionForm : public System::Windows::Forms::Form
	{
	public: 
		RecognitionForm(void)
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
	private: System::Windows::Forms::RichTextBox *  charRecBox;

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
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(OCR::RecognitionForm));
			this->charRecBox = new System::Windows::Forms::RichTextBox();
			this->SuspendLayout();
			// 
			// charRecBox
			// 
			this->charRecBox->AutoWordSelection = true;
			this->charRecBox->Location = System::Drawing::Point(8, 40);
			this->charRecBox->Name = S"charRecBox";
			this->charRecBox->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Vertical;
			this->charRecBox->Size = System::Drawing::Size(424, 296);
			this->charRecBox->TabIndex = 0;
			this->charRecBox->Text = S"";
			// 
			// RecognitionForm
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(448, 342);
			this->Controls->Add(this->charRecBox);
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->Name = S"RecognitionForm";
			this->Text = S"Recognized Text";
			this->ResumeLayout(false);

		}		

	


	public:
		void showText(System::String* text)
		{
			this->charRecBox->Text=text;
		}
	};
}