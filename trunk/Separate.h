#include "Line.h"
#pragma once
//#include <vector>


using namespace System::Drawing;
using namespace System::Collections;
using namespace System;

public __gc class Separate
{
private:
	bool **BinaryArray;

	int xSize;
	int ySize;
	int *Horizontal;
	int **Vertical;
	//int **VerticalC;
	int numberOfLines;
	static int thresh_char_gap=2;

	Graphics* g;

public:
	Separate(Bitmap* im,bool **B,Graphics* gr);
	Line *Lines;
	void LineSeparate();
	void drawHorizontalHist();
	void WordSeparate(ArrayList* start,ArrayList* end);
	void WordSeparate1(ArrayList* start,ArrayList* end);
	void CheckMattra(ArrayList* start,ArrayList* end,ArrayList** wordStart,ArrayList** wordEnd);
	void CharSeparate(ArrayList* start,ArrayList* end,ArrayList** wordStart,ArrayList** wordEnd);
	int getNumberOfLines();
	Line* getLines();

};

Separate::Separate(Bitmap* im,bool **B,Graphics* gr)
{
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
	/*myEnumerator =  NumberList->GetEnumerator();
	while (myEnumerator->MoveNext())
	{
    Number = *dynamic_cast<__box Int16*>(myEnumerator->Current);
    // Do something with Number
	}
	////
	*/

	for(int i=0;i<this->ySize;i++)
	{
		int count=0;
		for(int j=0;j<this->xSize;j++)
		{
			if(this->BinaryArray[i][j]==false)
			{
				count++;
			}
		}
		this->Horizontal[i]=count;
	}

	bool hasLineStarted=false;

	for(int i=0;i<this->ySize;i++)
	{
		if(hasLineStarted==false)
		{
			if(this->Horizontal[i]>0)
			{
				//String* c=i.ToString();
				//lineStart->Add(c);
				//lineStart.push_back(i);
				lineStart->Add(__box(i));
				hasLineStarted=true;
			}
		}
		else
		{
			if(this->Horizontal[i]<=0)
			{
				//String* c=(i-1).ToString();
				//lineEnd->Add(c);
				//lineEnd.push_back(i-1);
				lineEnd->Add(__box(i-1));
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
	g->DrawLine(p,0,s,this->xSize,s);
	g->DrawLine(p,0,e,this->xSize,e);
	}

	//Vertical=new int*[numberOfLines];
	/*for(int i=0;i<lineStart.size();i++)
	{
		int str=lineStart[i];
		//String st=(String*)lineStart[i];
//		int str=st->ToInt32();
		//char *s=(char*) lineStart[i];
	}*/
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
		//System::Windows::Forms::MessageBox::Show(y1.ToString(),"Y1 Value");
		//System::Windows::Forms::MessageBox::Show(y2.ToString(),"Y2 Value");
	
		for(int i=0;i<this->xSize;i++)
			{
				int count=0;
				
				for(int j=y1;j<=y2;j++)
					{
						//System::Windows::Forms::MessageBox::Show(this->BinaryArray[i][j].ToString(),"Binary Value");
						if(BinaryArray[j][i]==false)
							{
							count++;
							}
					}
				this->Vertical[verticalCount][i]=count;
			}

		verticalCount++;
	}
	
	Pen* p=new Pen(Color::Red,1);
	
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
		
			
			g->DrawLine(p,x1,y1,x1,y2);
			g->DrawLine(p,x2,y1,x2,y2);
		}
	cnt++;
	}

	int _average_word_length=(int) (_sum_word_length) / (_number_of_words);
			
	System::Windows::Forms::MessageBox::Show(_average_word_length.ToString(),"Average Word Length");

	

	//Pen* p=new Pen(Color::Red,1);
	
	//for(int i=0;i<this->xSize;i++)
	//{
