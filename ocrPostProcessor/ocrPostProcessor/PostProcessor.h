//Author : Rajesh Pandey
//Email: pandey.pandey@gmail.com, rajesh@mpp.org.np
//Sunday October 26, 2008
//Madan Puraskar Pustakalaya
//Program for processing the output provided by Nepali OCR
#pragma once

ref class PostProcessor
{
private: System::String^ processStr;
private: bool IsDependentVowel(wchar_t Vowel);

public:
	PostProcessor(System::String^ textStr);
	

public: System::String^ TextPostProcessor();
		/// end



};
