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
