
/**
 *   OCR
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
 * Date 11-01-2008
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

//This Class ConvMatrix
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

