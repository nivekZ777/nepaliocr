#pragma once
using namespace System::Drawing;

public __gc class invertColor
{
private: 
	System::Drawing::Bitmap* grayImage;
	System::Drawing::Bitmap* bainaryImage;
	System::Drawing::Bitmap* rgbImage;
	int xsize;
	int ysize;
	bool **BArray;
	int **GrayArray;

	static float coef01 = (float)0.2989;
	static float coef02 = (float)0.5870;
	static float coef03 = (float)0.1140;

public:

	rgbConvert(System::Drawing::Bitmap* im)
	{
		rgbImage = im;
		xsize = rgbImage->Width;
		ysize = rgbImage->Height;
		BArray = new bool * [ysize];
		GrayArray = new int * [ysize];
		for (int i = 0; i < ysize; i++ )
		{
			BArray[i] = new bool[xsize];
			GrayArray[i] = new int[xsize];
		}

		bainaryImage = new Bitmap(xsize, ysize, Imaging::PixelFormat::Format24bppRgb);
	}

	System::Drawing::Bitmap* getGrayImage ()
	{
		for( int i = 0; i < this->xsize; i++ )
		{
			for ( int j = 0; j < this->ysize; j++ )
			{
				System::Drawing::Color clr = this->rgbImage->GetPixel(i,j);
				int pixel = clr.ToArgb();				

				//int alpha = (pixel >> 24) & 0xff;// no need here
				int red = (pixel >> 16) & 0xff;
				int green = (pixel >>  8) & 0xff;
				int blue = (pixel      ) & 0xff;

				int grayC = int(coef01*red + coef02*green + coef03*blue);

				GrayArray[i][j] = grayC;
			}// inner for*/
		}

		return grayImage;
	}

	System::Drawing::Bitmap* GetBinaryImage()
	{
		return this->bainaryImage;
	}

	bool** GetBinaryArray( int level )
	{
		for( int yVal = 0; yVal < ysize; yVal++ )
		{
			for ( int xVal = 0; xVal < xsize; xVal++ )
			{
				System::Drawing::Color clr = this->rgbImage->GetPixel(xVal,yVal);
				int pixel = clr.ToArgb();				

				//int alpha = (pixel >> 24) & 0xff;// no need here
				int red = (pixel >> 16) & 0xff;
				int green = (pixel >>  8) & 0xff;
				int blue = (pixel      ) & 0xff;
				int grayC = int(coef01*red + coef02*green + coef03*blue);

				if ( grayC >= level )
				{
					BArray[yVal][xVal] = true;
					GrayArray[yVal][xVal] = 1;
					this->bainaryImage->SetPixel(xVal,yVal,Color::White);
				}
				else
				{
					BArray[yVal][xVal] = false;
					GrayArray[yVal][xVal] = 0;
					this->bainaryImage->SetPixel(xVal,yVal,Color::Black);
					
				}

			}// inner for*/
		}
		return BArray;
	}

	int** GetImageArray( )
	{	
		return GrayArray;
	}

};


