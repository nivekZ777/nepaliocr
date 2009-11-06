#include "StdAfx.h"
#include "Separate.h"

Separate::Separate(Bitmap* im,bool **B,Graphics* gr)
{
	tempoImage = im;
	this->xSize=im->Width;
	this->ySize=im->Height;
	this->BinaryArray=B;
	this->Horizontal=new int[ySize];
	this->g=gr;
	this->numberOfLines=0;

}

void Separate::LineSeparate()
{
	ArrayList* lineStart=new ArrayList();
	ArrayList* lineEnd=new ArrayList();
//	vector <int> lineStart;
//	vector <int> lineEnd;

	/////
	IEnumerator* startEnumerator;
	IEnumerator* endEnumerator;
	 

	for(int i=0;i<this->ySize;i++)
	{//traverse through Y direction in the image
		int count=0;
		for(int j=0;j<this->xSize;j++)
		{//traverse through X direction in the image
			if(this->BinaryArray[i][j]==false){
				//False = No pixel found 
				//Means Black Pixel found
				//Means Text found
				//Means start of line 
				count++;
			}
		}
		this->Horizontal[i]=count;
	}

	bool hasLineStarted=false;

	//Flag set.. 
	//Now that we know that we have found a black pixel, 
	//A line is started, and the line has not ended yet
	// If the line ends below, we will reset the flag 
	

	for(int i=0;i<this->ySize;i++)
	{
		if(hasLineStarted==false)
		{
			if(this->Horizontal[i]>0){
			//If this Horizontal[i] is greater than 0, we have already found a black pixel above.
				//now that we have found a black pixel, line is started 
				//So lets set the flag now 
				//So "Mister Flag Linestarted" = true; 
				// "Mister Flag Linestarted" is set
				// "Mister Flag Linestarted" is on
				
				lineStart->Add(__box(i));
				hasLineStarted=true;
			}
		}
		else
		{
			if(this->Horizontal[i]<=0)
			{
				 
				lineEnd->Add(__box(i-1));
				//No black pixels found above while counting pixels
				//So Horizontal[i] is less or equal to zero
				// So line has not started yet. 
				// So lets turn off the flag
				//So "Mister Flag Linestarted" = false; 
				// "Mister Flag Linestarted" is reset
				// "Mister Flag Linestarted" is off
				

				hasLineStarted=false;
			}
		}
	}

	startEnumerator =  lineStart->GetEnumerator();
	endEnumerator = lineEnd->GetEnumerator();
	
	Pen* p=new Pen(Color::Red,1);
	while (startEnumerator->MoveNext() &&  endEnumerator->MoveNext())
	{
    int s = *dynamic_cast<__box int*>(startEnumerator->Current);
    int e = *dynamic_cast<__box int*>(endEnumerator->Current);
	numberOfLines++;
	 
	}

 
	WordSeparate1(lineStart,lineEnd);
}

