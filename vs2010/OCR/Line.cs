using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NOCR
{
    public class Line
    {




        //private int LineNo;
        private int TotalWord;
        private int StartRow;
        private int EndRow;

        public
            Word[] Words;

        public Line()
        {
        }

        ///sr . starting row number of line
        ///er . ending row number of line
        public void set(int sr, int er)
        {

            this.StartRow = sr;
            this.EndRow = er;

        }
        ///Wd . number of words in this line
        public void setWord(int Wd)
        {
            this.TotalWord = Wd;
            this.Words = new Word[Wd];
        }

        public int getStartRow()
        {
            return this.StartRow;
        }
        ///
        public int getEndRow()
        {
            return this.EndRow;
        }
        public int getTotalWord()
        {
            return this.TotalWord;
        }


    }
}
