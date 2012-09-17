namespace NOCR
{
    partial class myWindow
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
            this.components = new System.ComponentModel.Container();
            this.panel1 = new System.Windows.Forms.Panel();
            this.pictureBox_myWindow = new System.Windows.Forms.PictureBox();
            this.saveButton_ImageViewer_Form = new System.Windows.Forms.Button();
            this.singleRecog = new System.Windows.Forms.Button();
            this.myWindowMenu = new System.Windows.Forms.MainMenu(this.components);
            this.mnuImage = new System.Windows.Forms.MenuItem();
            this.mnuSave = new System.Windows.Forms.MenuItem();
            this.menuItem1 = new System.Windows.Forms.MenuItem();
            this.mnuSingleRecognize = new System.Windows.Forms.MenuItem();
            this.mnuRecognizeAll = new System.Windows.Forms.MenuItem();
            this.mnuLogs = new System.Windows.Forms.MenuItem();
            this.mnuLogs_Show = new System.Windows.Forms.MenuItem();
            this.mnuLogs_Hide = new System.Windows.Forms.MenuItem();
            this.saveFileDialog_Image_Viewer = new System.Windows.Forms.SaveFileDialog();
            this.myRTB = new System.Windows.Forms.RichTextBox();
            this.rtbOutput = new System.Windows.Forms.RichTextBox();
            this.myWindowRecognizeButton = new System.Windows.Forms.Button();
            this.myWindowSeparateButton = new System.Windows.Forms.Button();
            this.avgHeightLabel = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.avgWidthLabel = new System.Windows.Forms.Label();
            this.smallHeightLabel = new System.Windows.Forms.Label();
            this.bigWidthLabel = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.bigHeightLabel = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.exitButton = new System.Windows.Forms.Button();
            this.nextButton = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.smallWidthLabel = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.pictureBoxSmall = new System.Windows.Forms.PictureBox();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_myWindow)).BeginInit();
            this.groupBox3.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxSmall)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.AutoScroll = true;
            this.panel1.Controls.Add(this.pictureBox_myWindow);
            this.panel1.Location = new System.Drawing.Point(8, 40);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(480, 432);
            this.panel1.TabIndex = 0;
            // 
            // pictureBox_myWindow
            // 
            this.pictureBox_myWindow.Location = new System.Drawing.Point(56, 32);
            this.pictureBox_myWindow.Name = "pictureBox_myWindow";
            this.pictureBox_myWindow.Size = new System.Drawing.Size(100, 50);
            this.pictureBox_myWindow.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pictureBox_myWindow.TabIndex = 0;
            this.pictureBox_myWindow.TabStop = false;
            // 
            // saveButton_ImageViewer_Form
            // 
            this.saveButton_ImageViewer_Form.Location = new System.Drawing.Point(64, 272);
            this.saveButton_ImageViewer_Form.Name = "saveButton_ImageViewer_Form";
            this.saveButton_ImageViewer_Form.Size = new System.Drawing.Size(72, 24);
            this.saveButton_ImageViewer_Form.TabIndex = 14;
            this.saveButton_ImageViewer_Form.Text = "Save";
            this.saveButton_ImageViewer_Form.Click += new System.EventHandler(this.saveButton_ImageViewer_Form_Click);
            // 
            // singleRecog
            // 
            this.singleRecog.Location = new System.Drawing.Point(168, 312);
            this.singleRecog.Name = "singleRecog";
            this.singleRecog.Size = new System.Drawing.Size(88, 24);
            this.singleRecog.TabIndex = 13;
            this.singleRecog.Text = "Single Recog";
            this.singleRecog.Click += new System.EventHandler(this.singleRecog_Click);
            // 
            // myWindowMenu
            // 
            this.myWindowMenu.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.mnuImage});
            // 
            // mnuImage
            // 
            this.mnuImage.Index = 0;
            this.mnuImage.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.mnuSave,
            this.menuItem1,
            this.mnuSingleRecognize,
            this.mnuRecognizeAll,
            this.mnuLogs});
            this.mnuImage.Text = "Image";
            // 
            // mnuSave
            // 
            this.mnuSave.Index = 0;
            this.mnuSave.Shortcut = System.Windows.Forms.Shortcut.CtrlS;
            this.mnuSave.Text = "Save";
            this.mnuSave.Click += new System.EventHandler(this.mnuSave_Click);
            // 
            // menuItem1
            // 
            this.menuItem1.Index = 1;
            this.menuItem1.Text = "-";
            // 
            // mnuSingleRecognize
            // 
            this.mnuSingleRecognize.Index = 2;
            this.mnuSingleRecognize.Shortcut = System.Windows.Forms.Shortcut.CtrlR;
            this.mnuSingleRecognize.Text = "Recognize";
            this.mnuSingleRecognize.Click += new System.EventHandler(this.mnuSingleRecognize_Click);
            // 
            // mnuRecognizeAll
            // 
            this.mnuRecognizeAll.Index = 3;
            this.mnuRecognizeAll.Shortcut = System.Windows.Forms.Shortcut.CtrlO;
            this.mnuRecognizeAll.Text = "Recognize all";
            this.mnuRecognizeAll.Click += new System.EventHandler(this.mnuRecognizeAll_Click);
            // 
            // mnuLogs
            // 
            this.mnuLogs.Index = 4;
            this.mnuLogs.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.mnuLogs_Show,
            this.mnuLogs_Hide});
            this.mnuLogs.Text = "Logs";
            // 
            // mnuLogs_Show
            // 
            this.mnuLogs_Show.Index = 0;
            this.mnuLogs_Show.Text = "Show";
            this.mnuLogs_Show.Click += new System.EventHandler(this.mnuLogs_Show_Click);
            // 
            // mnuLogs_Hide
            // 
            this.mnuLogs_Hide.Index = 1;
            this.mnuLogs_Hide.Text = "Hide";
            this.mnuLogs_Hide.Click += new System.EventHandler(this.mnuLogs_Hide_Click);
            // 
            // myRTB
            // 
            this.myRTB.Location = new System.Drawing.Point(16, 40);
            this.myRTB.Name = "myRTB";
            this.myRTB.Size = new System.Drawing.Size(208, 424);
            this.myRTB.TabIndex = 0;
            this.myRTB.Text = "";
            // 
            // rtbOutput
            // 
            this.rtbOutput.Location = new System.Drawing.Point(56, 112);
            this.rtbOutput.Name = "rtbOutput";
            this.rtbOutput.Size = new System.Drawing.Size(192, 64);
            this.rtbOutput.TabIndex = 15;
            this.rtbOutput.Text = "";
            // 
            // myWindowRecognizeButton
            // 
            this.myWindowRecognizeButton.Location = new System.Drawing.Point(176, 272);
            this.myWindowRecognizeButton.Name = "myWindowRecognizeButton";
            this.myWindowRecognizeButton.Size = new System.Drawing.Size(80, 24);
            this.myWindowRecognizeButton.TabIndex = 12;
            this.myWindowRecognizeButton.Text = "RecognizeAll";
            this.myWindowRecognizeButton.Click += new System.EventHandler(this.myWindowRecognizeButton_Click);
            // 
            // myWindowSeparateButton
            // 
            this.myWindowSeparateButton.Location = new System.Drawing.Point(64, 304);
            this.myWindowSeparateButton.Name = "myWindowSeparateButton";
            this.myWindowSeparateButton.Size = new System.Drawing.Size(80, 40);
            this.myWindowSeparateButton.TabIndex = 11;
            this.myWindowSeparateButton.Text = "Separate";
            this.myWindowSeparateButton.Click += new System.EventHandler(this.myWindowSeparateButton_Click);
            // 
            // avgHeightLabel
            // 
            this.avgHeightLabel.Location = new System.Drawing.Point(152, 72);
            this.avgHeightLabel.Name = "avgHeightLabel";
            this.avgHeightLabel.Size = new System.Drawing.Size(72, 24);
            this.avgHeightLabel.TabIndex = 10;
            // 
            // label6
            // 
            this.label6.Location = new System.Drawing.Point(56, 64);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(88, 24);
            this.label6.TabIndex = 9;
            this.label6.Text = "Average Height";
            // 
            // label5
            // 
            this.label5.Location = new System.Drawing.Point(56, 40);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(80, 24);
            this.label5.TabIndex = 7;
            this.label5.Text = "Average width";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.myRTB);
            this.groupBox3.Location = new System.Drawing.Point(796, 12);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(240, 472);
            this.groupBox3.TabIndex = 5;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Logs";
            this.groupBox3.Visible = false;
            // 
            // avgWidthLabel
            // 
            this.avgWidthLabel.Location = new System.Drawing.Point(152, 40);
            this.avgWidthLabel.Name = "avgWidthLabel";
            this.avgWidthLabel.Size = new System.Drawing.Size(72, 24);
            this.avgWidthLabel.TabIndex = 8;
            // 
            // smallHeightLabel
            // 
            this.smallHeightLabel.Location = new System.Drawing.Point(64, 16);
            this.smallHeightLabel.Name = "smallHeightLabel";
            this.smallHeightLabel.Size = new System.Drawing.Size(56, 16);
            this.smallHeightLabel.TabIndex = 2;
            // 
            // bigWidthLabel
            // 
            this.bigWidthLabel.Location = new System.Drawing.Point(224, 16);
            this.bigWidthLabel.Name = "bigWidthLabel";
            this.bigWidthLabel.Size = new System.Drawing.Size(120, 16);
            this.bigWidthLabel.TabIndex = 4;
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(144, 16);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(72, 16);
            this.label2.TabIndex = 3;
            this.label2.Text = "Image Width";
            // 
            // bigHeightLabel
            // 
            this.bigHeightLabel.Location = new System.Drawing.Point(88, 16);
            this.bigHeightLabel.Name = "bigHeightLabel";
            this.bigHeightLabel.Size = new System.Drawing.Size(56, 16);
            this.bigHeightLabel.TabIndex = 2;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.rtbOutput);
            this.groupBox2.Controls.Add(this.saveButton_ImageViewer_Form);
            this.groupBox2.Controls.Add(this.singleRecog);
            this.groupBox2.Controls.Add(this.myWindowRecognizeButton);
            this.groupBox2.Controls.Add(this.myWindowSeparateButton);
            this.groupBox2.Controls.Add(this.avgHeightLabel);
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.Controls.Add(this.avgWidthLabel);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.exitButton);
            this.groupBox2.Controls.Add(this.nextButton);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.smallWidthLabel);
            this.groupBox2.Controls.Add(this.smallHeightLabel);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.pictureBoxSmall);
            this.groupBox2.Location = new System.Drawing.Point(524, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(264, 480);
            this.groupBox2.TabIndex = 4;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Sliced Single Image";
            // 
            // exitButton
            // 
            this.exitButton.Location = new System.Drawing.Point(168, 424);
            this.exitButton.Name = "exitButton";
            this.exitButton.Size = new System.Drawing.Size(96, 48);
            this.exitButton.TabIndex = 6;
            this.exitButton.Text = "Exit";
            this.exitButton.Click += new System.EventHandler(this.exitButton_Click);
            // 
            // nextButton
            // 
            this.nextButton.Location = new System.Drawing.Point(128, 352);
            this.nextButton.Name = "nextButton";
            this.nextButton.Size = new System.Drawing.Size(64, 40);
            this.nextButton.TabIndex = 5;
            this.nextButton.Text = "Next";
            this.nextButton.Click += new System.EventHandler(this.nextButton_Click);
            // 
            // label3
            // 
            this.label3.Location = new System.Drawing.Point(128, 16);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(56, 16);
            this.label3.TabIndex = 4;
            this.label3.Text = "Width";
            // 
            // smallWidthLabel
            // 
            this.smallWidthLabel.Location = new System.Drawing.Point(192, 16);
            this.smallWidthLabel.Name = "smallWidthLabel";
            this.smallWidthLabel.Size = new System.Drawing.Size(56, 16);
            this.smallWidthLabel.TabIndex = 3;
            // 
            // label4
            // 
            this.label4.Location = new System.Drawing.Point(16, 16);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(40, 16);
            this.label4.TabIndex = 1;
            this.label4.Text = "Height";
            // 
            // pictureBoxSmall
            // 
            this.pictureBoxSmall.Location = new System.Drawing.Point(152, 200);
            this.pictureBoxSmall.Name = "pictureBoxSmall";
            this.pictureBoxSmall.Size = new System.Drawing.Size(100, 50);
            this.pictureBoxSmall.TabIndex = 0;
            this.pictureBoxSmall.TabStop = false;
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(8, 16);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(72, 16);
            this.label1.TabIndex = 1;
            this.label1.Text = "Image Height";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.bigWidthLabel);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.bigHeightLabel);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.panel1);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(504, 480);
            this.groupBox1.TabIndex = 3;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Input Image";
            // 
            // myWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1046, 555);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Menu = this.myWindowMenu;
            this.Name = "myWindow";
            this.Text = "myWindow";
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_myWindow)).EndInit();
            this.groupBox3.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxSmall)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.PictureBox pictureBox_myWindow;
        private System.Windows.Forms.Button saveButton_ImageViewer_Form;
        private System.Windows.Forms.Button singleRecog;
        private System.Windows.Forms.MainMenu myWindowMenu;
        private System.Windows.Forms.MenuItem mnuImage;
        private System.Windows.Forms.MenuItem mnuSave;
        private System.Windows.Forms.MenuItem menuItem1;
        private System.Windows.Forms.MenuItem mnuSingleRecognize;
        private System.Windows.Forms.MenuItem mnuRecognizeAll;
        private System.Windows.Forms.MenuItem mnuLogs;
        private System.Windows.Forms.MenuItem mnuLogs_Show;
        private System.Windows.Forms.MenuItem mnuLogs_Hide;
        private System.Windows.Forms.SaveFileDialog saveFileDialog_Image_Viewer;
        private System.Windows.Forms.RichTextBox myRTB;
        private System.Windows.Forms.RichTextBox rtbOutput;
        private System.Windows.Forms.Button myWindowRecognizeButton;
        private System.Windows.Forms.Button myWindowSeparateButton;
        private System.Windows.Forms.Label avgHeightLabel;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label avgWidthLabel;
        private System.Windows.Forms.Label smallHeightLabel;
        private System.Windows.Forms.Label bigWidthLabel;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label bigHeightLabel;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button exitButton;
        private System.Windows.Forms.Button nextButton;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label smallWidthLabel;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.PictureBox pictureBoxSmall;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBox1;
    }
}