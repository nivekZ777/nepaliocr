
#include "Separate.h"
#include "Line.h"
#include "ThresholedValue.h"
#include "rgbConvert.h"


#pragma once


using namespace System::Drawing;
using namespace System::Collections;
using namespace System;

public __gc class Resegment
{
private:
		int SizeThresHold;
		Bitmap* img;
		Bitmap* cropImage;
		int ImHeight;
		int ImWidth;
		int *WStore;
		int totalunits;
		bool BinaryDone;
		bool ImageLoaded;
		bool SeparateDone;
		bool **BinArray;
		int numberOfLines;
		Line *Lines;

public:
	Resegment(Bitmap* im,bool BinaryDone,bool ImageLoaded,bool SeparateDone, bool **BinArray,int numberOfLines, Line *Lines);
	void WidthStore();
	void TotalUnitCount();
	int ThresholdSize();
	void Do_Segmentation();
	void Crop_Image(int lineno,int wordno,int charno);
	int MultiFactorialAnalysis();
	int minimum(int *num,int width);
	int maximum(float *num,int width);
	int maximum(int *num,int width);
	void sortWidth();
	void adjustUnits(int lineno,int wordno,int charno);

};



