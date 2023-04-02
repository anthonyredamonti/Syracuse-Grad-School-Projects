///////////////////////////////////////////////////////////
//
// Anthony Redamonti
// 8-3-2021
//
// Employee.h
// CIS554 Object Oriented Programming in C++
// Exercise 9_2 - Overriding Base Class Members
//
// The purpose of the following class is to build an Employee
// class derived from the Community Member base class.
// It has two private data members: job title and yearly
// salary.
//
///////////////////////////////////////////////////////////
#ifndef __EMPLOYEE_H__
#define __EMPLOYEE_H__

#include "CommunityMember.h"
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

	string getJobTitle() { return jobTitle; }
	int getYearlySalary() { return yearlySalary; }

private:
	// private data members
	string jobTitle;
	int yearlySalary;
};

#endif