//		g->DrawLine(p,i,30,i,this->Vertical[0][i]+30);
//	}

	/*
	for(int i=0;i<numberOfLines;i++)
		{
			bool hasWordStarted=false;

			wordStart[i]=new ArrayList();
			wordEnd[i]=new ArrayList();

			for(int j=0;j<this->xSize;j++)
				{
				if(hasWordStarted==false)
					{
					if (Vertical[i][j]>0)
						{
							wordStart[i]->Add(__box(j));
							hasWordStarted=true;
						}
					}
				else
					{
					if(Vertical[i][j]<=0)
						{
							wordEnd[i]->Add(__box(j));
							hasWordStarted=false;
						}
					}
				}
		}
	Pen* p=new Pen(Color::Red,1);
			
	for(int i=0;i<numberOfLines;i++)
		{
			startEnumerator=start->GetEnumerator();
			endEnumerator=end->GetEnumerator();

			
			while(startEnumerator->MoveNext() && endEnumerator->MoveNext())
				{
					int y1=*dynamic_cast<__box int*> (startEnumerator->Current);
					int y2=*dynamic_cast<__box int*> (endEnumerator->Current);
					
					wordStartEnumerator=wordStart[i]->GetEnumerator();
					wordEndEnumerator=wordEnd[i]->GetEnumerator();

					while (wordStartEnumerator->MoveNext() &&  wordEndEnumerator->MoveNext())
						{
							int x1 = *dynamic_cast<__box int*>(wordStartEnumerator->Current);
							int x2 = *dynamic_cast<__box int*>(wordEndEnumerator->Current);
							g->DrawLine(p,x1,y1,x1,y2);
							g->DrawLine(p,x2,y1,x2,y2);
						}
				}
		}

*/

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
				//int _sum_word_gap=0;
				//int _number_of_gaps=0;
				_sum_word_gap+=(start_of_word2-end_of_word1);
				end_of_word1=x2;
				_number_of_gaps++;

				
			}
		
			//g->DrawLine(p,x1,y1,x1,y2);
			//g->DrawLine(p,x2,y1,x2,y2);
			no_of_word++;
		}
	//System::Windows::Forms::MessageBox::Show(_sum_word_gap.ToString(),"Sum of Word Gap");
	//System::Windows::Forms::MessageBox::Show(_number_of_gaps.ToString(),"Number Of Gaps");

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
				
				//draw
				
				//g->DrawLine(p,newx1,y1,newx1,y2);
				//g->DrawLine(p,newx2,y1,newx2,y2);

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
		//g->DrawLine(p,newx1,y1,newx1,y2);
		//g->DrawLine(p,newx2,y1,newx2,y2);

		//add newx1 in wordStart1
		//add newx2 in wordEnd1

		wordStart1[cnt]->Add(__box(newx1));
		wordEnd1[cnt]->Add(__box(newx2));


		cnt++;
	}

/*
	//draws Word Boundary

	startEnumerator=start->GetEnumerator();
	endEnumerator=end->GetEnumerator();
	
	cnt=0;

	Pen* p=new Pen(Color::Red,1);
	
	while(startEnumerator->MoveNext() && endEnumerator->MoveNext())
	{
		int y1=*dynamic_cast<__box int*> (startEnumerator->Current);
		int y2=*dynamic_cast<__box int*> (endEnumerator->Current);
	
		wordStartEnumerator1=wordStart1[cnt]->GetEnumerator();
		wordEndEnumerator1=wordEnd1[cnt]->GetEnumerator();
		
				
		while (wordStartEnumerator1->MoveNext() &&  wordEndEnumerator1->MoveNext())
		{
		int x1 = *dynamic_cast<__box int*>(wordStartEnumerator1->Current);
		int x2 = *dynamic_cast<__box int*>(wordEndEnumerator1->Current);
		
		g->DrawLine(p,x1,y1,x1,y2);
		g->DrawLine(p,x2,y1,x2,y2);

		}
		cnt++;
	}
*/
		
CheckMattra(start,end,wordStart1,wordEnd1);
	
}





void Separate::CheckMattra(ArrayList* lineStart,ArrayList* lineEnd,ArrayList** wordStart,ArrayList** wordEnd)
{
	//ArrayList** charStart=new ArrayList*();
	//ArrayList** charEnd=new ArrayList*();

	//IEnumerator *charStartEnumerator;
	//IEnumerator *charEndEnumerator;

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
				max=Horizontal[i];
				maxIndex=i;
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
			}
		}
		//static int i=1;

		

		
		
		/*wordStartEnumerator=wordStart[cnt]->GetEnumerator();
		wordEndEnumerator=wordEnd[cnt]->GetEnumerator();
		
		while (wordStartEnumerator->MoveNext() &&  wordEndEnumerator->MoveNext())
		{
		int x1 = *dynamic_cast<__box int*>(wordStartEnumerator->Current);
		int x2 = *dynamic_cast<__box int*>(wordEndEnumerator->Current);
		
		//g->DrawLine(p,x1,y1,x1,y2);
		//g->DrawLine(p,x2,y1,x2,y2);

		}
		cnt++;
		
*/
	
	}

	this->CharSeparate(lineStart,lineEnd,wordStart,wordEnd);
		

}



