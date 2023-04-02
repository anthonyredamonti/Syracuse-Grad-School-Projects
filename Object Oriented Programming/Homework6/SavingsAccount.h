/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
HW #6
8/26/2021

SavingsAccount.h

Below is the SavingsAccount class. It is used to store the 
savings balance and annual interest rate of a savings
account. The user can also use this class to modify the
annual interest rate.

*/

#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H
#include<iostream>

class SavingsAccount {
public:
	// ------------- PUBLIC DATA MEMBER FUNCTIONS ----------------
	
	// Default Constructor
	SavingsAccount();

	// Initialization Constuctor: used to initialize private data members.
	SavingsAccount(double inputSavingsBalance);

	// virtual destructor
	virtual ~SavingsAccount();

	// "Get/Set" functions.
	double getSavingsBalance(); 
	void setSavingsBalance(double inputSavingsBalance);
	static void modifyInterestRate(double inputInterestRate);
	static double getInterestRate();
	void calculateMonthlyInterest();

private:
	// -----------  PRIVATE DATA MEMBER FUNCTIONS ---------------
	void updateBalance(double interest);

	// -----------  PRIVATE DATA MEMBER VARIABLES ---------------
	double savingsBalance;
	static double annualInterestRate;

};

#endif
