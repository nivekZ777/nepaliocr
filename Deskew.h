#ifndef DESKEW_H
#define DESKEW_H

#include "HoughLine.h"

#pragma once

using namespace System::Collections;
using namespace System;
using namespace System::IO;
//using namespace System::Drawing::Bitmap;

public __gc class Deskew
{



public:
	//The Bitmap
	static System::Drawing::Bitmap *cBmp;
	//The range of angles to search for lines
	//static double cAlphaStart= -20;
	static double cAlphaStart= -20;
	static double cAlphaStep= 0.2;
	static int cSteps= 40 * 5;
	//Precalculation of sin and cos.
	static double *cSinA;
	static double *cCosA;
	//Range of d
	static double cDMin;
	static double cDStep= 1;
	static int cDCount;

	//Count of points that fit in a line.
	static int *cHMatrix;
	 

	Deskew(System::Drawing::Bitmap * im);

	double GetSkewAngle();
	void Calc();
	void Init();
	double GetAlpha(int Index);
	bool IsBlack(int x,int y);
	void Calc(int x,int y);
	double CalcDIndex(double d);
	HoughLine* GetTop(int count)[];



};

#endif