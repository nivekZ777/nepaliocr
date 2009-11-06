#include ".\externalpostprocessor.h"
 

externalPostProcessor::externalPostProcessor(System::String *applicationPath,System::String *PostProcessorApplicationFileName) //,System::String *inputFileName,System::String *outputFileName)
{
				// String *applicationPath = Application::StartupPath->ToString();
				 
				 applicationPath = applicationPath->Concat(applicationPath,"\\");
				 System::String *applicationName = applicationName->Concat(applicationPath,PostProcessorApplicationFileName);
				 this->outputFileName = System::String::Concat(applicationPath,"rawOutput.txt");

				 
				 try{
				 System::Diagnostics::Process *shellProcess = new System::Diagnostics::Process();
				 shellProcess->StartInfo->FileName = applicationName;
			  
				 
				 
				 shellProcess->StartInfo->CreateNoWindow = true;
				 shellProcess->StartInfo->RedirectStandardError = true;
				 shellProcess->StartInfo->UseShellExecute = false;
				 shellProcess->StartInfo->set_WorkingDirectory(applicationPath);
				 
				 //System::Windows::Forms::MessageBox::Show(shellProcess->StartInfo->get_WorkingDirectory()->ToString());
				 shellProcess->Start();
				 shellProcess->WaitForExit();
				// System::Windows::Forms::MessageBox::Show(applicationName,"running");
				 shellProcess->Close();
				/* if(shellProcess_Exited){
					 System::Windows::Forms::MessageBox::Show("exitted");
				 }*/
				 }
				 catch(System::Exception *ex){
					 System::Windows::Forms::MessageBox::Show("Error running PostProcessor",ex->ToString(),System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
				 }


}
 

System::String* externalPostProcessor::getText(){
	return this->outputFileName;
}
void externalPostProcessor::tryNewProcesor(void){
	 // Start the child process.
	System::Diagnostics::Process *p1 = new System::Diagnostics::Process();
		// Redirect the output stream of the child process.
		p1->StartInfo->UseShellExecute = false;
		p1->StartInfo->RedirectStandardOutput = true;
		p1->StartInfo->FileName = "ocrTextProcessor.exe";
		p1->Start();
		// Do not wait for the child process to exit before
		// reading to the end of its redirected stream.
		// p.WaitForExit();
		// Read the output stream first and then wait.
		System::String *output = p1->StandardOutput->ReadToEnd();
		p1->WaitForExit();

}