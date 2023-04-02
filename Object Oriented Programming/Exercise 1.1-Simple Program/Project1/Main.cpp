/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554-M401 Object Oriented Programming C++
Syracuse University
Exercise 8_2 - Operator Overloading with non-member 
functions
               
7/30/2021

Main.cpp

The following program creates a class called "loc" which 
contains objects having data members "latitude" and 
"longitude." 

The purpose of this program is to demonstrate how to
overload operators so that two loc objects can be added
together using the operators "+" or "+=".

The main function below tests the loc class and the
assignment operators.

*/

#include "loc.h"
#include <iostream>
using std::cout;
using std::endl;

// print Syracuse Banner
void printSyracuseBanner();

int main()
{
	// print Syracuse Banner
	printSyracuseBanner();

	// professional looking banner
	cout << "Anthony Redamonti\n" <<
		"Professor Jonathan S. Weissman\n" <<
		"CIS 554 - M401 Object Oriented Programming C++\n" <<
		"Syracuse University\n" <<
		"7/30/2021\n\n";

	loc ob1(10, 20), ob2(5, 30), ob3; // create three loc objects

	// demonstrate constructor
	cout << "Show proper construction of ob1 and ob2" << endl;
	cout << "Object ob1 = ";
	ob1.show(); // displays 10 20
	cout << "Object ob2 = ";
	ob2.show(); // displays 5 30
	cout << endl;

	//demonstrate operator+ 
	cout << "Show operator+" << endl;
	cout << "(ob1 + ob2).show= ";
	(ob1 + ob2).show();
	cout << endl;

	// default operator=
	cout << "Show default assignment operator" << endl;
	cout << "ob3 = ob1 + ob2 = ";
	ob3 = ob1 + ob2;
	ob3.show();
	cout << endl;

	// demonstrate that original loc objects have not been modified
	cout << "Show that original objects have not been modified" << endl;
	cout << "Object ob1= ";
	ob1.show();
	cout << "Object ob2= ";
	ob2.show();
	cout << endl;

	//demonstrate operator+ 
	cout << "Show operator+" << endl;
	cout << "(ob1 += ob2).show= ";
	(ob1 += ob2).show();
	cout << endl;

	// default operator=
	cout << "Show default assignment operator" << endl;
	cout << "ob3 = (ob1 += ob2) = ";
	ob3 = (ob1 += ob2);
	ob3.show();
	cout << endl;

	// demonstrate that original loc objects have not been modified
	cout << "Show that original objects have not been modified" << endl;
	cout << "Object ob1= ";
	ob1.show();
	cout << "Object ob2= ";
	ob2.show();
	cout << endl;
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
		<< "                *----------*                   *--------------*   \n";
}