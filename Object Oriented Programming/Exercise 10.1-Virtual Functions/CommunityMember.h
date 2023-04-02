///////////////////////////////////////////////////////////
/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
Exercise 10_2 - Abstract Classes
8/9/2021

CommunityMember.h

The purpose of this class is to provide a base class for
the Student and Employee derived classes. There is a pure
virtual function called "getCommunityMemberType."
*/
///////////////////////////////////////////////////////////
#ifndef __COMMUNITY_MEMBER_H__
#define __COMMUNITY_MEMBER_H__

#include <string>
using std::string;

#include <ostream>
using std::ostream;

// base class of employee (derivative) class
class CommunityMember
{
public:

	// default constructor
	CommunityMember();

	// initialization constructor
	CommunityMember(string commName, string fName, string lName, int memID);

	// destructor
	~CommunityMember();

	// public data member functions
	string getCommunityName();
	string getFirstName();
	string getLastName();
	int getMemberId();
	virtual string getCommunityMemberType() = 0; // virtual function

private:

	// private data members
	string communityName;
	string firstName;
	string lastName;
	int memberId;
};

#endif

