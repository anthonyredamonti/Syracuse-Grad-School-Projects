// TimeDiff.cpp

#include "TimeDiff.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;

TimeDiff::TimeDiff() {
}

int TimeDiff::SecondsSinceNoon(int& hours, int& minutes, int& seconds) {
	int total_seconds = 0;
	if (ValidateTime(hours, minutes, seconds) == false) { return -1; }
	if (hours >= 12) {
		hours = hours - 12;
	}
	else {
		hours = hours + 12;
	}
	total_seconds = total_seconds + (hours * 3600);
	total_seconds = total_seconds + (minutes * 60);
	total_seconds = total_seconds + seconds;
	return(total_seconds);
}

bool TimeDiff::ValidateTime(int& hours, int& minutes, int& seconds) {
	if ((hours < 0) || (hours > 23) || (minutes < 0) || (minutes > 59) || (seconds < 0) || (seconds > 59)) {
		return false;
	}
	return(true);
}

