#pragma once

using namespace System;

public __gc class ConvMatrix
	{	
	public: static int TopLeft = 0, TopMid = 0, TopRight = 0;
	public: static int MidLeft = 0, Pixel = 1, MidRight = 0;
	public: static int BottomLeft = 0, BottomMid = 0, BottomRight = 0;
	public: static int Factor = 1;
	public: static int Offset = 0;
	public: static void SetAll(int nVal)
		{
			TopLeft = TopMid = TopRight = MidLeft = Pixel = MidRight = BottomLeft = BottomMid = BottomRight = nVal;
		}
	};

