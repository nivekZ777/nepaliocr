using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.Drawing.Imaging;
using NOCR.Help;

namespace NOCR
{
    public partial class FormMainWindow : Form
    {
        public System.IO.StreamWriter logFile = new System.IO.StreamWriter("ocr.log");

        //user variable start 
        private Bitmap im, backup;
        private int pointX1, pointX2, pointY1, pointY2, xMouseDistance, yMouseDistance; //for capturing the points

        private Otsu ot = new Otsu();
        private Bitmap BinaryImage;
        private Bitmap selectedImage;
        private Graphics g;
        private int intLevel;
        private int[,] ImgArray;
        private int[,] BackupImgArray;
        private int[,] HeadBottom;

        private bool[,] BArray;
        private bool[,] BackupBArray;
        private bool[,] tmpBArray;
        private bool BinaryDone;
        private bool ImageLoaded;
        bool SeparateDone;
        bool ContrastDone;
        bool meanDone;
        bool deskewDone;
        bool rtbOutputShowing;
        bool imageSelection;
        bool TouchingCharIdentified;
        bool dragEnabled;
        private Point m_PanStartPoint;




        private int numberOfLines;
        //new variables
        int SizeThreshold;
        int totalUnits;
        int[] WStore;

        private Line[] Lines;

        private String applicationPath;
        String modelTrainDBPath;
        String scriptFilePath;
        String characterDBPath;

        private Thread ocrSampleThread;

        private System.Collections.SortedList slForCharacters;
        private System.Collections.SortedList slModelTranscription;	// for storing the model transcriptions
        private System.Collections.ArrayList alModelRec;			// for models that already recognized
        public FormMainWindow()
        {
            //user declarations
            this.BinaryDone = false;
            this.ImageLoaded = false;
            this.SeparateDone = false;
            this.ContrastDone = false;
            this.meanDone = false;
            this.deskewDone = false;
            this.TouchingCharIdentified = false;
            this.rtbOutputShowing = false;


            InitializeComponent();

            this.applicationPath = Application.StartupPath.ToString();

            int len = this.applicationPath.Length - 1;
            if (this.applicationPath.Substring(len).Equals("\\"))
            {
                this.applicationPath = this.applicationPath.Substring(0, len);
            }


            this.logFile.WriteLine("Log started ");
            this.logFile.WriteLine("ApplicationPath: ");
            this.logFile.WriteLine(Application.StartupPath.ToString());

            this.modelTrainDBPath += string.Concat(this.applicationPath, "\\htk\\DataBaseFile\\modelTrainDataBase.txt");

            this.alModelRec = new System.Collections.ArrayList();
            this.characterDBPath += string.Concat(this.applicationPath, "\\htk\\DataBaseFile\\characters.txt");
            this.scriptFilePath += string.Concat(this.applicationPath, "\\htk\\recognizer\\script.txt");

            this.LoadFromFile();
            this.delRTB();
        }



        public unsafe void Conv3x3(ConvMatrix m)
        {
            SetWaitCursorMethod(Cursors.WaitCursor);


            try
            {
                // Avoid divide by zero errors
                if (0 == m.Factor) return;

                Bitmap bSrc = (Bitmap)im.Clone();

                // GDI+ still lies to us - the return format is BGR, NOT RGB.
                BitmapData bmData = im.LockBits(new Rectangle(0, 0, im.Width, im.Height), ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);
                BitmapData bmSrc = bSrc.LockBits(new Rectangle(0, 0, bSrc.Width, bSrc.Height), ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);

                int stride = bmData.Stride;
                int stride2 = stride * 2;
                IntPtr Scan0 = bmData.Scan0;
                IntPtr SrcScan0 = bmSrc.Scan0;

                Byte* p = (Byte*)Scan0;
                Byte* pSrc = (Byte*)SrcScan0;

                int nOffset = stride - im.Width * 3;
                int nWidth = im.Width - 2;
                int nHeight = im.Height - 2;

                int nPixel;

                for (int y = 0; y < nHeight; ++y)
                {
                    for (int x = 0; x < nWidth; ++x)
                    {
                        nPixel = ((((pSrc[2] * m.TopLeft) + (pSrc[5] * m.TopMid) + (pSrc[8] * m.TopRight) +
                            (pSrc[2 + stride] * m.MidLeft) + (pSrc[5 + stride] * m.Pixel) + (pSrc[8 + stride] * m.MidRight) +
                            (pSrc[2 + stride2] * m.BottomLeft) + (pSrc[5 + stride2] * m.BottomMid) + (pSrc[8 + stride2] * m.BottomRight)) / m.Factor) + m.Offset);

                        if (nPixel < 0) nPixel = 0;
                        if (nPixel > 255) nPixel = 255;

                        p[5 + stride] = (Byte)nPixel;

                        nPixel = ((((pSrc[1] * m.TopLeft) + (pSrc[4] * m.TopMid) + (pSrc[7] * m.TopRight) +
                            (pSrc[1 + stride] * m.MidLeft) + (pSrc[4 + stride] * m.Pixel) + (pSrc[7 + stride] * m.MidRight) +
                            (pSrc[1 + stride2] * m.BottomLeft) + (pSrc[4 + stride2] * m.BottomMid) + (pSrc[7 + stride2] * m.BottomRight)) / m.Factor) + m.Offset);

                        if (nPixel < 0) nPixel = 0;
                        if (nPixel > 255) nPixel = 255;

                        p[4 + stride] = (Byte)nPixel;

                        nPixel = ((((pSrc[0] * m.TopLeft) + (pSrc[3] * m.TopMid) + (pSrc[6] * m.TopRight) +
                            (pSrc[0 + stride] * m.MidLeft) + (pSrc[3 + stride] * m.Pixel) + (pSrc[6 + stride] * m.MidRight) +
                            (pSrc[0 + stride2] * m.BottomLeft) + (pSrc[3 + stride2] * m.BottomMid) + (pSrc[6 + stride2] * m.BottomRight)) / m.Factor) + m.Offset);

                        if (nPixel < 0) nPixel = 0;
                        if (nPixel > 255) nPixel = 255;

                        p[3 + stride] = (Byte)nPixel;

                        p += 3;
                        pSrc += 3;
                    }
                    p += nOffset;
                    pSrc += nOffset;
                }

                im.UnlockBits(bmData);
                bSrc.UnlockBits(bmSrc);

                this.pictureBox1.Image = im;
                g = this.pictureBox1.CreateGraphics();
                //System.Windows.Forms.MessageBox.Show("Mean Removal Done!!!!","Threshold Value");
            }
            catch (Exception ex)
            {
                System.Windows.Forms.MessageBox.Show(ex.Message.ToString(), "Failed to Apply Mean Removal!!", System.Windows.Forms.MessageBoxButtons.OK, System.Windows.Forms.MessageBoxIcon.Error);
            }
            SetNormalCursorMethod(Cursors.Default);


        }


        #region uncomment later
        
