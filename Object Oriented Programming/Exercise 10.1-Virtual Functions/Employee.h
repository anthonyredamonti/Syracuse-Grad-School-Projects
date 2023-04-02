///////////////////////////////////////////////////////////
/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
Exercise 10_2 - Abstract Classes
8/9/2021

Employee.h

The following class is derived from the Community Member base
class. It overwrites the pure virtual function
getCommunityMemberType. The private data member variable are
the job title and yearly salary.
*/
///////////////////////////////////////////////////////////
#ifndef __EMPLOYEE_H__
#define __EMPLOYEE_H__

#include "CommunityMember.h"

// Employee class derived from the Community Member base class
class Employee :
	public CommunityMember
{
public:

	// default constructor
	Employee();

	// initialization contstructor
	Employee(string cNname, string fName, string lName, int memID, string jobTitle, int yearlySalary);

	// destructor
	~Employee();

	// public member functions
	string getJobTitle();
	int getYearlySalary();
	virtual string getCommunityMemberType(); // Virtual function allows base class pointers access to this function.

private:
	// private data members
	string jobTitle;
	int yearlySalary;
};

#endif

