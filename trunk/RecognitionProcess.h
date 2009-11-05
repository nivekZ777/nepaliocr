#pragma once

public __gc class RecognitionProcess
{
public:
	// attributes
	int leftX;		// left x coordinate of the image
	int rightX;	    // right x coordinate of the image
	int topY;		// top y coordinate of the image
	int bottomY;	// bottom y coordinate of the image
	int imWidth;	// width of the image
	int imHeight;	// height of the image

	int **imageArr;	// Image pixel array

	System::String* scriptFilePath;	// path of the script file	
	System::String* HMMListFilePath;// path of the HMM List File
	System::String* exeFileDir;		// path of the Executables File
	System::String* mmfFilePath;	// path of the Master Model File(MMF)
	System::String* mlfFilePath;	// path of the Master Labeled File(MLF)
	System::String*	dictFilePath;   // path of the Dictionary File
	System::String*	wordNetFilePath;// path of the Word Network File
	System::String*	recognitionTempFileDir;	// path of the temporary file directory

	System ::Collections::SortedList* slModel;		// list to store the model transcription database
	System ::Collections::ArrayList* alModelTrans;
	System::String* dbFilePath;

	// constructors
	RecognitionProcess(void);
	RecognitionProcess(System::String* path, int **imgArray);
	//RecognitionProcess(System::String* path,int **imgArray, int left_x, int right_x,int top_y, int bottom_y);

	/*Methods*/
	// loading the transcription of the trained models
	System::Collections::SortedList* LoadModelTranscriptions(System::String* dbFilePath);

	// setting the image boundary
	void ImageBoundarySet(int left_x, int right_x,int top_y, int bottom_y);

	// setting the word image boundary
	void SetImageBoundary(int left_x, int right_x,int top_y, int bottom_y);

	// reading the word image information and write the features into a file in binary format
	void PrepareWordData(System::String* wordFeatureFile);

	// recognize the image words using the HTK Toolkit
	System::Collections::ArrayList* RecognizeByHTK();
};
