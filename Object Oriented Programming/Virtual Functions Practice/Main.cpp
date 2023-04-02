/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
HW #5
8/18/2021

Main.cpp

The following program creates instances of the ProBaseballPlayer
class derived from the ProfessionalAthlete 
class.
*/

#include <iostream>   // needed for the standard library
#include <iomanip>    // needed for setw() and setfill()
#include <string>
#include "ProfessionalAthlete.h"  // defines the ProfessionalAthlete class
#include "ProBaseballPlayer.h"    // defines the ProBaseballPlayer class

// importing objects from the C++ standard library
using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::setfill;

// print "SU" for Syracuse University on the console
void printSyracuseBanner(); 

int main() {



	// print Syracuse Banner
	printSyracuseBanner();

	// information about program
	cout << "Welcome to the Athlete Comparison Program!\n" <<
		"The following program asks the user for athlete's\n" <<
		"name, \n\n" <<
		"The user will be asked a question and prompted for\n" <<
		"an answer. Once the user has provided 10 answers, the\n" <<
		"program will provide feedback on their performance.\n" <<
		"The program will then start from the beginning.\n\n";

	// initialize local variables
	vector<string>* pastTeamsString;


	// create new object 

}

// Print "SU" for Syracuse University on the console.
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