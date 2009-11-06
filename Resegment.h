
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
		int SizeThresHold;     //Threshold Size value which separates the touching characters from others
		Bitmap* img;			//source image
		Bitmap* cropImage;		//Unit Image 
		int ImHeight;			
		int ImWidth;
		int *WStore;			// Array to store the width of all the units in the image
		int totalunits;			// total number of the connected units in the image
		int *TouchingCharacterIndex;
		bool BinaryDone;

		bool Resegmentation_Complete;	
		bool ImageLoaded;
		bool SeparateDone;
		bool **BinArray;
		int numberOfLines;
		Line *Lines;
		Graphics *g;
		int flevel;
		int *Horizontal;
		int **HeadBottom; //Array with the information of headline position and bottomline position

public:
	Resegment(Bitmap* im,bool BinaryDone,bool ImageLoaded,bool SeparateDone, bool **BinArray,int numberOfLines, Line *Lines, Graphics *g,int totalUnits, int SizeThreshold,int flevel,int **headbottom);
	void WidthStore(); //Stores the width values to the array
	void TotalUnitCount(); //Calculates total unit count
	int ThresholdSize();	// Calculates and Returns Threshold Image
	void Do_Segmentation();	// Performs the resegmentation
	void Crop_Image(int lineno,int wordno,int charno); //crops the character unit image from given position
	int MultiFactorialAnalysis(int Headline_Pos,int Bottom_Pos);	// Performs the Multifactorial Analysis
	int minimum(int *num,int width); // Returns the minimum number from the given array
	int maximum(float *num,int width); //Returns the Largest Float value
	int maximum(int *num,int width); //Returns the largst integer value
	void sortWidth(); //Sort the width in ascending order
	int Truncate(int val); // Rounding off the float value
	void adjustUnits(int lineno,int wordno,int charno); // Adjust the boundaries after identifying the cut column
	void getPixelInRows(int height,int width,bool **bArray);
	int headLinePosition(int height,int width);
	int bottomLinePosition(int height,int width, int maxIndex,bool **BinaryArray);
//	void PrepareTouchingCharIndex();

};



	
