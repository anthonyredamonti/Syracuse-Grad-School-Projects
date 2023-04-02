/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
HW #2 - Exercise 4.14 p150-151
7/30/2021

Account.cpp

Below is the "Account" class, which is used to catalog the
accounts of a hardware store. The Account class has six
private data members: 

    - account number 
	- balance at the beginning of the month
	- total of all items charged by this customer this month
	- total of all credits applied to this customer's account
	  this month 
	- allowed credit limit
	- the newly calculated balance (= beginning 
	  balance + charges this month - credits this month)
	
Each data member has respective get/set functions, except 
the newly calculated balance which only has a get function.
The getNewBalance() function calls updateNewBalance() to 
update the newBalance private data member.

*/

#include <iostream>
#include "Account.h"

// The Account constructor which initializes the six private data members.
Account::Account()
	: accountNumber{ 0 },
	beginningBalance{ 0 },
	chargesThisMonth{ 0 },
	creditsThisMonth{ 0 },
	creditLimit{ 0 },
	newBalance{ 0 }
{}

// The data member function which retrieves the account number.
int Account::getAccountNumber() {
	return(accountNumber);
}

// The data member function which sets the account number.
void Account::setAccountNumber(int inputAccountNum) {
	accountNumber = inputAccountNum;
}

// The data member function which retrieves the beginning balance of the account.
double Account::getBeginningBalance() {
	return(beginningBalance);
}

// The data member function which sets the beginning balance of the account.
void Account::setBeginningBalance(double inputBeginningBalance) {
	beginningBalance = inputBeginningBalance;
}

// The data member function which retrieves the total charges this month of the account.
double Account::getChargesThisMonth() {
	return(chargesThisMonth);
}

// The data member function which sets the total charges this month of the account.
void Account::setChargesThisMonth(double inputChargesThisMonth) {
	chargesThisMonth = inputChargesThisMonth;
}

// The data member function which gets the total credits this month of the account.
double Account::getCreditsThisMonth() {
	return(creditsThisMonth);
}

// The data member function which sets the total credits this month of the account.
void Account::setCreditsThisMonth(double inputCreditsThisMonth) {
	creditsThisMonth = inputCreditsThisMonth;
}

// The data member function which gets the credit limit of the account.
double Account::getCreditLimit() {
	return(creditLimit);
}

// The data member function which sets the credit limit of the account.
void Account::setCreditLimit(double inputCreditLimit) {
	creditLimit = inputCreditLimit;
}

// The member function that returns the newly calculated balance of the account.
// The function calls "updateNewBalance" to perform the new balance calculation. 
double Account::getNewBalance() {
	updateNewBalance(); // perform new balance calculation
	return(newBalance);
}

// The private data member function "updateNewBalance" updates the newBalance data member.
// The function is only called by getNewBalance()
void Account::updateNewBalance() {
	newBalance = beginningBalance + chargesThisMonth - creditsThisMonth;
}