///////////////////////////////////////////////////////////
//
// Anthony Redamonti
// 8-3-2021
//
// Source.cpp
// CIS554 Object Oriented Programming in C++
// Exercise 9_2 - Overriding Base Class Members
//
// The following code tests the base class "CommunityMember"
// and its derived class member functions.
//
///////////////////////////////////////////////////////////

#include "CommunityMember.h"
#include "Employee.h"
#include "Student.h"
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::fixed; // used for displaying decimal of GPA
using std::vector;

double getDistance(vector<double> position1, vector<double> position2);

// Demonstrate CommunityMember class
void demonstrateCommunityMember(CommunityMember &communityMemberObj);

// Demonstrate Employee class
void demonstrateEmployee(Employee &employeeObj);

// Demonstrate Student class
void demonstrateStudent(Student &studentObj);

// print Syracuse Banner
void printSyracuseBanner();

int main()
{
	cout.precision(1); // 1 decimal place for GPA display

	// print Syracuse Banner
	printSyracuseBanner();

	// professional looking banner
	cout << "Anthony Redamonti\n" <<
		"Professor Jonathan S. Weissman\n" <<
		"CIS 554 - M401 Object Oriented Programming C++\n" <<
		"Syracuse University\n" <<
		"Exercise 9.1 - Simple Inheritance Test\n" <<
		"8/3/2021\n\n";

	// demonstrate CommunityMember default constructor
	cout << "***** Demonstrating the default constructor, and member methods, for class CommunityMember" << endl;
	CommunityMember commMember;
	demonstrateCommunityMember(commMember);
	cout << endl;

	// demonstrate CommunityMember initialization constructor
	cout << "***** Demonstrating the initialization constructor, and member methods, for class CommunityMember" << endl;
	CommunityMember commMemberHarry("Syracuse University", "Harry", "Potter", 1234);
	demonstrateCommunityMember(commMemberHarry);
	cout << endl;


	// demonstrate Employee default constructor
	cout << "***** Demonstrating the default constructor, and member methods, for class Employee" << endl;
	Employee commMemberEmp;
	demonstrateEmployee(commMemberEmp);
	cout << endl;


	// demonstrate Employee initialization constructor
	cout << "***** Demonstrating the initialization constructor, and member methods, for class Employee" << endl;
	Employee commMemberEmpHarry("Syracuse University", "Harry", "Potter", 1234, "Janitor", 25000);
	demonstrateEmployee(commMemberEmpHarry);
	cout << endl;

	// demonstrate Student initialization constructor
	cout << "***** Demonstrating the initialization constructor, and member methods, for class Student" << endl;
	Student commMemberEmpSally("Syracuse University", "Harry", "Potter", 1234, "History", 4.0);
	demonstrateStudent(commMemberEmpSally);
	cout << endl;


	vector<double> zeroes1 = { 0, 0 };
	vector<double> zeroes2 = zeroes1;

	double answer = getDistance(zeroes1, zeroes2);
	int x = 5;
}


// return the inputBase raised to the power of the inputExponent.
double powerFunc(double inputBase, int inputExponent) {
	double answer = 1;
	for (int i = 0; i < inputExponent; i++) {
		answer = answer * inputBase;
	}
	return answer;
}

// return the absolute distance between two (x,y) points.
double getDistance(vector<double> position1, vector<double> position2) {

	// initialize local variables
	double answer{ 0 };
	double x1{ position1[0] };
	double x2{ position2[0] };
	double y1{ position1[1] };
	double y2{ position2[1] };

	answer = sqrt((powerFunc((x2 - x1), 2) + powerFunc((y2 - y1), 2)));
	return answer;
}

// function that displays the community member data using private data member functions
void demonstrateCommunityMember(CommunityMember & c)
{
	cout << c.getFirstName() << " "
		<< c.getLastName()
		<< " is a member of the " << c.getCommunityName() << " community, with member ID " << c.getMemberId() << endl;
}

// function that displays the employee member data as well as the community member data of the employee object.
void demonstrateEmployee(Employee & employeeObject)
{
	cout << employeeObject.getFirstName() << " "
		<< employeeObject.getLastName()
		<< " is a member of the " << employeeObject.getCommunityName() << " community, " << " with member ID " << employeeObject.getMemberId() << endl
		<< "He/She is an employee with Job Title: " << employeeObject.getJobTitle() << ", making "
		<< employeeObject.getYearlySalary() << " per year." << endl;
}

// function that displays the student member data as well as the community member data of the student object.
// The getMemberId function belongs to the student class and overrides the base class member function of the 
// same name.
void demonstrateStudent(Student& studentObj) {
	cout << studentObj.getFirstName() << " "
		<< studentObj.getLastName()
		<< " is a member of the " << studentObj.getCommunityName() << " community, " << " with member ID " << studentObj.getMemberId() << endl
		<< "He/She is of the " << studentObj.getStudentDepartment() << " department with a GPA of: " << fixed << studentObj.getStudentGpa() << endl;
}

// print "SU" for Syracuse University on the console
void printSyracuseBanner() {
	cout
		<< "                   .-----------.            .----.          .----.\n"
		<< "                 /             |            |    |          |    |\n"
		<< "                /    .---------*            |    |          |    |\n"
		<< "               .    /                       |    |          |    |\n"
		<< "               |   |                        |    |          |    |\n"
		<< "               |    .                       |    |          |    |\n"
		<< "                .    *-------.              |    |          |    |\n"
		<< "                 *.            *            |    |          |    |\n"
		<< "                   *----.       *           |    |          |    |\n"
		<< "                          .      *          |    |          |    |\n"
		<< "                          |      |          |    |          |    |\n"
		<< "                         /       /          |    |          |    |\n"
		<< "                .-------*       *           *     *--------*     /\n"
		<< "                |             *              *                  / \n"
		<< "                *----------*                   *--------------*   \n";
}