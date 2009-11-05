#pragma once
#include<iostream>


using namespace std;


public __gc class TrainingProcess
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
	int htArray;	// height of the array
	int wdArray;    // width of the array

	int numOfFrame;

	System::String* modelName; // model name	

	System::Drawing::Bitmap* im;

	System::String* trainingFilePath;// path of the training file	
	System::String* prototypeFileDir;// path of the prototype file
	System::String* outputHMMFileDir;// path of the training file
	System::String* HMMNameFilePath; // path of the HMM Name File
	System::String* HMMListFilePath; // path of the HMM List File
	System::String* exeFileDir;		 // path of the Executables File
	System::String* mmfFilePath;	 // path of the Master Model File(MMF)
	System::String*	grammerFilePath; // path of the Grammer File
	System::String*	dictFilePath;    // path of the Dictionary File
	System::String*	transFilePath;   // path of the Transcription File
	System::String*	wordNetFileDir;  // path of the Word Network File

	// constructors
	TrainingProcess(void);
	TrainingProcess(System::String* path,int **imgArray,int leftX, int rightX,int topY, int bottomY);
	
	/* Methods */
	// setting the image actual boundary information
	void ImageBoundarySet(int left_x, int right_x,int top_y, int bottom_y);

	// reading the image information and write into a file in binary format
	void PrepareTrainingData();

	// train the image word using the HTK Toolkit
	void TrainingByHTK(int numOfFrame);

	// Get the model name
	System::String* GetTrainedModelName();
};
