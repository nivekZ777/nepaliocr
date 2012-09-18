using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using NOCR.Help;

namespace NOCR
{
    public partial class FormMainWindow
    {
        private delegate void SetWaitCursor(Cursor c);
        private delegate void SetNormalCursor(Cursor c);
        private delegate void UpdateStatusBar(string text);
        private delegate void UpdatePictureBox1(Bitmap image);


        private void SetWaitCursorMethod(Cursor c)
        {
            if(this.InvokeRequired)
            {
                SetWaitCursor s = new SetWaitCursor(SetWaitCursorMethod);
                this.Invoke(s, new object[] {c});
            }else{
                this.Cursor = c;
            }
        }
        private void SetNormalCursorMethod(Cursor c)
        {
            if (this.InvokeRequired)
            {
                SetNormalCursor s = new SetNormalCursor(SetNormalCursorMethod);
                this.Invoke(s, new object[] { c });
            }else{
                this.Cursor = c;
            }
        }

        private void UpdateStatusBarMethod(string text)
        {
            if(this.statusBar1.InvokeRequired)
            {
                UpdateStatusBar u = new UpdateStatusBar(UpdateStatusBarMethod);
                this.Invoke(u, new object[]{text});
            }else{
                this.statusBar1.Text = text;
            }
        }
        
        private void UpdatePictureBox1Method(Bitmap image)
        {
            if(this.pictureBox1.InvokeRequired)
            {
                UpdatePictureBox1 u = new UpdatePictureBox1(UpdatePictureBox1Method);
                this.Invoke(u, new object[] {image});
            }else{
                this.pictureBox1.Image = image;
            }
        }

        private void rtbMainOutput_MouseUp(System.Object sender, System.Windows.Forms.MouseEventArgs e)
        {
            try
            {
                if (e.Button == MouseButtons.Right)
                {

                    System.Windows.Forms.ContextMenu rtbCMenu = new System.Windows.Forms.ContextMenu();
                    System.Windows.Forms.MenuItem rtbExit = new System.Windows.Forms.MenuItem();
                    System.Windows.Forms.MenuItem rtbSaveInputMenu = new System.Windows.Forms.MenuItem();

                    rtbExit.Text = "Hide Output";
                    rtbSaveInputMenu.Text = "Save ";
                    rtbExit.Click += new System.EventHandler(rtbExit_Click);
                    rtbSaveInputMenu.Shortcut = System.Windows.Forms.Shortcut.CtrlD;
                    rtbSaveInputMenu.Click += new System.EventHandler(mnuSaveOutput_Click);


                    rtbCMenu.MenuItems.Add(rtbSaveInputMenu);
                    rtbCMenu.MenuItems.Add(rtbExit);
                    rtbCMenu.Show(this, new System.Drawing.Point(e.X, this.picture_panel.Height + e.Y));
                }
            }
            catch (System.Exception ex)
            {
                return;
            }
        }
        private void rtbExit_Click(System.Object sender, System.EventArgs e)
        {
            this.delRTB();
        }

        private void mnuSaveOutput_Click(System.Object sender, System.EventArgs e)
        {
            //Output Saving rajesh
            if (this.rtbOutputShowing)
            {
                // this.saveOutputDialog.Filter = "Text Files (*.txt)";
                //this.saveOutputDialog.Filter =  "Txt files (*.txt)|*.txt" ;
                this.saveOutputDialog.Filter = @"DOC|*.doc|RTF|*.rtf";
                //saveImageDialog.Filter= "PNG files (*.jpg)|*.jpg|PNG files (*.png)|*.png|All valid files (*.jpg/*.png)|*.jpg/*.png" ;
                this.saveOutputDialog.RestoreDirectory = true;
                this.saveOutputDialog.FilterIndex = 1;
                System.Windows.Forms.DialogResult outputDialog = this.saveOutputDialog.ShowDialog();
                if (outputDialog == System.Windows.Forms.DialogResult.OK)
                {
                    //System.String notepadOutputFileName = this.saveOutputDialog.FileName;
                    //System.IO.StreamWriter notepadOutSw = new System.IO.StreamWriter(notepadOutputFileName);
                    this.rtbMainOutput.SaveFile(this.saveOutputDialog.FileName, System.Windows.Forms.RichTextBoxStreamType.RichText);
                    System.Windows.Forms.MessageBox.Show("File Saved Successfully", "Saved Successfully!", System.Windows.Forms.MessageBoxButtons.OK, System.Windows.Forms.MessageBoxIcon.Exclamation);
                    //notepadOutSw.Write(this.rtbMainOutput.Text);
                    //notepadOutSw.Close();
                }
            }
            else
            {

                UpdateStatusBarMethod("No output to save");
            }
        }

