/*
 * Original code was forked from : http://code.google.com/p/nepaliocr/source/browse/trunk/myWindow.cpp?spec=svn146&r=138
 */

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace NOCR
{
    public partial class myWindow : Form
    {

        private Bitmap im;
        private Bitmap BinaryImage;

        bool[,] BinArray;

        private Graphics g;
        private int intLevel;
        private int[,] ImgArray;

        int[,] ImageArray;

        private bool[,] BArray;
        bool[,] tmpBArray;
        private bool BinaryDone;
        private bool ImageLoaded;
        bool SeparateDone;
        bool ContrastDone;
        bool meanDone;
        bool deskewDone;
        bool TouchingCharIdentified;


        private int numberOfLines;
        private Line[] Lines;

        private string applicationPath;
        string modelTrainDBPath;
        string scriptFilePath;
        string characterDBPath;


        private System.Collections.SortedList slForCharacters;
        private System.Collections.SortedList slModelTranscription;	// for storing the model transcriptions
        private System.Collections.ArrayList alModelRec;			// for models that already recognized

        Line[] LineInfo;
        int lineCount;
        private int lineno = 0;
        private int wordno = 0;
        private int charno = 0;
        private int x1, x2, y1, y2;
        Bitmap cropImage;


        public myWindow()
        {
            InitializeComponent();
        }
        public myWindow(
                        Bitmap im,
                        Bitmap BinaryImage,
                        Graphics g,
                        int intLevel,
                        int[,] ImgArray,
                        bool[,] BArray,
                        bool[,] tmpBArray,
                        bool BinaryDone,
                        bool ImageLoaded,
                        bool SeparateDone,
                        bool ContrastDone,
                        bool meanDone,
                        bool deskewDone,
                        int numberOfLines,
                        Line[] Lines,
                        String applicationPath,
                        String modelTrainDBPath,
                        String scriptFilePath,
                        String characterDBPath,
                        System.Collections.SortedList slForCharacters,
                        System.Collections.SortedList slModelTranscription,	// for storing the model transcriptions
                        System.Collections.ArrayList alModelRec)
        {

            InitializeComponent();
            this.im = im;
            this.BinaryImage = BinaryImage;
            this.g = g;
            this.intLevel = intLevel;
            this.ImgArray = ImgArray;
            this.BArray = BArray;
            this.tmpBArray = tmpBArray;
            this.BinaryDone = BinaryDone;
            this.ImageLoaded = ImageLoaded;
            this.SeparateDone = SeparateDone;
            this.ContrastDone = ContrastDone;
            this.meanDone = meanDone;
            this.deskewDone = deskewDone;
            this.numberOfLines = numberOfLines;
            this.Lines = Lines;
            this.applicationPath = applicationPath;
            this.modelTrainDBPath = modelTrainDBPath;
            this.scriptFilePath = scriptFilePath;
            this.characterDBPath = characterDBPath;
            this.slForCharacters = slForCharacters;
            this.slModelTranscription = slModelTranscription;	// for storing the model transcriptions
            this.alModelRec = alModelRec;
            this.pictureBox_myWindow.Image = this.im;
            this.bigHeightLabel.Text = this.im.Height.ToString();
            this.bigWidthLabel.Text = this.im.Width.ToString();
            //this.TouchingCharIdentified=TouchingCharIdentified;





            //application path
            this.applicationPath = Application.StartupPath.ToString();
            int len = this.applicationPath.Length - 1;
            if (this.applicationPath.Substring(len).Equals("\\"))
            {
                this.applicationPath = this.applicationPath.Substring(0, len);
            }

            this.modelTrainDBPath += string.Concat(this.applicationPath, "\\htk\\DataBaseFile\\modelTrainDataBase.txt");

            this.alModelRec = new System.Collections.ArrayList();
            this.characterDBPath += string.Concat(this.applicationPath, "\\htk\\DataBaseFile\\characters.txt");
            this.scriptFilePath += string.Concat(this.applicationPath, "\\htk\\recognizer\\script.txt");
            this.LoadFromFile();


        }

        private void mnuSave_Click(object sender, EventArgs e)
        {

        }

        private void mnuSingleRecognize_Click(object sender, EventArgs e)
        {

        }

        private void mnuRecognizeAll_Click(object sender, EventArgs e)
        {

        }

        private void mnuLogs_Show_Click(object sender, EventArgs e)
        {

        }

        private void mnuLogs_Hide_Click(object sender, EventArgs e)
        {

        }

        private void saveButton_ImageViewer_Form_Click(object sender, EventArgs e)
        {

        }

        private void myWindowSeparateButton_Click(object sender, EventArgs e)
        {

        }

        private void myWindowRecognizeButton_Click(object sender, EventArgs e)
        {

        }

        private void singleRecog_Click(object sender, EventArgs e)
        {

        }

        private void nextButton_Click(object sender, EventArgs e)
        {

        }

        private void exitButton_Click(object sender, EventArgs e)
        {

        }

        void LoadFromFile()
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
                    {
                        slForCharacters.Add(charStr, unicodeStr);
                    }
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
        internal void defineVar(int[,] ImgArray, bool[,] BArray, Line[] Lines, int numberOfLines)
        {
            this.ImageArray = ImgArray;
            this.BinArray = BArray;
            this.LineInfo = Lines;
            this.lineCount = numberOfLines;
            this.display(this.lineno, this.wordno, this.charno);

        }

        internal void display(int lineno,int wordno,int charno)
		{
			x1=this.LineInfo[lineno].Words[wordno].Units[charno].getStartColumn(); //Equivalent to . left_x
			x2=this.LineInfo[lineno].Words[wordno].Units[charno].getEndColumn();	//Equivalent to . right_x
			y1=this.LineInfo[lineno].getStartRow();		//Equivalent to . top_y
			y2=this.LineInfo[lineno].getEndRow();			 //Equivalent to . bottom_y
			
			int xsize=x2-x1+1;
			int ysize=y2-y1+1;
			 
			this.cropImage=new Bitmap(xsize,ysize,PixelFormat.Format24bppRgb);
			
			for(int i=y1;i<=y2;i++)//traverse throughy
			{
				for(int j=x1;j<=x2;j++)//traverse through x
				{
					if(this.BinArray[i,j])
					{
						 
						this.cropImage.SetPixel(j-x1,i-y1,Color.White);
					}
					else
					{
						this.cropImage.SetPixel(j-x1,i-y1,System.Drawing.Color.Black);
					}
			    }
			}
			this.pictureBoxSmall.Image=cropImage;
			this.smallHeightLabel.Text = this.cropImage.Height.ToString();
			this.smallWidthLabel.Text = this.cropImage.Width.ToString();
			//this.singleRecognize(x1,x2,y1,y2,0);
		}

    }
}


/**
 *   OCR
 * Programmed in C#, Visual Studio 2010
 * Microsoft Windows 7 
 * Professional 
 * Home Premium
 
 * Intel[R] 
 * 3 GB RAM
 * 2.80 GHZ , 1.00 GB of  RAM 
 *
 *
 * Requirements:
 *  
 * win2k or later\n
 * .NET FrameWork 4.0 or later 
 *
 * Version 1.0
 * first version
 *
 * Date 9-18-2012
 *
 ** Author Rajesh Pandey
 *
 * license
 * This code is absolutely free to use and modify. The code is provided "as is" with
 * no expressed or implied warranty. The author accepts no liability if it causes
 * any damage to your computer, causes your pet to fall ill, increases baldness
 * or makes your car start emitting strange noises when you start it up.
 * This code has no bugs, just undocumented features!
 * 
 *  
 *
 *  
 *
 */