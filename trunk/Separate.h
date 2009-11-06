#ifndef SEPARATE_H
#define SEPARATE_H

#include "Line.h"
#pragma once
//#include <vector>


using namespace System::Drawing;
using namespace System::Collections;
using namespace System;

public __gc class Separate
{
private:
	bool **BinaryArray;

	int xSize;
	int ySize;
	int *Horizontal;
	int *R2;
	int **Vertical;
	//int **VerticalC;
	int numberOfLines;
	int **HeadBottom;
	static int thresh_char_gap=2;

	Graphics* g;



public:
	Separate(Bitmap* im,bool **B,Graphics* gr);
	Line *Lines;
	void LineSeparate();
	void drawHorizontalHist();
	void WordSeparate(ArrayList* start,ArrayList* end);
	void WordSeparate1(ArrayList* start,ArrayList* end);
	void CheckMattra(ArrayList* start,ArrayList* end,ArrayList** wordStart,ArrayList** wordEnd);
	void CharSeparate(ArrayList* start,ArrayList* end,ArrayList** wordStart,ArrayList** wordEnd);
	int getNumberOfLines();
	Line* getLines();
	int** getHeadBottom();
};



	
#endif 

	

	