        private void mnuHelpBrowseImage_Click(System.Object sender, System.EventArgs e)
        {
            helpLoadImage hlpLoadImage = new helpLoadImage();
            hlpLoadImage.Show();
        }

        private void mnuHelpOCR_Click(System.Object sender, System.EventArgs e)
        {
            helpOCR hlpOCR = new helpOCR();
            hlpOCR.ShowHelpOCR();
            hlpOCR.Show();
        }

        private void mnuHelpTrain_Click(System.Object sender, System.EventArgs e)
        {
            helpOCR hlpOCR = new helpOCR();
            hlpOCR.ShowHelpTrain();
            hlpOCR.Show();
        }

        private void menuItem6_Click(System.Object sender, System.EventArgs e)
        {

            helpOCR hlpOCR = new helpOCR();
            hlpOCR.ShowHelpDeskew();
            hlpOCR.Show();
        }

        private void mnuHelpBinarize_Click(System.Object sender, System.EventArgs e)
        {
            helpOCR hlpOCR = new helpOCR();
            hlpOCR.ShowHelpBinarize();
            hlpOCR.Show();
        }

        private void mnuHelpSeparate_Click(System.Object sender, System.EventArgs e)
        {
            helpOCR hlpOCR = new helpOCR();
            hlpOCR.ShowHelpSeparate();
            hlpOCR.Show();
        }

        private void mnuHelpNoiseRemoval_Click(System.Object sender, System.EventArgs e)
        {
            helpOCR hlpOCR = new helpOCR();
            hlpOCR.ShowHelpNoiseRemoval();
            hlpOCR.Show();
        }

        private void mnuHelpContrast_Click(System.Object sender, System.EventArgs e)
        {
            helpOCR hlpOCR = new helpOCR();
            hlpOCR.ShowHelpContrast();
            hlpOCR.Show();
            //ShowHelpContrast
        }

        private void menuItem8_Click(System.Object sender, System.EventArgs e)
        {
            helpOCR hlpOCR = new helpOCR();
            hlpOCR.ShowHelpCropper();
            hlpOCR.Show();
        }

        private void mnuHelpSaveImage_Click(System.Object sender, System.EventArgs e)
        {
            helpOCR hlpOCR = new helpOCR();
            hlpOCR.ShowHelpSaveImage();
            hlpOCR.Show();
        }

        private void mnuHelpSaveOutput_Click(System.Object sender, System.EventArgs e)
        {
            helpOCR hlpOCR = new helpOCR();
            hlpOCR.ShowHelpSaveOutput();
            hlpOCR.Show();
        }

        private void mnuHelpImageRotateLeft_Click(System.Object sender, System.EventArgs e)
        {

            helpOCR hlpOCR = new helpOCR();
            hlpOCR.ShowHelpRotateLeft();
            hlpOCR.Show();
        }

        private void mnuHelpImageRotateRight_Click(System.Object sender, System.EventArgs e)
        {
            helpOCR hlpOCR = new helpOCR();
            hlpOCR.ShowHelpRotateRight();
            hlpOCR.Show();
        }

        private void mnuHelpImageRotateUpright_Click(System.Object sender, System.EventArgs e)
        {
            helpOCR hlpOCR = new helpOCR();
            hlpOCR.ShowHelpRotateUpright();
            hlpOCR.Show();

        }

        private void mnuHelpImageDeskew_Click(System.Object sender, System.EventArgs e)
        {
            helpOCR hlpOCR = new helpOCR();
            hlpOCR.ShowHelpDeskew();
            hlpOCR.Show();
        }

        private void mnuHelpImageRemoveNoise_Click(System.Object sender, System.EventArgs e)
        {
            helpOCR hlpOCR = new helpOCR();
            hlpOCR.ShowHelpNoiseRemoval();
            hlpOCR.Show();
        }

        private void mnuRemoveNoiseII_Click(System.Object sender, System.EventArgs e)
        {
            helpOCR hlpOCR = new helpOCR();
            hlpOCR.ShowHelpNoiseRemoval();
            hlpOCR.Show();
        }

