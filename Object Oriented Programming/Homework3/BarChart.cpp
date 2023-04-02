/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
HW #3 - Exercise 5.16 p206-207
8/6/2021

BarChart.cpp

Below is the "BarChart" class, which is used create a bar
chart. The sum of the five numbers contained in the 
numberVector are used to create the bar chart. The sum will
dictate the length of the bar chart printed to the console.

The constructor initializes the range of acceptable number
values from 1 to 30. 

The getNumber/setNumber public member functions check their
arguments for validity. The possible errors and their 
meaning are described below.

ERROR NUMBER         MEANING
     -1              Selected index argument is outside the
	                 range of acceptable values.
	 -2              Input number value is outside the range
	                 of acceptable number values.

*/

#include <iostream>
#include "BarChart.h"

using std::cout;
using std::endl;

// The BarChart constructor which initializes the private data members.
BarChart::BarChart()
	: minValue{ 1 }, // initialize minimum number value to 1
	maxValue{ 30 },  // initialize maximum number value to 30
	vectorSize{ 5 }, // initialize size of vector to 5
	numberVector(vectorSize) // initialize vector
{}

// get the private data member vectorSize (type const int)
int BarChart::getVectorSize() {
	return(vectorSize);
}

// get the private data member minValue (type const int)
int BarChart::getMinValue() {
	return(minValue);
}

// get the private data member maxValue (type const int)
int BarChart::getMaxValue() {
	return(maxValue);
}

// The data member function which retrieves a number in the vector.
// The index is used to specify the number.
int BarChart::getNumber(int index) {
	// check validity of index
	if (isValidIndex(index)) {
		return(numberVector[index]);
	}
	// invalid index
	else {
		cout << "The index " << index << " is outside the bounds of the size of the vector containing the numbers.\n"
			<< "Please only request valid indices in range 0 to " << vectorSize - 1 << "." << endl;
		return(-1); // error number
	}
}

// The public data member function that sets the value of an index in the numberVector.
int BarChart::setNumber(int index, int inputValue) {
	// if user input index is invalid, print the following message to the console and return.
	if (!isValidIndex(index)) {
		cout << "The index " << index << " is outside the bounds of the size of the vector containing the numbers.\n"
			<< "Please only request valid indices in range 0 to " << vectorSize - 1 << "." << endl;
		return(-1); // error number
	}
	// if user input value is invalid, print the following message to the console and return.
	else if (!isInputNumberValueValid(inputValue)) {
		cout << "The value " << inputValue << " is outside the range of acceptable values.\n"
			<< "Please only set numbers to values in the range " << minValue << " to " << maxValue << "." << endl;
		return(-2); // error number
	}
	// The input index and value are both valid. Set the input index in the numberVector to the input value.
	else {
		numberVector[index] = inputValue;
		return(1); // success
	}
}

// Check if index is valid (in range 0-4)
bool BarChart::isValidIndex(int index) {
	// If index >= 0 and index < vectorSize, index is valid.
	// Return true.
	if ((index >= 0) && (index < vectorSize)) {
		return(true);
	}

	// Return false for invalid index.
	else {
		return(false);
	}
}

// The member function that returns a boolean value.
// If the number is between 1-30, return true. Else return false.
bool BarChart::isInputNumberValueValid(int inputNumber) {
	// number within acceptable range
	if ((inputNumber >= minValue) && (inputNumber <= maxValue)) {
		return true;
	}
	// number not within acceptable range
	else {
		return(false);
	}
}

// The function is only called by getNewBalance()
void BarChart::printBarChart() {
	for (int i = 0; i < vectorSize; i++) {
		for (int j = 0; j < numberVector[i]; j++) {
			cout << "*";
		}
		cout << "\n";
	}
	cout << endl;
}