		private unsafe void Contrast(int nContrast)
		{
			SetWaitCursorMethod(Cursors.WaitCursor);
			

				//This method increases the contrast of the image. 
				//Thus making the image more visible. 

			
			if(this.im.PixelFormat != System.Drawing.Imaging.PixelFormat.Format24bppRgb){
				UpdateStatusBarMethod( @"Pixelformat is not 24 bytes per pixel RGB \(Format24bppRgb\)");
				//System.Windows.Forms.MessageBox.Show("Pixelformat is not 24 bytes per pixel RGB","Format24bppRgb");
				return;
			}
			//this.Cursor = System.Windows.Forms.Cursors.WaitCursor;
			try{
			double pixel = 0, contrast = (100.0+nContrast)/100.0;

			contrast *= contrast;

			int red, green, blue;
			
			// GDI+ still lies to us - the return format is BGR, NOT RGB.
			BitmapData bmData = im.LockBits(new Rectangle(0, 0, im.Width, im.Height), ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);
			int stride = bmData.Stride;
			IntPtr Scan0 = bmData.Scan0;
			
			//System.Byte p;
            Byte* p = (Byte*)(void*)Scan0;
			
			
				//Color clr = b.GetPixel(i,j);
				//int p= clr.ToArgb();				
			
				int nOffset = stride - im.Width*3;

				for(int y=0;y<im.Height;++y)
				{
					for(int x=0; x < im.Width; ++x )
					{
						blue = p[0];
						green = p[1];
						red = p[2];
				
						pixel = red/255.0;
						pixel -= 0.5;
						pixel *= contrast;
						pixel += 0.5;
						pixel *= 255;
						if (pixel < 0) pixel = 0;
						if (pixel > 255) pixel = 255;
						p[2] = (Byte) pixel;

						pixel = green/255.0;
						pixel -= 0.5;
						pixel *= contrast;
						pixel += 0.5;
						pixel *= 255;
						if (pixel < 0) pixel = 0;
						if (pixel > 255) pixel = 255;
						p[1] = (Byte) pixel;

						pixel = blue/255.0;
						pixel -= 0.5;
						pixel *= contrast;
						pixel += 0.5;
						pixel *= 255;
						if (pixel < 0) pixel = 0;
						if (pixel > 255) pixel = 255;
						p[0] = (Byte) pixel;					

						p += 3;
					}
					p += nOffset;
				}
			

			im.UnlockBits(bmData);
			
			this.pictureBox1.Image = im;
			g=this.pictureBox1.CreateGraphics();
			//System.Windows.Forms.MessageBox.Show("Contrast Done!!!!","Threshold Value"); ///fLevel.ToString()/
			}
		catch(Exception ex)
			{
				System.Windows.Forms.MessageBox.Show(ex.Message.ToString(),"Failed to Improve the Contrast!!",System.Windows.Forms.MessageBoxButtons.OK,System.Windows.Forms.MessageBoxIcon.Error);
				SetNormalCursorMethod(Cursors.Default);
			}
            SetNormalCursorMethod(Cursors.Default);
	

//			return true;
		}

        // end of function 
        
        #endregion

        private void Recognize()
        {
            /*
                    This method is used to recognize the text in the image.
                    First It loads the trained Data into Memory (Text)
		
                    Secondly It loads the separated lines, words and characters in the Memory (Images )
		
                    Performance Due to Trained Data(Text):
                    The overall performance of the OCR is affected by the Training data. 
                    For greater accuracy We train more but all those trained data has to be loaded. 
                    Finally due to this, It seems as if OCR is running slowly.

                    Performance due to Separated Words (Images)
                    The Performance also depends upon the separated characters. 
                    If the characters cannot be separated, its hard to recognize.


            */

            SetWaitCursorMethod(Cursors.WaitCursor);


            //Setting the cursor to wait because we will have a long process in the background
            RecognitionProcess rp = new RecognitionProcess(this.applicationPath, this.ImgArray);
            //Calling the recognition Process
            // load the transcription of the models

            UpdateStatusBarMethod("Loading Models ....");

            //aakarList added 
            //aakarList = new System.Collections.ArrayList();
            this.slModelTranscription = rp.LoadModelTranscriptions(this.modelTrainDBPath);

            //this.aakarList =  rp.aakarsList;
            //this.rassoEEkarList = rp.rassoEEkarList;


            int lineCount = this.numberOfLines;
            int wordCount = 0;
            int totalUnit = 0;
            int unitCount = 0;
            int left_x, right_x, top_y, bottom_y;
            System.String wordToRec = "";
            System.String dirOfRecFile = rp.recognitionTempFileDir;

            UpdateStatusBarMethod("Searching database directories ..");

            for (int i = 0; i < lineCount; i++)
            {
                top_y = this.Lines[i].getStartRow();//line start
                bottom_y = this.Lines[i].getEndRow();//line end

                wordCount = this.Lines[i].getTotalWord();
                for (int j = 0; j < wordCount; j++)
                {
                    unitCount = this.Lines[i].Words[j].getTotalUnit();
                    for (int k = 0; k < unitCount; k++)
                    {
                        left_x = this.Lines[i].Words[j].Units[k].getStartColumn();//wrod start
                        right_x = this.Lines[i].Words[j].Units[k].getEndColumn();//word end

                        // setting the actual image boundary
                        UpdateStatusBarMethod("Setting Image Boundaries ..");

                        rp.SetImageBoundary(left_x, right_x, top_y, bottom_y);
                        totalUnit++;
                        wordToRec += string.Concat(dirOfRecFile, totalUnit.ToString(), ".txt");

                        UpdateStatusBarMethod("Preparing word datas.. and running HTK Recognizer..  ");

                        rp.PrepareWordData(wordToRec);
                        UpdateStatusBarMethod("Recognization process in progress .. This may take some time .. please wait");
                    }
                }//wordcount
            }

            // preparing the script file to be recognized
            try
            {
                System.IO.StreamWriter sw = System.IO.File.AppendText(rp.scriptFilePath);
                for (int i = 1; i <= totalUnit; i++)
                {
                    System.String tmp = string.Concat((String)"\"", dirOfRecFile, i.ToString(), (String)".txt", (String)"\"");
                    sw.WriteLine(tmp);
                    sw.Flush();
                    //sw.WriteLine("\"" + dirOfRecFile+i + ".txt" + "\"");
                }
                sw.Close();
            }
            catch (System.Exception ex)
            {
                if (!this.InvokeRequired)
                {
                    System.Windows.Forms.MessageBox.Show(ex.Message.ToString(),
                                                         "Failed to prepare the script file!!",
                                                         System.Windows.Forms.MessageBoxButtons.OK,
                                                         System.Windows.Forms.MessageBoxIcon.Error);
                }
                return;
            }

            // recognize the words from the features file using the Viterbi decoder of the HTK Toolkit HVite
            // then read the Master Labeled File(MLF) and fetch the output models

            UpdateStatusBarMethod("Recognisation process in progress.. Please wait..");

            this.alModelRec = rp.RecognizeByHTK();
            UpdateStatusBarMethod("Recognition process complete..Showing Output...");

            this.ProvideOutput();

             UpdateStatusBarMethod(" Done.");
            
            /* after recognizing is done remove the script file and also the associated image features files */
            // remove the script file

            System.IO.File.Delete(rp.scriptFilePath);

            // remove all the temporary word image feature files
            for (int i = 1; i <= totalUnit; i++)
            {
                System.String tmp = string.Concat(dirOfRecFile, i.ToString(), ".txt");
                //System.IO.File.Delete(dirOfRecFile+i+".txt");
                System.IO.File.Delete(tmp);
            }

            SetNormalCursorMethod(Cursors.Default);
            UpdateStatusBarMethod("Output window closed");
            //this.pbOCR.Value = 100;


            this.logFile.Close();
        }


