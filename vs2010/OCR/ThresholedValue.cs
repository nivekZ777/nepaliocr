/*
 * Original Code was forked from http://code.google.com/p/nepaliocr/source/browse/trunk/ThresholedValue.h?spec=svn146&r=108
 */

using System.Drawing;

namespace NOCR
{
    public class ThresholedValue 
    {

        static int num_bins = 256;
        int xsize;
        int ysize;
        float[] counts;
        float sum_counts;
        float[] p;
        float[] omega;
        float[] mu;
        float mu_t;

        Bitmap ImageFile;

        public ThresholedValue(Bitmap bm)
        {
            ImageFile = bm;

            xsize = ImageFile.Width;
            ysize = ImageFile.Height;
        }

        private void ImHist()
        {
            counts = new float[256];
            for (int i = 0; i < 256; i++)
                counts[i] = 0;

            int max = 0;
            for (int i = 0; i < xsize; i++)
                for (int j = 0; j < ysize; j++)
                {
                    Color clr = ImageFile.GetPixel(i, j);
                    int pixel = clr.ToArgb();

                    //int alpha = (pixel >> 24) & 0xff;// no need here
                    /*int red = (pixel >> 16) & 0xff;
                    counts[red]++;

                    int green = (pixel >>  8) & 0xff;
                    counts[green]++;

                    int blue = (pixel      ) & 0xff;
                    counts[blue]++;*/

                    counts[(pixel >> 16) & 0xff]++; //red			
                    counts[(pixel >> 8) & 0xff]++;	//green		
                    counts[(pixel) & 0xff]++; //blue
                    //
                }// inner for*/
        }// end of function ImHist()




        private void calculateValue()
        {
            int i;
            sum_counts = 0;


            for (i = 0; i < /*sizeof(counts)*/256; i++)
            {
                //System.out.println(counts[i]);
                sum_counts += counts[i];
            }

            p = new float[256];
            omega = new float[256];
            mu = new float[256];

            p[0] = counts[0] / sum_counts;
            omega[0] = p[0];
            mu[0] = p[0] * 1;

            for (i = 1; i < /*sizeof(counts)*/256; i++)
            {
                p[i] = counts[i] / sum_counts;
                omega[i] = omega[i - 1] + p[i]; //cumulative sum
                mu[i] = mu[i - 1] + p[i] * (i + 1); //cumulative sum
            }
            mu_t = mu[255];
        }//end of function calculateValue()


        public float GetThresholed()
        {
            ImHist();
            calculateValue();
            float level = 0;
            double[]  sigma_b_squared;
            sigma_b_squared = new double[256];
            double maxval = 0;
            //float sigma_b_squared = (mu_t * omega - mu).^2 ./ (omega .* (1 - omega));

            for (int i = 0; i < 255; i++)
            {
                float div = omega[i] * (1 - omega[i]);
                //System.out.println("div  " + div);
                if (div == 0)
                    sigma_b_squared[i] = -1;
                else
                {
                    float tmp = (mu_t * omega[i] - mu[i]);
                    sigma_b_squared[i] = (tmp * tmp) / div;
                }

                if (maxval < sigma_b_squared[i])
                    maxval = sigma_b_squared[i];
            }// end of for */

            /**
            *Find the location of the maximum value of sigma_b_squared.
            *The maximum may extend over several bins, so average together the
            *locations.  If maxval is NaN, meaning that sigma_b_squared is all NaN,
            *then return 0.
            */
            int count = 0;
            int sumI = 0;

            if (maxval > -1)
            {
                for (int i = 0; i < 256; i++)
                {
                    if (maxval == sigma_b_squared[i])
                    {
                        sumI += i + 1;
                        count++;
                    }
                }//end of for
                float idx = sumI / count;
                level = (idx - 1) / (num_bins - 1);
            }// end of if
            else
                level = 0;

            return level;
        }

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