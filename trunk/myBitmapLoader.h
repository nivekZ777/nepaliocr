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
	/// Summary for myBitmapLoader
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public __gc class myBitmapLoader : public System::Windows::Forms::Form
	{
	public: 
		myBitmapLoader(void)
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
	private: System::Windows::Forms::PictureBox *  bmpLoaderNew;

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
			this->bmpLoaderNew = new System::Windows::Forms::PictureBox();
			this->SuspendLayout();
			// 
			// bmpLoaderNew
			// 
			this->bmpLoaderNew->Location = System::Drawing::Point(24, 32);
			this->bmpLoaderNew->Name = S"bmpLoaderNew";
			this->bmpLoaderNew->Size = System::Drawing::Size(200, 176);
			this->bmpLoaderNew->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->bmpLoaderNew->TabIndex = 0;
			this->bmpLoaderNew->TabStop = false;
			// 
			// myBitmapLoader
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(440, 294);
			this->Controls->Add(this->bmpLoaderNew);
			this->Name = S"myBitmapLoader";
			this->Text = S"Bitmap Loader";
			this->ResumeLayout(false);

		}		
	};
}