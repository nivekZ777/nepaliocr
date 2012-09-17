#include "StdAfx.h"
#include "Resegment.h"

Resegment::Resegment(Bitmap* im,bool BinaryDone,bool ImageLoaded,bool SeparateDone, bool **BinArray,int numberOfLines, Line *Lines)
{
	this->img=im;
	this->BinaryDone=BinaryDone;
	this->ImageLoaded=ImageLoaded;
	this->SeparateDone=SeparateDone;
	this->BinArray=BinArray;
	this->numberOfLines=numberOfLines;
	this->Lines=Lines;
}

void Resegment::TotalUnitCount()
{
	this->totalunits=0;
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
				if((x2-x1+1)>2)			// Avoiding the "Aakar"
				{
					this->totalunits++;
				}
			}
		}
	}
}

void Resegment::WidthStore()
{
	this->TotalUnitCount();
	this->WStore=new int[this->totalunits];
	int count=0;
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
				int wth=x2-x1+1;
			
				if(wth>2)
				{
					this->WStore[count]=wth;
					count++;
				}
			}
		}
	}
}

int Resegment::ThresholdSize()
{
	this->sortWidth();
	int sz;
	sz=(this->totalunits+1)/2;
	int val;
	val= this->WStore[sz];
	val=3*val/2 +1;
	return val;

}

void Resegment::Crop_Image(int lineno,int wordno,int charno)
{
	int x1,x2,y1,y2;

	x1=this->Lines[lineno].Words[wordno].Units[charno].getStartColumn(); //Equivalent to :: left_x
	x2=this->Lines[lineno].Words[wordno].Units[charno].getEndColumn();	//Equivalent to :: right_x
	y1=this->Lines[lineno].getStartRow();		//Equivalent to :: top_y
	y2=this->Lines[lineno].getEndRow();			 //Equivalent to :: bottom_y
			
	int xsize=x2-x1+1;
	int ysize=y2-y1+1;

	int val=this->ThresholdSize();
	//	System::Windows::Forms::MessageBox::Show(val.ToString(),"Threshold Size");
	this->cropImage=new Bitmap(xsize,ysize,Imaging::PixelFormat::Format24bppRgb);

	for(int i=y1;i<=y2;i++)//traverse throughy
	{
		for(int j=x1;j<=x2;j++)//traverse through x
		{
			if(this->BinArray[i][j])
			{
				this->cropImage->SetPixel(j-x1,i-y1,Color::White);
			}
			else
			{
				this->cropImage->SetPixel(j-x1,i-y1,Color::Black);
			}
		}
	}
}

