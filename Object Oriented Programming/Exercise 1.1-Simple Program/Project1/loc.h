///////////////////////////////////////////////////////////
// loc.h
// CIS554 Object Oriented Programming in C++
// Exercise 8_2 - Operator Overloading with non-member 
// functions
//      
// Anthony Redamonti
// 7-30-2021
//
///////////////////////////////////////////////////////////
/*

The following program creates a class called "loc" which
contains objects having data members "latitude" and
"longitude."

The purpose of this program is to demonstrate how to
overload operators so that two loc objects can be added
together using the operators "+" or "+=".

*/

#ifndef LOC_H
#define LOC_H
#include <iostream>
using std::cout;

class loc
{
	friend loc operator+=(loc&op1, loc &op2); // overload operator "+="
	int longitude, latitude; // data member variables

public:
	loc(int lon = 0, int lat = 0); // default constuctor initializing both data member variables to zero.
	void show(); // print latitude and longitude to console
	loc operator+(loc op2); // overload operator "+"
};

#endif
