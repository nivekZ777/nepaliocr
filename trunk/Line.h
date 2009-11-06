#pragma once
/**
 *
 * Date 07-01-2008
 *
 * Author Rajesh Pandey
 *
 * license
 * This code is absolutely free to use and modify. The code is provided "as is" with
 * no expressed or implied warranty. The author accepts no liability if it causes
 * any damage to your computer, causes your pet to fall ill, increases baldness
 * or makes your car start emitting strange noises when you start it up.
 * This code has no bugs, just undocumented features!
 * 
 *  
 *
 *  
 *
 */
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
