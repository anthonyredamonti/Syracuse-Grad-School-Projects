/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
HW #3 - Exercise 5.16 p206-207
8/6/2021

BarChart.h

Below is the "BarChart" class, which is used create a bar
chart. The sum of the five numbers contained in the
numberVector are used to create the bar chart. The sum will
dictate the length of the bar chart printed to the console.

*/

#ifndef BARCHART_H
#define BARCHART_H
#include<vector>

using std::vector;

class BarChart {
public:
	// ------------- PUBLIC DATA MEMBER FUNCTIONS ----------------

	BarChart(); // Constuctor used to initialize private data members.

	// "Get/Set" functions for the vector holding the numbers.
	int getNumber(int index);
	int setNumber(int index, int inputNumber);

	// display the Bar Chart on the console
	void printBarChart();

	// return the vector size containing the numbers
	int getVectorSize();

	// return the minimum value for each number in vector
	int getMinValue();

	// return the maximum value for each number in vector
	int getMaxValue();

private:
	// -----------  PRIVATE DATA MEMBER FUNCTIONS ---------------

	// check if input value is within valid range (1-30)
	bool isInputNumberValueValid(int inputNumber);

	// check if requested index in within valid range (0-4)
	bool isValidIndex(int index);

	// -----------  PRIVATE DATA MEMBER VARIABLES ---------------
	const int vectorSize;
	const int minValue;  // minimum value for each number in vector
	const int maxValue;  // maximum value for each number in vector
	vector<int> numberVector;
};

#endif
