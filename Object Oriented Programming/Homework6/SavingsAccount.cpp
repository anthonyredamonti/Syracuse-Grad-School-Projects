/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
HW #6
8/26/2021

SavingsAccount.cpp

Below is the SavingsAccount class. It is used to 
store the savings balance and annual interest 
rate of a savings account. The user can also use 
this class to modify the annual interest rate.

The annual interest rate is a static variable
that stores the annual interest rate for all
instances of the savings account class.
*/

#include "SavingsAccount.h"
#include <iomanip>    // needed for setw() and setfill()

using std::cout;
using std::setfill;
using std::setw;

// initialize static private member variable with 0.0 (double type) 
double SavingsAccount::annualInterestRate{ 0.0 };

// The SavingsAccount default constructor
SavingsAccount::SavingsAccount():
	savingsBalance{ 0 }
{}

// The SavingsAccount constructor which initializes the private data members
SavingsAccount::SavingsAccount(double inputSavingsBalance) :
	savingsBalance{ inputSavingsBalance }
{}

// virtual destructor
SavingsAccount::~SavingsAccount(){
	// nothing to do at this time.
}

// retrieve the balance of the savings for the account
double SavingsAccount::getSavingsBalance() {
	return(savingsBalance);
}

// set the savings balance for the account
void SavingsAccount::setSavingsBalance(double inputSavingsBalance) {
	savingsBalance = inputSavingsBalance;
}

// return the annual interest rate
double SavingsAccount::getInterestRate() {
	return(annualInterestRate);
}

// set the annual interest rate 
void SavingsAccount::modifyInterestRate(double inputInterestRate) {
	annualInterestRate = inputInterestRate;
}

// calculate the monthly interest using the interest rate and savings balance
void SavingsAccount::calculateMonthlyInterest() {
	
	// initialize local variables
	double annualInterestRateCopy{ 0 };
	double monthlyInterest{ 0 };

	// shift the interest rate two decimal places to the left
	annualInterestRateCopy = annualInterestRate / 100;

	// calculate the montly interest and use it to update the balance
    monthlyInterest = (savingsBalance * annualInterestRateCopy) / 12;
	updateBalance(monthlyInterest);
}

// add the monthly interest to the savings balance
void SavingsAccount::updateBalance(double monthlyInterest) {
	savingsBalance = savingsBalance + monthlyInterest;
}
