namespace NOCR
{
    public class Unit
    {

        private int StartColumn;
        private int EndColumn;
        public Unit()
        {
        }

        ///sc . starting column number of Unit
        ///ec . ending column number of Unit
        public void set(int sc, int ec)
        {
            this.StartColumn = sc;
            this.EndColumn = ec;
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

    }
}