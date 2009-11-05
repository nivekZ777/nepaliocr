#include "HoughLine.h"
#pragma once

using namespace System::Collections;
using namespace System;
using namespace System::IO;

public __gc class Deskew
{
	
public:
	static Bitmap* cBmp;
	static double cAlphaStart= -20;
	static double cAlphaStep= 0.2;
	static int cSteps= 40 * 5;
	static double *cSinA;
	static double *cCosA;
	static double cDMin;
	static double cDStep= 1;
	static int cDCount;
	static int *cHMatrix;


	Deskew(Bitmap* im);
	double GetSkewAngle();
	void Calc();
	void Init();
	double GetAlpha(int Index);
	bool IsBlack(int x,int y);
	void Calc(int x,int y);
	double CalcDIndex(double d);
	HoughLine* GetTop(int count)[];

};

Deskew::Deskew(Bitmap* im)
{
	cBmp=im;
}
double Deskew::GetSkewAngle()
{
	HoughLine *h1[];
	h1=new HoughLine* [20];

	double sum=0;
	int count=0;
	Calc();
	h1=this->GetTop(20);
	for(int i=0;i<20;i++)
		{
			sum+=h1[i]->Alpha;
			count+=1;
		}
	return sum/count;
}

void Deskew::Calc()
{
	double bMin=(cBmp->Height) / 4;
	double bMax=cBmp->Height * 3 / 4;

	int hMin=(int)bMin;
	int hMax=(int)bMax;
	System::Windows::Forms::MessageBox::Show(hMin.ToString()/*fLevel.ToString()*/,"bMin");
	System::Windows::Forms::MessageBox::Show(hMax.ToString()/*fLevel.ToString()*/,"bMax");					

	Init();

	for(int y=hMin;y<=hMax;y++)
		{
			for(int x=1;x<=(cBmp->Width)-2;x++)
				{
					if(IsBlack(x,y))
						{
							if(IsBlack(x,y+1))
								{
									//this->Calc(x,y);
								}
							else
							{
								Calc(x,y);
							}
						}
				}
		}
}

void Deskew::Init()
{
	double angle;
	cSinA=new double [cSteps-1];
	cCosA=new double [cSteps-1];


	for(int i=0;i<=cSteps-1;i++)
		{
			angle=(GetAlpha(i)) * (System::Math::PI) / 180;
			cSinA[i]=System::Math::Sin(angle);
			cCosA[i]=System::Math::Cos(angle);
		}
	
	cDMin= -(cBmp->Width);
	double cDCount0=2*(cBmp->Width + cBmp->Height)/ cDStep;
	cDCount=(int)cDCount0;
	cHMatrix=new int [cDCount * cSteps];

	for(int i=0;i<=(cDCount*cSteps)-1;i++)
	{
		cHMatrix[i]=0;
	}
}

double Deskew::GetAlpha(int Index)
{
	return cAlphaStart + (((double) Index) * cAlphaStep) ;
}

bool Deskew::IsBlack(int x,int y)
{
	System::Drawing::Color clr = cBmp->GetPixel(x,y);
	int pixel = clr.ToArgb();				

	int red = (pixel >> 16) & 0xff;
	int green = (pixel >>  8) & 0xff;
	int blue = (pixel      ) & 0xff;

	double luminance = (0.299 * red) + (0.587 * green) + (0.114 * blue);
	return luminance < 140;
}

void Deskew::Calc(int x,int y)
{
	double d;
	int dIndex,Index;




	for(int alpha=0;alpha<=cSteps-1;alpha++)
	{
		d=(y * cCosA[alpha])- (x * cSinA[alpha]);
		dIndex=CalcDIndex(d);
		Index=(dIndex*cSteps)+alpha;
		cHMatrix[Index]+=1;
	}

}

double Deskew::CalcDIndex(double d)
{
	return System::Convert::ToInt32(d - cDMin);
}

HoughLine* Deskew::GetTop(int count)[]
{
	HoughLine* h1[]=new HoughLine*[20];
	for(int i=0;i<count;i++)
	{
		h1[i]=new HoughLine();
	}
	for(int i=0;i<count;i++)
	{
		h1[i]->Count=0;
		h1[i]->Index=0;
		h1[i]->Alpha=0;
		h1[i]->d=0;
	}

	HoughLine* tmp;
	int AlphaIndex;
	int dIndex;
	int j;
	
	int hlLength=(int)cDCount*cSteps;
	
	for(int i=0;i<=hlLength-1;i++)
		{
					
			if(cHMatrix[i]>(h1[count-1]->Count))
				{
					h1[count-1]->Count=cHMatrix[i];
                	h1[count-1]->Index=i;
					j=count-1;
					while(j>0 && (h1[j]->Count > h1[j-1]->Count))
						{
							tmp=h1[j];
							h1[j]=h1[j-1];
							h1[j-1]=tmp;
							j--;
						}
				}
		}

	
	//StreamWriter *sw=new StreamWriter("trial.txt");

	for(int i=0;i<=count-1;i++)
		{
			dIndex=(h1[i]->Index) / cSteps;
	//		sw->WriteLine(dIndex);
			AlphaIndex=h1[i]->Index - dIndex * cSteps;
	//		sw->WriteLine(h1[i]->Index);
	//		sw->WriteLine(cSteps);
	//		sw->WriteLine(dIndex);
	//		sw->WriteLine(AlphaIndex);

			h1[i]->Alpha=GetAlpha(AlphaIndex);
			h1[i]->d=dIndex + cDMin;
		}
	//sw->Close();
	

	return h1;

}