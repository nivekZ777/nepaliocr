// ocrTextProcessor.cpp : main project file.

#include "stdafx.h"
#include "PostProcessor.h"

using namespace System;


int main(array<System::String ^> ^args)
{
	System::String ^inputText;
	System::String ^processedText;
	String ^arg0,^inputFileName,^outputFileName;
	inputFileName = "rawInput.txt";	  
	outputFileName = "rawOutput.txt";

	System::Collections::IEnumerator ^argEnum = args->GetEnumerator();
	
	System::IO::StreamWriter ^swLog = gcnew System::IO::StreamWriter("PostProcessr.log");

	try{
		//inputFileName = argument 0
		//Reading input file from argument 0
		System::String ^tempStr;
		System::IO::StreamReader ^sr = gcnew System::IO::StreamReader(inputFileName);
		 while(!System::String::IsNullOrEmpty(tempStr = sr->ReadLine())){
			 inputText = inputText->Concat(inputText,tempStr,"\n"); 
			 
		 }
		 sr->Close();
		 Console::Write(inputText);

		 PostProcessor^ pr = gcnew PostProcessor(inputText);
		 swLog->WriteLine("\n---------Input -----------\n");
		 swLog->Write(inputText);
		  swLog->WriteLine("\n---------Output -----------\n");
		 
		 processedText = pr->TextPostProcessor();
		
		 //outputFileName = argument 1
		//Reading input file from argument 1
		 System::IO::StreamWriter ^sw = gcnew System::IO::StreamWriter(outputFileName);
		 sw->Write(processedText);
		 swLog->Write(processedText);
		 swLog->WriteLine("\n--------- Logs -----------\n");
		 sw->Close();
		 swLog->WriteLine("Program Exitted successfully");
		 swLog->Close();
	}
	catch(System::Exception ^ioException1){

		
		swLog->Write("An Error Has Occured");
		//swLog->WriteLine(ioException1->ToString());
		swLog->Close();
		
	}

	
   
	
    return 0;
		 
}
 
 