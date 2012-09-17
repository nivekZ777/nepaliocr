using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NOCR
{
    public class Word
    {



        //private int WordNo;
        private int TotalUnit;
        private int StartColumn;
        private int EndColumn;

        public Unit[] Units;

        public Word()
        {
        }

        ///sc . starting column number of line
        ///ec . ending column number of line
        public void set(int sc, int ec)
        {
            this.StartColumn = sc;
            this.EndColumn = ec;
        }
        ///Ut . number of units in this word
        public void setUnit(int Ut)
        {
            this.TotalUnit = Ut;
            Units = new Unit[Ut];
        }
        public int getStartColumn()
        {
            return this.StartColumn;
        }
        ///
        public int getEndColumn()
        {
            return this.EndColumn;
        }

        public int getTotalUnit()
        {
            return this.TotalUnit;
        }


    }
}
