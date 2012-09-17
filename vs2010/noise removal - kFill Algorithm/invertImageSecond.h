#pragma once
using namespace System::Drawing;

public __gc class invertImageSecond
{
private: 
	System::Drawing::Bitmap* upImage;
	System::Drawing::Bitmap* downImage;
	int xsize;
	int ysize;
	int **upArray;
		
public:
	invertImageSecond(System::Drawing::Bitmap* BinaryImage, int **ImgArray)
	{

		upImage = BinaryImage;
		upArray = ImgArray;
		xsize = upImage->Width;
		ysize = upImage->Height;
		downImage = new Bitmap(xsize, ysize, Imaging::PixelFormat::Format24bppRgb);
	}

	System::Drawing::Bitmap* GetInvertedImage ()
	{
		for( int yVal = 0; yVal < ysize; yVal++ )
		{
			for ( int xVal = 0; xVal < xsize; xVal++ )
			{
				if ( upArray[yVal][xVal]== 1)
					this->downImage->SetPixel(xVal,yVal,Color::Black);
				else
					this->downImage->SetPixel(xVal,yVal,Color::White);
			}
		}

	return downImage;
	}
	
};
