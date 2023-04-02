///////////////////////////////////////////////////////////
//
// Anthony Redamonti
// 8-3-2021
//
// CommunityMember.h
// CIS554 Object Oriented Programming in C++
// Exercise 9_2 - Overriding Base Class Members
//
// The purpose of the following class is to build a Community
// Member base class comprised of four private data members.
//
///////////////////////////////////////////////////////////
#ifndef __COMMUNITY_MEMBER_H__
#define __COMMUNITY_MEMBER_H__

#include <string>
using std::string;

#include <ostream>
using std::ostream;

class CommunityMember
{
public:

	// default constructor
	CommunityMember();

	// initialization constructor
	CommunityMember(string commName, string fName, string lName, int memId);

	// destructor
	~CommunityMember();

	// public data member functions
	string getCommunityName() { return communityName; }
	string getFirstName() { return firstName; }
	string getLastName() { return lastName; }
	int getMemberId() { return memberId; }


private:
	// private data members
	string communityName;
	string firstName;
	string lastName;
	int memberId;
};

#endif

