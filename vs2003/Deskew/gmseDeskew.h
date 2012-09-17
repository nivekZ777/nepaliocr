#include "HoughLine.h"

#pragma once
using namespace System::Collections;
using namespace System;
using namespace System::IO;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
//using namespace tryDeskew;

/*
public class main
{
	public static void Main()
	{
		string fnIn = "d:\\skewsample_in.tif";
		string fnOut = "d:\\skewsample_out.tif";
		Bitmap bmpIn = new Bitmap(fnIn);
		gmseDeskew sk = new gmseDeskew(bmpIn);
		double skewangle = sk.GetSkewAngle;
		Bitmap bmpOut = RotateImage(bmpIn, -skewangle);
		bmpOut.Save(fnOut, ImageFormat.Tiff);
		Interaction.MsgBox("Skewangle: " + skewangle);
	}

	private static Bitmap RotateImage(Bitmap bmp, double angle)
	{
		Graphics g;
		Bitmap tmp = new Bitmap(bmp.Width, bmp.Height, PixelFormat.Format32bppRgb);

		tmp.SetResolution(bmp.HorizontalResolution, bmp.VerticalResolution);
		g = Graphics.FromImage(tmp);
		try 
		{
			g.FillRectangle(Brushes.White, 0, 0, bmp.Width, bmp.Height);
			g.RotateTransform(angle);
			g.DrawImage(bmp, 0, 0);
		}
		finally 
		{
			g.Dispose();
		}
		return tmp;
	}
}

*/
public __gc class Deskew
{
	// Representation of a line in the image.
	// The Bitmap
	Bitmap* cBmp;
	// The range of angles to search for lines
	static	double cAlphaStart = -20;
	static double cAlphaStep = 0.2;
	static int cSteps = 40 * 5;
	// Precalculation of sin and cos.
	static double *cSinA;
	static double *cCosA;
	// Range of d
	static double cDMin;
	static double cDStep = 1;
	int cDCount;
	// Count of points that fit in a line.
	static int *cHMatrix;

	// Calculate the skew angle of the image cBmp.
public:
	double Deskew::GetSkewAngle()
	{
		HougLine* hl[];
		int i;
		double sum;
		int count;

		// Hough Transformation
		Calc();
		// Top 20 of the detected lines in the image.
		hl = GetTop(20);
		// Average angle of the lines
		for (i = 0; i <= 19; i++) 
		{
			sum += hl(i).Alpha;
			count += 1;
		}
		return sum / count;
	}

	// Calculate the Count lines in the image with most points.
private:
	HoughLine* Deskew::GetTop(int count)[]
	{
		HougLine[] hl;
		int i;
		int j;
		HougLine tmp;
		int AlphaIndex;
		int dIndex;

		// ERROR: Not supported in C#: ReDimStatement

		for (i = 0; i <= Count - 1; i++) 
		{
			hl(i) = new HougLine();
		}
		for (i = 0; i <= cHMatrix.Length - 1; i++) 
		{
			if (cHMatrix(i) > hl(Count - 1).Count)
			{
				hl(Count - 1).Count = cHMatrix(i);
				hl(Count - 1).Index = i;
				j = Count - 1;
				while (j > 0 && hl(j).Count > hl(j - 1).Count) 
				{
					tmp = hl(j);
					hl(j) = hl(j - 1);
					hl(j - 1) = tmp;
					j -= 1;
				}
			}
		}
		for (i = 0; i <= Count - 1; i++) 
		{
			dIndex = hl(i).Index / cSteps;
			AlphaIndex = hl(i).Index - dIndex * cSteps;
			hl(i).Alpha = GetAlpha(AlphaIndex);
			hl(i).d = dIndex + cDMin;
		}
		return hl;
	}
public:
	Deskew(Bitmap* bmp)
	{
		cBmp = bmp;
	}
	// Hough Transforamtion:
private:
	void Calc()
	{
		int x;
		int y;
		int hMin = cBmp.Height / 4;
		int hMax = cBmp.Height * 3 / 4;

		Init();
		for (y = hMin; y <= hMax; y++) 
		{
			for (x = 1; x <= cBmp.Width - 2; x++) 
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
	// Calculate all lines through the point (x,y).
	private:
		void Calc(int x, int y)
	{
		int alpha;
		double d;
		int dIndex;
		int Index;

		for (alpha = 0; alpha <= cSteps - 1; alpha++) 
		{
			d = y * cCosA(alpha) - x * cSinA(alpha);
			dIndex = CalcDIndex(d);
			Index = dIndex * cSteps + alpha;
			try 
			{
				cHMatrix(Index) += 1;
			}
			catch (Exception ex) 
			{
				Debug.WriteLine(ex.ToString);
			}
		}
	}
	private:
	double CalcDIndex(double d)
	{
		return Convert.ToInt32(d - cDMin);
	}
	private:
	bool IsBlack(int x, int y)
	{
		Color c;
		double luminance;

		c = cBmp.GetPixel(x, y);
		luminance = (c.R * 0.299) + (c.G * 0.587) + (c.B * 0.114);
		return luminance < 140;
	}
	private:
	void Init()
	{
		int i;
		double angle;

		// Precalculation of sin and cos.
		// ERROR: Not supported in C#: ReDimStatement

		// ERROR: Not supported in C#: ReDimStatement

		for (i = 0; i <= cSteps - 1; i++) 
		{
			angle = GetAlpha(i) * Math.PI / 180.0;
			cSinA(i) = Math.Sin(angle);
			cCosA(i) = Math.Cos(angle);
		}
		// Range of d:
		cDMin = -cBmp.Width;
		cDCount = 2 * (cBmp.Width + cBmp.Height) / cDStep;
		// ERROR: Not supported in C#: ReDimStatement

	}

	public:
	double GetAlpha(int Index)
	{
		return cAlphaStart + Index * cAlphaStep;
	}
}



