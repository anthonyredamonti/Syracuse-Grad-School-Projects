///////////////////////////////////////////////////////////
//
// Anthony Redamonti
// 8-3-2021
//
// Student.h
// CIS554 Object Oriented Programming in C++
// Exercise 9_2 - Overriding Base Class Members
//
// The purpose of the following class is to build a Student
// class derived from the Community Member base class.
// It has two private data members: department and GPA.
//
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

private:
	// private data members
	string department;
	double gpa;
};


#endif
