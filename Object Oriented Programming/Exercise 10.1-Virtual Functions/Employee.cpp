///////////////////////////////////////////////////////////
/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
Exercise 10_2 - Abstract Classes
8/9/2021

Employee.cpp

The following class is derived from the Community Member base
class. It overwrites the pure virtual function
getCommunityMemberType. The private data member variable are
the job title and yearly salary.
*/
///////////////////////////////////////////////////////////

#include "Employee.h"
#include <iostream>
using std::cout;
using std::endl;

// default constructor 
// initialize our data to something meaningful
Employee::Employee()
	: jobTitle("Unknown"), yearlySalary(0)
{
	// no body needed. everthing was done in the initialization list
}

// initialization constructor
// initialize our base class with pertinent information
// then initialize this derived class data with the remaining pertinent data
Employee::Employee(string cName, string fName, string lName, int memID, string jTitle, int yrSalary)
	: CommunityMember(cName, fName, lName, memID), 
	jobTitle (jTitle), 
	yearlySalary(yrSalary)
{
	// no body needed. everthing was done in the initialization list
}

// Employee Class Destructor
Employee::~Employee()
{
	// nothing to do at this time.
}

// retrieve the employee's job title
string Employee::getJobTitle() {
	return jobTitle;
}

// retrieve the employee's yearly salary
int Employee::getYearlySalary() { 
	return yearlySalary; 
}


// virtual member function allows base class pointer access to this derivative public member function
string Employee::getCommunityMemberType()
{
	return ("My name is " + getFirstName() + ". I am an employee of the " + getCommunityName() + " community!\n");
}