        private void callPostProcessor(String text)
        {
            this.logFile.WriteLine(" Going to Run postprocessor  ....");
            PostProcessor postProcessor = new PostProcessor(text);
            this.rtbMainOutput.Text = postProcessor.TextPostProcessor();
            this.logFile.WriteLine(" Postprocessor Success.");
            /*
            String finalOutputFileName = String.Concat(Application.StartupPath.ToString(), "\\", "rawOutput.txt");
            //Delete previous file
            if (System.IO.File.Exists(finalOutputFileName))
            {
                try
                {
                    this.logFile.WriteLine("Cleaning old files ....");
                    System.IO.File.Delete(finalOutputFileName);
                    this.logFile.WriteLine("Succes cleaning old temporary files");
                }
                catch (System.Exception ex)
                {
                    this.logFile.WriteLine(String.Concat("Could not delete the files created by the previous OCR process \n\n Error Details : \n ---------------------\n ", ex.ToString()));

                    System.Windows.Forms.MessageBox.Show(String.Concat("Could not delete the files created by the previous OCR process \n\n Error Details : \n ---------------------\n ", ex.ToString()), "Cleaning Error");
                }
            }

            //Run the Post Processor Application
            
            
            //externalPostProcessor extPP = new externalPostProcessor(Application.StartupPath.ToString(), "ocrTextProcessor.exe");
            PostProcessor postProcessor = new PostProcessor(text);
           this.rtbMainOutput.Text =  postProcessor.TextPostProcessor();
            this.logFile.WriteLine(" Postprocessor Success.");

            /*
            if (System.IO.File.Exists(finalOutputFileName))
            {
                this.logFile.WriteLine(" Output File exists  ....");
                //System.Windows.Forms.MessageBox.Show("File Exists");					
                System.IO.StreamReader sr1 = new System.IO.StreamReader(finalOutputFileName);
                this.logFile.WriteLine(" Read output file  ....");

                ///FINAL OUTPUT HERE 
                //Show The final output in Main window 


                this.rtbMainOutput.Text = "";
                while (sr1.Peek() >= 0)
                {
                    this.rtbMainOutput.AppendText(sr1.ReadLine().ToString());
                    this.rtbMainOutput.AppendText("\n");


                }

                ///FINAL OUTPUT HERE 
                //Show The final output in Main window 

                //this.rtbMainOutput.Text = tempStr;


                //TEST RECOGNITIONWINDOW
                //RecognitionForm rw = new RecognitionForm();
                //rw.showText(tempStr);
                //rw.ShowDialog();

            }
            else
            {
                this.logFile.WriteLine("The output file could not be found");
                //System.Windows.Forms.MessageBox.Show("Still not complete");
                this.rtbMainOutput.Text = text;

            }
             */
        }




        private void close_button_Click_1(System.Object sender, System.EventArgs e)
        {
            //this.Dispose(true);

            this.makeBinary();


        }


        private void openImage_Click(System.Object sender, System.EventArgs e)
        {

            this.openImageFile();


        }

        private void separate_button_Click(System.Object sender, System.EventArgs e)
        {
            if ((this.ImageLoaded == true) && (this.BinaryDone == true))
            {
                this.separate();
            }
            else if ((this.ImageLoaded == false))
            {
                System.Windows.Forms.MessageBox.Show("Please load the image first", "Image not loaded");
            }
            else if (this.BinaryDone == false)
            {
                //System.Windows.Forms.Show("Please binarize the image before separating","Binarization not done");
                System.Windows.Forms.MessageBox.Show("Please binarize the image first", "Binarization not done");

            }
        }

        private void saveImage_Click(System.Object sender, System.EventArgs e)
        {
            this.saveImageFile();
        }




        //Try magnify function

        private void tryMagnify()
        {

            this.Contrast(10);

            this.ContrastDone = true;
            this.Update();


            //Binarization
            this.makeBinary();

            //separation
            this.SeparateDone = false;
            this.separate();


            NOCR.myWindow mw = new NOCR.myWindow(this.im,
            this.BinaryImage,
                this.g,
                this.intLevel,
                this.ImgArray,
                this.BArray,
                this.tmpBArray,
                this.BinaryDone,
                this.ImageLoaded,
                this.SeparateDone,
                this.ContrastDone,
                this.meanDone,
                this.deskewDone,
                this.numberOfLines,
                this.Lines,
                this.applicationPath,
                this.modelTrainDBPath,
                this.scriptFilePath,
                this.characterDBPath,
                this.slForCharacters,
                this.slModelTranscription,	// for storing the model transcriptions
                this.alModelRec
                );


            mw.defineVar(this.ImgArray, this.tmpBArray, this.Lines, this.numberOfLines);
            //mw.MdiParent = this;
            //mw.Show();
            //mw.ShowDialog();
            mw.Show();
        }

        private void findMagnification_Click(System.Object sender, System.EventArgs e)
        {
            if (this.ImageLoaded)
            {
                tryMagnify();
            }
            else
            {
                System.Windows.Forms.MessageBox.Show("Please load the image first", "Image not loaded");
            }

        }


        private void cb_Click(System.Object sender, System.EventArgs e)
        {
            if (this.ImageLoaded == true)
            {
                this.Contrast(10);
                this.ContrastDone = true;
                this.makeBinary();
                this.Update();
            }
            else
            {
                System.Windows.Forms.MessageBox.Show("Please load the image first", "Image not loaded");
            }
        }

        private void picture_panel_DragDrop(System.Object sender, System.Windows.Forms.DragEventArgs e)
        {
            bool allowFlag = true;
            String[] fileName;

            fileName = (String[])e.Data.GetData(DataFormats.FileDrop, false);


            // for(int a=0;a<fileName.Length;a++){
            //				 String ext = Path.GetExtension(fileName).tolower();
            //  if( (ext != ".jpg")|| (ext != ".jpeg")|| (ext != ".gif")|| (ext != ".png")|| (ext != ".tif")|| (ext != ".tiff")|| (ext != ".bmp") ) allow = false;

            // }
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
                e.Effect = DragDropEffects.All;
            else
                e.Effect = DragDropEffects.None;




            fileName = (String[])e.Data.GetData(DataFormats.FileDrop, false);

            for (int a = 0; a < fileName.Length; a++)
            {

                this.ImageLoaded = true;
                this.BinaryDone = false;
                this.SeparateDone = false;
                this.ContrastDone = false;
                this.meanDone = false;
                this.deskewDone = false;
                im = new Bitmap(fileName[a]);
                this.pictureBox1.Image = im;
                g = this.pictureBox1.CreateGraphics();
                myInfo.Text = "";
                myInfo1.Text = "";

                this.setResetMenu(this.ImageLoaded, this.BinaryDone, this.SeparateDone);

            }

        }

        private void picture_panel_DragEnter(System.Object sender, System.Windows.Forms.DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
                e.Effect = DragDropEffects.All;
            else
                e.Effect = DragDropEffects.None;
        }

        private void btnRotate_right_Click(System.Object sender, System.EventArgs e)
        {
            //Function to rotate clockwise direction by 90 degrees
            //Button_rotate_right : click event

            im.RotateFlip(RotateFlipType.Rotate90FlipNone);
            this.pictureBox1.Image = im;
        }

        private void FormMainWindow_Load(System.Object sender, System.EventArgs e)
        {
        }


        int Truncate(int val)
        {
            float temp = (float)(3 * val) / 2;
            int ttemp = 3 * val / 2;
            float x = temp - (float)(ttemp);
            //System.Windows.Forms.MessageBox.Show(temp.ToString(),"Threshold Size float value");
            if (x >= 0.5)
            {
                ttemp++;
            }
            //System.Windows.Forms.MessageBox.Show(ttemp.ToString(),"Threshold Size After Truncate");
            return ttemp;
        }
        void TotalUnitCount()
        {
            this.totalUnits = 0;
            for (int i = 0; i < this.numberOfLines; i++)
            {
                for (int j = 0; j < this.Lines[i].getTotalWord(); j++)
                {
                    for (int k = 0; k < this.Lines[i].Words[j].getTotalUnit(); k++)
                    {
                        int x1 = this.Lines[i].Words[j].Units[k].getStartColumn();
                        int x2 = this.Lines[i].Words[j].Units[k].getEndColumn();
                        int y1 = this.Lines[i].getStartRow();
                        int y2 = this.Lines[i].getEndRow();
                        if ((x2 - x1 + 1) > 2)			// Avoiding the "Aakar"
                        {
                            this.totalUnits++;
                        }
                    }
                }
            }
        }