        private void MeanRemoval(int nWeight)
        {

            
            SetWaitCursorMethod(Cursors.WaitCursor);
            /*

				This method does the mean removal of the image, before it is binarized. 
				Yhis is an essentinal part of the ` part. 

			*/

            ConvMatrix m = new ConvMatrix();
            //ConvMatrix* h1[];
            //h1=new ConvMatrix* [20];
            //h1=this.GetTopValR();

            m.SetAll(-1);
            m.Pixel = nWeight;
            m.Factor = nWeight - 8;
            this.Conv3x3(m);
            SetNormalCursorMethod(Cursors.Default);
            
        }

        private void openImageFile()
        {
            if (this.rtbOutputShowing == true) this.delRTB();
            //this.pbOCR.Value = 30;
            try
            {
                System.Windows.Forms.DialogResult d = this.openImageDialog.ShowDialog();

                if (d == System.Windows.Forms.DialogResult.OK)
                {


                    //reset all flags after successfull image loading
                    this.ImageLoaded = true;

                    this.BinaryDone = false;
                    this.SeparateDone = false;
                    this.ContrastDone = false;
                    this.meanDone = false;
                    this.deskewDone = false;
                    // creating a bitmap
                    im = new System.Drawing.Bitmap(this.openImageDialog.OpenFile());
                    //this.pbOCR.Value = 40;
                    UpdatePictureBox1Method(im);
                    //this.pictureBox1.Image = im;
                    //this.pbOCR.Value = 70;
                    g = this.pictureBox1.CreateGraphics();
                    //this.pbOCR.Value = 80;
                    myInfo.Text = "";
                    myInfo1.Text = "";

                    this.setResetMenu(this.ImageLoaded, this.BinaryDone, this.SeparateDone);


                    //System.Windows.Forms.MessageBox.Show("Image successfully loaded","Success");
                } // if (d == System.Windows.Forms.DialogResult.OK)
                //this.pbOCR.Value = 99;
                this.Update();
                //this.pbOCR.Value = 0; //reset value in progressbar
            }//end try
            catch (System.Exception fileOpenException)
            {
                System.Windows.Forms.MessageBox.Show(fileOpenException.ToString(), "Unable to open Image", System.Windows.Forms.MessageBoxButtons.OK, System.Windows.Forms.MessageBoxIcon.Error);

            }



        }

        private void saveImageFile()
        {

            /*

			This method is used to save the image file after certain image processing portion is complete.
			In case we need the file in future.

			*/


            //if(this.BinaryDone)
            //{	
            saveImageDialog.Filter = "JPG files (*.jpg)|*.jpg|PNG files (*.png)|*.png|All valid files (*.jpg/*.png)|*.jpg/*.png";
            saveImageDialog.FilterIndex = 1;
            saveImageDialog.RestoreDirectory = true;

            System.Windows.Forms.DialogResult d = this.saveImageDialog.ShowDialog();
            if (d == System.Windows.Forms.DialogResult.OK)
            {
                // creating a bitmap
                Bitmap save;
                save = new Bitmap(this.pictureBox1.Image);
                save.Save(saveImageDialog.FileName);
                UpdateStatusBarMethod("Image Saved Successfully");
            }
            //}
            //else{
            //		System.Windows.Forms.MessageBox.Show("The file was not saved because \n the image processing is not completed", "Action Incomplete");

            //	}

        }

        private void doDeSkew()
        {

            //If the lines in the image is tilted or slanted, this method is used to deskew the image. 
            //this.pbOCR.Value = 0;

            Deskew ds = new Deskew(im);
            //this.pbOCR.Value += 10;
            double skewAngle = ds.GetSkewAngle();
            //this.pbOCR.Value += 10;

            myInfo1.Text = "Skew Angle:";
            myInfo.Text = skewAngle.ToString();



            //System.Windows.Forms.MessageBox.Show(skewAngle.ToString(),"Skew Angle");

            if (skewAngle != 0)
            {
                im = this.RotateImage(-(float)skewAngle);
                //this.pbOCR.Value += 30;
                UpdatePictureBox1Method(im);
                //this.pictureBox1.Image = im;
                if (this.BinaryDone)
                {
                    this.resetVariablesAfterRotation();
                }
                //this.pbOCR.Value += 30;

            }
            //System.Windows.Forms.MessageBox.Show(" Image rotated successfully","Action Complete");




        }

