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
			this->panel_myWindow->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel_myWindow
			// 
			this->panel_myWindow->AutoScroll = true;
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
	};
}