        void WidthStore()
        {
            this.TotalUnitCount();
            this.WStore = new int[this.totalUnits];
            int count = 0;
            for (int i = 0; i < this.numberOfLines; i++)
            {
                for (int j = 0; j < this.Lines[i].getTotalWord(); j++)
                {
                    for (int k = 0; k < this.Lines[i].Words[j].getTotalUnit(); k++)
                    {
                        int x1 = this.Lines[i].Words[j].Units[k].getStartColumn();
                        int x2 = this.Lines[i].Words[j].Units[k].getEndColumn();
                        int y1 = this.Lines[i].getStartRow();
                        int y2 = this.Lines[i].getEndRow();
                        int wth = x2 - x1 + 1;

                        if (wth > 2)
                        {
                            this.WStore[count] = wth;
                            count++;
                        }
                    }
                }
            }
        }

        int ThresholdSize()
        {
            this.sortWidth();
            int sz;
            sz = (this.totalUnits + 1) / 2;
            int val;
            val = this.WStore[sz];
            val = this.Truncate(val);
            return val;

        }
        void sortWidth()
        {
            int temp;
            for (int i = 0; i < this.totalUnits; i++)
            {
                for (int j = i + 1; j < this.totalUnits; j++)
                {
                    if (this.WStore[i] > this.WStore[j])
                    {
                        temp = this.WStore[i];
                        this.WStore[i] = this.WStore[j];
                        this.WStore[j] = temp;
                    }
                }
            }
        }


        private void mnuLoadImage2_Click(System.Object sender, System.EventArgs e)
        {
            //Load image
            this.openImageFile();
        }

        private void mnuSaveImage_Click(System.Object sender, System.EventArgs e)
        {
            this.saveImageFile();
        }

        private void mnuFastRecognize_Click(System.Object sender, System.EventArgs e)
        {

            //if(this.ImageLoaded==true){
            // 
            ////contrast
            //this.Contrast(10);
            //this.ContrastDone=true;
            //this.Update();
            //
            ////mean removal
            ////this.MeanRemoval(9);
            ////this.meanDone= true;
            //this.Update();

            ////Binarization
            //this.makeBinary();
            //
            ////separation
            //this.separate();

            ////Recognition
            // this.Recognize();


            //}
            //else{
            // System.Windows.Forms.MessageBox.Show("Please load the image first","Image not loaded");

            //}
            this.DoOCR();

        }

        private void mnuExit_Click(System.Object sender, System.EventArgs e)
        {
            Application.Exit();
        }

        private void mnuFastRecognize2_Click(System.Object sender, System.EventArgs e)
        {
            this.DoOCR();
            //this.DoOCRThreaded();
        }

        private void DoOCR()
        {
            ocrSampleThread = new Thread(new ThreadStart(OCRThreadProcess));
            ocrSampleThread.Start();
        }

        private void OCRThreadProcess()
        {

            if (this.ImageLoaded == true)
            {

                //contrast
                this.Contrast(10);
                if (this.InvokeRequired)
                {
                    this.Invoke(new MethodInvoker(delegate
                                                      {
                                                          this.ContrastDone = true;

                                                      }));
                }
                else
                {
                    this.ContrastDone = true;
                    this.Update();
                }


                //mean removal
                //this.MeanRemoval(9);
                //this.meanDone= true;
                //this.Update();

                //Binarization
                this.makeBinary();

                //separation
                this.separate();

                //Recognition
                this.Recognize();


            }
            else
            {
                System.Windows.Forms.MessageBox.Show("Please load the image first", "Image not loaded");

            }
        }

        private void mnuRecognize_Click(System.Object sender, System.EventArgs e)
        {
            if (this.ImageLoaded)
            {
                if (this.SeparateDone)
                {
                    //if the image is loaded and words are separated.. recognition process is started
                    this.Recognize();

                }
                else
                {
                    System.Windows.Forms.MessageBox.Show("First Complete the preprocessing steps, words are not separated", "Preprocessing steps not complete");
                }
            }
            else
            {
                //Image is not loaded
                System.Windows.Forms.MessageBox.Show("Image not loaded, Please load the image first", "Image not loaded");
            }
            //OCR.RecognitionForm rw=new OCR.RecognitionForm();
            //rw.ShowDialog();
        }

        private void mnuBinarize_Click(System.Object sender, System.EventArgs e)
        {
            this.makeBinary();
        }

        private void mnuSeparate_Click(System.Object sender, System.EventArgs e)
        {
            if ((this.ImageLoaded == true) && (this.BinaryDone == true))
            {
                this.separate();
            }
            else if ((this.ImageLoaded == false))
            {
                System.Windows.Forms.MessageBox.Show("Please load the image first", "Image not loaded");
            }
            else if (this.BinaryDone == false)
            {
                //System.Windows.Forms.Show("Please binarize the image before separating","Binarization not done");
                System.Windows.Forms.MessageBox.Show("Please binarize the image first", "Binarization not done");

            }
        }

        private void mnuTrain_Click(System.Object sender, System.EventArgs e)
        {
            if (this.rtbOutputShowing == true) this.delRTB();
            //Check If the image is loaded or not.
            if (this.ImageLoaded)
            {

                //Check If the image is binarized first or not.

                if (this.BinaryDone)
                {
                    NOCR.TrainingForm tw = new NOCR.TrainingForm();
                    tw.defineVar(this.ImgArray, this.tmpBArray, this.Lines, this.numberOfLines);
                    tw.Show();
                }
                //If not binarized print an error message				
                else
                {
                    this.logFile.WriteLine("Trainer Returned: Attempted to perform operation without binarizing");
                    System.Windows.Forms.MessageBox.Show("Image is not Binarized", "Please Binarize first");
                }

            }
            //If an Image is not loaded, Print an error message to load the image.
            else
            {
                //Please Browse for image and Load the image
                this.logFile.WriteLine("Trainer Returned: Attempted to perform operation without loading the Image");
                UpdateStatusBarMethod("Image not loaded, Please Browse for image and load image first");
                System.Windows.Forms.MessageBox.Show("Image not loaded, Please Browse for image and load image first ", "Image Not loaded");
            }

        }

        private void createRTB()
        {
            //this function is used to create the richtextbox used producing output after recognition
            if (!this.InvokeRequired)
            {
                this.rtbMainOutput.Visible = true;

                this.mnuSaveOutput.Enabled = true;
            }
            if (this.rtbOutputShowing == false)
            {
                if (!this.InvokeRequired)
                {
                    this.picture_panel.Size = new System.Drawing.Size((this.picture_panel.Width),
                                                                      (this.picture_panel.Height - 96));
                }
                this.rtbOutputShowing = true;
            }
            else
            {
                return;
            }
        }
        private void delRTB()
        {
            //this function is used to remove the unnecessary richtextbox, which was used for producing output after recognition

            if (!this.InvokeRequired)
            {
                this.picture_panel.Size = new System.Drawing.Size((this.picture_panel.Width),
                                                                  (this.picture_panel.Height + 96));
                this.rtbMainOutput.Visible = false;
                //this.mnuSaveOutput.Enabled = true;
                //this.rtbOutput.Container.Dispose();
            }
            this.rtbOutputShowing = false;


        }

        private void mnuResegment_Click(System.Object sender, System.EventArgs e)
        {
            if (this.ImageLoaded && this.BinaryDone && this.SeparateDone)
            {
                Resegment rsg = new Resegment(im, BinaryDone, ImageLoaded, SeparateDone, BArray, this.numberOfLines, this.Lines, g, this.totalUnits, this.SizeThreshold, this.intLevel, this.HeadBottom);
                //	rsg.PrepareTouchingCharIndex();
                rsg.Do_Segmentation();
            }

        }