        private Bitmap RotateImage(float angle)
        {
            Graphics gr;
            Bitmap tmp = new Bitmap(2 * im.Width, 2 * im.Height, PixelFormat.Format24bppRgb);
            tmp.SetResolution(im.HorizontalResolution, im.VerticalResolution);
            gr = Graphics.FromImage(tmp);
            gr.FillRectangle(Brushes.White, 0, 0, 2 * im.Width, 2 * im.Height);
            gr.RotateTransform(angle);
            gr.DrawImage(im, 15, 0);
            gr.Dispose();
            return tmp;
        }

        private void makeBinary()
        {
            if (this.rtbOutputShowing == true) 
                this.delRTB();

            //this.pbOCR.Value = 0;

            /*

				This method binarizes the image. 
				The binarized image is used during the recognition process and training process.
 
				*/

            if (this.ImageLoaded)
            {
                //if (this.BinaryDone)
                //	return;



                try
                {
                    // set the cursor to wait.... 
                    SetWaitCursorMethod(Cursors.WaitCursor);
                    //this.pbOCR.Value += 5;

                    int thresholdValue = 0;
                    // calculating Thresholed Value for binary image					 
                    this.BinaryImage =  BinarizeUsingvc2003Method(this.im, out this.ImgArray, out this.BArray, out thresholdValue);
                    
                    //this.pictureBox1.Image = BinaryImage;
                    UpdatePictureBox1Method(BinaryImage);
                    this.BackupImgArray = this.ImgArray;
                    this.BackupBArray = this.BArray;

                    /*
                    im = BinarizeUsingOtsuMethod(this.im, out thresholdValue);
                    this.pictureBox1.Image = im;
                    
                     * 
                     */
                    if (!this.InvokeRequired)
                    {
                        myInfo1.Text = "Threshold Value";
                        myInfo.Text = thresholdValue.ToString();
                    }
                    this.BinaryDone = true;
                    //this.pbOCR.Value += 5;
                }
                catch (System.Exception ex)
                {
                    System.Windows.Forms.MessageBox.Show(ex.Message.ToString(), "Failed to Binarize the Image!!", System.Windows.Forms.MessageBoxButtons.OK, System.Windows.Forms.MessageBoxIcon.Error);
                    if (this.InvokeRequired)
                    {
                        //
                    }
                    else
                    {
                        this.Update();
                    }

                }

                SetNormalCursorMethod(Cursors.Default);
                UpdateStatusBarMethod("Binarization Done.");

                if (this.InvokeRequired){}
                else{
                    this.Update();
                    this.setResetMenu(this.ImageLoaded, this.BinaryDone, this.SeparateDone);
                }


            }// if(this.ImageLoaded)
        }

        private Bitmap BinarizeUsingvc2003Method(Bitmap imageToBinarize, out int[,] imgArray, out bool[,] bArray, out int thresholdValue)
        {
            ThresholedValue ts = new ThresholedValue(imageToBinarize);
            float fLevel = ts.GetThresholed();
            intLevel = (int)(fLevel * 255);
            //this.pbOCR.Value += 5;

            // getting an binary array of 					 
            rgbConvert rgbC = new rgbConvert(imageToBinarize);
            bArray = rgbC.GetBinaryArray(intLevel);
            imgArray = rgbC.GetImageArray();

            // Showing the binary image
            //this.BinaryImage = rgbC.GetBinaryImage();
            //this.pictureBox1.Image = this.BinaryImage;
            Bitmap binaryImage = rgbC.GetBinaryImage();
            //this.pbOCR.Value += 5;

            // set the cursor to Default.... 
            //this.Cursor = System.Windows.Forms.Cursors.Default;
            //System.Windows.Forms.MessageBox.Show(this.intLevel.ToString()/*fLevel.ToString()*/,"Threshold Value");

            thresholdValue = this.intLevel;
            return binaryImage;
        }

        private void separateChar()
        {
            /*

                This method is used to separate the characters, or the connected units  after the words are separated.

            */
            Pen p = new Pen(Color.Blue, 1);

            for (int i = 0; i < this.numberOfLines; i++)
            {
                for (int j = 0; j < this.Lines[i].getTotalWord(); j++)
                {
                    for (int k = 0; k < this.Lines[i].Words[j].getTotalUnit()-1; k++)
                    {
                        int x1 = this.Lines[i].Words[j].Units[k].getStartColumn();
                        int x2 = this.Lines[i].Words[j].Units[k].getEndColumn();
                        int y1 = this.Lines[i].getStartRow();
                        int y2 = this.Lines[i].getEndRow();

                        g.DrawLine(p, x1, y1, x1, y2);
                        g.DrawLine(p, x2, y1, x2, y2);
                    }
                }
            }// for(int i=0;i<this.numberOfLines;i++)
            UpdateStatusBarMethod("Character Separation Done");
            //if (this.pbOCR.Value < 50) this.pbOCR.Value += 10;

        }

