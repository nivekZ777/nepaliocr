#ifndef LINE_H
#define LINE_H
#pragma once
#include "Word.h"

class Line
{
//private: int LineNo;
private: int TotalWord;
private: int StartRow;
private: int EndRow;

public:
	Word *Words;

	Line(void)
	{
	}
	
	///sr -> starting row number of line
	///er -> ending row number of line
	void set( int sr, int er)
	{
		
		this->StartRow = sr;
		this->EndRow = er;
	
	}
	///Wd -> number of words in this line
	void setWord( int Wd )
	{
		this->TotalWord = Wd;
		this->Words = new Word[Wd];
	}
	
	int getStartRow()
	{
		return this->StartRow;
	}
	///
	int getEndRow()
	{
		return this->EndRow;
	}
	int getTotalWord()
	{
		return this->TotalWord;
	}
};
#endif