void Separate::WordSeparate(ArrayList* start,ArrayList* end)
{
	//System::Windows::Forms::MessageBox::Show(numberOfLines.ToString(),"Total Number Of Lines");
	
	IEnumerator *startEnumerator;
	IEnumerator *endEnumerator;

	startEnumerator=start->GetEnumerator();
	endEnumerator=end->GetEnumerator();
	
	Vertical=new int*[numberOfLines];
	
	
	int verticalCount=0;
	
	while(startEnumerator->MoveNext() && endEnumerator->MoveNext())
	{
		int y1=*dynamic_cast<__box int*> (startEnumerator->Current);
		int y2=*dynamic_cast<__box int*> (endEnumerator->Current);

		Vertical[verticalCount]=new int[xSize];
		 
		for(int i=0;i<this->xSize;i++)
			{
				int count=0;
				
				for(int j=y1;j<=y2;j++)
					{
						 if(BinaryArray[j][i]==false)
							{
							count++;
							}
					}
				this->Vertical[verticalCount][i]=count;
			}

		verticalCount++;
	}
	
	 
	int cnt=0;

	startEnumerator=start->GetEnumerator();
	endEnumerator=end->GetEnumerator();

int start_of_word=0;
int end_of_word=0;
int _sum_word_length=0;
int _number_of_words=0;
	
while(startEnumerator->MoveNext() && endEnumerator->MoveNext())
	{

	int y1=*dynamic_cast<__box int*> (startEnumerator->Current);
	int y2=*dynamic_cast<__box int*> (endEnumerator->Current);
	
	
	ArrayList* wordStart=new ArrayList();
	ArrayList* wordEnd=new ArrayList();
	IEnumerator *wordStartEnumerator,*wordEndEnumerator;
	
	bool hasWordStarted=false;

	for(int j=0;j<this->xSize;j++)
	{
		if(hasWordStarted==false)
		{
			if(Vertical[cnt][j]>0)
			{
				wordStart->Add(__box(j));
				hasWordStarted=true;
			}
		}
		else
		{
			if(Vertical[cnt][j]<=0)
			{
				wordEnd->Add(__box(j));
				hasWordStarted=false;
			}
		}

	}

	wordStartEnumerator=wordStart->GetEnumerator();
	wordEndEnumerator=wordEnd->GetEnumerator();
	
	while (wordStartEnumerator->MoveNext() &&  wordEndEnumerator->MoveNext())
		{
			int x1 = *dynamic_cast<__box int*>(wordStartEnumerator->Current);
			int x2 = *dynamic_cast<__box int*>(wordEndEnumerator->Current);
			
			start_of_word=x1;
			end_of_word=x2;
			_sum_word_length+=(end_of_word-start_of_word);
			_number_of_words++;
		
			
			 
		}
	cnt++;
	}

	int _average_word_length=(int) (_sum_word_length) / (_number_of_words);
			
	System::Windows::Forms::MessageBox::Show(_average_word_length.ToString(),"Average Word Length");

 
	 

}
void Separate::drawHorizontalHist()
{
	Pen* p=new Pen(Color::Red,1);
	
	for(int i=0;i<this->ySize;i++)
	{
		g->DrawLine(p,0,i,this->Horizontal[i],i);
	}
}