        private void separate()
        {
            if (this.rtbOutputShowing == true) this.delRTB();
            try
            {
                //this.pbOCR.Value = 40;
                UpdateStatusBarMethod("Separating lines and Words...");
                

                /*
				This method is used to separate the words and lines after binarization.
				*/

                this.tmpBArray = new bool[im.Height, im.Width];
                //System.Windows.Forms.MessageBox.Show(im.Height.ToString(),"Height");
                if (!this.InvokeRequired)
                {
                    myInfo1.Text = "Image Height";
                    myInfo.Text = im.Height.ToString();
                }
                //this.tmpBArray=this.BArray;
                for (int i = 0; i < im.Height; i++)
                {
                    for (int j = 0; j < im.Width; j++)
                    {
                        this.tmpBArray[i, j] = this.BArray[i, j];
                    }

                }
                if (this.BinaryDone == true) //If binarization is done
                {
                    if (this.SeparateDone == false)
                    {
                        Separate sp = new Separate(im, BArray, g);
                        sp.LineSeparate();						//Separate Lines from the image
                        //this.pbOCR.Value = 50;

                        this.numberOfLines = sp.getNumberOfLines(); //Get Number of Lines
                        this.Lines = sp.getLines();			//Get Lines
                        this.HeadBottom = sp.getHeadBottom();
                        this.SeparateDone = true;
                        this.separateChar();				//separate Characters					
                        //this.pbOCR.Value = 60;
                    }
                    else
                    {
                        this.separateChar();			//separate Characters
                        //this.pbOCR.Value = 60;
                    }
                    this.WidthStore();
                    this.SizeThreshold = this.ThresholdSize();
                    /*							Resegment* rsg=new Resegment(im,BinaryDone,ImageLoaded,SeparateDone,BArray,this.numberOfLines,this.Lines,g,this.totalUnits,this.SizeThreshold,this.intLevel,this.HeadBottom);
                    //							rsg.PrepareTouchingCharIndex();
                                                rsg.Do_Segmentation();
                    */
                }// if(this.BinaryDone==true) //If binarization is done

                this.setResetMenu(this.ImageLoaded, this.BinaryDone, this.SeparateDone);
                UpdateStatusBarMethod("Separation done");
                //this.Update();
                //this.pbOCR.Value = 70;
            }//end try 
            catch (System.Exception ex)
            {

                UpdateStatusBarMethod("!!!!! Separate Failed !!!!");
                if (this.InvokeRequired) { }
                else
                {
                    MessageBox.Show("Cannot Separate line, words and characters", "Error!!");
                }
            }//end Catch

        }

        private void LoadFromFile()
        {
            System.IO.StreamReader sr = System.IO.StreamReader.Null;
            System.String tempStr;
            System.String charStr;
            System.String unicodeStr;
            int index;

            try
            {
                this.slForCharacters = new System.Collections.SortedList();
                // read the characters and store
                sr = new System.IO.StreamReader(this.characterDBPath);
                tempStr = sr.ReadLine();
                while (tempStr.Length != 0)
                {
                    index = tempStr.IndexOf(" ");
                    charStr = tempStr.Substring(0, index);
                    unicodeStr = tempStr.Substring(index + 1);
                    if (!slForCharacters.ContainsKey(charStr))
                    { slForCharacters.Add(charStr, unicodeStr); }
                    tempStr = sr.ReadLine();
                }
                sr.Close();
            }
            catch (System.Exception ex)
            {
                System.String errorString1 = "";
                errorString1 = ex.Message.ToString();
                errorString1 += string.Concat("Database file access error \n\nThe system generated the following error:\n", errorString1);
                System.Windows.Forms.MessageBox.Show(errorString1, "Error");

                return;
            }
        }

