/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
HW #2 - Exercise 4.14 p150-151
7/30/2021

Account.h

Below are the public and private function and variable
declarations of the "Account" class. The Account class
is used to catalog the accounts of a hardware store. The 
Account class has six private data members:

	- account number
	- balance at the beginning of the month
	- total of all items charged by this customer this month
	- total of all credits applied to this customer's account
	  this month
	- allowed credit limit
	- the newly calculated balance

*/

#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account {
public:
	Account(); // Constuctor used to initialize private data members.

	// "Get/Set" functions for five of the private data members.
	int getAccountNumber();
	void setAccountNumber(int inputAccountNumber);
	double getBeginningBalance();
	void setBeginningBalance(double inputBeginningBalance);
	double getChargesThisMonth();
	void setChargesThisMonth(double inputChargesThisMonth);
	double getCreditsThisMonth();
	void setCreditsThisMonth(double inputCreditsThisMonth);
	double getCreditLimit();
	void setCreditLimit(double inputCreditLimit);

	// "Get" function for the new balance of the account
	double getNewBalance();

private:

	// private data member function called by getNewBalance()
	void updateNewBalance();

	// private data members
	int accountNumber;
	double beginningBalance; // balance at the beginning of the month
	double chargesThisMonth;
	double creditsThisMonth;
	double creditLimit;
	double newBalance; // the newly calculated balance
};

#endif