        private void mnuRecognize2_Click(System.Object sender, System.EventArgs e)
        {
            if (this.ImageLoaded)
            {
                if (this.SeparateDone)
                {
                    //if the image is loaded and words are separated.. recognition process is started
                    this.Recognize();

                }
                else
                {
                    System.Windows.Forms.MessageBox.Show("First Complete the preprocessing steps, words are not separated", "Preprocessing steps not complete");
                }
            }
            else
            {
                //Image is not loaded
                System.Windows.Forms.MessageBox.Show("Image not loaded, Please load the image first", "Image not loaded");
            }
            //OCR.RecognitionForm rw=new OCR.RecognitionForm();
            //rw.ShowDialog();
        }

        private void mnuMeanRemoval_Click(System.Object sender, System.EventArgs e)
        {

            if ((this.ImageLoaded == true))
            {
                this.MeanRemoval(9);
                this.meanDone = true;
                this.Update();

            }
        }

        private void mnuDeskew_Click(System.Object sender, System.EventArgs e)
        {
            if (this.ImageLoaded == true)
            {
                this.doDeSkew();
            }
            else
            {
                System.Windows.Forms.MessageBox.Show("Please Load the image first", "Image not loaded");
            }
        }

        private void mnuContrast_Click(System.Object sender, System.EventArgs e)
        {
            if (this.ImageLoaded == true)
            {
                this.Contrast(10);
                this.ContrastDone = true;
                this.Update();
            }
            else
            {
                System.Windows.Forms.MessageBox.Show("Please load the image first", "Image not loaded");
            }

        }

        private void mnuContrastAndBinarize_Click(System.Object sender, System.EventArgs e)
        {
            if (this.ImageLoaded == true)
            {
                this.Contrast(10);
                this.ContrastDone = true;
                this.makeBinary();
                this.Update();
            }
            else
            {
                System.Windows.Forms.MessageBox.Show("Please load the image first", "Image not loaded");
            }
        }

        private void mnuNoiseRemoval_Click(System.Object sender, System.EventArgs e)
        {
            this.makeClear();

        }
        void makeClear()
        {
            removeNoise rN = new removeNoise(this.BinaryImage, this.ImgArray);
            this.im = rN.GetClearImage();
            this.pictureBox1.Image = im;
        }


        private void enableCropper(System.Windows.Forms.ContextMenu ocrCMenu)
        {

            System.Windows.Forms.MenuItem mnuCropSelected = new System.Windows.Forms.MenuItem();
            mnuCropSelected.Text = "Crop Selected";
            mnuCropSelected.Click += new System.EventHandler(mnuCropSelected_Click);
            ocrCMenu.MenuItems.Add(mnuCropSelected);
            System.Drawing.Pen myCropPen = new System.Drawing.Pen(System.Drawing.Color.Blue, 1);
            //p.Color = System.Drawing.Color.Blue;
            myCropPen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dash;

            //this.g.DrawRectangle(Pens.Blue, new Rectangle(this.pointX1,this.pointY1,(this.pointX2-this.pointX1),(this.pointY2-this.pointY1)));
            this.g.DrawRectangle(myCropPen, new Rectangle(this.pointX1, this.pointY1, (this.pointX2 - this.pointX1), (this.pointY2 - this.pointY1)));
            this.imageSelection = true;




        }

        public void mnuCropSelected_Click(System.Object sender, System.EventArgs e)
        {


            if (this.xMouseDistance < this.im.Width && this.yMouseDistance < this.im.Height)
            {

                Bitmap cropImage1 = new Bitmap(this.xMouseDistance + 1, this.yMouseDistance + 1, PixelFormat.Format24bppRgb);
                for (int cropRow = 0; cropRow < (cropImage1.Height); cropRow++)
                {
                    for (int cropColumn = 0; cropColumn < (cropImage1.Width); cropColumn++)
                    {
                        cropImage1.SetPixel(cropColumn, cropRow, System.Drawing.Color.White);
                    } // for(int cropRow=0;  cropRow<(cropImage.Height); cropRow++){for(int cropColumn=0;cropColumn<(cropImage.Width) ;cropColumn++)
                } // for(int cropRow=0;  cropRow<(cropImage.Height); cropRow++)

                for (int i = this.pointY1, cropRow = 0; i < this.pointY2 & cropRow < (cropImage1.Height) - 1; i++, cropRow++)
                {
                    for (int cropColumn = 0, j = this.pointX1; j < this.pointX2 & cropColumn < (cropImage1.Width) - 1; j++, cropColumn++)
                    {

                        if (this.BArray[i, j] == true)
                            cropImage1.SetPixel(cropColumn, cropRow, System.Drawing.Color.White);
                        else
                            cropImage1.SetPixel(cropColumn, cropRow, System.Drawing.Color.Black);

                    } // for(int i=0;i<cropImage.Height;i++){for(int j=0;j<cropImage.Width;j++)
                } // for(int i=0;i<cropImage.Height;i++)
                this.pictureBox1.Image = cropImage1;
                this.im = cropImage1;
                this.ImageLoaded = true;
                //this.makeBinary();
                this.BinaryDone = false;
                this.SeparateDone = false;

            } // if(this.xMouseDistance < this.im.Width && this.yMouseDistance < this.im.Height)
            else
            {
                MessageBox.Show("Image cropped must be smaller than the original image ", "Crop Again");
            }
        }

        private void find_xy_MouseDistance(System.Windows.Forms.MouseEventArgs e)
        {

            //end preserving

            this.pointX2 = e.X;
            this.pointY2 = e.Y;
            int temp;


            if (this.pointX1 != this.pointX2 && this.pointY1 != this.pointY2)
            {
                if (this.pointX1 > this.pointX2)
                {
                    temp = this.pointX1;
                    this.pointX1 = this.pointX2;
                    this.pointX2 = temp;
                } // if(this.x1>this.x2)

                if (this.pointX1 > this.pointY2)
                {
                    temp = this.pointY1;
                    this.pointY1 = this.pointY2;
                    this.pointY2 = temp;
                } // if(this.pointY1>this.pointY2) 

            } // if(this.x1 != this.x2 && this.y1 != this.y2)
            else
            {
                UpdateStatusBarMethod("Unable to crop");
            }

            this.xMouseDistance = System.Math.Abs(this.pointX2 - this.pointX1);
            this.yMouseDistance = System.Math.Abs(this.pointY2 - this.pointY1);
        }

