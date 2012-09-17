/*
 * Original code was forked from http://code.google.com/p/nepaliocr/source/browse/trunk/HoughLine.h?spec=svn146&r=138
*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NOCR
{
    public class HoughLine
    {
        public int Count; 	// Count of points in the line.
        public int Index; 	// Index in Matrix.
        public double Alpha;
        // The line is represented as all x,y that solve y*cos(alpha)-x*sin(alpha)=d
        public double d;


        //houghline algorithm :: as folows
        //public HoughLine(double angle, int radius,int accumulator,int width,int height){}


    }
}


/**
 *   OCR
 * Programmed in C#, Visual Studio 2010
 * Microsoft Windows 7 
 * Professional 
 * Home Premium
 
 * Intel[R] 
 * 3 GB RAM
 * 2.80 GHZ , 1.00 GB of  RAM 
 *
 *
 * Requirements:
 *  
 * win2k or later\n
 * .NET FrameWork 4.0 or later 
 *
 * Version 1.0
 * first version
 *
 * Date 9-18-2012
 *
 ** Author Rajesh Pandey
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