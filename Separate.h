
/**
 *   OCR
 * Programmed in Visual C++ 2003 
 * Microsoft Windows XP 
 * Professional 
 * Version 2002 
 * Service Pack 3  
 * Intel[R] 
 * Pentium 4 CPU  2.80 GHZ 
 * 2.80 GHZ , 1.00 GB of  RAM 
 *
 *
 * Requirements:
 *  
 * win2k or later\n
 * .NET FrameWork 1.1 or later 
 *
 * Version 1.0
 * first version
 *
 * Date 07-01-2008
 *
 ** Credits : 
 * Author : Rajesh Pandey ::  nepaliocr@gmail.com
 *
 *
 * license
 * This code is absolutely free to use and modify. The code is provided "as is" with
 * no expressed or implied warranty. The author accepts no liability if it causes
 * any damage to your computer, causes your pet to fall ill, increases baldness
 * or makes your car start emitting strange noises when you start it up.
 * This code has no bugs, just undocumented features!
 * 
 *  
 *
 *  
 *
 */

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

	

	