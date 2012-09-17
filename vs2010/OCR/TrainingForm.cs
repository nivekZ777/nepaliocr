using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace NOCR
{
    public partial class TrainingForm : Form
    {

        bool[,] BinArray;
        int[,] ImageArray;
        Line[] LineInfo;
        int lineCount;
        Bitmap cropImage;
        int lineno = 0;
        int wordno = 0;
        int charno = 0;
        private int x1, x2, y1, y2;
        private string applicationPath;
        private string characterDBPath;
        private string modelTrainDBPath;
        private string modelName;

        // for recognition
        private string wordToRec;
        private System.Collections.ArrayList alRec;


        private System.Collections.SortedList slForCharacters;
        private System.Collections.ArrayList alForCharacters;
        System.Collections.IEnumerator charEnumerator;
        bool enableTrainingOnTextChanged;
        public TrainingForm()
        {
            this.applicationPath=Application.StartupPath.ToString();
			
			int len = this.applicationPath.Length -1;			
			if(this.applicationPath.Substring(len).Equals("\\"))
			{
				this.applicationPath = this.applicationPath.Substring(0,len);				
			}

			// getting the character database path
			//System.Windows.Forms.MessageBox.Show(this.applicationPath,"Path of characterDB path");

			this.characterDBPath+= string.Concat(this.applicationPath ,"\\htk\\DataBaseFile\\characters.txt");	
			//System.Windows.Forms.MessageBox.Show(this.characterDBPath,"Path of characterDB path");
			
			this.modelTrainDBPath += string.Concat(this.applicationPath , "\\htk\\DataBaseFile\\modelTrainDataBase.txt");
			// getting the path of the word to be tranied for which the recognition output is shown
			this.wordToRec += string.Concat(this.applicationPath ,"\\htk\\files\\trainfile.txt");

			this.alForCharacters = new System.Collections.ArrayList();

			InitializeComponent();
			//this.applicationPath = Application.StartupPath.ToString();
			// for the directory, path appear an extra '/'
			// here we are removing that '/'
			bool enableTrainingOnTextChanged = false;
        }

        private void mnuAdd_Click(object sender, EventArgs e)
        {

        }

        private void mnuTrain_Click(object sender, EventArgs e)
        {

        }

        private void mnuExit_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void mnuNext_Click(object sender, EventArgs e)
        {

        }

        private void mnuPrevious_Click(object sender, EventArgs e)
        {

        }

        private void prevButton_Click(object sender, EventArgs e)
        {
            if (charno > 0) //this.LineInfo[lineno].Words[wordno].getTotalUnit()-1)
            {
                this.charno--;
            }
            else
            {
                //this.charno=0;
                if (wordno > 0)// this.LineInfo[lineno].getTotalWord()-1)
                {
                    this.wordno--;
                    this.charno = this.LineInfo[lineno].Words[wordno].getTotalUnit() - 1;
                }


                else
                {
                    if (lineno > 0)
                    {
                        this.lineno--;
                        this.wordno = this.LineInfo[lineno].getTotalWord() - 1;
                        this.charno = this.LineInfo[lineno].Words[wordno].getTotalUnit() - 1;

                    }
                    else
                    {
                        this.lineno = this.lineCount - 1;
                        this.wordno = this.LineInfo[lineno].getTotalWord() - 1;
                        this.charno = this.LineInfo[lineno].Words[wordno].getTotalUnit() - 1;
                    }
                }
            }
            this.display(this.lineno, this.wordno, this.charno);
            this.Update();

        }

        private void nextButton_Click(object sender, EventArgs e)
        {
            if (charno < this.LineInfo[lineno].Words[wordno].getTotalUnit() - 1)
            {
                this.charno++;
            }
            else
            {
                //this.charno=0;
                if (wordno < this.LineInfo[lineno].getTotalWord() - 1)
                {
                    this.wordno++;
                    this.charno = 0;
                }


                else
                {
                    this.wordno = 0;
                    this.charno = 0;
                    if (lineno < this.lineCount - 1)
                    {
                        this.lineno++;
                    }
                    else
                    {
                        this.lineno = 0;
                        this.wordno = 0;
                        this.charno = 0;
                    }
                }
            }
            this.display(this.lineno, this.wordno, this.charno);
            this.Update();
        }

        private void addChar_Click(object sender, EventArgs e)
        {
			 int i = this.characterBox.SelectedIndex;
			 System.String text ="";
			 int numOfElement = 0;
			 if(i>=0)
			 {
				 try
				 {
					 this.alForCharacters.Add(this.characterBox.SelectedItem.ToString());
					 //this.alForCharacters.Add(this.comboBoxCharacters.SelectedItem.ToString());
					 //numOfElement = alForCharacters.Count;

					 this.charEnumerator=this.alForCharacters.GetEnumerator();
					 //for(int j=0;j<numOfElement;j++)

					 while(this.charEnumerator.MoveNext())
					 {
						 //System.String tmp=*dynamic_cast<__box String*>(this.charEnumerator.Current);
						 System.String tmp=(String)this.charEnumerator.Current;
						 text += string.Concat(text,tmp.ToString());
					 }
				 }
				 catch(System.Exception ex)
				 {
					 System.Windows.Forms.MessageBox.Show(ex.Message.ToString(),"Process Transcription Failed!!",System.Windows.Forms.MessageBoxButtons.OK,System.Windows.Forms.MessageBoxIcon.Error);
				     return;
				 }
				 this.combineChar.Text = text;
			 }
			 /*if(numOfElement>0)
			 {
				 this.buttonCompleted.Enabled = true;
			 }*/



			 //this.combineChar.Text=this.combineChar.Text.Concat(this.combineChar.Text,this.characterBox.SelectedItem.ToString());
		 }

        private void trainButton_Click(object sender, EventArgs e)
        {
			 if(this.enableTrainingOnTextChanged ==true){
			 
				 System.Windows.Forms.MessageBox.Show(this.combineChar.Text);
			 TrainingProcess tp=new TrainingProcess(this.applicationPath,this.ImageArray,this.x1,this.x2,this.y1,this.y2);
			 tp.PrepareTrainingData();
			 this.statusBar1.Text = "Training Please wait..";
			 this.Cursor = System.Windows.Forms.Cursors.WaitCursor;
			 tp.TrainingByHTK(tp.numOfFrame);
			 this.modelName = tp.GetTrainedModelName();

			 System.Windows.Forms.MessageBox.Show("Training Completed Successfully!","Success!!",MessageBoxButtons.OK,MessageBoxIcon.Exclamation);
			 
			 // delete the unnecessary temporary file
			 System.IO.File.Delete(wordToRec);

			 System.IO.StreamWriter sw = System.IO.StreamWriter.Null;
			 System.String tempStr;
			 try
			 {
				 
				 sw = System.IO.File.AppendText(this.modelTrainDBPath);
				 sw.WriteLine(this.modelName);


				 /*for(int i=0;i<this.alForCharacters.Count;i++)
				 {
					 tempStr = this.slForCharacters.GetByIndex(slForCharacters.IndexOfKey(alForCharacters[i])).ToString();
					 sw.WriteLine(tempStr);
				 }*/

				 this.charEnumerator=this.alForCharacters.GetEnumerator();
					 //for(int j=0;j<numOfElement;j++)

				while(this.charEnumerator.MoveNext())
//				 for(int i=0;i<this.alForCharacters.Count;i++)
				 {
					 //System.String tmp=*dynamic_cast<__box System.String>(this.charEnumerator.Current);
					 System.String tmp=(String)this.charEnumerator.Current;
					 tempStr = this.slForCharacters.GetByIndex(slForCharacters.IndexOfKey(tmp)).ToString();
					 //tempStr = this.slForCharacters.GetByIndex(slForCharacters.IndexOfKey(this.charEnumerator.Current).ToString());
					 sw.WriteLine(tempStr);
				 }
				 sw.WriteLine("*");
				 sw.Close();
				 this.characterBox.Text = "";
				 this.characterBox.SelectedIndex = -1;
				 //this.labelRecWord.Text = "";
				 this.alForCharacters.Clear();

				 // disable some buttons
				 //this.buttonCompleted.Enabled = false;
				 //this.groupBox1.Enabled = false;
				 
			 }
			 catch(System.Exception ex)
			 {
				 System.Windows.Forms.MessageBox.Show(ex.Message.ToString(),"Failed to Load the Model DataBase!!",System.Windows.Forms.MessageBoxButtons.OK,System.Windows.Forms.MessageBoxIcon.Error);
			     return;
			 }
			 
			 this.statusBar1.Text = "          Done    ";
			 this.Cursor = System.Windows.Forms.Cursors.Default;
			 bool enableTrainingOnTextChanged = false;
		 }
			 else{
				 System.Windows.Forms.MessageBox.Show("Nothing to Train.");
			 }
		 }

        public void defineVar(int[,] ImgArray, bool[,] BArray, Line[] Lines, int numberOfLines)
			{
				this.ImageArray=ImgArray;
				this.BinArray=BArray;
				this.LineInfo=Lines;
				this.lineCount=numberOfLines;
				this.display(this.lineno,this.wordno,this.charno);
				this.LoadComboBoxFromFile();
			}


		public void display(int lineno,int wordno,int charno)
		{
			x1=this.LineInfo[lineno].Words[wordno].Units[charno].getStartColumn();
			x2=this.LineInfo[lineno].Words[wordno].Units[charno].getEndColumn();
			y1=this.LineInfo[lineno].getStartRow();
			y2=this.LineInfo[lineno].getEndRow();

			int xsize=x2-x1+1;
			int ysize=y2-y1+1;
			
			//xsize=400;
			//ysize=400;

			this.cropImage=new Bitmap(xsize,ysize,System.Drawing.Imaging.PixelFormat.Format24bppRgb);
			
			for(int i=y1;i<=y2;i++)
			{
				for(int j=x1;j<=x2;j++)
				{
					if(this.BinArray[i,j])
					{
						this.cropImage.SetPixel(j-x1,i-y1,Color.White);
					}
					else
					{
						this.cropImage.SetPixel(j-x1,i-y1,Color.Black);
					}
			    }
			}
			this.pictureBox1.Image=cropImage;
		}

		public System.Collections.SortedList getSortedList()
				 {
					 return this.slForCharacters;
				 }

		private void LoadComboBoxFromFile()
		 {
			System.IO.StreamReader sr = System.IO.StreamReader.Null;
			System.String tempStr;
			System.String charStr;
			System.String unicodeStr;
			int index;

			try
			{
				slForCharacters = new System.Collections.SortedList();
				// read the characters and store
				sr = new System.IO.StreamReader(this.characterDBPath);
				tempStr = sr.ReadLine();
				while (tempStr.Length!=0)
				{
					index = tempStr.IndexOf(" ");
					charStr = tempStr.Substring(0,index);
					unicodeStr = tempStr.Substring(index+1);
					if(!slForCharacters.ContainsKey(charStr)){
						slForCharacters.Add(charStr,unicodeStr);
						this.characterBox.Items.Add(charStr);
					}
					tempStr = sr.ReadLine();
				}
				sr.Close();
			}
			catch(System.Exception ex)
			{
				System.Windows.Forms.MessageBox.Show(ex.Message.ToString(),"Can't load the Combo box!!",System.Windows.Forms.MessageBoxButtons.OK,System.Windows.Forms.MessageBoxIcon.Error);
			    return;
			}
		 }

        private void combineChar_TextChanged(object sender, EventArgs e)
        {
            this.enableTrainingOnTextChanged = true;
        }
    }
}
