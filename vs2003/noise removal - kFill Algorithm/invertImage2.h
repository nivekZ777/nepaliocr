#pragma once
using namespace System::Drawing;

public __gc class invertImage2
{
private: 
	System::Drawing::Bitmap* sultoImage;
	System::Drawing::Bitmap* ultoImage;
	int **onetwokoarray;
	int xsize;
	int ysize;
		
	
public:

	invertImage2(System::Drawing::Bitmap* BinaryImage)
	{
		sultoImage = BinaryImage;
		xsize = sultoImage->Width;
		ysize = sultoImage->Height;
		onetwokoarray = new int * [ysize];
		for (int i = 0; i < ysize; i++ )
		{
			onetwokoarray[i] = new int[xsize];
		}

		ultoImage = new Bitmap(xsize, ysize, Imaging::PixelFormat::Format24bppRgb);

	}

			
	System::Drawing::Bitmap* GetInvertedImage()
	{
		for( int i = 0; i < this->xsize; i++ )
		{
			for ( int j = 0; j < this->ysize; j++ )
			{
				onetwokoarray[i][j]=1;
			}
		}
		
		for( int yVal = 0; yVal < ysize; yVal++ )
		{
			for ( int xVal = 0; xVal < xsize; xVal++ )
			{


				if(this->onetwokoarray[yVal][xVal] == 1)
					this->ultoImage->SetPixel(xVal,yVal,Color::Pink);
				else
					this->ultoImage->SetPixel(xVal,yVal,Color::Green);

			}
		}
		return this->ultoImage;
	}

		

};
