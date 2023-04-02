///////////////////////////////////////////////////////////
/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
Exercise 10_2 - Abstract Classes
8/9/2021

CommunityMember.cpp

The purpose of this class is to provide a base class for
the Student and Employee derived classes. There is a pure
virtual function called "getCommunityMemberType."
*/
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

// retrieve the community member's community name
string CommunityMember::getCommunityName() { 
	return communityName; 
}

// retrieve the community member's first name
string CommunityMember::getFirstName() { 
	return firstName; 
}

// retrieve the community member's last name
string CommunityMember::getLastName() { 
	return lastName; 
}

// retrieve the community member's member identification
int CommunityMember::getMemberId() { 
	return memberId; 
}

// print the message that the base class method was called
string CommunityMember::getCommunityMemberType() { 
	return ("Base Class GetCommunityMemberType method called!!\n"); 
}

// initialization constructor
// initialize our data to what the user requires
CommunityMember::CommunityMember(string cName, string fName, string lName, int mID)
	: communityName(cName), firstName(fName), lastName(lName), memberId(mID)
{
	// no body needed. everthing was done in the initialization list
}


CommunityMember::~CommunityMember()
{
	// nothing to do at this time
}
