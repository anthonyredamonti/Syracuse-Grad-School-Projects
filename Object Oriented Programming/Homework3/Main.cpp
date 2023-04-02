/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554-M401 Object Oriented Programming C++
Syracuse University
HW #3 - Exercise 5.16 p206-207
8/6/2021

Main.cpp

The following program creates an instance of the BarChart 
class and prompts the user to input five values between 1
and 30. If the user attempts to set a number to a value 
outside of this range, an error message will appear, and
the user will be prompted to re-enter a valid number.

The BarChart public member function "printBarChart" will
display a bar chart on the console with a length equal to
the sum of the 5 numbers.

*/

#include <iostream>   // needed for the standard library
#include "BarChart.h"  // defines the BarChart class

// importing objects from the C++ standard library
using std::cin;
using std::cout;
using std::endl;

// print "SU" for Syracuse University on the console
void printSyracuseBanner(); 

int main() {

	// initialize local variable
	int inputNumber{ 0 };

	// print Syracuse Banner
	printSyracuseBanner();

	// information about program
	cout << "Welcome to the bar chart generator!\n" <<
		"The following program takes 5 numbers as input.\n" <<
		"Then a bar chart is printed, the length of which\n" <<
		"is equal to the cumulative sum of the five numbers.\n\n";

	// create new Bar Chart object 
	BarChart barChartObj;

	// prompt the user for five numbers
	cout << "Please enter five numbers with values between " << barChartObj.getMinValue() << " and " << barChartObj.getMaxValue() << ".\n";

	// prompt for each number
	for (int i = 0; i < barChartObj.getVectorSize(); i++) {
		int error{ 0 }; // local error variable
		cout << "Number " << i+1 << ": ";
		cin >> inputNumber;
		error = barChartObj.setNumber(i, inputNumber);
		
		// if there was an error(s), ask for the number again (repeat iteration).
		if ((error == -1) || (error == -2)) {
			i = i - 1;
		}
	}
	
	// print the bar chart
	cout << "BAR CHART PRINTED BELOW\n";
	barChartObj.printBarChart();

}

// print "SU" for Syracuse University on the console
void printSyracuseBanner() {
	cout 
		<< "                   .-----------.            .----.          .----.\n"
		<< "                 /             |            |    |          |    |\n"
		<< "                /    .---------*            |    |          |    |\n"
		<< "               .    /                       |    |          |    |\n"
		<< "               |   |                        |    |          |    |\n"
		<< "               |    .                       |    |          |    |\n"
		<< "                .    *-------.              |    |          |    |\n"
		<< "                 *.            *            |    |          |    |\n"
		<< "                   *----.       *           |    |          |    |\n"
		<< "                          .      *          |    |          |    |\n"
		<< "                          |      |          |    |          |    |\n"
		<< "                         /       /          |    |          |    |\n"
		<< "                .-------*       *           *     *--------*     /\n"
		<< "                |             *              *                  / \n"
		<< "                *----------*                   *--------------*   \n\n";
}