        private void ProvideOutput()
        {
            /*
                    This method prints the output in a new dialog box.
             */

            System.String tempStr = "";
            System.String text = "";
            System.Collections.ArrayList tempAl;	// temporary working array list
            System.String ucodeStr;


            bool aaKarFound = false;
            bool rassoEEkarFound = false;
            int aaKarCounter = 0;
            int rassoEEkarCounter = 0;

            int tempcount = 0;	//Added for postprocessor : Multifactorial added
            try
            {
                int index = 0;
                int ind = 0;
                for (int i = 0; i < this.numberOfLines; i++) //Number of lines
                {
                    for (int j = 0; j < this.Lines[i].getTotalWord(); j++) //number of words
                    {
                        for (int k = 0; k < this.Lines[i].Words[j].getTotalUnit(); k++) //number of units
                        {
                            if (ind < this.alModelRec.Count)			// increment ind++ (till the alModelRec
                            {// Block Start
                                ucodeStr = "";									//initially unicodestr = ""
                                System.Collections.IEnumerator ENum;			//Enum a looper
                                ENum = this.alModelRec.GetEnumerator();

                                System.String tempStr1 = "";
                                int tempCount = 0;									//Counter (tempCount)
                                while (ENum.MoveNext())
                                {
                                    if (ind == tempCount)
                                    {
                                        tempStr = ENum.Current.ToString(); //keep the temporary value in tempStr
                                        break;
                                    }
                                    tempCount++;			//find the tempCount						
                                }


                                tempStr1 = tempStr; //multifactorial added

                                index = this.slModelTranscription.IndexOfKey(tempStr);
                                ind++;
                                tempAl = (System.Collections.ArrayList)slModelTranscription.GetByIndex(index);
                                System.Collections.IEnumerator tempNum = tempAl.GetEnumerator();

                                int tcount = 0; //multifactorial added

                                while (tempNum.MoveNext())
                                {
                                    tempStr = (String)tempNum.Current;
                                    ucodeStr += string.Concat(ucodeStr, slForCharacters.GetKey(slForCharacters.IndexOfValue(tempStr)));

                                    tcount++; //multifactorial added
                                }

                                text += string.Concat(text, ucodeStr);			//multifactorial added


                                tempcount = tcount;


                            } //end if

                            ///////////////// Whole Block 
                        }
                        text += string.Concat(text, (String)" ");
                    }
                    text += string.Concat(text, (String)"\n");
                }
            }
            catch (System.Exception ex)
            {
                System.Windows.Forms.MessageBox.Show(ex.Message.ToString(), "Failed to provide the output!!", System.Windows.Forms.MessageBoxButtons.OK, System.Windows.Forms.MessageBoxIcon.Error);
                return;
            }



            System.String notepadOutputFileName = string.Concat(this.applicationPath, "\\", "rawInput.txt");
            System.IO.StreamWriter notepadOutSw = new System.IO.StreamWriter(notepadOutputFileName);
            notepadOutSw.Write(text);
            notepadOutSw.Close();
            try
            {
                this.callPostProcessor(text);
            }
            catch (System.Exception ex)
            {
                System.Windows.Forms.MessageBox.Show("Garbled Output", "The Post Processor which checks for errors has failed, \nIt seems that the postprocessor was not found or the postprocessor cannot be run");
                UpdateStatusBarMethod("PostProcessor Failed");
                this.rtbMainOutput.Text = text;
            }

            //this.rtbMainOutput.Text = text;
            this.createRTB();

            //	PostProcessor *pp = new PostProcessor(text);
            //OCR.RecognitionForm rw=new OCR.RecognitionForm();
            //
            ////rw.showText(text);
            ////rw.MdiParent = this;
            //rw.showText(text);
            //rw.ShowDialog();



            // 
            // rtbOutput
            // 

            /*this.createRTB();*/
            UpdateStatusBarMethod("Recognition Complete");
            SetNormalCursorMethod(Cursors.Default);
            //this.pbOCR.Value = 100;
            /*this.rtbOutput.Text = text;*/
        }

        void mnuCropper_Click(System.Object sender, System.EventArgs e)
        {

        }

        Bitmap BinarizeUsingOtsuMethod(Bitmap org, out int thresholdValue)
        {

            Bitmap temp = (Bitmap)org.Clone();
            ot.Convert2GrayScaleFast(temp);
            int otsuThreshold = ot.getOtsuThreshold((Bitmap)temp);
            ot.threshold(temp, otsuThreshold);
            //textBox1.Text = otsuThreshold.ToString();
            //pictureBox1.Image = temp;
            thresholdValue = otsuThreshold;
            return temp;
        }
    }
}
