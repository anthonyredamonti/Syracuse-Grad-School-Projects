// Fig. 9.2: Time.cpp
// Time class member-function definitions.
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "Time.h"

using std::cout;
using std::endl;
using std::setw;
using std::setfill;
using std::invalid_argument;

Time::Time(int hour, int minute, int second)
{
	setTime(hour, minute, second);
}

// set new Time value using universal time
void Time::setTime(int input_hour, int input_minute, int input_second) {
	setHour(input_hour);
	setMinute(input_minute);
	setSecond(input_second);
}

void Time::setHour(int input_hour) {
	if ((input_hour >= 0) && (input_hour < 24)) {
		hour = input_hour;
	}
	else {
		throw invalid_argument("hour was out of range");
	}
}

void Time::setMinute(int input_minute) {
	if ((input_minute >= 0) && (input_minute < 60)) {
		minute = input_minute;
	}
	else {
		throw invalid_argument("minute was out of range");
	}
}

void Time::setSecond(int input_second) {
	if ((input_second >= 0) && (input_second < 60)) {
		second = input_second;
	}
	else {
		throw invalid_argument("second was out of range");
	}
}

unsigned int Time::getHour() const{
	return(hour);
}

unsigned int Time::getMinute() const{
	return(minute);
}

unsigned int Time::getSecond() const{
	return(second);
}

void Time::printUniversal() const {
	cout << setfill('0') << setw(2) << hour << ":"
		<< setw(2) << minute << ":" << setw(2) << second << endl;
}

void Time::printStandard() const {
	cout << ((hour == 0 || hour == 12) ? 12 : hour % 12) << ":"
		<< setfill('0') << setw(2) << minute << ":" << setw(2)
		<< second << (hour < 12 ? "AM" : "PM") << endl;
}