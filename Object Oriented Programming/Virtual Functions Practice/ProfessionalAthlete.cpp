/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
HW #5
8/18/2021

ComputerAssistedInstruction.cpp

Below is the "ComputerAssistedInstruction" class, which
teaches the user various levels of arithmetic. The user
will set the arithmetic type and difficulty level before
beginning.

The setQuestion() public data member function generates
a new question and returns that question to the user.
The setQuestion() function calls the helper function
updateRandNum1AndRandNum2() to set private data members
randomNumber1 and randomNumber2. It also calls helper
function calculateCorrectAnswer() to calculate the 
correct answer to the new question.

The rand() function is limited by RAND_MAX, which is 
library-dependent but is guaranteed to be at least 
32767. Therefore, the private data member variable,
maxDifficultyLevel, is set to 5 (5 digits max).

*/

#include <iostream>
#include <iomanip>
#include "ProfessionalAthlete.h"

using std::cout;
using std::setprecision;
using std::fixed;

// The ProfessionalAthlete constructor which initializes the private data members
ProfessionalAthlete::ProfessionalAthlete(string inputFirstName, string inputLastName,
	string inputOrganization, double inputAnnualSalary, int inputSkillLevel)
	: organization(inputOrganization),
	firstName(inputFirstName),
	lastName(inputLastName),
	annualSalary(inputAnnualSalary),
	maxSkillLevel(1000),
	minSkillLevel(0)
{
	setSkillLevel(inputSkillLevel);
}

// retrieve the professional athlete's first name
string ProfessionalAthlete::getFirstName() {
	return firstName;
}

// set the professional athlete's first name
void ProfessionalAthlete::setFirstName(string inputFirstName) {
	firstName = inputFirstName;
}

// retrieve the professional athlete's last name
string ProfessionalAthlete::getLastName() {
	return lastName;
}

// set the professional athlete's first name
void ProfessionalAthlete::setLastName(string inputLastName) {
	lastName = inputLastName;
}

// retrieve the professional athlete's organization
string ProfessionalAthlete::getOrganization() {
	return organization;
}

// set the professional athlete's organization
void ProfessionalAthlete::setOrganization(string inputOrganization) {
	organization = inputOrganization;
}

// retrieve the professional athlete's annual salary
double ProfessionalAthlete::getAnnualSalary() {
	return annualSalary;
}

// set the professional athlete's annual salary
void ProfessionalAthlete::setAnnualSalary(double inputAnnualSalary) {
	annualSalary = inputAnnualSalary;
}

// retrieve the skill level of the athlete
int ProfessionalAthlete::getSkillLevel() {
	return skillLevel;
}

// set the skill level for the professional athlete
void ProfessionalAthlete::setSkillLevel(int inputSkillLevel) {
	if ((inputSkillLevel < minSkillLevel) || (inputSkillLevel > maxSkillLevel)) {
		cout << "\nSkill level not within " << minSkillLevel << " and " << maxSkillLevel;
	}
	else {
		skillLevel = inputSkillLevel;
	}
}

// print the stats of the professional athlete.
// Is pure virtual, so this base class implementation should never be called.
void ProfessionalAthlete::printStats() {
	cout << "\nName: " << firstName << " " << lastName
		<< "\nOrganization: " << organization
		<< "\nAnnual salary: $" << fixed << setprecision(2) << annualSalary
		<< "\nSkill Level: " << skillLevel
		<< '\n';
}

// destructor for the ProfessionalAthlete class 
ProfessionalAthlete::~ProfessionalAthlete() {
	// nothing to do at this time
}