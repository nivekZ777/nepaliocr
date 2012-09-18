using System;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;

namespace NOCR
{
    public unsafe class Separate
    {
    
    bool[,] BinaryArray;
	int xSize;
	int ySize;
	int[] Horizontal;
	int[] R2;
	int[,] Vertical;
	//int **VerticalC;
	int numberOfLines;
	int[,] HeadBottom;
	static int thresh_char_gap=2;

	Graphics g;
    public Line[] Lines;


//This is the constructor for the class Separate
internal Separate(Bitmap im,bool[,] B,Graphics gr)
{
//Takes input : Bitmap image							: Bitmap* im
// the binarised image in the form of boolean array		: bool **B
//The graphics of image									: Graphics* gr

	//referencing										:xSize <= Width of image
	//													:ySize <= Height of Image
	//													:BinaryArray <= B , Graphics g <= gr, 
	//A new array of size ySize is created				:Horizontal[height of image] 
	this.xSize=im.Width;
	this.ySize=im.Height;
	this.BinaryArray=B;
	this.Horizontal=new int[ySize];
	this.g=gr;
	this.numberOfLines=0;
}

//This is a function which separates lines
internal void LineSeparate()
{
	List<int> lineStart=new List<int>();
    List<int> lineEnd = new List<int>();
//	vector <int> lineStart;
//	vector <int> lineEnd;

/////
	IEnumerator startEnumerator;
	IEnumerator endEnumerator;
	 

	for(int i=0;i<this.ySize;i++)
	{
		int count=0;
		for(int j=0;j<this.xSize;j++)
		{
			if(this.BinaryArray[i,j]==false)
			{
				count++;
			}
		}
		this.Horizontal[i]=count;
	}

	bool hasLineStarted=false;

	for(int i=0;i<this.ySize;i++)
	{
		if(hasLineStarted==false)
		{
			if(this.Horizontal[i]>0)
			{ 
				lineStart.Add(i);
				hasLineStarted=true;
			}
		}
		else
		{
			if(this.Horizontal[i]<=0)
			{
				 
				lineEnd.Add(i-1);
				hasLineStarted=false;
			}
		}
	}

	startEnumerator =  lineStart.GetEnumerator();
	endEnumerator = lineEnd.GetEnumerator();
	
	//Red Pen are used to draw lines when they are separated
	Pen p=new Pen(Color.Red,1);
	while (startEnumerator.MoveNext() &&  endEnumerator.MoveNext())
	{ //possible error because startenumerator and endenumerator might not be same.
    int s = (int)startEnumerator.Current;
    int e = (int)endEnumerator.Current;
	numberOfLines++;
	g.DrawLine(p,0,s,this.xSize,s);
	g.DrawLine(p,0,e,this.xSize,e);
	}
	this.HeadBottom=new int[this.numberOfLines,1000];
    //for(int i=0;i<this.numberOfLines;i++)
    //{
    //    this.HeadBottom[i,1000]= new int();
    //        //new int[2];
    //}
 
	//System.Windows.Forms.MessageBox.Show("ok");
	WordSeparate1(lineStart,lineEnd);
}

//WordSeparate is used to separate words 
void WordSeparate(List<int> start, List<int> end)
{
	
	IEnumerator startEnumerator;
	IEnumerator endEnumerator;

	startEnumerator=start.GetEnumerator();
	endEnumerator=end.GetEnumerator();
	
	//Vertical=new int[numberOfLines,1000];
	
	
	int verticalCount=0;
	
	while(startEnumerator.MoveNext() && endEnumerator.MoveNext())
	{
		int y1=(int)(startEnumerator.Current);
		int y2=(int) (endEnumerator.Current);

		//Vertical[verticalCount,1000] = new int();
            //new int[xSize,1000];
	
		for(int i=0;i<this.xSize;i++)
			{
				int count=0;
				
				for(int j=y1;j<=y2;j++)
					{
						if(BinaryArray[j,i]==false)
							{
							count++;
							}
					}
				this.Vertical[verticalCount,i]=count;
			}

		verticalCount++;
	}
	
	Pen p=new Pen(Color.Red,1);
	
	int cnt=0;

	startEnumerator=start.GetEnumerator();
	endEnumerator=end.GetEnumerator();

int start_of_word=0;
int end_of_word=0;
int _sum_word_length=0;
int _number_of_words=0;
	
while(startEnumerator.MoveNext() && endEnumerator.MoveNext())
	{

	int y1=(int) (startEnumerator.Current);
	int y2=(int) (endEnumerator.Current);
	
	
	List<int> wordStart=new List<int>();
    List<int> wordEnd = new List<int>();
	IEnumerator wordStartEnumerator,wordEndEnumerator;
	
	bool hasWordStarted=false;

	for(int j=0;j<this.xSize;j++)
	{
		if(hasWordStarted==false)
		{
			if(Vertical[cnt,j]>0)
			{
				wordStart.Add(j);
				hasWordStarted=true;
			}
		}
		else
		{
			if(Vertical[cnt,j]<=0)
			{
				wordEnd.Add(j);
				hasWordStarted=false;
			}
		}

	}

	wordStartEnumerator=wordStart.GetEnumerator();
	wordEndEnumerator=wordEnd.GetEnumerator();
	
	while (wordStartEnumerator.MoveNext() &&  wordEndEnumerator.MoveNext())
		{
			int x1 = (int)(wordStartEnumerator.Current);
            int x2 = (int)(wordEndEnumerator.Current);
			
			start_of_word=x1;
			end_of_word=x2;
			_sum_word_length+=(end_of_word-start_of_word);
			_number_of_words++;
		
			
			g.DrawLine(p,x1,y1,x1,y2);
			g.DrawLine(p,x2,y1,x2,y2);
		}
	cnt++;
	}

	int _average_word_length=(int) (_sum_word_length) / (_number_of_words);
			
	System.Windows.Forms.MessageBox.Show(_average_word_length.ToString(),"Average Word Length");

 
	 

}
//Draws horizontal histogram
void drawHorizontalHist()
{
	Pen p=new Pen(Color.Red,1);
	
	for(int i=0;i<this.ySize;i++)
	{
		g.DrawLine(p,0,i,this.Horizontal[i],i);
	}
}

//Word separate
void WordSeparate1(List<int> start, List<int> end)
{
    List<int> wordStart = new List<int>();
	List<int> wordEnd=new List<int>();
	
	List<int> wordStart1=new List<int>();
    List<int> wordEnd1 = new List<int>();
	//IEnumerator wordStartEnumerator1,wordEndEnumerator1;
	//This Function Needs to be upgraded
	
	IEnumerator startEnumerator;
	IEnumerator endEnumerator;
    IEnumerator wordStartEnumerator;
    IEnumerator wordEndEnumerator;

	int start_of_word2=0;
	int end_of_word1=0;
	int _sum_word_gap=0;
	int _number_of_gaps=0;


	startEnumerator=start.GetEnumerator(); //linestart (from Separate )
	endEnumerator=end.GetEnumerator(); // lineEnd (from Separate)
	
	//Vertical=new int[numberOfLines,1000];
	
	
	int verticalCount=0;
	
	while(startEnumerator.MoveNext() && endEnumerator.MoveNext())
	{
		int y1=(int) (startEnumerator.Current);
		int y2=(int) (endEnumerator.Current);

		//Vertical[verticalCount,1000]= new int();
            //new int[xSize];
	
        Vertical = new int[ySize,xSize];
		for(int i=0;i<this.xSize;i++)
			{
				int count=0;
				
				for(int j=y1;j<=y2;j++)
					{
						if(BinaryArray[j,i]==false)
							{
							count++;
							}
					}
                
				this.Vertical[verticalCount,i]=count;
			}

		verticalCount++;
	}


	
	//Pen* p=new Pen(Color.Red,1);
	
	int cnt=0;

	startEnumerator=start.GetEnumerator();
	endEnumerator=end.GetEnumerator();
	
while(startEnumerator.MoveNext() && endEnumerator.MoveNext())
	{

	int y1=(int) (startEnumerator.Current);
	int y2=(int) (endEnumerator.Current);
	wordStart= new List<int>();
	wordEnd = new List<int>();

	
	
	bool hasWordStarted=false;

	for(int j=0;j<this.xSize;j++)
	{
		if(hasWordStarted==false)
		{
			if(Vertical[cnt,j]>0)
			{
				wordStart.Add(j);
				hasWordStarted=true;
			}
		}
		else
		{
			if(Vertical[cnt,j]<=0)
			{
				wordEnd.Add(j);
				hasWordStarted=false;
			}
		}

	}

    wordStartEnumerator = wordStart.GetEnumerator();
    wordEndEnumerator = wordEnd.GetEnumerator();
 
	int no_of_word=0;
	while (wordStartEnumerator.MoveNext() &&  wordEndEnumerator.MoveNext())
		{
			
			int x1 = (int)(wordStartEnumerator.Current);
			int x2 = (int)(wordEndEnumerator.Current);
			
			if(no_of_word==0)
			{
			end_of_word1=x2;
			}
			else
			{
				start_of_word2=x1;
				 
				_sum_word_gap+=(start_of_word2-end_of_word1);
				end_of_word1=x2;
				_number_of_gaps++;

				
			}
		
			 
			no_of_word++;
		}
	 
	cnt++;
	}

	if(_number_of_gaps==0){
		System.Windows.Forms.MessageBox.Show("It seems that gaps between words is invalid \n Please reload a proper image ....","invalid image width");
		
	}
	int _average_word_gaps=(int)(_sum_word_gap)/(_number_of_gaps);		
	//System.Windows.Forms.MessageBox.Show(_average_word_gaps.ToString(),"Average Word Gaps");
	
	cnt=0;
	
	startEnumerator=start.GetEnumerator();
	endEnumerator=end.GetEnumerator();
	
	while(startEnumerator.MoveNext() && endEnumerator.MoveNext())
	{
		int y1=(int) (startEnumerator.Current);
		int y2=(int) (endEnumerator.Current);
	
		wordStartEnumerator=wordStart.GetEnumerator();
		wordEndEnumerator=wordEnd.GetEnumerator();
		int word_count=0;
		int newx1 = 0,newx2 = 0,tempx2 = 0;

		wordStart1=new List<int>();
		wordEnd1=new List<int>();

		
		while (wordStartEnumerator.MoveNext() &&  wordEndEnumerator.MoveNext())
		{
		int x1 = (int)(wordStartEnumerator.Current);
        int x2 = (int)(wordEndEnumerator.Current);
		
		
			if(word_count==0)
			{
			newx1=x1;
			tempx2=x2;
			}

			else
			{
				if(x1-tempx2>=_average_word_gaps)	//the word gap is ge 5
				{
				newx2=tempx2;
				 

				wordStart1.Add(newx1);
				wordEnd1.Add(newx2);

				//add newx1 in wordStart1
				//add newx2 in wordEnd1

				newx1=x1;
				tempx2=x2;
				}
				else				//the word gap is l 5 i.e no word is still formed
				{
				tempx2=x2;
				}
			}

		word_count++;
		}
		newx2=tempx2;
		 
		wordStart1.Add(newx1);
		wordEnd1.Add(newx2);


		cnt++;
	}

 
		
CheckMattra(start,end,wordStart1,wordEnd1);
	
}




//Checks Mattra
void CheckMattra(List<int> lineStart,List<int> lineEnd,List<int> wordStart,List<int> wordEnd)
{
	 
	IEnumerator lineStartEnumerator,lineEndEnumerator;
	//IEnumerator *wordStartEnumerator,*wordEndEnumerator;

	lineStartEnumerator=lineStart.GetEnumerator();
	lineEndEnumerator=lineEnd.GetEnumerator();


	Pen p=new Pen(Color.White,1);
 
	//int cnt=0;
	//drawHorizontalHist();
	int linecount=0;

	while(lineStartEnumerator.MoveNext() && lineEndEnumerator.MoveNext())
	{
		int y1=(int) (lineStartEnumerator.Current);
        int y2 = (int)(lineEndEnumerator.Current);
		int max=0;
		int maxIndex = 0;
		int[] mIndex=new int[100];
		int cntMattra=0;
		for(int i=y1;i<=y2;i++)
		{
			if(Horizontal[i]>max)
			{
				max=Horizontal[i];
				maxIndex=i;
			}
		}

		for(int i=y1;i<=y2;i++)
		{
			if((double)Horizontal[i] >= (double)Horizontal[maxIndex]*(0.9))
			{
				//max=Horizontal[i];
				mIndex[cntMattra]=i;
				cntMattra++;
			}
		}
		//g.DrawLine(p,0,maxIndex,this.xSize,maxIndex);
	
		//Added Code By Sanjeev Maharjan
		for(int j=0;j<this.xSize;j++)
		{
			for(int k=0;k<cntMattra;k++)
			{
				this.BinaryArray[mIndex[k],j]=true;
				g.DrawLine(p,0,mIndex[k],this.xSize,mIndex[k]);
			}
		}
		this.HeadBottom[linecount,0]=maxIndex-y1;
		R2=new int[this.xSize];
		for(int i=0;i<this.xSize;i++)
		{
			for(int j=maxIndex;j<y2;j++)
			{
				if(this.BinaryArray[j,i]==false && this.BinaryArray[j+1,i]==true)
				{
					R2[i]=j;
				}
			}
		}
		int maxR2=maxIndex;
		for(int i=0;i<this.xSize;i++)
		{
			if(maxR2<R2[i])
			{
				maxR2=R2[i];
			}
		}
		this.HeadBottom[linecount,1]=maxR2-y1;
		
		//Removing top Modifier
			for(int k=0;k<this.xSize;k++)
			{
				for(int j=y1;j<=maxIndex;j++)
				{	
					this.BinaryArray[j,k]=true;
				}
			}
		
			for(int j=y1;j<=maxIndex;j++)
			{
				g.DrawLine(p,0,j,this.xSize,j);
			}
			//Removing Lower Modifier
		//Removing Lower Modifier
		for(int k=0;k<this.xSize;k++)
		{
			for(int j=maxR2;j<=y2;j++)
			{	
				this.BinaryArray[j,k]=true;
			}
		}
		for(int j=maxR2;j<=y2;j++)
		{
			g.DrawLine(p,0,j,this.xSize,j);
		}
	
	linecount++;
	}

	this.CharSeparate(lineStart,lineEnd,wordStart,wordEnd);
		

}
internal int[,]  getHeadBottom()
{
	return (this.HeadBottom);
}
void CharSeparate(List<int> start,List<int> end,List<int> wStart,List<int> wEnd)
{
 
	

	int[,] VerticalC;
	 
	
	//enumerator for Line
	IEnumerator startEnumerator, endEnumerator;

	//enumerator for word
	IEnumerator wordStartEnumerator,wordEndEnumerator;

	//enumerator for char
	//IEnumerator *charStartEnumerator,*charEndEnumerator;

	startEnumerator=start.GetEnumerator();
	endEnumerator=end.GetEnumerator();
	
	VerticalC=new int[ySize,xSize];
	//this.Lines=new Line[this.numberOfLines];

	int verticalCount=0;
	
	while(startEnumerator.MoveNext() && endEnumerator.MoveNext())
	{
		int y1=(int) (startEnumerator.Current);
		int y2=(int) (endEnumerator.Current);

		//VerticalC[ySize,xSize]=new int();
	
		for(int i=0;i<this.xSize;i++)
			{
				int count=0;
				
				for(int j=y1;j<=y2;j++)
					{
						if(BinaryArray[j,i]==false)
							{
							count++;
							}
					}
				VerticalC[verticalCount,i]=count;
			}

		verticalCount++;
	}


	startEnumerator=start.GetEnumerator();
	endEnumerator=end.GetEnumerator();

	int totalNoOfWord=0;
	int lineCount=0;
	while(startEnumerator.MoveNext() && endEnumerator.MoveNext())
	{
		int y1=(int) (startEnumerator.Current);
		int y2=(int) (endEnumerator.Current);
		
		wordStartEnumerator=wStart.GetEnumerator();
		wordEndEnumerator=wEnd.GetEnumerator();

		 
		int wordCount=0;
			
			while(wordStartEnumerator.MoveNext() && wordEndEnumerator.MoveNext())
				{
					int x1 = (int)(wordStartEnumerator.Current);
					int x2 = (int)(wordEndEnumerator.Current);
					
				 
					bool hasCharStarted=false;

					int charCount=0;

						for(int j=x1;j<=x2;j++)
							{
								if(hasCharStarted==false)
									{
										if(VerticalC[lineCount,j]>0)
											{
												charCount++;
												//charStart[lineCount,wordCount].Add(__box(j));
												hasCharStarted=true;
											}
									}
								else
									{
										if(VerticalC[lineCount,j]<=0)
											{
												//charEnd[lineCount,wordCount].Add(__box(j));
												hasCharStarted=false;
											}
									}
									
									//there are 'charCount' number of characters at 'wordCount' th word of line number 'lineCount'

							}
 

					wordCount++;
					totalNoOfWord++;
				}

		lineCount++;
	}

	int[,] allInOne=new int[totalNoOfWord,1000];

	
	startEnumerator=start.GetEnumerator();
	endEnumerator=end.GetEnumerator();

	int arrayCount=0;

	lineCount=0;
	while(startEnumerator.MoveNext() && endEnumerator.MoveNext())
	{
		int y1=(int) (startEnumerator.Current);
		int y2=(int) (endEnumerator.Current);
		
		wordStartEnumerator=wStart.GetEnumerator();
		wordEndEnumerator=wEnd.GetEnumerator();
 
		int wordCount=0;
			
			while(wordStartEnumerator.MoveNext() && wordEndEnumerator.MoveNext())
				{
					int x1 = (int)(wordStartEnumerator.Current);
					int x2 = (int)(wordEndEnumerator.Current);
					
				 
					bool hasCharStarted=false;

					int charCount=0;

						for(int j=x1;j<=x2;j++)
							{
								if(hasCharStarted==false)
									{
										if(VerticalC[lineCount,j]>0)
											{
												//totalNoOfChar++;
												charCount++;
												//charStart[lineCount,wordCount].Add(__box(j));
												hasCharStarted=true;
											}
									}
								else
									{
										if(VerticalC[lineCount,j]<=0)
											{
												//charEnd[lineCount,wordCount].Add(__box(j));
												hasCharStarted=false;
											}
									}
									
									//there are 'charCount' number of characters at 'wordCount' th word of line number 'lineCount'

							}

							allInOne[arrayCount,3]=new int();

							allInOne[arrayCount,0]=lineCount;
							allInOne[arrayCount,1]=wordCount;
							allInOne[arrayCount,2]=charCount;

							arrayCount++;
							
 

					wordCount++;
				}

		lineCount++;
	}


	//Start Of the creation of the data structure
	startEnumerator=start.GetEnumerator();
	endEnumerator=end.GetEnumerator();

	this.Lines=new Line[this.numberOfLines];

	lineCount=0;
	while(startEnumerator.MoveNext() && endEnumerator.MoveNext())
	{
		int y1=(int) (startEnumerator.Current);
		int y2=(int) (endEnumerator.Current);

        if (this.Lines[lineCount]==null) this.Lines[lineCount] = new Line();
		this.Lines[lineCount].set(y1,y2);

		wordStartEnumerator=wStart.GetEnumerator();
		wordEndEnumerator=wEnd.GetEnumerator();
 
		
					int wordCountInLine=0;
					
					for(int i=0;i<totalNoOfWord;i++)
					{
						if(allInOne[i,0]==lineCount)
						{
							wordCountInLine++;
						}
						else if(allInOne[i,0]>lineCount)
						{
							break;
						}
					}

					this.Lines[lineCount].setWord(wordCountInLine);

			int wordCount=0;

			while(wordStartEnumerator.MoveNext() && wordEndEnumerator.MoveNext())
				{
					int x1 = (int)(wordStartEnumerator.Current);
					int x2 = (int)(wordEndEnumerator.Current);

                    if (this.Lines[lineCount].Words[wordCount]==null)
                        this.Lines[lineCount].Words[wordCount] = new Word();
					this.Lines[lineCount].Words[wordCount].set(x1,x2);

					int charCountInWord=0;
					for(int i=0;i<totalNoOfWord;i++)
					{
						if(allInOne[i,0]==lineCount && allInOne[i,1]==wordCount)
						{
							charCountInWord=allInOne[i,2];
							break;
						}
					}

					this.Lines[lineCount].Words[wordCount].setUnit(charCountInWord);

				 
					bool hasCharStarted=false;

					int charCount=0;

					int x11 = 0,x22 = 0;

						for(int j=x1;j<=x2;j++)
							{
								
								if(hasCharStarted==false)
									{
										if(VerticalC[lineCount,j]>0)
											{
												//charStart[lineCount,wordCount].Add(__box(j));
												x11=j;
												hasCharStarted=true;
											}
									}
								else
									{
										if(VerticalC[lineCount,j]<=0)
											{
												//charEnd[lineCount,wordCount].Add(__box(j));
												x22=j;
												if(this.Lines[lineCount].Words[wordCount].Units[charCount] ==null)
                                                    this.Lines[lineCount].Words[wordCount].Units[charCount] = new Unit();
												this.Lines[lineCount].Words[wordCount].Units[charCount].set(x11,x22);
												charCount++;
												
												hasCharStarted=false;
											}
									}
									
									
							}

							
					wordCount++;
				}

		lineCount++;
	}
 



	
	
}
//returns number of lines from the class Separate
internal int getNumberOfLines()
{
	return this.numberOfLines;
}

//returns Lines from this class
internal Line[] getLines()
{
	return this.Lines;
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