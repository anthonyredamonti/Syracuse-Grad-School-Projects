/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
HW #5
8/18/2021

ProBaseballPlayer.h

Below is the "ProfessionalAthlete" class, which
teaches the user various levels of arithmetic. The user
will set the arithmetic type and difficulty level before
beginning. 
*/

#ifndef PROBASEBALLPLAYER
#define PROBASEBALLPLAYER
#include<vector>
#include<array>
#include<iostream>

using std::string;
using std::array;
using std::vector;

class ProBaseballPlayer : 
	public ProfessionalAthlete
{
public:
	// ------------- PUBLIC DATA MEMBER FUNCTIONS ----------------
	
	// Constuctor used to initialize private data members.
	ProBaseballPlayer(string inputFirstName, string inputLastName, double inputAnnualSalary, 
		string team, int fieldPosition, int inputSkillLevel); 

	// virtual destructor
	virtual ~ProBaseballPlayer();

	// "Get/Set" functions.
	string getTeam();
	void setTeam(string inputTeam);
	int getFieldPosition();
	void setFieldPosition(int inputFieldPosition);
	
	vector<string>* getPastTeamsVector();
	virtual void printStats(); // print the stats of the baseball player

private:
	// -----------  PRIVATE DATA MEMBER FUNCTIONS ---------------
	void setFieldPositionString();

	// -----------  PRIVATE DATA MEMBER VARIABLES ---------------
	string currentTeam;
	vector<string> pastTeams;
	int fieldPosition; // 1-9
	string fieldPositionString;
	array<string, 9> positionStringsArray;

};

#endif
