#include "StdAfx.h"
#include "RecognitionProcess.h"
#include "FileManipulating.h"
#include <iostream>

#define FRAME_HT 40
#define FRAME_WD 8

using namespace std;



RecognitionProcess::RecognitionProcess(void)
{
}

RecognitionProcess::RecognitionProcess(System::String* path,int **imgArray)
{
	this->imageArr = imgArray;
	
	this->imWidth = 0;
	this->imHeight = 0;

	this->scriptFilePath = this->scriptFilePath->Concat(path ,"\\htk\\recognizer\\script.txt");
	this->HMMListFilePath = this->HMMListFilePath->Concat(path ,"\\htk\\files\\hmmlist.txt");
	this->exeFileDir = this->exeFileDir->Concat(path ,"\\htk\\executables\\");
	this->mmfFilePath = this->mmfFilePath->Concat(path ,"\\htk\\files\\nepaliOCR.mmf");
	this->mlfFilePath = this->mlfFilePath->Concat(path ,"\\htk\\files\\labeled.mlf");
	this->dictFilePath = this->dictFilePath->Concat(path ,"\\htk\\files\\def\\dict.txt");
	this->wordNetFilePath = this->wordNetFilePath->Concat(path ,"\\htk\\files\\def\\net.slf");
	this->recognitionTempFileDir = this->recognitionTempFileDir->Concat(path ,"\\htk\\recognizer\\");
	
}

void RecognitionProcess::ImageBoundarySet(int left_x, int right_x,int top_y, int bottom_y)
{
	/*
	try
	{
		bool pixelFound = false;
		for(int yVal=top_y; yVal<=bottom_y; yVal++)
		{
			for(int xVal=left_x; xVal<=right_x; xVal++)
			{
				if(this->imageArr[yVal][xVal]==0 && pixelFound)
				{
					if(xVal<this->leftX){this->leftX = xVal;}
					if(xVal>this->rightX){this->rightX = xVal;}
					if(yVal>this->bottomY){this->bottomY = yVal;}
				}
				else if(this->imageArr[yVal][xVal]==0)
				{
					pixelFound = true;
					this->leftX = xVal;
					this->rightX = xVal;
					this->topY = yVal;
					this->bottomY = yVal;	
				}
			}
		}
	}
	catch(System::NullReferenceException* ex)
	{
		System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"Image Boundary Finding Error",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
		exit(0);
	}*/
	this->leftX=left_x;
	this->rightX=right_x;
	this->topY=top_y;
	this->bottomY=bottom_y;
}

System::Collections::SortedList* RecognitionProcess::LoadModelTranscriptions(System::String* dbFilePath)
{
	// load the model transcription database
	 System::IO::StreamReader* sr = System::IO::StreamReader::Null;
	 slModel = new System ::Collections::SortedList();
	 System::String* key;
	 System::String* tempStr;
	 int count=0;
	 bool modelName = true;

	 try
	 {
		sr = new System::IO::StreamReader(dbFilePath);
		 
		/*


		while (!System::String::IsNullOrEmpty((tempStr = sr->ReadLine())))
		{
			if(tempStr->Equals("*"))
			{
				count = 0;
				slModel->Add(key,alModelTrans);
			}
			else
			{
				if(count==0)
				{
					key = tempStr;
					alModelTrans = new System::Collections::ArrayList();
					count++;
				}
				else
				{
					alModelTrans->Add(tempStr);
				}
			}
		}
		*/
		while(sr->Peek()>=0)
		{
			tempStr=sr->ReadLine();
			if(tempStr->Equals("*"))
			{
				count = 0;
				slModel->Add(key,alModelTrans);
			}
			else
			{
				if(count==0)
				{
					key = tempStr;
					alModelTrans = new System::Collections::ArrayList();
					count++;
				}
				else
				{
					alModelTrans->Add(tempStr);
				}
			}
			
		}
		sr->Close();

		return slModel;
	 }
	 catch(System::Exception* ex)
	{

		System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"Failed to Load the Model DataBase!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
		exit(0);
	}
}


void RecognitionProcess::SetImageBoundary(int left_x, int right_x,int top_y, int bottom_y)
{
	this->leftX = left_x;
	this->rightX = right_x;
	this->topY = top_y;
	this->bottomY = bottom_y;

	//Setting the training image boundary...	
	//this->ImageBoundarySet(this->leftX,this->rightX,this->topY,this->bottomY);
}


void RecognitionProcess::PrepareWordData(System::String* wordFeatureFile)
{
	FileManipulating* fm = new FileManipulating();
	fm->PrepareData(wordFeatureFile, this->imageArr, this->leftX, this->rightX, this->topY, this->bottomY);
}

System::Collections::ArrayList* RecognitionProcess::RecognizeByHTK()
{
	FileManipulating* fm = new FileManipulating();
	fm->RecognizeByHMM(this->recognitionTempFileDir,this->exeFileDir,this->mmfFilePath,this->mlfFilePath,this->wordNetFilePath,this->dictFilePath,this->HMMListFilePath, this->scriptFilePath); 
	
	System::Collections::ArrayList* al = fm->FetchOutputModels(this->mlfFilePath);

	return al;
}