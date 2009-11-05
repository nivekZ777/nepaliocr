
#include "StdAfx.h"
#include "HShell.h"
#include "FileManipulating.h"


#define FRAME_HT 40
#define FRAME_WD 8
#define PI 3.14

#undef MessageBox

using namespace std;
using namespace System;

FileManipulating::FileManipulating(void)
{
	this->dctArr = new float * [FRAME_HT];
	for(int i=0;i<FRAME_HT;i++)
	{
		dctArr[i] = new float[FRAME_WD];
	}
}
/*
System::String* string_handling(System::String *temp1,System::String *temp2,System::String *temp3)
{
temp2->Concat(temp3);
temp1->Concat(temp2);
return(temp1);

}

System::String* string_handling(System::String *temp1,System::String *temp2)
{

//tempo2->Concat(tempo3);
temp1->Concat(temp2);
return(temp1);
}

*/
System::String* FileManipulating::GetModelName(System::String* filePath)
{

	try
	{
		System::IO::StreamReader* sr = System::IO::StreamReader::Null;
		System::IO::StreamWriter* sw = System::IO::StreamWriter::Null;
		System::String* tempStr;
		



		// getting the model name
		if(!System::IO::File::Exists(filePath))
		{
			sw = new System::IO::StreamWriter(filePath);
			sw->Write("h0");
			sw->Close();
		}

		sr = new System::IO::StreamReader(filePath);
		tempStr=sr->ReadLine();
		if (tempStr->Length==0)
		//if(System::String::IsNullOrEmpty((tempStr = sr->ReadLine())))
		{
			System::Windows::Forms::MessageBox::Show("No model name specified in the file","Can't get the model name!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
			exit(0);			
		}
		sr->Close();
		return tempStr;
	}
	catch(System::Exception* ex)
	{
		System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"Can't get the model name!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
		exit(0);
	}
}


void FileManipulating::CreatePrototypeFile(System::String* fromFile, System::String* toFile, System::String* modelName)
{
	System::IO::StreamWriter* sw = System::IO::StreamWriter::Null;
	System::IO::StreamReader* sr = System::IO::StreamReader::Null;
    System::String* tempStr;
    bool firstLine = true;
	System::String *mytmp;

	System::Windows::Forms::MessageBox::Show(fromFile->ToString(),"From: yup u got it!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
	System::Windows::Forms::MessageBox::Show(toFile->ToString(),"To: yup u got it!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
	System::Windows::Forms::MessageBox::Show(modelName->ToString(),"ModelName: yup u got it!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
		

    try
    {
        // read the content and store the specific text to the prototype file
        sr = new System::IO::StreamReader(fromFile);
        sw = new System::IO::StreamWriter(toFile);
		

		//tempStr=sr->ReadLine();

		while(sr->Peek()>=0)
		{
			tempStr=sr->ReadLine();
			if(firstLine)
			{
				mytmp=mytmp->Concat("~h \"",modelName,"\"");
				sw->WriteLine(mytmp);
				firstLine = false;

			}
			else
			{
			sw->WriteLine(tempStr);
			}
			sw->Flush();
		}

		/*
		tempStr= sr->ReadToEnd();
	
		mytmp=mytmp->Concat("~h \"",modelName,"\"");
		sw->WriteLine(mytmp);
		sw->WriteLine(tempStr);
        // while (!System::String::IsNullOrEmpty((tempStr = sr->ReadLine())))
        
		/*
		tempStr=sr->ReadLine();
		while(tempStr->Length!=0)
		{
			//
			
            if (firstLine)
            {
				// just change the first line according to the appropriate model name
                mytmp=mytmp->Concat("~h \"",modelName,"\"");
				sw->WriteLine(mytmp);
				//sw->WriteLine("~h \"" + modelName + "\"");
                firstLine = false;
            }
            else
            {
				tempStr="";
				tempStr= sr->ReadLine();
				sw->WriteLine(tempStr);
            }
			
        }
*/
		System::Windows::Forms::MessageBox::Show("ya looks gud","Prototype file creation success!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
		

		sr->Close();
		sw->Close();
		
    }
    catch (System::Exception* excp)
    {
		System::Windows::Forms::MessageBox::Show(excp->Message->ToString(),"Can't Create Prototype File!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
		exit(0);
    }
}



void FileManipulating::CreateHMMFile(System::String *exeFileDir, System::String *outputHmmDir, System::String *prototypeFile, System::String *trainFile)
{
	try
	{

		System::String* batchFileName = batchFileName->Concat(outputHmmDir, "\\" ,"_HInit.bat");
		System::IO::StreamWriter* sw = new System::IO::StreamWriter(batchFileName);
		System::String* tempStr = "";
		
		System::String* HHH="HInit";

		System::String* invComa="\"";

		// building the associate command for the initialization
		tempStr=tempStr->Concat(tempStr,invComa, exeFileDir ,HHH, invComa);
		//tempStr->a
		tempStr=tempStr->Concat(tempStr," -m 1"," -M ");			// required for training from single sample
		//tempStr += " -M ";
		tempStr=tempStr->Concat(tempStr,invComa, outputHmmDir , invComa,(String*)" ");
		//tempStr += "\"" + outputHmmDir + "\"";
		//tempStr += " ";
		
		tempStr=tempStr->Concat(tempStr,invComa, prototypeFile,invComa,(String*)" ");
		//tempStr += "\"" + prototypeFile + "\"";
		//tempStr += " ";
		
		tempStr=tempStr->Concat(tempStr,invComa, trainFile , invComa);
		//tempStr += "\"" + trainFile + "\"";
		
		sw->Write(tempStr);
		sw->Close();
		
		System::Windows::Forms::MessageBox::Show("Create HMM File on Process","ya sounds gud!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
		
		// create a process and execute 
		System::Diagnostics::Process *p = new System::Diagnostics::Process();
		p->StartInfo->FileName = batchFileName;
		p->Start();
		p->WaitForExit();
	}
	catch (System::Exception* excp)
    {
		//System::Windows::Forms::MessageBox::Show
		System::Windows::Forms::MessageBox::Show(excp->Message->ToString(),"Can't Create HMM Training File!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
		exit(0);
    }	
}

void FileManipulating::AddModelDefToMasterModelFile(System::String *mmfFilePath, System::String *fromHmmFile)
{
	try
	{
		System::IO::StreamReader* sr = System::IO::StreamReader::Null;
		System::IO::StreamWriter* sw = System::IO::StreamWriter::Null;
		System::String* tempStr;
		int lineNum = 0;
		System::Windows::Forms::MessageBox::Show(mmfFilePath,"MMF FilePath: ya sounds gud!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
		System::Windows::Forms::MessageBox::Show(fromHmmFile,"HMM File: ya sounds gud!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
		
		// if the file does not exist then directly copy the entire content of the prototype file
		if(!System::IO::File::Exists(mmfFilePath))
		{
			System::IO::File::Copy(fromHmmFile,mmfFilePath);
		}
		else
		{
			sw = System::IO::File::AppendText(mmfFilePath);
			sr = new System::IO::StreamReader(fromHmmFile);
			
			// Add the content from line number 4 of the prototype file
			//while (!System::String::IsNullOrEmpty((tempStr = sr->ReadLine())))
			tempStr= sr->ReadLine();

			System::Windows::Forms::MessageBox::Show("working gud till here!","HMM File: ya sounds gud!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
       // while (!System::String::IsNullOrEmpty((tempStr = sr->ReadLine())))
        
			
		/*while(tempStr->Length!=0)
		{
			//tempStr= sr->ReadLine();
			
				lineNum++;
				if (lineNum<4)
				{
				}
				else
				{
					sw->WriteLine(tempStr);
				}
				tempStr= sr->ReadLine();
				
		}*/

		while(sr->Peek()>=0)
		{
			tempStr=sr->ReadLine();
            lineNum++;
			
			if(lineNum<3)
			{}

			else
			{
			sw->WriteLine(tempStr);
			}
			sw->Flush();
		}

		sr->Close();
		sw->Close();
	}
	}
	catch(System::Exception* ex)
	{
		System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"HMM Model Name adding to MMF file Failed!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
		exit(0);
	}
}

void FileManipulating::AddModelNameToHMMListFile(System::String *hmmListFile, System::String *hmmNameFile, System::String *modelName)
{
	System::IO::StreamWriter* sw = System::IO::StreamWriter::Null;
	try
	{
		// add model name to the HMM List file
		sw = System::IO::File::AppendText(hmmListFile);
		sw->WriteLine(modelName);
		sw->Close();

		// add model name to the HMM Name File
		sw = new System::IO::StreamWriter(hmmNameFile);
		sw->Write(modelName);
		sw->Close();
	}
	catch(System::Exception* ex)
	{
		System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"HMM Model Name adding to HMM List file Failed!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
		exit(0);
	}
}

void FileManipulating::BuildWordNetwork(System::String *gramFile, System::String *dictFile, System::String *transFile, System::String *wdnetFileDir, System::String* execpath, System::String* modelName)
{
	System::IO::StreamWriter* sw = System::IO::StreamWriter::Null;
	try
	{
		// add model name to the grammer file
		System::String* text = "";
		System::String* tmp = "";
		// check the existance of grammer file
		if(!System::IO::File::Exists(gramFile))
		{
			sw = new System::IO::StreamWriter(gramFile);
			System::String* wd="$WORD = ";
			System::String* semiColon=";";
			System::String* enter="\n";
			tmp=tmp->Concat(wd, modelName ,semiColon,enter,(String*)"([$WORD])");
			text=tmp;
			//text = "$WORD = "+ modelName + ";" + "\n" + "([$WORD])";
			sw->Write(text);
			sw->Close();
		}
		else
		{
			// create streamreader
			System::IO::StreamReader* sr = new System::IO::StreamReader(gramFile);
			System::String* line;
			System::String *tmp;
			int  k;


			

			// Read and display lines from the file until the end of 
			// the file is reached.
			//line = sr->ReadLine();
			//while (!System::String::IsNullOrEmpty(line = sr->ReadLine())) 
			while(sr->Peek()>=0)
			{
				//tempStr=sr->ReadLine();
            	line= sr->ReadLine();

				k = line->IndexOf(";");
				if(k < 0 )
				{
					//text += line+"\n";
					//String * tmp;
					text = text->Concat(text,line,(String*)"\n");
				}
				else
				{
					line = line->Substring(0,k);
					
					text=text->Concat(text,line ,(String*)"|",modelName,(String*)";" ,(String*)"\n");
					
					//text += line + "|" + modelName + ";" + "\n";
				}
				//line=sr->ReadLine();
			}



			sr->Close();
			// write to the grammer file
			sw = new System::IO::StreamWriter(gramFile);
			sw->Write(text);
			sw->Close();
		}
		System::Windows::Forms::MessageBox::Show("Building Network working gud till here!","ya sounds gud!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
		// add model name to the dictionary file
		
		sw = System::IO::File::AppendText(dictFile);
		modelName = modelName->Concat(modelName,(String*)" [",modelName,(String*)"] ",modelName);
		
		//modelName = string_handling(modelName," [" + modelName + "] ",modelName);
		
		sw->WriteLine(modelName);
		sw->Close();

		// add model name & associated transcription to the transcripton database file

		// build the world network
		/*1. Creating _HParse.bat*/
		System::String* parseFile = parseFile->Concat(wdnetFileDir,(String*)"_HParse.bat");
		//System::String* tmp="";
		//text=tmp->Concat(execpath,"HParse"," ","\"",gramFile,"\""," ","\"",wdnetFileDir,"net.slf","\"");
		sw = new System::IO::StreamWriter(parseFile);
		System::String* invComma="\"";
		text=invComma;
		text = text->Concat(text,execpath,(String*)"HParse",invComma,(String*)" ");
		text = text->Concat(text,invComma,gramFile,invComma,(String*)" ");
		text = text->Concat(text,invComma,wdnetFileDir,(String*)"net.slf",invComma);

		/*text=text->Concat(text,"\"",execpath,"HPARSE","\""," ");
		text=text->Concat(text,"\"",gramFile,"\""," ");
		text=text->Concat(text,"\"",wdnetFileDir);
		text=text->Concat(text,"net.slf","\"");
		/*text = "\"" + execpath + "HParse" + "\"" + " ";
		text += "\"" + gramFile + "\"" + " ";
		text += "\"" + wdnetFileDir + "net.slf" + "\"";*/
		sw->Write(text);
		sw->Close();
		
		/*2. Creating _HSGen.bat*/
		//System::String* genFile = wdnetFileDir + "_HSGen.bat";
		System::String* genFile;
		genFile=genFile->Concat(wdnetFileDir ,"_HSGen.bat");
		sw = new System::IO::StreamWriter(genFile);
//		System::String* invComma="\"";
		text=invComma;
		text = text->Concat(text,execpath,(String*)"HSGen",invComma,(String*)" ");
		text = text->Concat(text,invComma,wdnetFileDir,(String*)"net.slf",invComma,(String*)" ");
		text = text->Concat(text,invComma,dictFile,invComma);

		/*text->Concat("\"" , execpath , "HSGen");
		text->Concat("\"" , " ","\"");
		text->Concat(wdnetFileDir , "net.slf" , "\"" , " ");
		text->Concat("\"", dictFile, "\"");
*/
		sw->Write(text);
		sw->Close();

		// create a process and execute the batch files
		System::Diagnostics::Process* p = new System::Diagnostics::Process();
		// execute _HParse.bat
		p->StartInfo->FileName = parseFile;
		p->Start();
		p->WaitForExit();

		// execute _HSGen.bat
		p->StartInfo->FileName = genFile;
		p->Start();
		p->WaitForExit();

		System::Windows::Forms::MessageBox::Show("Building Network success!","ya sounds gud!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);

	}
	catch(System::Exception* ex)
	{
		System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"Building Word Network Failed!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
		exit(0);
	}
}

void FileManipulating::RecognizeByHMM(System::String* recDir, System::String* execFile, System::String *mmfFile, System::String *mlfFile, System::String *wdNetFile, System::String *dictFile, System::String* hmmListFile, System::String *scriptFile)
{
	try
	{
		System::String* batchFileName = batchFileName->Concat(recDir,"_HVite.bat");
		//System::String* batchFileName;
		//batchFileName->Concat(recDir,"_HVite.bat");
		System::IO::StreamWriter* sw = new System::IO::StreamWriter(batchFileName);
		System::String* tempStr = "";

		/*System::String *a,*b,*c;
		a="ashish";
		b="lamichhan";
		a->Concat("ashish");*/


		// building the associate command for the initialization
		System::String* invComma="\"";
		tempStr = tempStr->Concat(tempStr,invComma,execFile,(String*)"HVite",invComma);
		tempStr = tempStr->Concat(tempStr," -H ");			// required for training from single sample
		tempStr = tempStr->Concat(tempStr,invComma,mmfFile,invComma);
		tempStr = tempStr->Concat(tempStr," -i ");
		tempStr = tempStr->Concat(tempStr,invComma,mlfFile,invComma);
		tempStr = tempStr->Concat(tempStr," -w ");
		tempStr = tempStr->Concat(tempStr,invComma,wdNetFile,invComma);
		tempStr = tempStr->Concat(tempStr,(String*)" ");
		tempStr = tempStr->Concat(tempStr,invComma,dictFile,invComma);
		tempStr = tempStr->Concat(tempStr,(String*)" ");
		tempStr = tempStr->Concat(tempStr,invComma,hmmListFile,invComma);
		tempStr = tempStr->Concat(tempStr," -S ");
		tempStr = tempStr->Concat(tempStr,invComma,scriptFile,invComma);

		/*tempStr->Concat("\"" , execFile , "HVite" , "\"");
		tempStr->Concat(" -H ","\"" , mmfFile , "\"");
		tempStr->Concat(" -i ","\"" , mlfFile , "\"");
		tempStr->Concat(" -w ","\"" , wdNetFile , "\"");
		tempStr->Concat(" ","\"" , dictFile , "\"");
		tempStr->Concat(" ","\"" , hmmListFile , "\"");
		tempStr->Concat(" -S ","\"" , scriptFile ,"\"");
*/
		
		sw->Write(tempStr);
		sw->Close();

		// create a process and execute 
		System::Diagnostics::Process* p = new System::Diagnostics::Process();
		p->StartInfo->FileName = batchFileName;
		p->Start();
		p->WaitForExit();
	}
	catch (System::Exception* excp)
    {
		System::Windows::Forms::MessageBox::Show(excp->Message->ToString(),"Can't Create/Execute Viterbi Decoder!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
		exit(0);
    }
}

System::Collections::ArrayList* FileManipulating::FetchOutputModels(System::String *mlfFilePath)
{
	System::IO::StreamReader* sr = System::IO::StreamReader::Null;
	System::Collections::ArrayList* alWord = new System::Collections::ArrayList();

	System::String* tempStr;
	System::String* text;
	int lineNo = 0;

	try
	{
		sr = new System::IO::StreamReader(mlfFilePath);
		text = "";
		int index = 0;
		int stIndex = 0;
		int enIndex = 0;
		int length = 0;
		System::String* str;

		//tempStr=sr->ReadLine();
		//while(!System::String::IsNullOrEmpty(tempStr = sr->ReadLine()))
		while (sr->Peek()>=0)
		{
			tempStr=sr->ReadLine();
			
			lineNo++;
			if(lineNo==3)
			{
				index = tempStr->IndexOf(" ",0) + 1;		// omit first word
				stIndex = tempStr->IndexOf(" ",index) + 1;	// omit second word
				enIndex = tempStr->IndexOf(" ",stIndex);
				length = enIndex - stIndex;
				str = tempStr->Substring(stIndex,length);
				//text += str + "\n";
				text=text->Concat(text,str,(String*)"\n");
				lineNo = 0;							
				alWord->Add(str);
			}
			//tempStr=sr->ReadLine();
		}
		sr->Close();

		return alWord;
	}
	catch(System::Exception* ex)
	{
		System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"Error in Reading MLF File",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
		exit(0);
	}
}

void FileManipulating::PrepareData(System::String* dataFileName, int **imageArr, int leftX, int rightX, int topY, int bottomY)
{
	try{
		int frameWidth = 8;		// width of each window
		int frameHeight = 40;	// height of each window

		int imWidth;			// width of the image
		int imHeight;			// height of the image

		int NoOfWindow = 0;		// contain the number of frame
		float list[150][320];	// contain the information of each frame in an one dimentional float array
		int size_L = 0;	

		// Getting the actual width and height of the image and setting it into the window
		if((((rightX - leftX) +1 ) % frameWidth) == 0)
		{
			imWidth = (rightX - leftX) + 1 ;
		}
		else
		{
			imWidth = (((rightX - leftX) + 1) + (8 - (((rightX - leftX)+1) % 8)) );
		}

		if((((bottomY -  topY) + 1 ) % frameHeight) == 0)
		{
			imHeight = (bottomY - topY) + 1;
		}
		else
		{
			imHeight = (((bottomY -  topY) + 1) + (40 - (((bottomY - topY) + 1)  % 40)) );
		}

		// Declare and set the proper size of the windowz
		signed int ** Window;	
		Window = new signed int *[imHeight];
		for (int j = 0; j< imHeight ; j++)
		{
			Window [j] = new signed int [imWidth];
		}

		// initialize the array with 1
		for(int i = 0; i < imHeight ;i++ )
		{
			for(int k = 0; k < imWidth ; k++)
			{
				Window[i][k]=1;
			}
		}
		
		
		//mapping the image into the wordarray
		for (int i=topY ; i<=bottomY; i++ )
		{
			for (int j=leftX; j<=rightX; j++ )
				Window[i-topY][j-leftX] = imageArr[i][j];
		}

		//Working with DCT for extracting feature
		int c =  0;
		int win_y1 = 0;
		int win_y2 = 40;
		int win_x1 = 0;
		int win_x2 =win_x1 + 8 ;
		int MaxWinCount = (imHeight / 40 ) * (imWidth / 8);
		

		for(int a = win_x1   ; a < win_x2 ; a++)
		{
			int d = 0;
			for(int b = win_y1; b < win_y2; b++)
			{  
				dctArr[d][c]= Window[b][a];
				d++;
			}
			c++;
			if(d==40 && c==8)
			{
				// checking for the height constrain
				if( win_y2 < imHeight - 1)
				{
					a = win_x1 -1;
				}

				win_y2 = win_y2 + 40;
				win_y1 = win_y1 + 40;
				
				// applying DCT calculation on each pixel
				ApplyDCT();

				NoOfWindow++;
				int val;
				int k1=0;
				for(int p = 0; p < FRAME_HT ;p++ )
				{
					for(int j=0;j<FRAME_WD;j++)
					{
						// building a feature vector hat contain the DCT info of each window
						list[size_L][k1]=dctArr[p][j];
						k1++;
					}
				}
				size_L++;
			}
			if( c== 8)
			{
				c=0;
			}
			if(MaxWinCount != NoOfWindow &&  a+1 >= win_x2)//setting windows 
			{
				if( win_y2 - 40  == imHeight )
				{
					win_y1 = 0;
					win_y2 = 40;
					win_x1 =win_x2;
					win_x2 = win_x2 + 8;
					a = win_x1 -1 ;

				}
			}
			else if (MaxWinCount == NoOfWindow )
			{
				break;
			}
		} 

		//***************************************************************************

		// required for dynamic prototyping
		this->numOfFrame = NoOfWindow;
		
		int Header1[2];
		Header1[0] = NoOfWindow;
		Header1[1] = 1000;
		short Header2[2];
		Header2[0] = 4 * 320;
		Header2[1] = 9;
		FILE *file; 
		char *FileName = new char[9];
		
		flag = FALSE ;
		//flag = FALSE;
//		flag=FALSE;
		vaxOrder = TRUE;
		IOFilter filter = NoOFilter ;

		
		// training file	
		//int len = dataFileName->Length;
		int len=dataFileName->Length;
		
		//char userFile[500];
		char *userFile;
		userFile=new char[500];

//		char ashish[500];
		//std::string *as;
		//as->
		
//		System::String sdf;
//		sdf.get_Chars(i);
		
		
		for(int i=0;i<len;i++)
		{
			//userFile[i] = (char)dataFileName[i];
			userFile[i] = dataFileName->get_Chars(i);
		}
		userFile[len] = '\0';
		

		file = FOpen(userFile, filter, &flag);
		//System::Windows::Forms::MessageBox::Show("ya u r rocking till 1!","yup u got it !!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);

		//file = FOpen(userFile, filter, 0);
		WriteInt(file, Header1, 2 , TRUE); 
		WriteShort(file,Header2, 2 , TRUE);

		//System::Windows::Forms::MessageBox::Show("ya u r rocking till 2!","yup u got it !!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);

		for(int ad = 0; ad < NoOfWindow; ad++)
		{
			for(int af = 0; af < 320; af ++)
			{
				list[ad][af] = list[ad][af] + 8;
				WriteFloat(file,&list[ad][af],1,TRUE);
			}
		}
		//FClose(file, flag);
		FClose(file, flag);
	}
	catch(System::NullReferenceException* ex)
	{
		System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"Error",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
		exit(0);
	}
}

void FileManipulating::ApplyDCT()
{
  float cucv, temp;

	for (int u=0;u<FRAME_HT;u++)
    {
		for (int v=0;v<FRAME_WD;v++)
		{
			if (u==0 && v==0) cucv = 1/1.4142135623730; else cucv = 1;
			dctArr[u][v] = 0.081649658092772603273242802490226 * cucv * (float)Fdct(u, v);
		}
    }
}

float FileManipulating::Fdct(int u,int v)
{
  float res = 0;
  for (int i = 0 ; i < FRAME_HT ; i++ )
  {
	  for (int j = 0 ; j < FRAME_WD ; j++ )
	  {
		  res += (dctArr[i][j] * cos( ((2*i + 1)*u*PI) / (2 * FRAME_HT) ) * cos( ((2*j + 1)*v*PI) / (2* FRAME_WD) ));	  
	  }
  }
  return res;
}

