/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
HW #6
8/26/2021

Main.cpp

The following program creates two instance of the SavingsAccount
class: saver1 and saver2. The initial account balances of saver1 
and saver2 are set by the user. The initial annual interest rate
is also set by the user. Initial account balances and the interest
rate are displayed to the console.
The monthly interest is calculated for both objects and is used 
to update the account balances. The updated balances are displayed
to the console. 
The interest rate is then set again by the user. The monthly 
interest is updated again and used to update the account balances. 
The updated balances are displayed on the console.

*/

#include "SavingsAccount.h"  // defines the TrajectoryCommands class
#include <iomanip>

// importing objects from the C++ standard library
using std::cin;
using std::cout;
using std::fixed;
using std::setprecision;
using std::numeric_limits;
using std::streamsize;

// print "SU" for Syracuse University on the console
void printSyracuseBanner(); 

int main() {

	// initialize local variables
	double initialSavingsBalance1{ 0.0 };
	double initialSavingsBalance2{ 0.0 };
	double inputInterestRate{ 0.0 };

	// print Syracuse Banner
	printSyracuseBanner();

	// information about program
	cout << "\nWelcome to the Savings Account Program!" <<
		"\nThe program will create two instances of the" <<
		"\nSavingsAccount class." <<
		"\nThe initial savings balances of both accounts" <<
		"\nare set by the user. The user then sets the" <<
		"\nannual interest rate, and the new balances" << 
		"\nare displayed." <<
		"\nThe user then sets the annual interest rate" <<
		"\nagain, and new balances for the next month " <<
		"\nare displayed. The program then terminates.\n";

	// create three instances of the savings account class
	SavingsAccount saver1;
	SavingsAccount saver2;

	// prompt the user for an initial account balance of saver1
	cout << "\nPlease enter an initial account balance for Account 1: $";
	cin >> initialSavingsBalance1;

	// check for invalid user input
	while (cin.fail()) {
		cout << "\nPlease enter a dollar amount.";
		//clear the error
		cin.clear();
		//discard invalid characters
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nPlease enter an initial account balance for Account 1: $";
		cin >> initialSavingsBalance1;
	}

	// set the initial savings balance of saver1
	saver1.setSavingsBalance(initialSavingsBalance1);

	// prompt the user for an initial account balance of saver2
	cout << "Please enter an initial account balance for Account 2: $";
	cin >> initialSavingsBalance2;

	// check for invalid user input
	while (cin.fail()) {
		cout << "\nPlease enter a dollar amount.";
		//clear the error
		cin.clear();
		//discard invalid characters
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nPlease enter an initial account balance for Account 2: $";
		cin >> initialSavingsBalance2;
	}

	// set the initial savings balance of saver2
	saver2.setSavingsBalance(initialSavingsBalance2);

	// diplay the initial account balances entered by the user
	cout << "\nAccount 1 initial account balance: $" << setprecision(2) << fixed << saver1.getSavingsBalance();
	cout << "\nAccount 2 initial account balance: $" << setprecision(2) << fixed << saver2.getSavingsBalance();

	// prompt the user for the annual interest rate and update the interest rate
	cout << "\n\nPlease enter an annual interest rate: %";
	cin >> inputInterestRate;

	// check for invalid user input
	while (cin.fail()) {
		cout << "\nPlease enter a valid percentage.";
		//clear the error
		cin.clear();
		//discard invalid characters
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		// prompt the user for the annual interest rate and update the interest rate
		cout << "\nPlease enter an annual interest rate: %";
		cin >> inputInterestRate;
	}

	// modify the monthly interest rate
	saver1.modifyInterestRate(inputInterestRate);
	
	// display the modified interest rate
	cout << "\nInitial annual interest rate: %" << setprecision(2) << fixed << saver1.getInterestRate();

	// calculate the monthly interest for each account
	saver1.calculateMonthlyInterest();
	saver2.calculateMonthlyInterest();

	// display the modified account balances
	cout << "\n\nAccount 1 updated balance: $" << setprecision(2) << fixed << saver1.getSavingsBalance();
	cout << "\nAccount 2 updated balance: $" << setprecision(2) << fixed << saver2.getSavingsBalance();
	cout << '\n';

	// prompt the user for the annual interest rate and update the interest rate
	cout << "\nPlease re-enter an annual interest rate: %";
	cin >> inputInterestRate;

	// check for invalid user input
	while (cin.fail()) {
		cout << "\nPlease enter a valid percentage.";
		//clear the error
		cin.clear();
		//discard invalid characters
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		// prompt the user for the annual interest rate and update the interest rate
		cout << "\nPlease re-enter an annual interest rate: %";
		cin >> inputInterestRate;
	}

	// modify the monthly interest rate
	saver1.modifyInterestRate(inputInterestRate);

	// display the modified interest rate
	cout << "\nUpdated annual interest rate: %" << setprecision(2) << fixed << saver1.getInterestRate();

	// calculate the monthly interest for each account
	saver1.calculateMonthlyInterest();
	saver2.calculateMonthlyInterest();

	// display the modified account balances
	cout << "\n\nAccount 1 updated balance: $" << setprecision(2) << fixed << saver1.getSavingsBalance();
	cout << "\nAccount 2 updated balance: $" << setprecision(2) << fixed << saver2.getSavingsBalance();
	cout << '\n';
}

// Print "SU" for Syracuse University on the console.
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
		<< "                *----------*                   *--------------*   \n\n";
}