        private void setResetMenu(bool ImageLoaded, bool BinaryDone, bool SeparateDone)
        {
            //set reset menus depending upon the flags


            if (ImageLoaded)
            {

                this.mnuLoadImage.Visible = true;
                this.mnuLoadImage.Enabled = true;
                this.mnuMagnification.Enabled = true;


                this.mnuBinarize.Enabled = true;
                this.mnuBinarize.DefaultItem = true;
                // this.mnuBinarize.Visible = true;

                this.mnuFastRecognize.Enabled = true;
                this.mnuFastRecognize.DefaultItem = true;
                this.mnuFastRecognize.Visible = true;

                this.mnuFastRecognize2.Enabled = true;
                this.mnuFastRecognize2.DefaultItem = true;
                this.mnuFastRecognize2.Visible = true;


                this.mnuContrast.Enabled = true;
                this.mnuMeanRemoval.Enabled = true;
                this.mnuContrastAndBinarize.Enabled = true;

                this.mnuCropper.Enabled = true;
                this.mnuRotate.Enabled = true;
                this.mnuSaveImage.Enabled = true;
                this.mnuDeskew.Enabled = true;


                this.mnuAdvanced.Enabled = true;
                this.mnuOCR.Enabled = true;
                this.mnuImage.Enabled = true;

                if (BinaryDone)
                {
                    this.mnuNoiseRemoval.Enabled = true;
                    this.mnuBinarize.DefaultItem = false;
                    this.mnuFastRecognize.DefaultItem = false;


                    this.mnuSeparate.Enabled = true;
                    this.mnuSeparate.DefaultItem = true;
                    //this.mnuSeparate.Visible = true;

                    if (SeparateDone)
                    {
                        this.mnuBinarize.DefaultItem = false;
                        this.mnuSeparate.DefaultItem = false;
                        this.mnuFastRecognize.DefaultItem = false;

                        this.mnuRecognize.Enabled = true;
                        this.mnuRecognize.DefaultItem = true;
                        this.mnuRecognize2.DefaultItem = true;

                        this.mnuTrain.Enabled = true;


                        this.mnuRecognize.Enabled = true;
                        this.mnuRecognize2.Enabled = true;

                    } // if(SeparateDone)

                    else
                    {
                        this.mnuRecognize.Enabled = false;
                        this.mnuTrain.Enabled = false;
                    }

                } // if(BinaryDone)
                else
                {
                    this.mnuBinarize.Enabled = true;
                    this.mnuBinarize.DefaultItem = true;
                    this.mnuBinarize.Visible = true;

                    this.mnuSeparate.Enabled = false;


                }

            } // if(ImageLoaded)

            else
            {
                this.mnuLoadImage.Enabled = true;
                this.mnuLoadImage.Visible = true;
                this.mnuLoadImage.DefaultItem = true;
                //


                this.mnuNoiseRemoval.Enabled = false;
                this.mnuBinarize.Enabled = false;
                this.mnuContrast.Enabled = false;
                this.mnuMeanRemoval.Enabled = false;
                this.mnuContrastAndBinarize.Enabled = false;
                this.mnuSeparate.Enabled = false;

                this.mnuRecognize.Enabled = false;
                this.mnuTrain.Enabled = false;
                this.mnuRecognize2.Enabled = false;
                this.mnuFastRecognize.Enabled = false;
                this.mnuFastRecognize2.Enabled = false;
                this.mnuMagnification.Enabled = false;

                this.mnuCropper.Enabled = false;
                this.mnuRotate.Enabled = false;
                this.mnuSaveImage.Enabled = false;
                this.mnuDeskew.Enabled = false;


                this.mnuAdvanced.Enabled = false;
                this.mnuOCR.Enabled = false;
                this.mnuImage.Enabled = true;

            }


        }
        private void picture_panel_MouseUp(System.Object sender, System.Windows.Forms.MouseEventArgs e)
        {
            this.pointX2 = e.X;
            this.pointY2 = e.Y;

            this.drawContextMenu(e);
            this.crobPictureBox.Visible = false;

        }

        private void drawContextMenu(System.Windows.Forms.MouseEventArgs e)
        {
            try
            {
                //Left Click
                if (e.Button == MouseButtons.Left)
                { //Left Click

                    System.Windows.Forms.ContextMenu ocrCMenu = new System.Windows.Forms.ContextMenu();
                    System.Windows.Forms.MenuItem Cseparator = new System.Windows.Forms.MenuItem();
                    Cseparator.Text = "-";

                    //System.Windows.Forms.MenuItem mnuNewCropper = new System.Windows.Forms.MenuItem();
                    //mnuNewCropper.Text = "New Crop Selected";
                    //mnuNewCropper.Click+= new System.EventHandler(this,mnuNewCrop_Click);
                    //ocrCMenu.MenuItems.Add(mnuNewCropper);


                    if (this.ImageLoaded == false)
                    {//Left Click, If image not loaded, load image
                        //Create Load Image Menu
                        System.Windows.Forms.MenuItem CmnuLoadImage = new System.Windows.Forms.MenuItem();
                        CmnuLoadImage.Text = "New Image";
                        CmnuLoadImage.Click += new System.EventHandler(mnuLoadImage2_Click);
                        //ocrCMenu.MenuItems.Add(this.mnuLoadImage);
                        ocrCMenu.MenuItems.Add(CmnuLoadImage);



                    } // if(e.Button == MouseButtons.Left){if(this.ImageLoaded ==false)
                    else
                    {
                        //Create Fast Recognize menu
                        System.Windows.Forms.MenuItem CmnuFastRecognize = new System.Windows.Forms.MenuItem();
                        CmnuFastRecognize.Text = "OCR ";
                        CmnuFastRecognize.DefaultItem = true;
                        CmnuFastRecognize.Click += new System.EventHandler(mnuFastRecognize_Click);
                        //Create Binarize menu
                        if (this.ImageLoaded == true && this.BinaryDone == false)
                        { //Left click, if image loaded, recognize it

                            //Finding the points 
                            if (this.pointX1 != this.pointX2)
                            {
                                this.find_xy_MouseDistance(e);

                                this.enableNewCropper(ocrCMenu);
                                //System.Windows.Forms.MenuItem mnuNewCropper = new System.Windows.Forms.MenuItem();
                                //mnuNewCropper.Text = "New Crop Selected";
                                //mnuNewCropper.Click+= new System.EventHandler(this,mnuNewCrop_Click);
                                //ocrCMenu.MenuItems.Add(mnuNewCropper);
                            }

                            System.Windows.Forms.MenuItem CmnuBinarization = new System.Windows.Forms.MenuItem();
                            CmnuBinarization.Text = "Binarize ";
                            CmnuBinarization.Click += new System.EventHandler(mnuBinarize_Click);

                            //ocrCMenu.MenuItems.Add(CmnuFastRecognize);
                            //ocrCMenu.MenuItems.Add(this.mnuFastRecognize);

                            ocrCMenu.MenuItems.Add(CmnuFastRecognize);
                            ocrCMenu.MenuItems.Add(CmnuBinarization);

                            //draw here

                            //ocrCMenu.MenuItems.Add(this.mnuBinarize);
                            this.mnuLoadImage.Enabled = true;

                            //set reset menus
                            this.mnuBinarize.Enabled = true;
                            this.mnuContrast.Enabled = true;
                            this.mnuContrastAndBinarize.Enabled = true;
                            this.mnuCropper.Enabled = true;
                            this.mnuRotate.Enabled = true;

                            this.mnuSeparate.Enabled = false;
                            this.mnuRecognize.Enabled = false;
                            //this.mnuRecognize2.DefaultItem = true;
                            this.mnuTrain.Enabled = false;
                            //ENd set reset menus

                        }
                        if (this.ImageLoaded == true && this.BinaryDone == true)
                        { //Left click, if image loaded, and Binarized, separate it

                            //this.mnuStart.MenuItems.Add(this.mnuLoadImage);
                            // Todo: add condition for checking this.xMouseDistance, this.yMouseDistance
                            //	MessageBox.Show("ok");
                            //	find_xy_MouseDistance
                            if (this.pointX1 != this.pointX2)
                            {
                                this.find_xy_MouseDistance(e);
                                this.enableCropper(ocrCMenu);
                            }



                            // if((this.BinaryDone == true) && (this.xMouseDistance >0) )
                            System.Windows.Forms.MenuItem CmnuSeparate = new System.Windows.Forms.MenuItem();
                            CmnuSeparate.Text = "Separate";
                            CmnuSeparate.Click += new System.EventHandler(mnuSeparate_Click);
                            ocrCMenu.MenuItems.Add(CmnuSeparate);

                            //ocrCMenu.MenuItems.Add(this.mnuSeparate);
                            //ocrCMenu.MenuItems.Add(this.mnuFastRecognize);

                            //set reset menus
                            this.mnuSeparate.Enabled = true;


                        }


                    }//end Else
                    if (this.SeparateDone == true)
                    {
                        ocrCMenu.MenuItems.Add(Cseparator);
                        System.Windows.Forms.MenuItem CmnuRecognize = new System.Windows.Forms.MenuItem();
                        CmnuRecognize.Text = "Recognize Separated Units";
                        CmnuRecognize.Click += new System.EventHandler(mnuRecognize_Click);
                        ocrCMenu.MenuItems.Add(CmnuRecognize);

                        System.Windows.Forms.MenuItem CmnuTrain = new System.Windows.Forms.MenuItem();
                        CmnuTrain.Text = "Train Separated Units";
                        CmnuTrain.Click += new System.EventHandler(mnuTrain_Click);
                        ocrCMenu.MenuItems.Add(CmnuTrain);




                        //ocrCMenu.MenuItems.Add(this.mnuRecognize);
                        //ocrCMenu.MenuItems.Add(this.mnuTrain);

                        //set reset menus
                        this.mnuRecognize.Enabled = true;
                        this.mnuTrain.Enabled = true;
                        //ENd set reset menus


                    }





                    ocrCMenu.Show(this, new System.Drawing.Point(e.X % this.Width, e.Y % this.Height));
                } // if(e.Button == MouseButtons.Left) 




                //Right Click
                if (e.Button == MouseButtons.Right)
                {//Right Click
                    if (this.ImageLoaded == true)
                    { //Rotate Image on right click
                        System.Windows.Forms.ContextMenu ocrCMenu = new System.Windows.Forms.ContextMenu();

                        System.Windows.Forms.MenuItem CmnuLoadImage = new System.Windows.Forms.MenuItem();
                        CmnuLoadImage.Text = "New Image";
                        CmnuLoadImage.Click += new System.EventHandler(mnuLoadImage_Click);
                        ocrCMenu.MenuItems.Add(CmnuLoadImage);

                        System.Windows.Forms.MenuItem CmnuSeparator_rightClick = new System.Windows.Forms.MenuItem();
                        CmnuSeparator_rightClick.Text = "-";
                        ocrCMenu.MenuItems.Add(CmnuSeparator_rightClick);

                        System.Windows.Forms.MenuItem CmnuRotateLeft = new System.Windows.Forms.MenuItem();
                        CmnuRotateLeft.Text = "Rotate Right ";
                        CmnuRotateLeft.Click += new System.EventHandler(mnuRotate_Click);
                        ocrCMenu.MenuItems.Add(CmnuRotateLeft);

                        System.Windows.Forms.MenuItem CmnuRotateRight = new System.Windows.Forms.MenuItem();
                        CmnuRotateRight.Text = "Rotate Left ";
                        CmnuRotateRight.Click += new System.EventHandler(rotateLeft);
                        ocrCMenu.MenuItems.Add(CmnuRotateRight);


                        System.Windows.Forms.MenuItem CmnuRotateUpright = new System.Windows.Forms.MenuItem();
                        CmnuRotateUpright.Text = "Rotate Upright ";
                        CmnuRotateUpright.Click += new System.EventHandler(rotateUpright);
                        ocrCMenu.MenuItems.Add(CmnuRotateUpright);


                        //ocrCMenu.MenuItems.Add(this.mnuRotate);
                        //ocrCMenu.MenuItems.Add(this.mnuLoadImage);
                        ocrCMenu.Show(this, new System.Drawing.Point(e.X, e.Y));
                    }
                } // if(e.Button == MouseButtons.Right)

            }
            catch (System.Exception mouseExceptions)
            {
                // this.statusBar1.Text = "Don\'t mess much with mouse";
                UpdateStatusBarMethod("Left click for options, right Click for new Image");
            }
        }

