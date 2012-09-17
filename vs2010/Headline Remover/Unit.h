#pragma once

class Unit
{

private: int StartColumn;
private: int EndColumn;

public:

	Unit(void)
	{
	}

	///sc -> starting column number of Unit
	///ec -> ending column number of Unit
	void set(int sc, int ec)
	{
		this->StartColumn = sc;
		this->EndColumn = ec;
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

};
