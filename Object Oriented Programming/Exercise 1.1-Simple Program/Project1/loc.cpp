///////////////////////////////////////////////////////////
// loc.cpp
//
// Anthony Redamonti
// 7-30-2021
//
// CIS554 Object Oriented Programming in C++
// Exercise 8_2 - Operator Overloading with non-member 
// functions
//
/*
The following program creates a class called "loc" which
contains objects having data members "latitude" and
"longitude."

The purpose of this program is to demonstrate how to
overload operators so that two loc objects can be added
together using the operators "+" or "+=".//
*/
///////////////////////////////////////////////////////////

#include "loc.h"

// loc constuctor with longitude and latitude data member
// variables initialized.
loc::loc(int lon, int lat)
	: longitude(lon), latitude(lat)
{}

// print the longitude and latitude of the loc object 
// to the console.
void loc::show()
{
	cout << longitude << " ";
	cout << latitude << "\n";
}

// Overload + for loc.
loc loc::operator+(loc op2)
{
	loc temp;

	temp.longitude = op2.longitude + longitude;
	temp.latitude = op2.latitude + latitude;

	return temp;
}

// Overload += for loc.
loc operator+=(loc &op1, loc &op2)
{
	loc temp;
	temp.longitude = op1.longitude + op2.longitude;
	temp.latitude = op1.latitude + op2.latitude;
	return temp;
}
