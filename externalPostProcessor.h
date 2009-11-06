#pragma once

public __gc class externalPostProcessor
{
public:
	externalPostProcessor(System::String *applicationPath,System::String *PostProcessorApplicationFileName);
public: 
	void tryNewProcesor(void);
	 
public: System::String* getText();
private:
	 
	System::String *inputFileName, *outputFileName;
	 
	System::String *outputString;
	
	 
	 
};
