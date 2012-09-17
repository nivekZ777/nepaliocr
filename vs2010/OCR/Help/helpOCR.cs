using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace NOCR.Help
{
    public partial class helpOCR : Form
    {
        public helpOCR()
        {
            InitializeComponent();
        }
        
	public void ShowHelpOCR(){
 
				this.enableDisable(this.pictureBoxHelpOCR,new System.Drawing.Size(576, 328)," Help : OCR");
				this.pictureBoxHelpOCR2.Visible = true;
			}
			
		public void ShowHelpTrain(){
 
				this.enableDisable(this.pictureBox3,new System.Drawing.Size(912, 560)," Help : Training");
				this.pictureBoxHelpTrainWindow.Visible = true;


			}
				
			public void ShowHelpDeskew(){
 
				this.enableDisable(this.pictureBoxDeskew,new System.Drawing.Size(424, 320)," Help : Deskewing a tilted image");
			}
			public void ShowHelpNoiseRemoval(){
 
				this.enableDisable(this.pictureBoxHelpRemoveNoise,new System.Drawing.Size(344, 344)," Help : Removing Noise from an Image");
			}

			public void ShowHelpBinarize(){
				this.enableDisable(this.pictureBoxHelpBinarize,new System.Drawing.Size(344, 272)," Help : Binarizing an image");
			}
			
			
			public void ShowHelpSeparate(){
				this.enableDisable(this.pictureBoxHelpSeparate,new System.Drawing.Size(344, 296)," Help : Separating A binarized image");
			}
						
			public void ShowHelpContrast(){
					this.enableDisable(this.pictureBoxHelpContrast,new System.Drawing.Size(656, 416)," Help : Adding Contrast to a Picture");
					this.pictureBoxContrastAdded.Visible = true;
			}
			
									
			public void ShowHelpCropper(){
				 this.enableDisable(this.pictureBoxHelpCropper,new System.Drawing.Size(648, 512)," Help : Adding Cropping a Picture");
					
			}
		
			public void ShowHelpSaveImage(){
				this.enableDisable(this.pictureBoxHelpSaveImage,new System.Drawing.Size(224, 232)," Help : Saving image");				
			}
	
				 
			public void ShowHelpSaveOutput(){
				this.enableDisable(this.pictureBoxHelpSaveOutput,new System.Drawing.Size(376, 240)," Help : Saving Output text");				
			}
			public void ShowHelpRotateLeft(){
				this.enableDisable(this.pictureBoxHelpRotateLeft,new System.Drawing.Size(304, 368)," Help : Rotating the Image to left");				
			}
			public void ShowHelpRotateRight(){
				this.enableDisable(this.pictureBoxHelpImageRotateRight,new System.Drawing.Size(304, 368)," Help : Rotating the Image to right");				
			}
				

				public void ShowHelpRotateUpright(){
				this.enableDisable(this.pictureBoxHelpRotateUpright,new System.Drawing.Size(304, 368)," Help : Rotating the Image upright");				
			}
			void enableDisable(System.Windows.Forms.PictureBox pb, System.Drawing.Size size,System.String titleBarString){
				this.pictureBoxHelpOCR.Visible = false;
				this.pictureBoxHelpOCR2.Visible =  false;
				this.pictureBoxHelpBinarize.Visible  = false;
				this.pictureBoxHelpRemoveNoise.Visible = false;
				this.pictureBoxHelpSeparate.Visible  =false;
				this.pictureBoxHelpContrast.Visible = false;
				this.pictureBoxContrastAdded.Visible = false;
				this.pictureBoxHelpCropper.Visible = false;
				this.pictureBoxHelpSaveImage.Visible =false;			
				this.pictureBoxHelpSaveOutput.Visible =false;
				this.pictureBoxHelpRotateLeft.Visible =false;
				this.pictureBoxHelpImageRotateRight.Visible =false;
				this.pictureBoxHelpRotateUpright.Visible =false;
				this.pictureBoxHelpTrainWindow.Visible = false;

				this.pictureBox3.Visible = false;
				this.pictureBoxDeskew.Visible = false;

				pb.Visible = true;
				this.Size = size;
				this.Text = titleBarString;
				int closeButton_x = Math.Abs ((int)(this.Width/2));
				
				int closeButton_y = (int)this.btnClose.Location.Y;
				this.btnClose.Location = new System.Drawing.Point(closeButton_x,closeButton_y);
				 
		}

            private void btnClose_Click(object sender, EventArgs e)
            {
                this.Hide();
            }
    }
}
