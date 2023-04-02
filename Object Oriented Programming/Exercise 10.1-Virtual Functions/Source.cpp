///////////////////////////////////////////////////////////
/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
Exercise 10_2 - Abstract Classes
8/9/2021

Source.cpp

The following program is an example of abstract classes
within polymorphism. It creates instances of the student 
and employee objects and calls their getCommunityMemberType 
functions and prints the results to the console.

*/
///////////////////////////////////////////////////////////

#include "CommunityMember.h"
#include "Employee.h"
#include "Student.h"
#include <iostream>
using std::cout;

// print member type of the community member pointer
void PrintMemberType(CommunityMember*);

// print "SU" for Syracuse University on the console
void printSyracuseBanner();

int main()
{
	// print Syracuse Banner
	printSyracuseBanner();

	// professional looking banner
	cout << "The following program demonstrates abstract classes by using pure virtual\n"
		<< "functions. Instances of the student and employee classes are created. Their\n" 
		<< "public data member functions \"getCommunityMemberType()\" are called and\n"
		<< "the results are printed to the console.\n\n";

	// initialize some CommunityMember objects
	Student taylorSwift("Syracuse University", "Taylor", "Swift", 1234, "Music", 4.0);
	Employee carrieUnderwood("Syracuse University", "Carrie", "Underwood", 5678, "Country Singer", 1000000);

	cout << taylorSwift.getCommunityMemberType() 
		<< carrieUnderwood.getCommunityMemberType();

	return 0;
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