///////////////////////////////////////////////////////////
//
// Anthony Redamonti
// 8-3-2021
//
// Student.cpp
// CIS554 Object Oriented Programming in C++
// Exercise 9_2 - Overriding Base Class Members
//
// The purpose of the following class is to build a Student
// class derived from the Community Member base class.
// It has two private data members: department and GPA.
//
// The getMemberId data member function of the base class is
// overridden in this class. The ID is multiplied by 100 to
// signify that the ID belongs to a student.
//
///////////////////////////////////////////////////////////

#include "Student.h"
#include <iostream>
using std::cout;
using std::endl;

// default constructor 
// initialize our data to something meaningful
Student::Student()
	: department("Non-matriculated"), gpa(0)
{
	// no body needed. everthing was done in the initialization list
}

// initialization constructor
// initialize our base class with pertinent information
// then initialize this derived class data with the remaining pertinent data
Student::Student(string inputCommunityName, string inputFirstName, string inputLastName, int inputMemberId, string inputDepartment, double inputGpa)
	: CommunityMember(inputCommunityName, inputFirstName, inputLastName, inputMemberId), department(inputDepartment), gpa(inputGpa)
{
	// no body needed. everthing was done in the initialization list
}

Student::~Student()
{
	// nothing to do at this time.
}

// retrive private data member using the following public data member function
// retieves the department of the student (type string)
string Student::getStudentDepartment() {
	return(department);
}

// retrieve private data member "gpa" which is of type double
double Student::getStudentGpa() {
	return(gpa);
}

// override the base class (CommunityMember) member function
int Student::getMemberId() {
	int memId{ 0 };
	memId = CommunityMember::getMemberId();
	memId = memId * 100; // trailing zeroes indicate student's ID
	return(memId);
}