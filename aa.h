#pragma once

class aakarChecker
{
public:
	System::Collections::SortedList *aakarList;
	System::Collections::ArrayList *keys;
	System::Collections::ArrayList *values;
	aakarChecker(void);
	~aakarChecker(void);
	void put(String *key){
		aakarList->Add(key);
	}
};
