namespace NOCR
{
    partial class FormMainWindow
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
            this.menuItem6 = new System.Windows.Forms.MenuItem();
            this.picture_panel = new System.Windows.Forms.Panel();
            this.rtbOutput = new System.Windows.Forms.RichTextBox();
            this.statusBar1 = new System.Windows.Forms.StatusBar();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.crobPictureBox = new System.Windows.Forms.PictureBox();
            this.mnuRemoveNoiseII = new System.Windows.Forms.MenuItem();
            this.menuItem5 = new System.Windows.Forms.MenuItem();
            this.mnuHelpSeparate = new System.Windows.Forms.MenuItem();
            this.mnuAdvancedHelp = new System.Windows.Forms.MenuItem();
            this.mnuHelpBinarize = new System.Windows.Forms.MenuItem();
            this.mnuHelpNoiseRemoval = new System.Windows.Forms.MenuItem();
            this.mnuHelpContrast = new System.Windows.Forms.MenuItem();
            this.mnuHelpTrain = new System.Windows.Forms.MenuItem();
            this.mnuHelpOCR = new System.Windows.Forms.MenuItem();
            this.mnuMagnification = new System.Windows.Forms.MenuItem();
            this.mnuHelpBrowseImage = new System.Windows.Forms.MenuItem();
            this.mnuAbout = new System.Windows.Forms.MenuItem();
            this.mnuVersionInfo = new System.Windows.Forms.MenuItem();
            this.menuItem4 = new System.Windows.Forms.MenuItem();
            this.mnuHowDoI = new System.Windows.Forms.MenuItem();
            this.mnuHelpCropperMain = new System.Windows.Forms.MenuItem();
            this.menuItem8 = new System.Windows.Forms.MenuItem();
            this.mnuHelpSaving = new System.Windows.Forms.MenuItem();
            this.mnuHelpSaveImage = new System.Windows.Forms.MenuItem();
            this.mnuHelpSaveOutput = new System.Windows.Forms.MenuItem();
            this.mnuHelpImage = new System.Windows.Forms.MenuItem();
            this.mnuHelpImageRotateLeft = new System.Windows.Forms.MenuItem();
            this.mnuHelpImageRotateRight = new System.Windows.Forms.MenuItem();
            this.mnuHelpImageRotateUpright = new System.Windows.Forms.MenuItem();
            this.menuItem9 = new System.Windows.Forms.MenuItem();
            this.mnuHelpImageDeskew = new System.Windows.Forms.MenuItem();
            this.menuItem10 = new System.Windows.Forms.MenuItem();
            this.mnuHelpImageRemoveNoise = new System.Windows.Forms.MenuItem();
            this.menuItem1 = new System.Windows.Forms.MenuItem();
            this.panel1 = new System.Windows.Forms.Panel();
            this.rtbMainOutput = new System.Windows.Forms.RichTextBox();
            this.pbOCR = new System.Windows.Forms.ProgressBar();
            this.mnuCropper = new System.Windows.Forms.MenuItem();
            this.mnuLoadImage2 = new System.Windows.Forms.MenuItem();
            this.mnuRotate = new System.Windows.Forms.MenuItem();
            this.mnuSaveImage = new System.Windows.Forms.MenuItem();
            this.mnuStart = new System.Windows.Forms.MenuItem();
            this.mnuFastRecognize = new System.Windows.Forms.MenuItem();
            this.mnuSaveOutput = new System.Windows.Forms.MenuItem();
            this.mnuExit = new System.Windows.Forms.MenuItem();
            this.ocrMenu = new System.Windows.Forms.MainMenu(this.components);
            this.mnuOCR = new System.Windows.Forms.MenuItem();
            this.mnuFastRecognize2 = new System.Windows.Forms.MenuItem();
            this.mnuRecognize = new System.Windows.Forms.MenuItem();
            this.mnuAdvanced = new System.Windows.Forms.MenuItem();
            this.mnuBinarize = new System.Windows.Forms.MenuItem();
            this.menuItem2 = new System.Windows.Forms.MenuItem();
            this.mnuSeparate = new System.Windows.Forms.MenuItem();
            this.mnuTrain = new System.Windows.Forms.MenuItem();
            this.mnuRecognize2 = new System.Windows.Forms.MenuItem();
            this.menuItem3 = new System.Windows.Forms.MenuItem();
            this.mnuMeanRemoval = new System.Windows.Forms.MenuItem();
            this.mnuContrast = new System.Windows.Forms.MenuItem();
            this.mnuContrastAndBinarize = new System.Windows.Forms.MenuItem();
            this.mnuNoiseRemoval = new System.Windows.Forms.MenuItem();
            this.mnuResegment = new System.Windows.Forms.MenuItem();
            this.mnuImage = new System.Windows.Forms.MenuItem();
            this.mnuLoadImage = new System.Windows.Forms.MenuItem();
            this.mnuDeskew = new System.Windows.Forms.MenuItem();
            this.myInfo1 = new System.Windows.Forms.Label();
            this.myInfo = new System.Windows.Forms.Label();
            this.openImageDialog = new System.Windows.Forms.OpenFileDialog();
            this.saveImageDialog = new System.Windows.Forms.SaveFileDialog();
            this.saveOutputDialog = new System.Windows.Forms.SaveFileDialog();
            this.picture_panel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.crobPictureBox)).BeginInit();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuItem6
            // 
            this.menuItem6.Index = 4;
            this.menuItem6.Text = "Deskew Image";
            this.menuItem6.Click += new System.EventHandler(this.menuItem6_Click);
            // 
            // picture_panel
            // 
            this.picture_panel.AllowDrop = true;
            this.picture_panel.AutoScroll = true;
            this.picture_panel.BackColor = System.Drawing.Color.Gainsboro;
            this.picture_panel.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.picture_panel.Controls.Add(this.pictureBox1);
            this.picture_panel.Controls.Add(this.rtbOutput);
            this.picture_panel.Controls.Add(this.statusBar1);
            this.picture_panel.Controls.Add(this.crobPictureBox);
            this.picture_panel.Location = new System.Drawing.Point(12, 12);
            this.picture_panel.Name = "picture_panel";
            this.picture_panel.Size = new System.Drawing.Size(992, 568);
            this.picture_panel.TabIndex = 1;
            this.picture_panel.MouseUp += new System.Windows.Forms.MouseEventHandler(this.picture_panel_MouseUp);
            // 
            // rtbOutput
            // 
            this.rtbOutput.Location = new System.Drawing.Point(5, 12);
            this.rtbOutput.Name = "rtbOutput";
            this.rtbOutput.Size = new System.Drawing.Size(100, 96);
            this.rtbOutput.TabIndex = 20;
            this.rtbOutput.Text = "";
            // 
            // statusBar1
            // 
            this.statusBar1.Location = new System.Drawing.Point(0, 548);
            this.statusBar1.Name = "statusBar1";
            this.statusBar1.Size = new System.Drawing.Size(988, 16);
            this.statusBar1.TabIndex = 18;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(5, 12);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(100, 100);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseDown);
            this.pictureBox1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseMove);
            this.pictureBox1.MouseUp += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseUp);
            // 
            // crobPictureBox
            // 
            this.crobPictureBox.Location = new System.Drawing.Point(865, 12);
            this.crobPictureBox.Name = "crobPictureBox";
            this.crobPictureBox.Size = new System.Drawing.Size(104, 96);
            this.crobPictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.crobPictureBox.TabIndex = 2;
            this.crobPictureBox.TabStop = false;
            this.crobPictureBox.Visible = false;
            // 
            // mnuRemoveNoiseII
            // 
            this.mnuRemoveNoiseII.Index = 5;
            this.mnuRemoveNoiseII.Text = "Remove Noise";
            this.mnuRemoveNoiseII.Click += new System.EventHandler(this.mnuRemoveNoiseII_Click);
            // 
            // menuItem5
            // 
            this.menuItem5.Index = 3;
            this.menuItem5.Text = "-";
            // 
            // mnuHelpSeparate
            // 
            this.mnuHelpSeparate.Index = 1;
            this.mnuHelpSeparate.Text = "Separate";
            this.mnuHelpSeparate.Click += new System.EventHandler(this.mnuHelpSeparate_Click);
            // 
            // mnuAdvancedHelp
            // 
            this.mnuAdvancedHelp.Index = 3;
            this.mnuAdvancedHelp.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.mnuHelpBinarize,
            this.mnuHelpSeparate,
            this.mnuHelpNoiseRemoval,
            this.mnuHelpContrast});
            this.mnuAdvancedHelp.Text = "Advanced";
            // 
            // mnuHelpBinarize
            // 
            this.mnuHelpBinarize.Index = 0;
            this.mnuHelpBinarize.Text = "Binarize";
            this.mnuHelpBinarize.Click += new System.EventHandler(this.mnuHelpBinarize_Click);
            // 
            // mnuHelpNoiseRemoval
            // 
            this.mnuHelpNoiseRemoval.Index = 2;
            this.mnuHelpNoiseRemoval.Text = "Noise Removal";
            this.mnuHelpNoiseRemoval.Click += new System.EventHandler(this.mnuHelpNoiseRemoval_Click);
            // 
            // mnuHelpContrast
            // 
            this.mnuHelpContrast.Index = 3;
            this.mnuHelpContrast.Text = "Contrast";
            this.mnuHelpContrast.Click += new System.EventHandler(this.mnuHelpContrast_Click);
            // 
            // mnuHelpTrain
            // 
            this.mnuHelpTrain.Index = 2;
            this.mnuHelpTrain.Text = "Train";
            this.mnuHelpTrain.Click += new System.EventHandler(this.mnuHelpTrain_Click);
            // 
            // mnuHelpOCR
            // 
            this.mnuHelpOCR.Index = 1;
            this.mnuHelpOCR.Text = "OCR";
            this.mnuHelpOCR.Click += new System.EventHandler(this.mnuHelpOCR_Click);
            // 
            // mnuMagnification
            // 
            this.mnuMagnification.Enabled = false;
            this.mnuMagnification.Index = 5;
            this.mnuMagnification.Text = "Magnification";
            this.mnuMagnification.Click += new System.EventHandler(this.mnuMagnification_Click);
            // 
            // mnuHelpBrowseImage
            // 
            this.mnuHelpBrowseImage.Index = 0;
            this.mnuHelpBrowseImage.Text = "Load Image";
            this.mnuHelpBrowseImage.Click += new System.EventHandler(this.mnuHelpBrowseImage_Click);
            // 
            // mnuAbout
            // 
            this.mnuAbout.Index = 4;
            this.mnuAbout.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.mnuVersionInfo,
            this.menuItem4,
            this.mnuHowDoI,
            this.mnuAdvancedHelp,
            this.mnuHelpCropperMain,
            this.mnuHelpSaving,
            this.mnuHelpImage});
            this.mnuAbout.Text = "&Help";
            // 
            // mnuVersionInfo
            // 
            this.mnuVersionInfo.Index = 0;
            this.mnuVersionInfo.Text = "About &Nepali OCR";
            this.mnuVersionInfo.Click += new System.EventHandler(this.mnuVersionInfo_Click);
            // 
            // menuItem4
            // 
            this.menuItem4.Index = 1;
            this.menuItem4.Text = "-";
            // 
            // mnuHowDoI
            // 
            this.mnuHowDoI.Index = 2;
            this.mnuHowDoI.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.mnuHelpBrowseImage,
            this.mnuHelpOCR,
            this.mnuHelpTrain,
            this.menuItem5,
            this.menuItem6,
            this.mnuRemoveNoiseII});
            this.mnuHowDoI.Text = "How Do I ?";
            // 
            // mnuHelpCropperMain
            // 
            this.mnuHelpCropperMain.Index = 4;
            this.mnuHelpCropperMain.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.menuItem8});
            this.mnuHelpCropperMain.Text = "Cropper";
            // 
            // menuItem8
            // 
            this.menuItem8.Index = 0;
            this.menuItem8.Text = "Select Cropped Image";
            this.menuItem8.Click += new System.EventHandler(this.menuItem8_Click);
            // 
            // mnuHelpSaving
            // 
            this.mnuHelpSaving.Index = 5;
            this.mnuHelpSaving.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.mnuHelpSaveImage,
            this.mnuHelpSaveOutput});
            this.mnuHelpSaving.Text = "Saving";
            // 
            // mnuHelpSaveImage
            // 
            this.mnuHelpSaveImage.Index = 0;
            this.mnuHelpSaveImage.Text = "Image";
            this.mnuHelpSaveImage.Click += new System.EventHandler(this.mnuHelpSaveImage_Click);
            // 
            // mnuHelpSaveOutput
            // 
            this.mnuHelpSaveOutput.Index = 1;
            this.mnuHelpSaveOutput.Text = "Output";
            this.mnuHelpSaveOutput.Click += new System.EventHandler(this.mnuHelpSaveOutput_Click);
            // 
            // mnuHelpImage
            // 
            this.mnuHelpImage.Index = 6;
            this.mnuHelpImage.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.mnuHelpImageRotateLeft,
            this.mnuHelpImageRotateRight,
            this.mnuHelpImageRotateUpright,
            this.menuItem9,
            this.mnuHelpImageDeskew,
            this.menuItem10,
            this.mnuHelpImageRemoveNoise});
            this.mnuHelpImage.Text = "Image";
            // 
            // mnuHelpImageRotateLeft
            // 
            this.mnuHelpImageRotateLeft.Index = 0;
            this.mnuHelpImageRotateLeft.Text = "Roate Left";
            this.mnuHelpImageRotateLeft.Click += new System.EventHandler(this.mnuHelpImageRotateLeft_Click);
            // 
            // mnuHelpImageRotateRight
            // 
            this.mnuHelpImageRotateRight.Index = 1;
            this.mnuHelpImageRotateRight.Text = "Rotate Right";
            this.mnuHelpImageRotateRight.Click += new System.EventHandler(this.mnuHelpImageRotateRight_Click);
            // 
            // mnuHelpImageRotateUpright
            // 
            this.mnuHelpImageRotateUpright.Index = 2;
            this.mnuHelpImageRotateUpright.Text = "Rotate upright";
            this.mnuHelpImageRotateUpright.Click += new System.EventHandler(this.mnuHelpImageRotateUpright_Click);
            // 
            // menuItem9
            // 
            this.menuItem9.Index = 3;
            this.menuItem9.Text = "-";
            // 
            // mnuHelpImageDeskew
            // 
            this.mnuHelpImageDeskew.Index = 4;
            this.mnuHelpImageDeskew.Text = "Deskew";
            this.mnuHelpImageDeskew.Click += new System.EventHandler(this.mnuHelpImageDeskew_Click);
            // 
            // menuItem10
            // 
            this.menuItem10.Index = 5;
            this.menuItem10.Text = "-";
            // 
            // mnuHelpImageRemoveNoise
            // 
            this.mnuHelpImageRemoveNoise.Index = 6;
            this.mnuHelpImageRemoveNoise.Text = "Remove Noise";
            this.mnuHelpImageRemoveNoise.Click += new System.EventHandler(this.mnuHelpImageRemoveNoise_Click);
            // 
            // menuItem1
            // 
            this.menuItem1.Index = 4;
            this.menuItem1.Text = "-";
            // 
            // panel1
            // 
            this.panel1.AutoScroll = true;
            this.panel1.Controls.Add(this.rtbMainOutput);
            this.panel1.Controls.Add(this.pbOCR);
            this.panel1.Location = new System.Drawing.Point(9, 12);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(990, 743);
            this.panel1.TabIndex = 24;
            // 
            // rtbMainOutput
            // 
            this.rtbMainOutput.Location = new System.Drawing.Point(8, 584);
            this.rtbMainOutput.Name = "rtbMainOutput";
            this.rtbMainOutput.Size = new System.Drawing.Size(976, 96);
            this.rtbMainOutput.TabIndex = 19;
            this.rtbMainOutput.Text = "";
            // 
            // pbOCR
            // 
            this.pbOCR.Location = new System.Drawing.Point(3, 686);
            this.pbOCR.Name = "pbOCR";
            this.pbOCR.Size = new System.Drawing.Size(992, 8);
            this.pbOCR.Step = 100;
            this.pbOCR.TabIndex = 23;
            // 
            // mnuCropper
            // 
            this.mnuCropper.Enabled = false;
            this.mnuCropper.Index = 3;
            this.mnuCropper.Text = "Image Cropper";
            this.mnuCropper.Click += new System.EventHandler(this.mnuCropper_Click);
            // 
            // mnuLoadImage2
            // 
            this.mnuLoadImage2.Index = 0;
            this.mnuLoadImage2.Shortcut = System.Windows.Forms.Shortcut.CtrlN;
            this.mnuLoadImage2.Text = "&New Image";
            this.mnuLoadImage2.Click += new System.EventHandler(this.mnuLoadImage2_Click);
            // 
            // mnuRotate
            // 
            this.mnuRotate.Enabled = false;
            this.mnuRotate.Index = 2;
            this.mnuRotate.Shortcut = System.Windows.Forms.Shortcut.CtrlR;
            this.mnuRotate.Text = "Rotate Right";
            this.mnuRotate.Click += new System.EventHandler(this.mnuRotate_Click);
            // 
            // mnuSaveImage
            // 
            this.mnuSaveImage.Enabled = false;
            this.mnuSaveImage.Index = 1;
            this.mnuSaveImage.Shortcut = System.Windows.Forms.Shortcut.CtrlS;
            this.mnuSaveImage.Text = "&Save Image";
            this.mnuSaveImage.Click += new System.EventHandler(this.mnuSaveImage_Click);
            // 
            // mnuStart
            // 
            this.mnuStart.Index = 0;
            this.mnuStart.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.mnuLoadImage2,
            this.mnuSaveImage,
            this.mnuFastRecognize,
            this.mnuSaveOutput,
            this.mnuExit});
            this.mnuStart.Text = "&File";
            // 
            // mnuFastRecognize
            // 
            this.mnuFastRecognize.Enabled = false;
            this.mnuFastRecognize.Index = 2;
            this.mnuFastRecognize.Text = "Fast Recognize";
            this.mnuFastRecognize.Click += new System.EventHandler(this.mnuFastRecognize_Click);
            // 
            // mnuSaveOutput
            // 
            this.mnuSaveOutput.Enabled = false;
            this.mnuSaveOutput.Index = 3;
            this.mnuSaveOutput.Shortcut = System.Windows.Forms.Shortcut.CtrlD;
            this.mnuSaveOutput.Text = "Save Output";
            this.mnuSaveOutput.Click += new System.EventHandler(this.mnuSaveOutput_Click);
            // 
            // mnuExit
            // 
            this.mnuExit.Index = 4;
            this.mnuExit.Shortcut = System.Windows.Forms.Shortcut.CtrlW;
            this.mnuExit.Text = "&Exit";
            this.mnuExit.Click += new System.EventHandler(this.mnuExit_Click);
            // 
            // ocrMenu
            // 
            this.ocrMenu.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.mnuStart,
            this.mnuOCR,
            this.mnuAdvanced,
            this.mnuImage,
            this.mnuAbout});
            // 
            // mnuOCR
            // 
            this.mnuOCR.Enabled = false;
            this.mnuOCR.Index = 1;
            this.mnuOCR.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.mnuFastRecognize2,
            this.mnuRecognize});
            this.mnuOCR.Text = "OCR";
            // 
            // mnuFastRecognize2
            // 
            this.mnuFastRecognize2.Checked = true;
            this.mnuFastRecognize2.Enabled = false;
            this.mnuFastRecognize2.Index = 0;
            this.mnuFastRecognize2.Shortcut = System.Windows.Forms.Shortcut.CtrlO;
            this.mnuFastRecognize2.Text = "&OCR";
            this.mnuFastRecognize2.Click += new System.EventHandler(this.mnuFastRecognize2_Click);
            // 
            // mnuRecognize
            // 
            this.mnuRecognize.Enabled = false;
            this.mnuRecognize.Index = 1;
            this.mnuRecognize.Text = "Recognize";
            this.mnuRecognize.Click += new System.EventHandler(this.mnuRecognize_Click);
            // 
            // mnuAdvanced
            // 
            this.mnuAdvanced.Enabled = false;
            this.mnuAdvanced.Index = 2;
            this.mnuAdvanced.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.mnuBinarize,
            this.menuItem2,
            this.mnuSeparate,
            this.mnuTrain,
            this.mnuRecognize2,
            this.menuItem3,
            this.mnuMeanRemoval,
            this.mnuContrast,
            this.mnuContrastAndBinarize,
            this.mnuNoiseRemoval,
            this.mnuResegment});
            this.mnuAdvanced.Text = "&Advanced";
            // 
            // mnuBinarize
            // 
            this.mnuBinarize.Enabled = false;
            this.mnuBinarize.Index = 0;
            this.mnuBinarize.Shortcut = System.Windows.Forms.Shortcut.CtrlB;
            this.mnuBinarize.Text = "Binarize";
            this.mnuBinarize.Click += new System.EventHandler(this.mnuBinarize_Click);
            // 
            // menuItem2
            // 
            this.menuItem2.Index = 1;
            this.menuItem2.Text = "-";
            // 
            // mnuSeparate
            // 
            this.mnuSeparate.Enabled = false;
            this.mnuSeparate.Index = 2;
            this.mnuSeparate.Shortcut = System.Windows.Forms.Shortcut.CtrlP;
            this.mnuSeparate.Text = "Separate";
            this.mnuSeparate.Click += new System.EventHandler(this.mnuSeparate_Click);
            // 
            // mnuTrain
            // 
            this.mnuTrain.Enabled = false;
            this.mnuTrain.Index = 3;
            this.mnuTrain.Shortcut = System.Windows.Forms.Shortcut.CtrlT;
            this.mnuTrain.Text = "Train";
            this.mnuTrain.Click += new System.EventHandler(this.mnuTrain_Click);
            // 
            // mnuRecognize2
            // 
            this.mnuRecognize2.Enabled = false;
            this.mnuRecognize2.Index = 4;
            this.mnuRecognize2.Shortcut = System.Windows.Forms.Shortcut.CtrlE;
            this.mnuRecognize2.Text = "Recognize";
            this.mnuRecognize2.Click += new System.EventHandler(this.mnuRecognize2_Click);
            // 
            // menuItem3
            // 
            this.menuItem3.Index = 5;
            this.menuItem3.Text = "-";
            // 
            // mnuMeanRemoval
            // 
            this.mnuMeanRemoval.Enabled = false;
            this.mnuMeanRemoval.Index = 6;
            this.mnuMeanRemoval.Text = "Mean Removal";
            this.mnuMeanRemoval.Click += new System.EventHandler(this.mnuMeanRemoval_Click);
            // 
            // mnuContrast
            // 
            this.mnuContrast.Enabled = false;
            this.mnuContrast.Index = 7;
            this.mnuContrast.Text = "Contrast Only";
            this.mnuContrast.Click += new System.EventHandler(this.mnuContrast_Click);
            // 
            // mnuContrastAndBinarize
            // 
            this.mnuContrastAndBinarize.Enabled = false;
            this.mnuContrastAndBinarize.Index = 8;
            this.mnuContrastAndBinarize.Text = "Contrast and Binarize";
            this.mnuContrastAndBinarize.Click += new System.EventHandler(this.mnuContrastAndBinarize_Click);
            // 
            // mnuNoiseRemoval
            // 
            this.mnuNoiseRemoval.Index = 9;
            this.mnuNoiseRemoval.Text = "Noise Removal";
            this.mnuNoiseRemoval.Click += new System.EventHandler(this.mnuNoiseRemoval_Click);
            // 
            // mnuResegment
            // 
            this.mnuResegment.Index = 10;
            this.mnuResegment.Text = "Resegment";
            this.mnuResegment.Click += new System.EventHandler(this.mnuResegment_Click);
            // 
            // mnuImage
            // 
            this.mnuImage.Index = 3;
            this.mnuImage.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.mnuLoadImage,
            this.mnuDeskew,
            this.mnuRotate,
            this.mnuCropper,
            this.menuItem1,
            this.mnuMagnification});
            this.mnuImage.Text = "&Image";
            // 
            // mnuLoadImage
            // 
            this.mnuLoadImage.Index = 0;
            this.mnuLoadImage.Shortcut = System.Windows.Forms.Shortcut.CtrlN;
            this.mnuLoadImage.Text = "Load Image";
            this.mnuLoadImage.Click += new System.EventHandler(this.mnuLoadImage_Click);
            // 
            // mnuDeskew
            // 
            this.mnuDeskew.Enabled = false;
            this.mnuDeskew.Index = 1;
            this.mnuDeskew.Text = "Deskew";
            this.mnuDeskew.Click += new System.EventHandler(this.mnuDeskew_Click);
            // 
            // myInfo1
            // 
            this.myInfo1.Location = new System.Drawing.Point(521, -51);
            this.myInfo1.Name = "myInfo1";
            this.myInfo1.Size = new System.Drawing.Size(72, 24);
            this.myInfo1.TabIndex = 22;
            // 
            // myInfo
            // 
            this.myInfo.Location = new System.Drawing.Point(393, -43);
            this.myInfo.Name = "myInfo";
            this.myInfo.Size = new System.Drawing.Size(72, 8);
            this.myInfo.TabIndex = 21;
            // 
            // openImageDialog
            // 
            this.openImageDialog.Filter = "Image Files(*.BMP;*.JPG;*.GIF;*.png)|*.BMP;*.JPG;*.GIF;*.PNG|All files (*.*)|*.*";
            // 
            // saveImageDialog
            // 
            this.saveImageDialog.DefaultExt = "*.jpg";
            // 
            // FormMainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1018, 729);
            this.Controls.Add(this.picture_panel);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.myInfo1);
            this.Controls.Add(this.myInfo);
            this.Menu = this.ocrMenu;
            this.Name = "FormMainWindow";
            this.Text = "Nepali OCR";
            this.picture_panel.ResumeLayout(false);
            this.picture_panel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.crobPictureBox)).EndInit();
            this.panel1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.MenuItem menuItem6;
        private System.Windows.Forms.Panel picture_panel;
        private System.Windows.Forms.StatusBar statusBar1;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.PictureBox crobPictureBox;
        private System.Windows.Forms.MenuItem mnuRemoveNoiseII;
        private System.Windows.Forms.MenuItem menuItem5;
        private System.Windows.Forms.MenuItem mnuHelpSeparate;
        private System.Windows.Forms.MenuItem mnuAdvancedHelp;
        private System.Windows.Forms.MenuItem mnuHelpBinarize;
        private System.Windows.Forms.MenuItem mnuHelpNoiseRemoval;
        private System.Windows.Forms.MenuItem mnuHelpContrast;
        private System.Windows.Forms.MenuItem mnuHelpTrain;
        private System.Windows.Forms.MenuItem mnuHelpOCR;
        private System.Windows.Forms.MenuItem mnuMagnification;
        private System.Windows.Forms.MenuItem mnuHelpBrowseImage;
        private System.Windows.Forms.MenuItem mnuAbout;
        private System.Windows.Forms.MenuItem mnuVersionInfo;
        private System.Windows.Forms.MenuItem menuItem4;
        private System.Windows.Forms.MenuItem mnuHowDoI;
        private System.Windows.Forms.MenuItem mnuHelpCropperMain;
        private System.Windows.Forms.MenuItem menuItem8;
        private System.Windows.Forms.MenuItem mnuHelpSaving;
        private System.Windows.Forms.MenuItem mnuHelpSaveImage;
        private System.Windows.Forms.MenuItem mnuHelpSaveOutput;
        private System.Windows.Forms.MenuItem mnuHelpImage;
        private System.Windows.Forms.MenuItem mnuHelpImageRotateLeft;
        private System.Windows.Forms.MenuItem mnuHelpImageRotateRight;
        private System.Windows.Forms.MenuItem mnuHelpImageRotateUpright;
        private System.Windows.Forms.MenuItem menuItem9;
        private System.Windows.Forms.MenuItem mnuHelpImageDeskew;
        private System.Windows.Forms.MenuItem menuItem10;
        private System.Windows.Forms.MenuItem mnuHelpImageRemoveNoise;
        private System.Windows.Forms.MenuItem menuItem1;
        private System.Windows.Forms.RichTextBox rtbOutput;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.RichTextBox rtbMainOutput;
        private System.Windows.Forms.MenuItem mnuCropper;
        private System.Windows.Forms.MenuItem mnuLoadImage2;
        private System.Windows.Forms.MenuItem mnuRotate;
        private System.Windows.Forms.MenuItem mnuSaveImage;
        private System.Windows.Forms.MenuItem mnuStart;
        private System.Windows.Forms.MenuItem mnuFastRecognize;
        private System.Windows.Forms.MenuItem mnuSaveOutput;
        private System.Windows.Forms.MenuItem mnuExit;
        private System.Windows.Forms.MainMenu ocrMenu;
        private System.Windows.Forms.MenuItem mnuOCR;
        private System.Windows.Forms.MenuItem mnuFastRecognize2;
        private System.Windows.Forms.MenuItem mnuRecognize;
        private System.Windows.Forms.MenuItem mnuAdvanced;
        private System.Windows.Forms.MenuItem mnuBinarize;
        private System.Windows.Forms.MenuItem menuItem2;
        private System.Windows.Forms.MenuItem mnuSeparate;
        private System.Windows.Forms.MenuItem mnuTrain;
        private System.Windows.Forms.MenuItem mnuRecognize2;
        private System.Windows.Forms.MenuItem menuItem3;
        private System.Windows.Forms.MenuItem mnuMeanRemoval;
        private System.Windows.Forms.MenuItem mnuContrast;
        private System.Windows.Forms.MenuItem mnuContrastAndBinarize;
        private System.Windows.Forms.MenuItem mnuNoiseRemoval;
        private System.Windows.Forms.MenuItem mnuResegment;
        private System.Windows.Forms.MenuItem mnuImage;
        private System.Windows.Forms.MenuItem mnuLoadImage;
        private System.Windows.Forms.MenuItem mnuDeskew;
        private System.Windows.Forms.Label myInfo1;
        private System.Windows.Forms.Label myInfo;
        private System.Windows.Forms.OpenFileDialog openImageDialog;
        private System.Windows.Forms.ProgressBar pbOCR;
        private System.Windows.Forms.SaveFileDialog saveImageDialog;
        private System.Windows.Forms.SaveFileDialog saveOutputDialog;

    }
}

