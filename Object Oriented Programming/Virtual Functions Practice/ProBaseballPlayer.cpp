/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
HW #5
8/18/2021

ProBaseballPlayer.cpp

Below is the "ComputerAssistedInstruction" class, which
teaches the user various levels of arithmetic. The user
will set the arithmetic type and difficulty level before
beginning.

*/

#include <iostream>
#include <iomanip>
#include <vector> // needed for string operator vector
#include "ProfessionalAthlete.h"
#include "ProBaseballPlayer.h"

using std::cout;
using std::endl;
using std::vector;
using std::fixed;
using std::setprecision;

// The ProBaseballPlayer constructor which initializes the private data members
ProBaseballPlayer::ProBaseballPlayer(string inputFirstName, string inputLastName, double inputAnnualSalary, 
	string inputTeam, int inputFieldPosition, int inputSkillLevel)
	: ProfessionalAthlete(inputFirstName, inputLastName, "MLB", inputAnnualSalary, inputSkillLevel),
	currentTeam(inputTeam),
	fieldPosition(inputFieldPosition)
{
	positionStringsArray = { "Pitcher", "Catcher", "First Baseman", "Second Baseman", "Third Baseman", "Shortstop", "Left Fielder", "Center Fielder", "Right Fielder" };
	setFieldPositionString();
}

// virtual destructor
ProBaseballPlayer::~ProBaseballPlayer(){
	// nothing to do at this time.
}

// retrieve the baseball player's field position
int ProBaseballPlayer::getFieldPosition() {
	return fieldPosition;
}

void ProBaseballPlayer::setFieldPosition(int inputFieldPosition) {
	if ((inputFieldPosition < 1) || (inputFieldPosition > 9)) {
		cout << "\nThe field position is not between 1 and 9.";
	}
	else {
		fieldPosition = inputFieldPosition;
	}
}

// Use a for loop to search through the position strings array for a match.
// When found, assign the string to the baseball player's field position string.
void ProBaseballPlayer::setFieldPositionString() {
	for (int i = 0; i < positionStringsArray.size(); i++) {
		if (fieldPosition - 1 == i) {
			fieldPositionString = positionStringsArray[i];
		}
	}
}

// return a reference to the past teams vector
vector<string>* ProBaseballPlayer::getPastTeamsVector() {
	vector<string>* pntrPastTeams = &pastTeams;
	return(pntrPastTeams);
}

// define pure virtual class to print the stats of the player
void ProBaseballPlayer::printStats() {
	cout << "\nHi! My name is " << getFirstName() << " " << getLastName() << '.'
		<< "\nI am a " << fieldPositionString << " for the " << currentTeam << " in the " << getOrganization() << '.'
		<< "\nI make $" << fixed << setprecision(2) << getAnnualSalary() << " per year."	<< '\n';
}