void Separate::CharSeparate(ArrayList* start,ArrayList* end,ArrayList** wStart,ArrayList** wEnd)
{
	//ArrayList*** wordStart=new ArrayList*();
	//ArrayList** wordEnd=new ArrayList*();
	//ArrayList** wordStart1=new ArrayList*();
	//ArrayList** wordEnd1=new ArrayList*();
	//IEnumerator *wordStartEnumerator1,*wordEndEnumerator1;

	

	int** VerticalC;
	//ArrayList*** charStart=new ArrayList**();
	//ArrayList*** charEnd=new ArrayList**();

	
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

		//*charStart[lineCount]=new System::Collections::ArrayList();
		//*charEnd[lineCount]=new System::Collections::ArrayList();

		int wordCount=0;
			
			while(wordStartEnumerator->MoveNext() && wordEndEnumerator->MoveNext())
				{
					int x1 = *dynamic_cast<__box int*>(wordStartEnumerator->Current);
					int x2 = *dynamic_cast<__box int*>(wordEndEnumerator->Current);
					
					//charStart[lineCount][wordCount]=new ArrayList();
					//charEnd[lineCount][wordCount]=new ArrayList();

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

							//System::Windows::Forms::MessageBox::Show(charCount.ToString(),"Number Of Characters");
							//System::Windows::Forms::MessageBox::Show(wordCount.ToString(),"In WordNo.");
							//System::Windows::Forms::MessageBox::Show(lineCount.ToString(),"Of LineNo.");


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

		//*charStart[lineCount]=new System::Collections::ArrayList();
		//*charEnd[lineCount]=new System::Collections::ArrayList();

		int wordCount=0;
			
			while(wordStartEnumerator->MoveNext() && wordEndEnumerator->MoveNext())
				{
					int x1 = *dynamic_cast<__box int*>(wordStartEnumerator->Current);
					int x2 = *dynamic_cast<__box int*>(wordEndEnumerator->Current);
					
					//charStart[lineCount][wordCount]=new ArrayList();
					//charEnd[lineCount][wordCount]=new ArrayList();

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
							

							//System::Windows::Forms::MessageBox::Show(charCount.ToString(),"Number Of Characters");
							//System::Windows::Forms::MessageBox::Show(wordCount.ToString(),"In WordNo.");
							//System::Windows::Forms::MessageBox::Show(lineCount.ToString(),"Of LineNo.");


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

		//*charStart[lineCount]=new System::Collections::ArrayList();
		//*charEnd[lineCount]=new System::Collections::ArrayList();

		
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

					
					//charStart[lineCount][wordCount]=new ArrayList();
					//charEnd[lineCount][wordCount]=new ArrayList();

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

							//System::Windows::Forms::MessageBox::Show(charCount.ToString(),"Number Of Characters");
							//System::Windows::Forms::MessageBox::Show(wordCount.ToString(),"In WordNo.");
							//System::Windows::Forms::MessageBox::Show(lineCount.ToString(),"Of LineNo.");


					wordCount++;
				}

		lineCount++;
	}
/*

Pen* p=new Pen(Color::Red,1);
	
	for(int i=0;i<this->numberOfLines;i++)
	{
		for(int j=0;j<this->Lines[i].getTotalWord();j++)
		{
			for(int k=0;k<this->Lines[i].Words[j].getTotalUnit();k++)
			{
				int x1=this->Lines[i].Words[j].Units[k].getStartColumn();
				int x2=this->Lines[i].Words[j].Units[k].getEndColumn();
				int y1=this->Lines[i].getStartRow();
				int y2=this->Lines[i].getEndRow();

					g->DrawLine(p,x1,y1,x1,y2);
					g->DrawLine(p,x2,y1,x2,y2);
			}
		}
	}

*/

/*
for(int i=0;i<10;i++)
{
	charStart[i]=new ArrayList*();
	for(int j=0;j<10;j++)
	{
		charStart[i][j]=new ArrayList();

		for(int k=0;k<10;k++)
		{
			charStart[i][j]->Add(__box(k));
	
		}
	}
}
*/

	/*
	
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
			}

		verticalCount++;
	}

	startEnumerator=start->GetEnumerator();
	endEnumerator=end->GetEnumerator();

	int lineCount=0;
	while(startEnumerator->MoveNext() && endEnumerator->MoveNext())
	{
		int y1=*dynamic_cast<__box int*> (startEnumerator->Current);
		int y2=*dynamic_cast<__box int*> (endEnumerator->Current);
		
		wordStartEnumerator=wStart[lineCount]->GetEnumerator();
		wordEndEnumerator=wEnd[lineCount]->GetEnumerator();

		*charStart[lineCount]=new System::Collections::ArrayList();
		*charEnd[lineCount]=new System::Collections::ArrayList();

		int wordCount=0;
			
			while(wordStartEnumerator->MoveNext() && wordEndEnumerator->MoveNext())
				{
					int x1 = *dynamic_cast<__box int*>(wordStartEnumerator->Current);
					int x2 = *dynamic_cast<__box int*>(wordEndEnumerator->Current);
					
					charStart[lineCount][wordCount]=new ArrayList();
					charEnd[lineCount][wordCount]=new ArrayList();

					bool hasCharStarted=false;

						for(int j=x1-1;j<=x2+1;j++)
							{
								if(hasCharStarted==false)
									{
										if(VerticalC[lineCount][j]>0)
											{
												charStart[lineCount][wordCount]->Add(__box(j));
												hasCharStarted=true;
											}
									}
								else
									{
										if(VerticalC[lineCount][j]<=0)
											{
												charEnd[lineCount][wordCount]->Add(__box(j));
												hasCharStarted=false;
											}
									}

							}
					wordCount++;
				}

		lineCount++;
	}


//draw Character Boundary;
	startEnumerator=start->GetEnumerator();
	endEnumerator=end->GetEnumerator();
	
	lineCount=0;

	Pen* p=new Pen(Color::Red,1);
	
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
				
					charStartEnumerator=charStart[lineCount][wordCount]->GetEnumerator();
					charEndEnumerator=charEnd[lineCount][wordCount]->GetEnumerator();
						while(charStartEnumerator->MoveNext() && charEndEnumerator->MoveNext())
							{
								int x11= *dynamic_cast<__box int*> (charStartEnumerator->Current);
								int x22= *dynamic_cast<__box int*> (charEndEnumerator->Current);
								
								g->DrawLine(p,x11,y1,x11,y2);
								g->DrawLine(p,x22,y1,x22,y2);

							
							}
				wordCount++;
			}
		lineCount++;
	}

	


	/*
	Pen* p=new Pen(Color::Red,1);
	
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
			if(VerticalC[cnt][j]>0)
			{
				wordStart[cnt]->Add(__box(j));
				hasWordStarted=true;
			}
		}
		else
		{
			if(VerticalC[cnt][j]<=0)
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
	
			//g->DrawLine(p,x1,y1,x1,y2);
			//g->DrawLine(p,x2,y1,x2,y2);

			if(no_of_word==0)
			{
			end_of_word1=x2;
			}
			else
			{
				start_of_word2=x1;
				//int _sum_word_gap=0;
				//int _number_of_gaps=0;
				_sum_word_gap+=(start_of_word2-end_of_word1);
				end_of_word1=x2;
				_number_of_gaps++;

				
			}
		
			//g->DrawLine(p,x1,y1,x1,y2);
			//g->DrawLine(p,x2,y1,x2,y2);
			no_of_word++;
		}
	//System::Windows::Forms::MessageBox::Show(_sum_word_gap.ToString(),"Sum of Word Gap");
	//System::Windows::Forms::MessageBox::Show(_number_of_gaps.ToString(),"Number Of Gaps");

	cnt++;
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
				if(x1-tempx2>=_average_word_gaps-thresh_char_gap)	//the word gap is ge 5
				{
				newx2=tempx2;
				
				//draw
				
				//g->DrawLine(p,newx1,y1,newx1,y2);
				//g->DrawLine(p,newx2,y1,newx2,y2);

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
		//g->DrawLine(p,newx1,y1,newx1,y2);
		//g->DrawLine(p,newx2,y1,newx2,y2);

		//add newx1 in wordStart1
		//add newx2 in wordEnd1

		wordStart1[cnt]->Add(__box(newx1));
		wordEnd1[cnt]->Add(__box(newx2));


		cnt++;
	}


	//draws Word Boundary

	startEnumerator=start->GetEnumerator();
	endEnumerator=end->GetEnumerator();
	
	cnt=0;

//	Pen* p=new Pen(Color::Red,1);
	
	while(startEnumerator->MoveNext() && endEnumerator->MoveNext())
	{
		int y1=*dynamic_cast<__box int*> (startEnumerator->Current);
		int y2=*dynamic_cast<__box int*> (endEnumerator->Current);
	
		wordStartEnumerator1=wordStart1[cnt]->GetEnumerator();
		wordEndEnumerator1=wordEnd1[cnt]->GetEnumerator();
		
				
		while (wordStartEnumerator1->MoveNext() &&  wordEndEnumerator1->MoveNext())
		{
		int x1 = *dynamic_cast<__box int*>(wordStartEnumerator1->Current);
		int x2 = *dynamic_cast<__box int*>(wordEndEnumerator1->Current);
		
		g->DrawLine(p,x1,y1,x1,y2);
		g->DrawLine(p,x2,y1,x2,y2);

		}
		cnt++;
	}
		
*/
	
}

int Separate::getNumberOfLines()
{
	return this->numberOfLines;
}

Line* Separate::getLines()
{
	return this->Lines;
}




	
	
	

	

	