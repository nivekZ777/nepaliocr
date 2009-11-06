#pragma once
#include "Unit.h"

class Word
{
//private: int WordNo;
private: int TotalUnit;
private: int StartColumn;
private: int EndColumn;

public:

	Unit *Units;

	Word(void)
	{
	}

	///sc -> starting column number of line
	///ec -> ending column number of line
	void set( int sc, int ec )
	{
		this->StartColumn = sc;
		this->EndColumn = ec;
	}
	///Ut -> number of units in this word
	void setUnit(int Ut)
	{
		this->TotalUnit = Ut;
		Units = new Unit[Ut];
	}
	int getStartColumn()
	{
		return this->StartColumn;
	}
	///
	int getEndColumn()
	{
		return this->EndColumn;
	}

	int getTotalUnit()
	{
		return this->TotalUnit;
	}
};