        private void mnuLoadImage_Click(System.Object sender, System.EventArgs e)
        {
            this.openImageFile();
        }

        private void mnuRotate_Click(System.Object sender, System.EventArgs e)
        {

            //Function to rotate clockwise direction by 90 degrees
            //Button_rotate_right : click event

            im.RotateFlip(RotateFlipType.Rotate90FlipNone);
            this.pictureBox1.Image = im;
            if (this.BinaryDone)
            {
                this.resetVariablesAfterRotation();
            }
        }
        private void rotateLeft(System.Object sender, System.EventArgs e)
        {

            //Function to rotate clockwise direction by 90 degrees
            //Button_rotate_right : click event

            im.RotateFlip(RotateFlipType.Rotate270FlipNone);
            this.pictureBox1.Image = im;
            if (this.BinaryDone)
            {
                this.resetVariablesAfterRotation();
            }
        }
        private void rotateUpright(System.Object sender, System.EventArgs e)
        {

            //Function to rotate clockwise direction by 90 degrees
            //Button_rotate_right : click event

            im.RotateFlip(RotateFlipType.Rotate180FlipNone);
            this.pictureBox1.Image = im;
            if (this.BinaryDone)
            {
                this.resetVariablesAfterRotation();
            }
        }

        void resetVariablesAfterRotation()
        {
            this.ImageLoaded = true;

            this.BinaryDone = false;
            this.SeparateDone = false;
            this.ContrastDone = false;
            this.meanDone = false;
            this.deskewDone = false;
            this.makeBinary();
            this.BinaryDone = true;

        }

        private void mnuMagnification_Click(System.Object sender, System.EventArgs e)
        {
            if (this.ImageLoaded)
            {
                tryMagnify();

            }
            else
            {
                System.Windows.Forms.MessageBox.Show("Please load the image first", "Image not loaded");
            }
        }

        private void pictureBox1_MouseDown(System.Object sender, System.Windows.Forms.MouseEventArgs e)
        {
            //reset variables x2 and y2 
            //if already initialized
            m_PanStartPoint = new System.Drawing.Point(e.X, e.Y);

            if (this.pointX1 != null && this.pointX2 != null)
            {
                this.pointX2 = this.pointX1;
                this.pointY2 = this.pointY1;
            }
            //
            this.pointX1 = e.X;
            this.pointY1 = e.Y;
            this.crobPictureBox.Visible = false;
            this.dragEnabled = true;

        }

        private void pictureBox1_MouseUp(System.Object sender, System.Windows.Forms.MouseEventArgs e)
        {
            this.pointX2 = e.X;
            this.pointY2 = e.Y;

            this.drawContextMenu(e);
            this.dragEnabled = false;

        }

        private void pictureBox1_MouseMove(System.Object sender, System.Windows.Forms.MouseEventArgs e)
        {
            //this.crobPictureBox.Visible = true;
            //this.crobPictureBox.BringToFront();
            //g.Flush();
            //draw rectangles on mouse move event
            System.Drawing.Pen myPen_MouseMove = new System.Drawing.Pen(System.Drawing.Color.Red, 1);
            //p.Color = System.Drawing.Color.Blue;
            myPen_MouseMove.DashStyle = System.Drawing.Drawing2D.DashStyle.DashDot;

            if (this.dragEnabled)
            {
                this.pointX2 = e.X;
                this.pointY2 = e.Y;
                this.pictureBox1.Refresh();
                if (e.Button == MouseButtons.Left)
                {
                    long xBoundary = 0;
                    long yBoundary = 0;

                    long DeltaX = 0;
                    long DeltaY = 0;
                    bool DoScroll = false;
                    // CurrentPos represents the top left corner's coordinates.
                    System.Drawing.Point CurrentPos = new System.Drawing.Point(Math.Abs(picture_panel.AutoScrollPosition.X), (Math.Abs(picture_panel.AutoScrollPosition.Y)));

                    //Pretty sure this isn't the best way of doing this
                    //However, if we don't pause a little, the user could easily scroll
                    //at super-speeds. I'd look into another way of throttling the scroll speed.
                    System.Threading.Thread.Sleep(50);

                    xBoundary = CurrentPos.X + picture_panel.Width - SystemInformation.VerticalScrollBarWidth;
                    yBoundary = CurrentPos.Y + picture_panel.Height - SystemInformation.HorizontalScrollBarHeight;


                    //Check to see if we are out of the visible area
                    if (e.X > xBoundary | e.X < CurrentPos.X)
                    {
                        DeltaX = e.X - xBoundary;
                        DoScroll = true;
                    }
                    if (e.Y > yBoundary | e.Y < CurrentPos.Y)
                    {
                        DeltaY = e.Y - yBoundary;
                        DoScroll = true;
                    }

                    //Make the adjustment.
                    if (DoScroll == true)
                    {
                        this.picture_panel.AutoScrollPosition = new System.Drawing.Point((int)(DeltaX - picture_panel.AutoScrollPosition.X), (int)(DeltaY - picture_panel.AutoScrollPosition.Y));
                    }




                    //point checker
                    //Graphics.DrawImage(newImage, destRect, srcRect, units);
                    if (this.pointX1 < this.pointX2)
                    { //Normal condition, drag from left to right (x1 <x2)
                        if (this.pointY1 < this.pointY2)
                        { //Normal Condition drag from top to bottom (y1 <y2)
                            this.g.DrawRectangle(myPen_MouseMove, new Rectangle(this.pointX1, this.pointY1, Math.Abs(this.pointX2 - this.pointX1), Math.Abs(this.pointY2 - this.pointY1)));
                        }
                        else
                        {	//drag from bottom to top (y1 > y2)
                            this.g.DrawRectangle(myPen_MouseMove, new Rectangle(this.pointX1, this.pointY2, Math.Abs(this.pointX2 - this.pointX1), Math.Abs(this.pointY2 - this.pointY1)));
                        }
                    }
                    else
                    {	//drag from right to left i.e. (this.pointX1 > this.pointX2)
                        if (this.pointY1 < this.pointY2)
                        { //Normal Condition drag from top to bottom (y1 <y2)
                            this.g.DrawRectangle(myPen_MouseMove, new Rectangle(this.pointX2, this.pointY1, Math.Abs(this.pointX2 - this.pointX1), Math.Abs(this.pointY2 - this.pointY1)));
                        }
                        else
                        {//drag from bottom to top (y1 > y2)
                            this.g.DrawRectangle(myPen_MouseMove, new Rectangle(this.pointX2, this.pointY2, Math.Abs(this.pointX2 - this.pointX1), Math.Abs(this.pointY2 - this.pointY1)));
                        }
                    }

                    //point checker ends


                }
                this.pictureBox1.Refresh();
            }

        }