void Separate::WordSeparate1(ArrayList* start,ArrayList* end)
{
	ArrayList** wordStart=new ArrayList*();
	ArrayList** wordEnd=new ArrayList*();
	IEnumerator *wordStartEnumerator,*wordEndEnumerator;
	ArrayList** wordStart1=new ArrayList*();
	ArrayList** wordEnd1=new ArrayList*();
	//IEnumerator *wordStartEnumerator1,*wordEndEnumerator1;

	
	IEnumerator *startEnumerator;
	IEnumerator *endEnumerator;

	int start_of_word2=0;
	int end_of_word1=0;
	int _sum_word_gap=0;
	int _number_of_gaps=0;


	startEnumerator=start->GetEnumerator();
	endEnumerator=end->GetEnumerator();
	
	Vertical=new int*[numberOfLines];
	
	
	int verticalCount=0;
	
	while(startEnumerator->MoveNext() && endEnumerator->MoveNext())
	{
		int y1=*dynamic_cast<__box int*> (startEnumerator->Current);
		int y2=*dynamic_cast<__box int*> (endEnumerator->Current);

		Vertical[verticalCount]=new int[xSize];
	
		for(int i=0;i<this->xSize;i++)
			{
				int count=0;
				
				for(int j=y1;j<=y2;j++)
					{
						if(BinaryArray[j][i]==false)
							{
							count++;
							}
					}
				this->Vertical[verticalCount][i]=count;
			}

		verticalCount++;
	}


	
	//Pen* p=new Pen(Color::Red,1);
	
	int cnt=0;

	startEnumerator=start->GetEnumerator();
	endEnumerator=end->GetEnumerator();
	
while(startEnumerator->MoveNext() && endEnumerator->MoveNext())
	{

	int y1=*dynamic_cast<__box int*> (startEnumerator->Current);
	int y2=*dynamic_cast<__box int*> (endEnumerator->Current);
	wordStart[cnt]=new ArrayList();
	wordEnd[cnt]=new ArrayList();

	
	
	bool hasWordStarted=false;

	for(int j=0;j<this->xSize;j++)
	{
		if(hasWordStarted==false)
		{
			if(Vertical[cnt][j]>0)
			{
				wordStart[cnt]->Add(__box(j));
				hasWordStarted=true;
			}
		}
		else
		{
			if(Vertical[cnt][j]<=0)
			{
				wordEnd[cnt]->Add(__box(j));
				hasWordStarted=false;
			}
		}

	}

	wordStartEnumerator=wordStart[cnt]->GetEnumerator();
	wordEndEnumerator=wordEnd[cnt]->GetEnumerator();
	int no_of_word=0;
	while (wordStartEnumerator->MoveNext() &&  wordEndEnumerator->MoveNext())
		{
			
			int x1 = *dynamic_cast<__box int*>(wordStartEnumerator->Current);
			int x2 = *dynamic_cast<__box int*>(wordEndEnumerator->Current);
			
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
		System::Windows::Forms::MessageBox::Show("It seems that gaps between words is invalid \n Please reload a proper image ....","invalid image width");
		
	}
	int _average_word_gaps=(int)(_sum_word_gap)/(_number_of_gaps);		
	//System::Windows::Forms::MessageBox::Show(_average_word_gaps.ToString(),"Average Word Gaps");






	

	
	cnt=0;
	
	startEnumerator=start->GetEnumerator();
	endEnumerator=end->GetEnumerator();
	
	while(startEnumerator->MoveNext() && endEnumerator->MoveNext())
	{
		int y1=*dynamic_cast<__box int*> (startEnumerator->Current);
		int y2=*dynamic_cast<__box int*> (endEnumerator->Current);
	
		wordStartEnumerator=wordStart[cnt]->GetEnumerator();
		wordEndEnumerator=wordEnd[cnt]->GetEnumerator();
		int word_count=0;
		int newx1,newx2,tempx2;

		wordStart1[cnt]=new ArrayList();
		wordEnd1[cnt]=new ArrayList();

		
		while (wordStartEnumerator->MoveNext() &&  wordEndEnumerator->MoveNext())
		{
		int x1 = *dynamic_cast<__box int*>(wordStartEnumerator->Current);
		int x2 = *dynamic_cast<__box int*>(wordEndEnumerator->Current);
		
		
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
				 

				wordStart1[cnt]->Add(__box(newx1));
				wordEnd1[cnt]->Add(__box(newx2));

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
		 
		wordStart1[cnt]->Add(__box(newx1));
		wordEnd1[cnt]->Add(__box(newx2));


		cnt++;
	}

 
		
CheckMattra(start,end,wordStart1,wordEnd1);
	
}



void Separate::CheckMattra(ArrayList* lineStart,ArrayList* lineEnd,ArrayList** wordStart,ArrayList** wordEnd)
{
	 
	System::Drawing::Graphics* imageCopy;
	imageCopy = Graphics::FromImage(tempoImage);
	
	IEnumerator *lineStartEnumerator,*lineEndEnumerator;
	//IEnumerator *wordStartEnumerator,*wordEndEnumerator;

	lineStartEnumerator=lineStart->GetEnumerator();
	lineEndEnumerator=lineEnd->GetEnumerator();

	Pen* p=new Pen(Color::White,1);
  
	//int cnt=0;
	//drawHorizontalHist();

	while(lineStartEnumerator->MoveNext() && lineEndEnumerator->MoveNext())
	{
		int y1=*dynamic_cast<__box int*> (lineStartEnumerator->Current);
		int y2=*dynamic_cast<__box int*> (lineEndEnumerator->Current);
		int max=0;
		int maxIndex;
		int *mIndex=new int[100];
		int cntMattra=0;
		for(int i=y1;i<=y2;i++)
		{
			if(Horizontal[i]>max)
			{
				max=Horizontal[i]; //Maximum  number of pixels in row of a line to check for headline
				maxIndex=i;			// Index for the start of the headline
			}
		}

		for(i=y1;i<=y2;i++)
		{
			if((double)Horizontal[i] >= (double)Horizontal[maxIndex]*(0.9))
			{
				//max=Horizontal[i];
				mIndex[cntMattra]=i;
				cntMattra++;
			}
		}

	//g->DrawLine(p,0,maxIndex,this->xSize,maxIndex);
		for(int j=0;j<this->xSize;j++)
		{
			for(int k=0;k<cntMattra;k++)
			{
				this->BinaryArray[mIndex[k]][j]=true;
				g->DrawLine(p,0,mIndex[k],this->xSize,mIndex[k]);
				imageCopy->DrawLine(p,0,mIndex[k],this->xSize,mIndex[k]);
			}
		}
	/*
		bool fflag=false;
		int r1;
		for(int j=y1;j<=maxIndex;j++)
		{
			for(int k=0;k<this->xSize;k++)
			{
				if(!this->BinaryArray[j][k])
				{
					fflag=true;
					r1=j;
					break;
				}
			}
			if (fflag)
			{
				break;
			}
		}*/
		//Removing top Modifier
		for(int k=0;k<this->xSize;k++)
		{
			for(int j=y1;j<=maxIndex;j++)
			{
				this->BinaryArray[j][k]=true;
			}
		}
		
		for(int j=y1;j<=maxIndex;j++)
		{
			g->DrawLine(p,0,j,this->xSize,j);
			imageCopy->DrawLine(p,0,j,this->xSize,j);
		}
		
		
		/*
		int temp=maxIndex-r1;
		System::Windows::Forms::MessageBox::Show(temp.ToString(),"Temp");
		int r2=y2-temp;
		System::Windows::Forms::MessageBox::Show(r2.ToString(),"R2");
			
		for(int k=0;k<this->xSize;k++)
		{
			for(int j=r2;j<=y2;j++)
			{
				this->BinaryArray[j][k]=true;
			}
		}
		
		for(int j=r2;j<=y2;j++)
		{
			g->DrawLine(p,0,j,this->xSize,j);
			imageCopy->DrawLine(p,0,j,this->xSize,j);
		}*/


	}
	this->CharSeparate(lineStart,lineEnd,wordStart,wordEnd);
	imageCopy->Dispose();
	tempoImage->Save("C:\\test.jpg");
	tempoImage->Dispose();
	output=Image::FromFile("C:\\test.jpg");
	
	
}



void Separate::CharSeparate(ArrayList* start,ArrayList* end,ArrayList** wStart,ArrayList** wEnd)
{
 
	

	int** VerticalC;
	 
	
	//enumerator for Line
	IEnumerator *startEnumerator, *endEnumerator;

	//enumerator for word
	IEnumerator *wordStartEnumerator,*wordEndEnumerator;

	//enumerator for char
	//IEnumerator *charStartEnumerator,*charEndEnumerator;

	startEnumerator=start->GetEnumerator();
	endEnumerator=end->GetEnumerator();
	
	VerticalC=new int*[numberOfLines];
	//this->Lines=new Line[this->numberOfLines];

	int verticalCount=0;
	
	while(startEnumerator->MoveNext() && endEnumerator->MoveNext())
	{
		int y1=*dynamic_cast<__box int*> (startEnumerator->Current);
		int y2=*dynamic_cast<__box int*> (endEnumerator->Current);

		VerticalC[verticalCount]=new int[xSize];
	
		for(int i=0;i<this->xSize;i++)
			{
				int count=0;
				
				for(int j=y1;j<=y2;j++)
					{
						if(BinaryArray[j][i]==false)
							{
							count++;
							}
					}
				VerticalC[verticalCount][i]=count;
				//System::Windows::Forms::MessageBox::Show(count.ToString(),"Vertical Count");
			}

		verticalCount++;
	}


	startEnumerator=start->GetEnumerator();
	endEnumerator=end->GetEnumerator();

	int totalNoOfWord=0;
	int lineCount=0;
	while(startEnumerator->MoveNext() && endEnumerator->MoveNext())
	{
		int y1=*dynamic_cast<__box int*> (startEnumerator->Current);
		int y2=*dynamic_cast<__box int*> (endEnumerator->Current);
		
		wordStartEnumerator=wStart[lineCount]->GetEnumerator();
		wordEndEnumerator=wEnd[lineCount]->GetEnumerator();

		 
		int wordCount=0;
			
			while(wordStartEnumerator->MoveNext() && wordEndEnumerator->MoveNext())
				{
					int x1 = *dynamic_cast<__box int*>(wordStartEnumerator->Current);
					int x2 = *dynamic_cast<__box int*>(wordEndEnumerator->Current);
					
				 
					bool hasCharStarted=false;

					int charCount=0;

						for(int j=x1;j<=x2;j++)
							{
								if(hasCharStarted==false)
									{
										if(VerticalC[lineCount][j]>0)
											{
												charCount++;
												//charStart[lineCount][wordCount]->Add(__box(j));
												hasCharStarted=true;
											}
									}
								else
									{
										if(VerticalC[lineCount][j]<=0)
											{
												//charEnd[lineCount][wordCount]->Add(__box(j));
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

	int **allInOne=new int*[totalNoOfWord];

	
	startEnumerator=start->GetEnumerator();
	endEnumerator=end->GetEnumerator();

	int arrayCount=0;

	lineCount=0;
	while(startEnumerator->MoveNext() && endEnumerator->MoveNext())
	{
		int y1=*dynamic_cast<__box int*> (startEnumerator->Current);
		int y2=*dynamic_cast<__box int*> (endEnumerator->Current);
		
		wordStartEnumerator=wStart[lineCount]->GetEnumerator();
		wordEndEnumerator=wEnd[lineCount]->GetEnumerator();
 
		int wordCount=0;
			
			while(wordStartEnumerator->MoveNext() && wordEndEnumerator->MoveNext())
				{
					int x1 = *dynamic_cast<__box int*>(wordStartEnumerator->Current);
					int x2 = *dynamic_cast<__box int*>(wordEndEnumerator->Current);
					
				 
					bool hasCharStarted=false;

					int charCount=0;

						for(int j=x1;j<=x2;j++)
							{
								if(hasCharStarted==false)
									{
										if(VerticalC[lineCount][j]>0)
											{
												//totalNoOfChar++;
												charCount++;
												//charStart[lineCount][wordCount]->Add(__box(j));
												hasCharStarted=true;
											}
									}
								else
									{
										if(VerticalC[lineCount][j]<=0)
											{
												//charEnd[lineCount][wordCount]->Add(__box(j));
												hasCharStarted=false;
											}
									}
									
									//there are 'charCount' number of characters at 'wordCount' th word of line number 'lineCount'

							}

							allInOne[arrayCount]=new int[3];

							allInOne[arrayCount][0]=lineCount;
							allInOne[arrayCount][1]=wordCount;
							allInOne[arrayCount][2]=charCount;

							arrayCount++;
							
 

					wordCount++;
				}

		lineCount++;
	}


	//Start Of the creation of the data structure
	startEnumerator=start->GetEnumerator();
	endEnumerator=end->GetEnumerator();

	this->Lines=new Line[this->numberOfLines];

	lineCount=0;
	while(startEnumerator->MoveNext() && endEnumerator->MoveNext())
	{
		int y1=*dynamic_cast<__box int*> (startEnumerator->Current);
		int y2=*dynamic_cast<__box int*> (endEnumerator->Current);
		
		this->Lines[lineCount].set(y1,y2);

		wordStartEnumerator=wStart[lineCount]->GetEnumerator();
		wordEndEnumerator=wEnd[lineCount]->GetEnumerator();
 
		
					int wordCountInLine=0;
					
					for(int i=0;i<totalNoOfWord;i++)
					{
						if(allInOne[i][0]==lineCount)
						{
							wordCountInLine++;
						}
						else if(allInOne[i][0]>lineCount)
						{
							break;
						}
					}

					this->Lines[lineCount].setWord(wordCountInLine);

			int wordCount=0;

			while(wordStartEnumerator->MoveNext() && wordEndEnumerator->MoveNext())
				{
					int x1 = *dynamic_cast<__box int*>(wordStartEnumerator->Current);
					int x2 = *dynamic_cast<__box int*>(wordEndEnumerator->Current);
					
					this->Lines[lineCount].Words[wordCount].set(x1,x2);

					int charCountInWord=0;
					for(int i=0;i<totalNoOfWord;i++)
					{
						if(allInOne[i][0]==lineCount && allInOne[i][1]==wordCount)
						{
							charCountInWord=allInOne[i][2];
							break;
						}
					}

					this->Lines[lineCount].Words[wordCount].setUnit(charCountInWord);

				 
					bool hasCharStarted=false;

					int charCount=0;

					int x11,x22;

						for(int j=x1;j<=x2;j++)
							{
								
								if(hasCharStarted==false)
									{
										if(VerticalC[lineCount][j]>0)
											{
												//charStart[lineCount][wordCount]->Add(__box(j));
												x11=j;
												hasCharStarted=true;
											}
									}
								else
									{
										if(VerticalC[lineCount][j]<=0)
											{
												//charEnd[lineCount][wordCount]->Add(__box(j));
												x22=j;
												
												this->Lines[lineCount].Words[wordCount].Units[charCount].set(x11,x22);
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

int Separate::getNumberOfLines()
{
	return this->numberOfLines;
}

Line* Separate::getLines()
{
	return this->Lines;
}




	