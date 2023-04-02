/*
Anthony Redamonti
Professor Jonathan S.Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
HW #1 - Exercise 3.10 p100
7/28/2021

Invoice.h

For a full description of the Invoice class, please
see Invoice.cpp.
*/ 

#ifndef INVOICE_H
#define INVOICE_H

using std::string;

class Invoice {
public:
	Invoice(); // Constuctor used to initialize private data members.

	// Get/Set functions for each of the four private data members.
	string getPartNumber();
	void setPartNumber(string inputPartNum);
	string getPartDescription();
	void setPartDescription(string inputPartDescrip);
	int getQuantity();
	void setQuantity(int inputQuantity);
	int getPricePerItem();
	void setPricePerItem(int inputPricePerItem);

	// getInvoiceAmount member function
	int getInvoiceAmount();
private:
	// private data members
	string partNumber;
	string partDescription;
	int quantity;
	int pricePerItem;
};

#endif
