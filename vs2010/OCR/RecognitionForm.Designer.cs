namespace NOCR
{
    partial class RecognitionForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.charRecBox = new System.Windows.Forms.RichTextBox();
            this.SuspendLayout();
            // 
            // charRecBox
            // 
            this.charRecBox.AutoWordSelection = true;
            this.charRecBox.Location = new System.Drawing.Point(28, 22);
            this.charRecBox.Name = "charRecBox";
            this.charRecBox.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.Vertical;
            this.charRecBox.Size = new System.Drawing.Size(424, 296);
            this.charRecBox.TabIndex = 1;
            this.charRecBox.Text = "";
            // 
            // RecognitionForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(479, 348);
            this.Controls.Add(this.charRecBox);
            this.Name = "RecognitionForm";
            this.Text = "Recognized Text";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.RichTextBox charRecBox;
    }
}