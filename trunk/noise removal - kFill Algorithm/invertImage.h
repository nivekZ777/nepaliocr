#pragma once
using namespace System::Drawing;

public __gc class invertImage
{
private: 
	System::Drawing::Bitmap* sultoImage;
	System::Drawing::Bitmap* ultoImage;
	int xsize;
	int ysize;
	int threshold;

	static float coef01 = (float)0.2989;
	static float coef02 = (float)0.5870;
	static float coef03 = (float)0.1140;
	
public:

	invertImage(System::Drawing::Bitmap* BinaryImage, int intLevel)
	{
		threshold=intLevel;
		sultoImage = BinaryImage;
		xsize = sultoImage->Width;
		ysize = sultoImage->Height;
		
		ultoImage = new Bitmap(xsize, ysize, Imaging::PixelFormat::Format24bppRgb);
	}

			
	System::Drawing::Bitmap* GetInvertedImage()
	{
		for( int yVal = 0; yVal < ysize; yVal++ )
		{
			for ( int xVal = 0; xVal < xsize; xVal++ )
			{

				System::Drawing::Color clr = this->sultoImage->GetPixel(xVal,yVal);
				int pixel = clr.ToArgb();				

				int red = (pixel >> 16) & 0xff;
				int green = (pixel >>  8) & 0xff;
				int blue = (pixel      ) & 0xff;
				int grayC = int(coef01*red + coef02*green + coef03*blue);

				if ( grayC >= threshold )
					this->ultoImage->SetPixel(xVal,yVal,Color::Black);
				else
					this->ultoImage->SetPixel(xVal,yVal,Color::White);

			}
		}
		return this->ultoImage;
	}

		

};
