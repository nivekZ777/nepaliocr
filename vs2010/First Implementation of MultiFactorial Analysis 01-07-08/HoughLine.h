#pragma once

using namespace System::Collections;
using namespace System;

public __gc class HoughLine
{
public:
	int Count; 	// Count of points in the line.
	int Index; 	// Index in Matrix.
	double Alpha; 
	// The line is represented as all x,y that solve y*cos(alpha)-x*sin(alpha)=d
	double d;

	/*int Count;
	int Index;
	double Alpha;
	double d;*/
};



/*
//houghline algorithm :: as folows
public HoughLine(double angle,
                 int radius,
                 int accumulator,
                 int width,
                 int height);

*/