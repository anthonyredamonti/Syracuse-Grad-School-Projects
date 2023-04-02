/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554-M401 Object Oriented Programming C++
Syracuse University
HW #2 - Exercise 4.14 p150-151
7/30/2021

Main.cpp

The following program creates an instance of the Account 
class and prompts the user to input values for five of its 
private data members:

	- account number
	- balance at the beginning of the month
	- total of all items charged by this customer this month
	- total of all credits applied to this customer's account
	  this month
	- allowed credit limit

The program then calls getNewBalance to retrieve the updated
account balance. The updated account balance is output to the
console. If the updated account balance is greater than the 
credit limit, the program will output the account number, 
credit limit, balance, and the message: "Credit Limit 
Exceeded."

The program will not terminate until the user enters -1 when 
prompted for the account number.

*/

#include <iostream>   // needed for the standard library
#include <iomanip>    // needed for the setw function
#include "Account.h"  // defines the Account class

// importing objects from the C++ standard library
using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::setw;

// print "SU" for Syracuse University on the console
void printSyracuseBanner(); 

int main() {

	// create new Account object 
	Account accountObj;

	// initialize local variables to zero
	int inputAccountNum{ 0 };
	double inputBeginningBalance{ 0 };
	double inputChargesThisMonth{ 0 };
	double inputCreditsThisMonth{ 0 };
	double inputCreditLimit{ 0 };

	// set precision for 2 decimal places
	cout.precision(2);

	// print Syracuse Banner
	printSyracuseBanner();

	// professional looking banner
	cout << "Anthony Redamonti\n" <<
			"Professor Jonathan S. Weissman\n" <<
			"CIS 554 - M401 Object Oriented Programming C++\n" <<
			"Syracuse University\n" <<
			"HW #2 - Exercise 4.14 p150-151\n" <<
			"7/30/2021\n\n";

	// prompt the user for the account number
	cout << "Enter account number (or -1 to quit): ";
	cin >> inputAccountNum;

	// if the user entered -1 for the account number, terminate the program.
	while (inputAccountNum != -1) {
		accountObj.setAccountNumber(inputAccountNum);

		// prompt the user for the balance at the beginning of the month
		cout << "Enter beginning balance: ";
		cin >> inputBeginningBalance;
		accountObj.setBeginningBalance(inputBeginningBalance);

		// prompt the user for the total of all items charged this month
		cout << "Enter total charges: ";
		cin >> inputChargesThisMonth;
		accountObj.setChargesThisMonth(inputChargesThisMonth);

		// prompt the user for the total number of credits applied this month
		cout << "Enter total credits: ";
		cin >> inputCreditsThisMonth;
		accountObj.setCreditsThisMonth(inputCreditsThisMonth);

		// prompt the user for the credit limit of the account
		cout << "Enter credit limit: ";
		cin >> inputCreditLimit;
		accountObj.setCreditLimit(inputCreditLimit);

		// display the newly calculated balance
		cout << "New balance is: " << fixed << accountObj.getNewBalance() << endl;
		
		// if the credit limit has been exceeded, display the account number,
		// credit limit, newly calculated balance and the "Credit Limit
		// Exceeded" message.
		if (accountObj.getNewBalance() > accountObj.getCreditLimit()) {
			cout << "Account: " << setw(10) << accountObj.getAccountNumber() << endl;
			cout << "Credit limit: " << setw(7) << fixed << accountObj.getCreditLimit() << endl;
			cout << "Balance: " << setw(13) << fixed << accountObj.getNewBalance() << endl; 
			cout << "Credit Limit Exceeded" << endl;
		}

		// prompt the user for the next account number
		cout << "\nEnter account number (or -1 to quit): ";
		cin >> inputAccountNum;
	}
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