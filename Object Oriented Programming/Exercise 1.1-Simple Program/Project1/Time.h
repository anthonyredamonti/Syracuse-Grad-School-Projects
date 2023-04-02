#pragma once

// Fig. 9.1: Time.h
// Time class definition.
// TIme functions are defined in Time.cpp

// prevenet multiple inclusions of header
#ifndef TIME_H
#define TIME_H

class Time {
public:
	explicit Time(int hour = 0, int minute = 0, int second = 0);
	
	// get functions
	void setTime(int hour, int minute, int second); // set hour, minute, and second
	void setHour(int hour);
	void setMinute(int minute);
	void setSecond(int second);
	
	// set functions
	unsigned int getTime() const;
	unsigned int getHour() const;
	unsigned int getMinute() const;
	unsigned int getSecond() const;

	void printUniversal() const; // print time in universal-time format
	void printStandard() const; // print time in standard-time format
private:
	unsigned int hour; // 0-23 (24-hour clock format)
	unsigned int minute; // 0-59
	unsigned int second; // 0-59
};
#endif