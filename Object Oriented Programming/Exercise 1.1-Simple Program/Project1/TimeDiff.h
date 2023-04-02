// TimeDiff.h

#pragma once
#include<string>

class TimeDiff
{
public:
	explicit TimeDiff();
	int SecondsSinceNoon(int& hour, int& minute, int& second);
private:
	bool ValidateTime(int& hour, int& minute, int& second);
};
