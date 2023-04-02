///////////////////////////////////////////////////////////
/*
Anthony Redamonti
Professor Jonathan S.Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
Exercise 10_2 - Abstract Classes
8/9/2021

Student.cpp

The purpose of the following class is to build a Student
class derived from the Community Member base class.
It has two private data members: department and GPA.
*/
///////////////////////////////////////////////////////////
#ifndef STUDENT_H
#define STUDENT_H

#include "CommunityMember.h"

/* The following Student class is derived from the Community Member class. */
class Student :
	public CommunityMember {
public:
	// default constructor
	Student();

	// initialization constructor
	Student(string inputCommunityName, string inputFirstName, string inputLastName, int inputMemberId, string inputDepartment, double inputGpa);

	~Student();

	// retrieve the student's department
	string getStudentDepartment();

	// retrive the student's gpa
	double getStudentGpa();

	// override the base class (CommunityMember) member function
	int getMemberId();

	// virtual function retrieving member type (student) using polymorphism
	virtual string getCommunityMemberType();

private:
	// private data members
	string department;
	double gpa;
};


#endif
