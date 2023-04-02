/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554-M401 Object Oriented Programming C++
Syracuse University
HW #1 - Exercise 3.10 p100
7/28/2021

Main.cpp

The following program creates a class called "Invoice" which
is used to catalog the invoices of a hardware store. The 
Invoice class has four data members: part number (type string),
part description (type string), quantity of the item being
sold (type int), and a price per item (type int). Each data 
member has respective get/set functions.

The Invoice Class also has a function getInvoiceAmount that 
calculates the invoice amount and returns it as an integer
value. If the quantity is not positive, it is set to zero.
If the price per item is not positive, it is set to zero.

The main function below tests the Invoice class and its
member functions.
*/

#include <iostream>   // needed for the standard library
#include <iomanip>    // needed for setw function
#include "Invoice.h"  // defines the Invoice class

// importing objects (and string class) from the C++ standard library
using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::string;

int main() {
	
	// Initialize the local parameters with values representing  
	// the purchase of 3 hammers at $5 per hammer.
	string partNumber{ "800-1909" };
	string partDescription{ "Hammer" };
	int quantity{ 3 };
	int pricePerItem{ 5 };
	int invalidQuantity{ -3 };
	int invalidPricePerItem{ -5 };

	// Create an Invoice object (instance of the Invoice class).
	Invoice invoiceObj;

	// Print the initialized values of the four data members. 
	// Use setw function to align output strings.
	cout << "INITIAL VALUE OF INVOICEOBJ DATA MEMBERS" << endl;
	cout << "part number: " << setw(10) << invoiceObj.getPartNumber() << endl;
	cout << "part description: " << setw(5) << invoiceObj.getPartDescription() << endl;
	cout << "quantity: " << setw(11) << invoiceObj.getQuantity() << endl;
	cout << "price per item: " << setw(4) << "$" << invoiceObj.getPricePerItem() << endl;
	cout << "\n";
	// Test the getInvoiceAmount member function.
	// Use setw function to align output strings.
	cout << "INITIAL INVOICE AMOUNT: " << setw(4) << "$" << invoiceObj.getInvoiceAmount() << endl;
	cout << "\n";

	// Set invoice object's four data members to the values of the local variables.
	invoiceObj.setPartNumber(partNumber);
	invoiceObj.setPartDescription(partDescription);
	invoiceObj.setQuantity(quantity);
	invoiceObj.setPricePerItem(pricePerItem);

	cout << "INVOICEOBJ DATA MEMBERS UPDATED" << endl;
	cout << "\n";

	// Print the new values of the four data members.
	// They should match the values of the local variables.
	// Use setw function to align output strings.
	cout << "VALUE OF INVOICEOBJ DATA MEMBERS" << endl;
	cout << "part number: " << setw(14) << invoiceObj.getPartNumber() << endl;
	cout << "part description: " << setw(7) << invoiceObj.getPartDescription() << endl;
	cout << "quantity: " << setw(11) << invoiceObj.getQuantity() << endl;
	cout << "price per item: " << setw(4) << "$" << invoiceObj.getPricePerItem() << endl;
	cout << "\n";

	// Test the getInvoiceAmount member function.
	cout << "INVOICE AMOUNT: " << setw(4) << "$" << invoiceObj.getInvoiceAmount() << endl;
	cout << "\n";
	
	// Print the invalid quantity and invalid price per item.
	cout << "LOCAL VARIABLES WITH INVALID VALUES" << endl;
	cout << "Quantity: " << setw(12) << invalidQuantity << endl;
	cout << "Price per item: " << setw(4) << "$" << invalidPricePerItem << endl;
	cout << "\n";

	// Set the quantity and price per item to invalid values.
	invoiceObj.setQuantity(invalidQuantity);
	invoiceObj.setPricePerItem(invalidPricePerItem);

	cout << "INVOICEOBJ DATA MEMBERS UPDATED" << endl;
	cout << "\n";

	// Print the results of setting the quantity and price per item to
	// invalid values.
	cout << "VALUE OF INVOICEOBJ DATA MEMBERS" << endl;
	cout << "quantity: " << setw(8) << invoiceObj.getQuantity() << endl;
	cout << "price per item: " << setw(1) << "$" << invoiceObj.getPricePerItem() << endl;
}