/*
 * Original code was forked from : http://code.google.com/p/nepaliocr/source/browse/trunk/RecognitionProcess.cpp?spec=svn146&r=108 and 
 * http://code.google.com/p/nepaliocr/source/browse/trunk/RecognitionProcess.h?spec=svn146&r=108
 */
namespace NOCR
{
    public class RecognitionProcess
    {
        int leftX;		// left x coordinate of the image
        int rightX;	    // right x coordinate of the image
        int topY;		// top y coordinate of the image
        int bottomY;	// bottom y coordinate of the image
        int imWidth;	// width of the image
        int imHeight;	// height of the image

        int[,] imageArr;	// Image pixel array

        internal System.String scriptFilePath;	// path of the script file	
        internal System.String HMMListFilePath;// path of the HMM List File
        internal System.String exeFileDir;		// path of the Executables File
        internal System.String mmfFilePath;	// path of the Master Model File(MMF)
        internal System.String mlfFilePath;	// path of the Master Labeled File(MLF)
        internal System.String dictFilePath;   // path of the Dictionary File
        internal System.String wordNetFilePath;// path of the Word Network File
        internal System.String recognitionTempFileDir;	// path of the temporary file directory

        internal System.Collections.SortedList slModel;		// list to store the model transcription database
        internal System.Collections.ArrayList alModelTrans;

        //System.Collections.ArrayList *aakarsList;
        //System.Collections.ArrayList *rassoEEkarList;
        //System.Collections.ArrayList *aaKarList;
        System.String dbFilePath;

        public RecognitionProcess()
        {

        }
        public RecognitionProcess(System.String path, int[,] imgArray)
        {
            this.imageArr = imgArray;

            this.imWidth = 0;
            this.imHeight = 0;

            this.scriptFilePath += string.Concat(path, "\\htk\\recognizer\\script.txt");
            this.HMMListFilePath += string.Concat(path, "\\htk\\files\\hmmlist.txt");
            this.exeFileDir += string.Concat(path, "\\htk\\executables\\");
            this.mmfFilePath += string.Concat(path, "\\htk\\files\\nepaliOCR.mmf");
            this.mlfFilePath += string.Concat(path, "\\htk\\files\\labeled.mlf");
            this.dictFilePath += string.Concat(path, "\\htk\\files\\def\\dict.txt");
            this.wordNetFilePath += string.Concat(path, "\\htk\\files\\def\\net.slf");
            this.recognitionTempFileDir += string.Concat(path, "\\htk\\recognizer\\");
            //this.aakarsList = new System.Collections.ArrayList();
            //this.rassoEEkarList = new System.Collections.ArrayList();

        }

        internal System.Collections.SortedList LoadModelTranscriptions(System.String dbFilePath)
        {
            // load the model transcription database
            System.IO.StreamReader sr = System.IO.StreamReader.Null;
            slModel = new System.Collections.SortedList();


            System.String key = "";
            System.String tempStr;
            int count = 0;
            bool modelName = true;
            try
            {
                sr = new System.IO.StreamReader(dbFilePath);
                while (sr.Peek() >= 0)
                {

                    tempStr = sr.ReadLine();
                    if (tempStr.Equals("*"))
                    {
                        count = 0;
                        slModel.Add(key, alModelTrans);


                    }
                    else
                    {
                        if (count == 0)
                        {
                            key = tempStr;
                            alModelTrans = new System.Collections.ArrayList();
                            count++;
                        }
                        else
                        {
                            alModelTrans.Add(tempStr);
                            //PostProcessing Details Here
                            //ArrayList aakarList contains list of model names
                            //				if(tempStr.Equals("093E")){
                            //					this.aakarsList.Add(key);
                            ////PostProcessing Details here
                            //	
                            //}
                            //if(tempStr.Equals("093F")){
                            //	this.rassoEEkarList.Add(key);
                            //}
                        }
                    }
                    //if(tempStr.Equals("093E")){
                    //	System.Windows.Forms.MessageBox.Show("Found",key.ToString());
                    //}
                } //End while
                sr.Close();

                //while(aaKarList.GetEnumerator().MoveNext()){
                //	  
                //	myaaKarListCounter++;
                //}
                return slModel;
            }
            catch (System.Exception ex)
            {
                System.Windows.Forms.MessageBox.Show(ex.Message.ToString(), "Failed to Load the Model DataBase!!", System.Windows.Forms.MessageBoxButtons.OK, System.Windows.Forms.MessageBoxIcon.Error);
                return null;
            }
        }


        public void SetImageBoundary(int left_x, int right_x, int top_y, int bottom_y)
        {
            this.leftX = left_x;
            this.rightX = right_x;
            this.topY = top_y;
            this.bottomY = bottom_y;

            //Setting the training image boundary...	
            //this.ImageBoundarySet(this.leftX,this.rightX,this.topY,this.bottomY);
        }


        public void PrepareWordData(System.String wordFeatureFile)
        {
            FileManipulating fm = new FileManipulating();
            fm.PrepareData(wordFeatureFile, this.imageArr, this.leftX, this.rightX, this.topY, this.bottomY);
        }

        public System.Collections.ArrayList RecognizeByHTK()
        {
            FileManipulating fm = new FileManipulating();
            fm.RecognizeByHMM(this.recognitionTempFileDir, this.exeFileDir, this.mmfFilePath, this.mlfFilePath, this.wordNetFilePath, this.dictFilePath, this.HMMListFilePath, this.scriptFilePath);

            System.Collections.ArrayList al = fm.FetchOutputModels(this.mlfFilePath);


            return al;
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