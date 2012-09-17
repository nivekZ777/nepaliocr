using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace NOCR
{
    public partial class RecognitionForm : Form
    {
        public RecognitionForm()
        {
            InitializeComponent();
        }

        public void showText(String text)
		{
			this.charRecBox.Text=text;
		}
    }
}
