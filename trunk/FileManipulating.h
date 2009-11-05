#pragma once
#include<iostream>




using namespace std;
public __gc class FileManipulating
{
public:
	// attributes
	float **dctArr; // dct array
	int numOfFrame;

	// constructor
	FileManipulating(void);
	
	/* Methods */

	// For Training
	System::String* GetModelName(System::String* filePath);
	void CreatePrototypeFile(System::String* Fromfile, System::String* Tofile, System::String* modelName);
	void CreateHMMFile(System::String* exeFileDir,System::String* outputHmmDir,System::String* prototypeFile,System::String* trainFile);
	void AddModelDefToMasterModelFile(System::String* mmfFilePath, System::String* fromHmmFile);
	void AddModelNameToHMMListFile(System::String* hmmListFile, System::String* hmmNameFile, System::String* modelName);
	void BuildWordNetwork(System::String* gramFile, System::String* dictFile, System::String* transFile, System::String* wdnetFileDir, System::String* execpath, System::String* modelName);

	// For both Training and Recognition
	void PrepareData(System::String* dataFileName, int **imageArr, int leftX, int rightX, int topY, int bottomY);

	// For Recognition
	void RecognizeByHMM(System::String* recDir, System::String* execFile, System::String* mmfFile, System::String* mlfFile, System::String* wdNetFile, System::String* dictFile, System::String* hmmListFile, System::String* scriptFile);
	System::Collections::ArrayList* FetchOutputModels(System::String* mlfFilePath);

	// apply DCT
	void ApplyDCT();
	float Fdct(int u, int v);
};
