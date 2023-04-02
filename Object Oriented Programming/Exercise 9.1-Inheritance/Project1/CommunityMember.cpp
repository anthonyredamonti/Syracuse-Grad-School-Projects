///////////////////////////////////////////////////////////
//
// Anthony Redamonti
// 8-3-2021
//
// CommunityMember.cpp
// CIS554 Object Oriented Programming in C++
// Exercise 9_2 - Overriding Base Class Members
//
// The purpose of the following code is to build a Community
// Member base class for the derived Employee and Student 
// classes.
// The Community Member class has four private data members:
// last name, first name, community name, and member ID.
//
///////////////////////////////////////////////////////////
#include "CommunityMember.h"
#include <iostream>
using std::cout;
using std::endl;

// default constructor
// initialize our data to something usefule
CommunityMember::CommunityMember()
	: communityName("Unknown"), firstName("Jane"), lastName("Doe"), memberId(0)
{
	// no body needed. everthing was done in the initialization list
}

// initialization constructor
// initialize our data to what the user requires
CommunityMember::CommunityMember(string cName, string fName, string lName, int mId)
	: communityName(cName), firstName(fName), lastName(lName), memberId(mId)
{
	// no body needed. everthing was done in the initialization list
}

// CommunityMember deconstructor
CommunityMember::~CommunityMember()
{
	// nothing to do at this time
}
