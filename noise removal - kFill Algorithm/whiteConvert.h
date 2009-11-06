#pragma once
using namespace System::Drawing;

public __gc class whiteConvert
{
private: 
	System::Drawing::Bitmap* setoImage;
	System::Drawing::Bitmap* rgbImage;
	int xsize;
	int ysize;
	

public:

	whiteConvert(System::Drawing::Bitmap* im)
	{
		rgbImage = im;
		xsize = rgbImage->Width;
		ysize = rgbImage->Height;
		setoImage = new Bitmap(xsize, ysize, Imaging::PixelFormat::Format24bppRgb);
	}

	
	System::Drawing::Bitmap* GetWhiteImage()
	{
		for( int yVal = 0; yVal < ysize; yVal++ )
		{
			for ( int xVal = 0; xVal < xsize; xVal++ )
			{
				this->setoImage->SetPixel(xVal,yVal,Color::White);

			}
		}
		return this->setoImage;
	}

	

};
