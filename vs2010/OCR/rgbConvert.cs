using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;

namespace NOCR
{
    public class rgbConvert
    {

	System.Drawing.Bitmap grayImage;
	System.Drawing.Bitmap bainaryImage;
	System.Drawing.Bitmap rgbImage;
	int xsize;
	int ysize;
	bool[,] BArray;
	int[,] GrayArray;

	const float coef01 = (float)0.2989;
    const float coef02 = (float)0.5870;
    const float coef03 = (float)0.1140;

public rgbConvert(System.Drawing.Bitmap im)
	{
		rgbImage = im;
		xsize = rgbImage.Width;
		ysize = rgbImage.Height;
		BArray = new bool[ysize,xsize];//[][];
		GrayArray = new int [ysize,xsize];
        //for (int i = 0; i < ysize; i++ )
        //{
        //    BArray[i] = new bool[xsize];
        //    GrayArray[i] = new int[xsize];
        //}

		bainaryImage = new Bitmap(xsize, ysize, PixelFormat.Format24bppRgb);
	}

	System.Drawing.Bitmap getGrayImage ()
	{
		for( int i = 0; i < this.xsize; i++ )
		{
			for ( int j = 0; j < this.ysize; j++ )
			{
				System.Drawing.Color clr = this.rgbImage.GetPixel(i,j);
				int pixel = clr.ToArgb();				

				//int alpha = (pixel >> 24) & 0xff;// no need here
				int red = (pixel >> 16) & 0xff;
				int green = (pixel >>  8) & 0xff;
				int blue = (pixel      ) & 0xff;

				int grayC = (int)(coef01*red + coef02*green + coef03*blue);

				GrayArray[i,j] = grayC;
			}// inner for*/
		}

		return grayImage;
	}

	internal System.Drawing.Bitmap GetBinaryImage()
	{
		return this.bainaryImage;
	}

	public bool[,] GetBinaryArray( int level )
	{
		for( int yVal = 0; yVal < ysize; yVal++ )
		{
			for ( int xVal = 0; xVal < xsize; xVal++ )
			{
				System.Drawing.Color clr = this.rgbImage.GetPixel(xVal,yVal);
				int pixel = clr.ToArgb();				

				//int alpha = (pixel >> 24) & 0xff;// no need here
				int red = (pixel >> 16) & 0xff;
				int green = (pixel >>  8) & 0xff;
				int blue = (pixel      ) & 0xff;
				int grayC = (int)(coef01*red + coef02*green + coef03*blue);

				if ( grayC >= level )
				{
					BArray[yVal,xVal] = true;
					GrayArray[yVal,xVal] = 1;
					this.bainaryImage.SetPixel(xVal,yVal,Color.White);
				}
				else
				{
					BArray[yVal,xVal] = false;
					GrayArray[yVal,xVal] = 0;
					this.bainaryImage.SetPixel(xVal,yVal,System.Drawing.Color.Black);
				}

			}// inner for*/
		}
		return BArray;
	}

	public int[,] GetImageArray( )
	{	
		return GrayArray;
	}

}
}