int Resegment::MultiFactorialAnalysis()
{
	int i,j;
	
	ThresholedValue* ts = new ThresholedValue(this->cropImage);
	float fLevel;
	fLevel= ts->GetThresholed();
	int levl;
	levl = int(fLevel*255);
	rgbConvert* rgbC = new rgbConvert(this->cropImage);
	
	int **BArray;
	int height;
	bool **tempArray;
	tempArray=rgbC->GetBinaryArray(levl);
	BArray= rgbC->GetImageArray();
	
	
	bool flag=false;
	int width;
	width=this->cropImage->Width;
	int *top;
	int *bottom;
	int down,up;
	int count=0;
	bool temp,temp1;
	float *Fic,*Fmt,*Fdm,*Fdmc,*Summation;;

    top=new int[width];
	bottom=new int[width];
	Fic=new float[width];
	Fmt=new float[width];
	Summation=new float[width];
	Fdm=new float[width];
	Fdmc=new float[width];
	for(i=0;i<=this->cropImage->Width-1;i++)
	{
		flag=false;
		top[i]=0;
		bottom[i]=0;
		Fic[i]=0;
		Fmt[i]=0;
		Summation[i]=0;
		Fdm[i]=0;
		Fdmc[i]=0;
		for(j=0;j<=this->cropImage->Height-1;j++)
		{
			if(BArray[j][i]==0)
			{
				if(flag==false)
				{
					top[i]=j;
					//	System::Windows::Forms::MessageBox::Show(top[i].ToString(),"Top Value");
					flag=true;
				}
				else
				{
					bottom[i]=j;
				}
			}
		}
	}
	
	up=minimum(top,width);
	down=maximum(bottom,width);
	height=down-up;
/*	
	this->richTextBox1->AppendText("up:");
	this->richTextBox1->AppendText(up.ToString());
	this->richTextBox1->AppendText("down:");
	this->richTextBox1->AppendText(down.ToString());
	this->richTextBox1->AppendText("Height:");
	this->richTextBox1->AppendText(height.ToString());
	//System::Windows::Forms::MessageBox::Show(up.ToString(),"Up");
	//System::Windows::Forms::MessageBox::Show(down.ToString(),"Down");
	//System::Windows::Forms::MessageBox::Show(height.ToString(),"Height");
*/
	for(j=0;j<width;j++)
	{
        count=0;
		for(i=0;i<height;i++)
		{
			temp=tempArray[i][j];
			temp1=tempArray[i+1][j];
			if(temp!=temp1)
			{
				count++;
			}
		}
		if(count!=0)
		{
			Fic[j]=(float)1/(float)count;
		}
		else
		{
            Fic[j]=-1;
		}
	}
	
	float inccount;
	
	for(i=0;i<width;i++)
	{
		inccount=0;
		for(j=0;j<height;j++)
		{
			if(BArray[j][i]==0)
			{
				inccount++;
			}
		}
		//System::Windows::Forms::MessageBox::Show(inccount.ToString(),"blob size");
		//	System::Windows::Forms::MessageBox::Show(height.ToString(),"Bigger T");
		Fmt[i]=1-inccount/(float)height;
	}
	
	float mid=(float)width/2;

	for(i=0;i<width;i++)
	{
		int l1=top[i]-up;
		int l2=down-bottom[i];
		int mn,mx;
		if(l1>=l2)
		{
			mn=l2;
			mx=l1;
		}
		else
		{
			mn=l1;
			mx=l2;
		}
		if(mx==0)
		{
			Fdm[i]=-10;
		}	
		else
		{
			Fdm[i]=(float)mn/(float)mx;
		}
		int ll1=i;
		int ll2=width-i-1;
		int mmn,mmx;
		if(ll1>=ll2)
		{
			mmn=ll2;
			mmx=ll1;
		}
		else
		{
			mmn=ll1;
			mmx=ll2;
		}
		if(mmx==0)
		{
			Fdmc[i]=-10;
		}
		else
		{
			Fdmc[i]=(float)mmn/(float)mmx;
		}
	}

	for(i=0;i<width;i++)
	{
		float sum=0.0;
		sum=Fic[i]+Fmt[i]+Fdm[i]+Fdmc[i];
	//	System::Windows::Forms::MessageBox::Show(sum.ToString(),"Sum");
		Summation[i]=sum/4;
	}
		
	int cutcolumn=maximum(Summation,width);
	return cutcolumn;
}


int Resegment::minimum(int *num,int width)
{
	int mini=num[0];
	for (int i=1;i<=width-1;i++)
	{
		//System::Windows::Forms::MessageBox::Show(mini.ToString(),"Mini Value");
		//System::Windows::Forms::MessageBox::Show(num[i].ToString(),"Num Value");
		if(mini>=num[i] && num[i]>=0)
		{
			mini=num[i];
			//System::Windows::Forms::MessageBox::Show(mini.ToString(),"Mini Value");
		}
	}
	return mini;
}

int Resegment::maximum(float *num,int width)
{
	float maxi=num[0];
	int maxcol;
	for (int i=1;i<width;i++)
	{
		//System::Windows::Forms::MessageBox::Show(maxi.ToString(),"Maxi");
		//System::Windows::Forms::MessageBox::Show(num[i].ToString(),"Column Value");
		if(maxi<=num[i])
		{
			maxcol=i;
			maxi=num[i];
		}
		//System::Windows::Forms::MessageBox::Show(maxcol.ToString(),"MaxCol");
	}
	return maxcol;
}

