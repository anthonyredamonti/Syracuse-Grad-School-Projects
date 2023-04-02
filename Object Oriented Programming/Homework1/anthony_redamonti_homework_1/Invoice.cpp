/*
Anthony Redamonti
Professor Jonathan S.Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
HW #1 - Exercise 3.10 p100
7/28/2021

Invoice.cpp

Below is the "Invoice" class, which is used to catalog the 
invoices of a hardware store. The Invoice class has four 
data members: part number (type string), part description 
(type string), quantity of the item being sold (type int), 
and a price per item (type int). Each data member has 
respective get/set functions.

The Invoice Class also has a function getInvoiceAmount that
calculates the invoice amount and returns it as an integer
value. If the quantity is not positive, it is set to zero.
If the price per item is not positive, it is set to zero.
*/

#include <iostream>
#include "Invoice.h"

using std::string; // using the string class from the C++ standard library

// The Invoice constructor which initializes the four private data members.
Invoice::Invoice() 
	:  partNumber{""},
	partDescription{""},
	quantity{0},
	pricePerItem{0}
{}

// The data member function which retrieves the part number of the invoice.
string Invoice::getPartNumber() {
	return(partNumber);
}

// The data member function which sets the part number of the invoice.
void Invoice::setPartNumber(string inputPartNum) {
	partNumber = inputPartNum;
}

// The data member function which retrieves the description of the invoice.
string Invoice::getPartDescription() {
	return(partDescription);
}

// The data member function which sets the description of the invoice.
void Invoice::setPartDescription(string inputPartDescrip) {
	partDescription = inputPartDescrip;
}

// The data member function which retrieves the quantity of the invoice.
int Invoice::getQuantity() {
	return(quantity);
}

// The data member function which sets the quantity of the invoice.
// If the input value is less than zero, it is set to zero.
void Invoice::setQuantity(int inputQuantity) {
	if (inputQuantity < 0) {
		inputQuantity = 0;
	}
	quantity = inputQuantity;
}

// The data member function which gets the price per item of the invoice.
int Invoice::getPricePerItem() {
	return(pricePerItem);
}

// The data member function which sets the price per item of the invoice.
// If the input value is less than zero, it is set to zero.
void Invoice::setPricePerItem(int inputPricePerItem) {
	if (inputPricePerItem < 0) {
		inputPricePerItem = 0;
	}
	pricePerItem = inputPricePerItem;
}

// The member function that calculates and returns the invoice amount, 
// which is the product of the quantity and the price per item.
int Invoice::getInvoiceAmount() {
	int invoiceAmount{ quantity * pricePerItem };
	return(invoiceAmount);
}