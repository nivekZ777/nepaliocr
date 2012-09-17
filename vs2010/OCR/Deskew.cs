/*
 * Original Code was forked from http://code.google.com/p/nepaliocr/source/browse/trunk/Deskew.cpp?spec=svn146&r=138
 */

using System;

namespace NOCR
{
    public class Deskew
    {
        //The Bitmap
        static System.Drawing.Bitmap cBmp;
        //The range of angles to search for lines
        //static double cAlphaStart= -20;
        static double cAlphaStart = -20;
        static double cAlphaStep = 0.2;
        static int cSteps = 40 * 5;
        //Precalculation of sin and cos.
        static double[] cSinA;
        static double[] cCosA;
        //Range of d
        static double cDMin;
        static double cDStep = 1;
        static int cDCount;

        //Count of points that fit in a line.
        static int[] cHMatrix;
        

//## Deskew.Deskew(Bitmap * im) ##
        public Deskew(System.Drawing.Bitmap im)
        {
            cBmp = im;
        }

//##### double Deskew.GetSkewAngle() ####
//Calculate the skew angle of the image cBmp.
public double GetSkewAngle()
{
	HoughLine[] h1;		//creating a pointer
	int i;
	h1=new HoughLine[20];	//creating new array of class HoughLine, array of size 20 
 	double sum=0;			//initializing sum
	int count=0;			//initializing count

	Calc();					//calculate
	//Hough Transformation
	
	h1=this.GetTop(20);
	//Top 20 of the detected lines in the image.

	//Average angle of the lines
	for (i = 0; i <= 19; i++) 
		{
			
			sum+=h1[i].Alpha;
			
			//if(h1[i].Alpha==-20){ System.Windows.Forms.MessageBox.Show("Alpha is 20","What happened");}
			
			count+=1;
		}
		if(sum/count==-20){
			System.Windows.Forms.MessageBox.Show("The image must be already deskewed. \n\n\nIf the image is still skewed then it might be out of the scope of the deskew algorithm used", "Image is already Deskewed");
			return 0;
		}
		else{
			return sum/count;
		}
	
}


//######### void Deskew.Calc() ###########
void Calc()
{
	int x;
	int y;
	double bMin=(cBmp.Height) / 4;
	double bMax=cBmp.Height * 3 / 4;

	int hMin=(int)bMin;
	int hMax=(int)bMax;

	//bMin = 1/4th of ImageHeight
	//bMax = 3/4th of ImageHeight
//	System.Windows.Forms.MessageBox.Show(hMin.ToString()/*fLevel.ToString()*/,"bMin");
//	System.Windows.Forms.MessageBox.Show(hMax.ToString()/*fLevel.ToString()*/,"bMax");					
	Init();

	//y runs from 1/4th of image to 3/4th of image
	for(y=hMin;y<=hMax;y++)
		{
			//x runs from 1 to (width of image-2)
			for(x=1;x<=(cBmp.Width)-2;x++)
				{
				// Only lower edges are considered.
				if (IsBlack(x, y))
				{
					if (!IsBlack(x, y + 1))
					{
						Calc(x, y);
					}
				}
			}
		}
}
//################################## Deskew . Init() ###############
void Init()
{
	//int i;
	double angle;
	// Precalculation of sin and cos.
		//  ReDimStatement
		// ReDimStatement
	cSinA=new double [cSteps-1];
	cCosA=new double [cSteps-1];


	for(int i=0;i<=cSteps-1;i++)
		{
			angle=(GetAlpha(i)) * (System.Math.PI) / 180.0;
			cSinA[i]=System.Math.Sin(angle);		//find sine angle
			cCosA[i]=System.Math.Cos(angle);		//find cosine angle
		}
	
	cDMin= -(cBmp.Width);
	double cDCount0=2*(cBmp.Width + cBmp.Height)/ cDStep;

	cDCount=(int)cDCount0;
	cHMatrix=new int [cDCount * cSteps];

	for(int i=0;i<=(cDCount*cSteps)-1;i++)
	{
		cHMatrix[i]=0;
	}
}


//##################### Deskew . GetAlpha #############
double GetAlpha(int Index)
{
	return cAlphaStart + (((double) Index) * cAlphaStep) ;
}

bool IsBlack(int x,int y)
{
	System.Drawing.Color c;
	double luminance;
	int pixel;
	int red;
	int green;
	int blue;

	System.Drawing.Color clr = cBmp.GetPixel(x,y);
	pixel = clr.ToArgb();				

	

	red = (pixel >> 16) & 0xff;
	green = (pixel >>  8) & 0xff;
	blue = (pixel      ) & 0xff;
	
	luminance = (0.299 * red) + (0.587 * green) + (0.114 * blue);
	return luminance < 140;
}


//################# Deskew . Calc(int x, int y) ##################
// Calculate all lines through the point (x,y).
void Calc(int x,int y)		//parameters image pixels(x, and y) coordinates
{
	int alpha;
	double d;
    double dIndex;
    int Index;			
	



	for(alpha=0;alpha<=cSteps-1;alpha++)
	{
		
		d=(y * cCosA[alpha])- (x * cSinA[alpha]); //x Cos(alpha) + y Sin(alpha) = P
												  //P = x Cos(alpha) + y Sin(alpha)
												  //this turns out to be :
													// d = y Cos(alpha) + x Sin(alpha)
													// d = y cCos(alpha) - x cSin(alpha)
		dIndex=CalcDIndex(d);
		Index= Convert.ToInt32(dIndex*cSteps)+alpha;
		
		cHMatrix[Index]+=1;
		

	}

}

//########### double Deskew.CalcDIndex(double d) #######
double CalcDIndex(double d)
{
	return System.Convert.ToInt32(d - cDMin);
}

//######## HoughLine* Deskew.GetTop(int count)[] ###
//Calculate the Count lines in the image with most points.
HoughLine[] GetTop(int count)
{
	HoughLine[] h1=new HoughLine[20]; //declaration 
	int integerI;
	int integerJ;
	HoughLine tmp;				//temporary houghline datatype
	int AlphaIndex;				//temp 
	int dIndex;					//temp 
			
	// ERROR: Not supported in C#: ReDimStatement
	// .. Some vb codes are left unimplemented here August 18, 2007 ....: 

    for (integerI = 0; integerI <= (count - 1); integerI++)   //initialize the value of houghline, initially to zero 
	{							//Continue until it increases upto count
        h1[integerI] = new HoughLine();
	}


    for (integerI = 0; integerI < count; integerI++)
	{
        h1[integerI].Count = 0;			//initialize each components of houghline to zero
        h1[integerI].Index = 0;			//initialize
        h1[integerI].Alpha = 0;			//initialiae
        h1[integerI].d = 0;				//initialiae
	}

				//temp
	
	int hlLength=(int)cDCount*cSteps;
	
	for(int i=0;i<=hlLength-1;i++)
		{
					
			if(cHMatrix[i]>(h1[count-1].Count))
				{
					h1[count-1].Count=cHMatrix[i];
                	h1[count-1].Index=i;
					integerJ=count-1;
                    while (integerJ > 0 && (h1[integerJ].Count > h1[integerJ - 1].Count))
						{
                            tmp = h1[integerJ];
                            h1[integerJ] = h1[integerJ - 1];
                            h1[integerJ - 1] = tmp;
                            integerJ -= 1;  // means j--;
						}
				}
		}

	
	//StreamWriter *sw=new StreamWriter("trial.txt");

	for(int i=0;i<=count-1;i++)
		{
			dIndex=(h1[i].Index) / cSteps;
			AlphaIndex=h1[i].Index - dIndex * cSteps;
			h1[i].Alpha=GetAlpha(AlphaIndex);
			h1[i].d=dIndex + cDMin;
		}
	
	

	return h1;

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