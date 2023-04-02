/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
HW #5
8/18/2021

ProfessionalAthlete.h

Below is the "ProfessionalAthlete" class, which
teaches the user various levels of arithmetic. The user
will set the arithmetic type and difficulty level before
beginning. 
*/

#ifndef PROFESSIONALATHLETE
#define PROFESSIONALATHLETE
#include<vector>
#include<string>
#include<iostream>

using std::string;

class ProfessionalAthlete{
public:
	// ------------- PUBLIC DATA MEMBER FUNCTIONS ----------------

	// Constuctor used to initialize private data members.
	ProfessionalAthlete(string inputFirstName, string inputLastName, string inputOrganization, 
		double inputAnnualSalary, int inputSkillLevel);

	// destructor
	virtual ~ProfessionalAthlete();

	// "Get/Set" functions.
	string getOrganization();
	void setOrganization(string inputOrganization);
	string getLastName();
	void setLastName(string inputLastName);
	string getFirstName();
	void setFirstName(string inputFirstName);
	double getAnnualSalary();
	void setAnnualSalary(double inputAnnualSalary);
	int getSkillLevel();
	void setSkillLevel(int inputSkillLevel);

	virtual void printStats() = 0; // pure virtual function

private:
	// -----------  PRIVATE DATA MEMBER VARIABLES ---------------
	string organization;
	string lastName;
	string firstName;
	double annualSalary;
	int skillLevel;
	int maxSkillLevel;
	int minSkillLevel;
};

#endif