int Resegment::maximum(int *num,int width)
{
	int maxi=num[0];
	for (int i=1;i<width;i++)
	{
		if(maxi<=num[i])
		{
			maxi=num[i];
		}
	}
	return maxi;
}

void Resegment::sortWidth()
{
	int temp;
	for(int i=0;i<this->totalunits;i++)
	{
		for(int j=i+1;j<this->totalunits;j++)
		{
			if(this->WStore[i]>this->WStore[j])
			{
				temp=this->WStore[i];
				this->WStore[i]=this->WStore[j];
				this->WStore[j]=temp;
			}
		}
	}
}

void Resegment::adjustUnits(int lineno,int wordno,int charno)
{
	int x1,x2,y1,y2;

	x1=this->Lines[lineno].Words[wordno].Units[charno].getStartColumn(); //Equivalent to :: left_x
	x2=this->Lines[lineno].Words[wordno].Units[charno].getEndColumn();	//Equivalent to :: right_x
	y1=this->Lines[lineno].getStartRow();		//Equivalent to :: top_y
	y2=this->Lines[lineno].getEndRow();
	int xsize=x2-x1+1;
	int ysize=y2-y1+1;

	this->Crop_Image(lineno,wordno,charno);

	int col=this->MultiFactorialAnalysis();

	//		this->richTextBox1->AppendText(col.ToString());
	//		this->richTextBox1->AppendText("Cut column ");
	
	int units=this->Lines[lineno].Words[wordno].getTotalUnit();

	int *start,*end;

	start= new int[units+1];
	end=new int[units+1];
/*
		this->richTextBox1->AppendText("\n units  ");
		this->richTextBox1->AppendText(units.ToString());
		this->richTextBox1->AppendText("\n");
		this->richTextBox1->AppendText("\n char no  ");
		this->richTextBox1->AppendText(charno.ToString());
		this->richTextBox1->AppendText("\n");
*/	
	for(int i=0;i<units;i++)
	{
		int sc=this->Lines[lineno].Words[wordno].Units[i].getStartColumn();
	/*	this->richTextBox1->AppendText("\n Original Start  ");
		this->richTextBox1->AppendText(sc.ToString());
		this->richTextBox1->AppendText("\n");*/
	}

	for(int i=0;i<=units;i++)
	{
		int sc=this->Lines[lineno].Words[wordno].Units[i].getStartColumn();
		int ed=this->Lines[lineno].Words[wordno].Units[i].getEndColumn();
		if(i<charno)
		{
			start[i]=sc;
			end[i]=ed;
		}
		else if(i>(charno+1))
		{
			start[i]=this->Lines[lineno].Words[wordno].Units[i-1].getStartColumn();
			end[i]=this->Lines[lineno].Words[wordno].Units[i-1].getEndColumn();
		}
		else if(i==charno)
		{
			start[i]=sc;
			end[i]=sc+col;
		}
		else if(i==(charno+1))
		{
			start[i]=end[i-1]+1;
			end[i]=this->Lines[lineno].Words[wordno].Units[i-1].getEndColumn();;
		}
	}
			//new unit size and setting the start and end columns for each unit
	this->Lines[lineno].Words[wordno].setUnit(units+1);
	for(int i=0;i<=units;i++)
	{
		this->Lines[lineno].Words[wordno].Units[i].set(start[i],end[i]);
		//System::Windows::Forms::MessageBox::Show(start[i].ToString(),"Start column");
/*		this->richTextBox1->AppendText("\nStart ");
				this->richTextBox1->AppendText(start[i].ToString());
				this->richTextBox1->AppendText("\n");*/
     }
}
void Resegment::Do_Segmentation()
{
	if(this->ImageLoaded && this->BinaryDone)
	{
		this->WidthStore();
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
	
					int wchar=x2-x1;
					int val=this->ThresholdSize();
					
					if(val<wchar)
					{
						this->adjustUnits(i,j,k);
					}
				}
			}
		}
	}
}
