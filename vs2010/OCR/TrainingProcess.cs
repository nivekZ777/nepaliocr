using System;

namespace NOCR
{
    internal class TrainingProcess
    {
        public int leftX;		// left x coordinate of the image
        public int rightX;	    // right x coordinate of the image
        public int topY;		// top y coordinate of the image
        public int bottomY;	// bottom y coordinate of the image
        public int imWidth;	// width of the image
        public int imHeight;	// height of the image

        public int[,] imageArr;	// Image pixel array
        public int htArray;	// height of the array
        public int wdArray;    // width of the array

        public int numOfFrame;

        public String modelName; // model name	

        public System.Drawing.Bitmap im;

        String trainingFilePath;// path of the training file	
        public System.String prototypeFileDir;// path of the prototype file
        public System.String outputHMMFileDir;// path of the training file
        public System.String HMMNameFilePath; // path of the HMM Name File
        public System.String HMMListFilePath; // path of the HMM List File
        public System.String exeFileDir;		 // path of the Executables File
        public System.String mmfFilePath;	 // path of the Master Model File(MMF)
        public System.String grammerFilePath; // path of the Grammer File
        public System.String dictFilePath;    // path of the Dictionary File
        public System.String transFilePath;   // path of the Transcription File
        public System.String wordNetFileDir;  // path of the Word Network File


        public TrainingProcess(System.String path, int[,] imgArray, int left_x, int right_x, int top_y, int bottom_y)
        {
            this.imageArr = imgArray;
            this.leftX = left_x;
            this.rightX = right_x;
            this.topY = top_y;
            this.bottomY = bottom_y;
            this.imWidth = 0;
            this.imHeight = 0;
            this.modelName = "";

            this.trainingFilePath += string.Concat(path, "\\htk\\files\\trainfile.txt");
            this.prototypeFileDir += string.Concat(path, "\\htk\\files\\prototypes\\");
            this.outputHMMFileDir += string.Concat(path, "\\htk\\files");
            this.HMMNameFilePath += string.Concat(path, "\\htk\\files\\hmmName.txt");
            this.HMMListFilePath += string.Concat(path, "\\htk\\files\\hmmlist.txt");
            this.exeFileDir += string.Concat(path, "\\htk\\executables\\");
            this.mmfFilePath += string.Concat(path, "\\htk\\files\\nepaliOCR.mmf");
            this.grammerFilePath += string.Concat(path, "\\htk\\files\\def\\gram.txt");
            this.dictFilePath += string.Concat(path, "\\htk\\files\\def\\dict.txt");
            this.transFilePath += string.Concat(path, "\\htk\\files\\transcription.txt");
            this.wordNetFileDir += string.Concat(path, "\\htk\\files\\def\\");

            //Setting the training image boundary...	
            //this.ImageBoundarySet(this.leftX,this.rightX,this.topY,this.bottomY);
        }

       public void ImageBoundarySet(int left_x, int right_x, int top_y, int bottom_y)
        {
            try
            {
                bool pixelFound = false;
                for (int yVal = top_y; yVal <= bottom_y; yVal++)
                {
                    for (int xVal = left_x; xVal <= right_x; xVal++)
                    {
                        if (this.imageArr[yVal,xVal] == 0 && pixelFound)
                        {
                            if (xVal < this.leftX) { this.leftX = xVal; }
                            if (xVal > this.rightX) { this.rightX = xVal; }
                            if (yVal > this.bottomY) { this.bottomY = yVal; }
                        }
                        else if (this.imageArr[yVal,xVal] == 0)
                        {
                            pixelFound = true;
                            this.leftX = xVal;
                            this.rightX = xVal;
                            this.topY = yVal;
                            this.bottomY = yVal;
                        }
                    }
                }
            }
            catch (System.NullReferenceException ex)
            {
                System.Windows.Forms.MessageBox.Show(ex.Message.ToString(), "Image Boundary Finding Error", System.Windows.Forms.MessageBoxButtons.OK, System.Windows.Forms.MessageBoxIcon.Error);
                return;
            }
        }

        public void PrepareTrainingData()
        {
            FileManipulating fm = new FileManipulating();
            fm.PrepareData(this.trainingFilePath,  this.imageArr, this.leftX, this.rightX, this.topY, this.bottomY);
            this.numOfFrame = fm.numOfFrame;
        }


        public void TrainingByHTK(int numOfFrame)
        {
            try
            {
                // getting the model number

                FileManipulating fm = new FileManipulating();

                System.String tmp = fm.GetModelName(this.HMMNameFilePath);

                int modelNum = System.Int32.Parse(tmp.Substring(1)) + 1;
                this.modelName += string.Concat("h", modelNum.ToString());
                System.String from = "";
                //System.Windows.Forms.MessageBox.Show("ya executed","yup u got it!!",System.Windows.Forms.MessageBoxButtons.OK,System.Windows.Forms.MessageBoxIcon.Error);

                // building the prototype file according to the model name
                // select the prototype file according to the number of frame
                // range 1 - 2 : prototype1.hmm
                // range 3 - 6 : prototype2.hmm
                // range 6 - 12: prototype3.hmm
                // range 12 - *: prototype4.hmm


                if (numOfFrame < 2)
                {
                    from += string.Concat(this.prototypeFileDir, "prototype", "1", ".hmm");
                }
                else if (numOfFrame >= 2 && numOfFrame < 6)
                {
                    from += string.Concat(this.prototypeFileDir, "prototype", "2", ".hmm");
                }
                else if (numOfFrame >= 6 && numOfFrame < 12)
                {
                    from += string.Concat(this.prototypeFileDir, "prototype", "3", ".hmm");
                }
                else if (numOfFrame >= 12)
                {
                    from += string.Concat(this.prototypeFileDir, "prototype", "4", ".hmm");
                }


                System.String to = string.Concat(this.prototypeFileDir, this.modelName, ".hmm");


                fm.CreatePrototypeFile(from, to, this.modelName);

                //System.Windows.Forms.MessageBox.Show("ya executed","yup u got it!!",System.Windows.Forms.MessageBoxButtons.OK,System.Windows.Forms.MessageBoxIcon.Error);

                // Create HMM file by the HTK Tool HInit
                fm.CreateHMMFile(this.exeFileDir, this.outputHMMFileDir, to, this.trainingFilePath);

                // Add Newly Created HMM Model definition into MMF(Master Model File)
                from = "";
                from += string.Concat(from, this.outputHMMFileDir, "\\", this.modelName);
                fm.AddModelDefToMasterModelFile(this.mmfFilePath, from);

                // Add the Model Name to HMM List and HMM Name file
                fm.AddModelNameToHMMListFile(this.HMMListFilePath, this.HMMNameFilePath, this.modelName);

                // add the model to the grammer file, dictionary file, transcription database and build the word Network 
                fm.BuildWordNetwork(this.grammerFilePath, this.dictFilePath, this.transFilePath, this.wordNetFileDir, this.exeFileDir, this.modelName);

                // delete the trainfile, Temporary Prototype File & HMM Model File
                System.IO.File.Delete(trainingFilePath);
                System.IO.File.Delete(to);
                System.IO.File.Delete(from);
            }
            catch (System.Exception ex)
            {
                System.Windows.Forms.MessageBox.Show(ex.Message.ToString(), "Training using HTK Failed!!", System.Windows.Forms.MessageBoxButtons.OK, System.Windows.Forms.MessageBoxIcon.Error);
                return;
            }
        }

       public System.String GetTrainedModelName()
        {
            return this.modelName;
        }

    }
}