        private void drawMyMenu(System.Windows.Forms.MenuItem abc, String myMenuText)
        {

            abc.Enabled = true;
            abc.Text = myMenuText;
            //abc.Click += new System.EventHandler(mnuSaveImage_Click);
            //abc.set_siz = System.Drawing.Size(len, wid);
            //abc.Text = myMenuText;
            //

        }
        private void mnuVersionInfo_Click(System.Object sender, System.EventArgs e)
        {
            //System.Windows.Forms.MessageBox.Show("Build: Dec 15 2008","Nepali OCR ");
            about aboutMPP = new about();
            aboutMPP.Show();

        }


        private void mnuNewCrop_Click(System.Object sender, System.EventArgs e)
        {
            UpdateStatusBarMethod("");
            if (this.xMouseDistance < this.im.Width && this.yMouseDistance < this.im.Height)
            {



                try
                {
                    this.im = this.selectedImage;
                    this.pictureBox1.Image = im;

                    this.ImageLoaded = true;
                    this.BinaryDone = false;
                    this.SeparateDone = false;
                }
                catch (System.Exception CroppingException)
                {
                    UpdateStatusBarMethod("TRY CROPPING AGAIN  ");
                }

            } // if(this.xMouseDistance < this.im.Width && this.yMouseDistance < this.im.Height)
            else
            {
                UpdateStatusBarMethod("Image Cropped Must be Smaller than the original Image, Please crop again");
                return;
                //MessageBox.Show("Image cropped must be smaller than the original image ","Crop Again");
            }




        }

        private void enableNewCropper(System.Windows.Forms.ContextMenu ocrCMenu)
        {



            System.Windows.Forms.MenuItem mnuNewCropper = new System.Windows.Forms.MenuItem();
            mnuNewCropper.Text = "Crop Selected Image";
            mnuNewCropper.Click += new System.EventHandler(mnuNewCrop_Click);
            ocrCMenu.MenuItems.Add(mnuNewCropper);
            try
            {

                //System.Windows.Forms.MessageBox.Show(String.Format("Image Size : {0} {1} ",im.Width,im.Height));
                selectedImage = new Bitmap(Math.Abs(this.pointX2 - this.pointX1), Math.Abs(this.pointY2 - this.pointY1));
                Graphics gr2 = Graphics.FromImage(selectedImage);
                //Graphics.DrawImage(newImage, destRect, srcRect, units);
                gr2.DrawImage(im, (new Rectangle(0, 0, Math.Abs(this.pointX2 - this.pointX1), Math.Abs(this.pointY2 - this.pointY1))), (new Rectangle(this.pointX1, this.pointY1, Math.Abs(this.pointX2 - this.pointX1), Math.Abs(this.pointY2 - this.pointY1))), GraphicsUnit.Pixel);
                this.crobPictureBox.Visible = true;
                this.crobPictureBox.BringToFront();
                this.crobPictureBox.Image = selectedImage;
                this.crobPictureBox.Location = new System.Drawing.Point(872, 8);
                //MessageBox.Show (String.Format("Height is {0} and Width is {1} ",im.Height.ToString(),im.Width.ToString()),"Original Image" );
                //MessageBox.Show (String.Format("Height is {0} and Width is {1} ",selectedImage.Height.ToString(),selectedImage.Width.ToString()),"Cropped image" );

            }
            catch (System.Exception ex)
            {
                return;
            }
            this.pictureBox1.Refresh();
            System.Drawing.Pen myCropPen = new System.Drawing.Pen(System.Drawing.Color.Blue, 1);
            //p.Color = System.Drawing.Color.Blue;
            myCropPen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dot;

            //this.g.DrawRectangle(Pens.Black, new Rectangle(this.pointX1,this.pointY1,(this.pointX2-this.pointX1),(this.pointY2-this.pointY1)));
            ///////////////////			this.g.DrawRectangle(myCropPen, new Rectangle(this.pointX1,this.pointY1,Math.Abs(this.pointX2-this.pointX1),Math.Abs(this.pointY2-this.pointY1)));


            if (this.dragEnabled)
            {
                //this.pointX2 = e.X;
                //this.pointY2 = e.Y;
                this.pictureBox1.Refresh();

                //point checker
                //Graphics.DrawImage(newImage, destRect, srcRect, units);
                if (this.pointX1 < this.pointX2)
                { //Normal condition, drag from left to right (x1 <x2)
                    if (this.pointY1 < this.pointY2)
                    { //Normal Condition drag from top to bottom (y1 <y2)
                        this.g.DrawRectangle(myCropPen, new Rectangle(this.pointX1, this.pointY1, Math.Abs(this.pointX2 - this.pointX1), Math.Abs(this.pointY2 - this.pointY1)));
                    }
                    else
                    {	//drag from bottom to top (y1 > y2)
                        this.g.DrawRectangle(myCropPen, new Rectangle(this.pointX1, this.pointY2, Math.Abs(this.pointX2 - this.pointX1), Math.Abs(this.pointY2 - this.pointY1)));
                    }
                }
                else
                {	//drag from right to left i.e. (this.pointX1 > this.pointX2)
                    if (this.pointY1 < this.pointY2)
                    { //Normal Condition drag from top to bottom (y1 <y2)
                        this.g.DrawRectangle(myCropPen, new Rectangle(this.pointX2, this.pointY1, Math.Abs(this.pointX2 - this.pointX1), Math.Abs(this.pointY2 - this.pointY1)));
                    }
                    else
                    {//drag from bottom to top (y1 > y2)
                        this.g.DrawRectangle(myCropPen, new Rectangle(this.pointX2, this.pointY2, Math.Abs(this.pointX2 - this.pointX1), Math.Abs(this.pointY2 - this.pointY1)));
                    }
                }

                //point checker ends
            }

            this.imageSelection = true;
            //delete myCropPen;

        }




    }
}
