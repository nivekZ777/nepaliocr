namespace NOCR
{
    partial class TrainingForm
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
            this.mnuTrainer = new System.Windows.Forms.MenuItem();
            this.mnuAdd = new System.Windows.Forms.MenuItem();
            this.mnuTrain = new System.Windows.Forms.MenuItem();
            this.mnuExit = new System.Windows.Forms.MenuItem();
            this.mnuNext = new System.Windows.Forms.MenuItem();
            this.trainMenu = new System.Windows.Forms.MainMenu(this.components);
            this.menuItem4 = new System.Windows.Forms.MenuItem();
            this.mnuPrevious = new System.Windows.Forms.MenuItem();
            this.lblOutput = new System.Windows.Forms.Label();
            this.statusBar1 = new System.Windows.Forms.StatusBar();
            this.addChar = new System.Windows.Forms.Button();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.combineChar = new System.Windows.Forms.TextBox();
            this.trainButton = new System.Windows.Forms.Button();
            this.characterBox = new System.Windows.Forms.ComboBox();
            this.prevButton = new System.Windows.Forms.Button();
            this.nextButton = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // mnuTrainer
            // 
            this.mnuTrainer.Index = 0;
            this.mnuTrainer.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.mnuAdd,
            this.mnuTrain,
            this.mnuExit});
            this.mnuTrainer.Text = "Trainer";
            // 
            // mnuAdd
            // 
            this.mnuAdd.Index = 0;
            this.mnuAdd.Shortcut = System.Windows.Forms.Shortcut.CtrlA;
            this.mnuAdd.Text = "&Add";
            this.mnuAdd.Click += new System.EventHandler(this.mnuAdd_Click);
            // 
            // mnuTrain
            // 
            this.mnuTrain.Index = 1;
            this.mnuTrain.Shortcut = System.Windows.Forms.Shortcut.CtrlS;
            this.mnuTrain.Text = "&Train";
            this.mnuTrain.Click += new System.EventHandler(this.mnuTrain_Click);
            // 
            // mnuExit
            // 
            this.mnuExit.Index = 2;
            this.mnuExit.Shortcut = System.Windows.Forms.Shortcut.CtrlW;
            this.mnuExit.Text = "&Exit";
            this.mnuExit.Click += new System.EventHandler(this.mnuExit_Click);
            // 
            // mnuNext
            // 
            this.mnuNext.Index = 0;
            this.mnuNext.Shortcut = System.Windows.Forms.Shortcut.CtrlN;
            this.mnuNext.Text = "&Next";
            this.mnuNext.Click += new System.EventHandler(this.mnuNext_Click);
            // 
            // trainMenu
            // 
            this.trainMenu.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.mnuTrainer,
            this.menuItem4});
            // 
            // menuItem4
            // 
            this.menuItem4.Index = 1;
            this.menuItem4.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.mnuNext,
            this.mnuPrevious});
            this.menuItem4.Text = "Scroll";
            // 
            // mnuPrevious
            // 
            this.mnuPrevious.Index = 1;
            this.mnuPrevious.Shortcut = System.Windows.Forms.Shortcut.CtrlP;
            this.mnuPrevious.Text = "&Previous";
            this.mnuPrevious.Click += new System.EventHandler(this.mnuPrevious_Click);
            // 
            // lblOutput
            // 
            this.lblOutput.Location = new System.Drawing.Point(200, 92);
            this.lblOutput.Name = "lblOutput";
            this.lblOutput.Size = new System.Drawing.Size(48, 24);
            this.lblOutput.TabIndex = 24;
            // 
            // statusBar1
            // 
            this.statusBar1.Location = new System.Drawing.Point(0, 410);
            this.statusBar1.Name = "statusBar1";
            this.statusBar1.Size = new System.Drawing.Size(742, 22);
            this.statusBar1.TabIndex = 23;
            // 
            // addChar
            // 
            this.addChar.Location = new System.Drawing.Point(304, 156);
            this.addChar.Name = "addChar";
            this.addChar.Size = new System.Drawing.Size(56, 34);
            this.addChar.TabIndex = 22;
            this.addChar.Text = "Add (CtrlA)";
            this.addChar.Click += new System.EventHandler(this.addChar_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(16, 8);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(104, 112);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // combineChar
            // 
            this.combineChar.Location = new System.Drawing.Point(168, 164);
            this.combineChar.Name = "combineChar";
            this.combineChar.Size = new System.Drawing.Size(100, 20);
            this.combineChar.TabIndex = 21;
            this.combineChar.TextChanged += new System.EventHandler(this.combineChar_TextChanged);
            // 
            // trainButton
            // 
            this.trainButton.Location = new System.Drawing.Point(304, 196);
            this.trainButton.Name = "trainButton";
            this.trainButton.Size = new System.Drawing.Size(56, 40);
            this.trainButton.TabIndex = 20;
            this.trainButton.Text = "Train (Ctrl S)";
            this.trainButton.Click += new System.EventHandler(this.trainButton_Click);
            // 
            // characterBox
            // 
            this.characterBox.Location = new System.Drawing.Point(16, 164);
            this.characterBox.Name = "characterBox";
            this.characterBox.Size = new System.Drawing.Size(121, 21);
            this.characterBox.TabIndex = 19;
            // 
            // prevButton
            // 
            this.prevButton.Location = new System.Drawing.Point(200, 36);
            this.prevButton.Name = "prevButton";
            this.prevButton.Size = new System.Drawing.Size(72, 40);
            this.prevButton.TabIndex = 18;
            this.prevButton.Text = "<<Previous (Ctrl P)";
            this.prevButton.Click += new System.EventHandler(this.prevButton_Click);
            // 
            // nextButton
            // 
            this.nextButton.Location = new System.Drawing.Point(296, 36);
            this.nextButton.Name = "nextButton";
            this.nextButton.Size = new System.Drawing.Size(56, 40);
            this.nextButton.TabIndex = 17;
            this.nextButton.Text = "NEXT>> (Ctrl N)";
            this.nextButton.Click += new System.EventHandler(this.nextButton_Click);
            // 
            // panel1
            // 
            this.panel1.AutoScroll = true;
            this.panel1.Controls.Add(this.pictureBox1);
            this.panel1.Location = new System.Drawing.Point(8, 4);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(128, 128);
            this.panel1.TabIndex = 16;
            // 
            // TrainingForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(742, 432);
            this.Controls.Add(this.lblOutput);
            this.Controls.Add(this.statusBar1);
            this.Controls.Add(this.addChar);
            this.Controls.Add(this.combineChar);
            this.Controls.Add(this.trainButton);
            this.Controls.Add(this.characterBox);
            this.Controls.Add(this.prevButton);
            this.Controls.Add(this.nextButton);
            this.Controls.Add(this.panel1);
            this.Menu = this.trainMenu;
            this.Name = "TrainingForm";
            this.Text = "TrainingForm";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuItem mnuTrainer;
        private System.Windows.Forms.MenuItem mnuAdd;
        private System.Windows.Forms.MenuItem mnuTrain;
        private System.Windows.Forms.MenuItem mnuExit;
        private System.Windows.Forms.MenuItem mnuNext;
        private System.Windows.Forms.MainMenu trainMenu;
        private System.Windows.Forms.MenuItem menuItem4;
        private System.Windows.Forms.MenuItem mnuPrevious;
        private System.Windows.Forms.Label lblOutput;
        private System.Windows.Forms.StatusBar statusBar1;
        private System.Windows.Forms.Button addChar;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.TextBox combineChar;
        private System.Windows.Forms.Button trainButton;
        private System.Windows.Forms.ComboBox characterBox;
        private System.Windows.Forms.Button prevButton;
        private System.Windows.Forms.Button nextButton;
        private System.Windows.Forms.Panel panel1;
    }
}