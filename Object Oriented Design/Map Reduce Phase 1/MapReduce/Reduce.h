/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
4/9/2022

Reduce.h

Below is the "Reduce" class, which is called by the Workflow class.
The constructor takes the output file path as an argument.
The public data member function "reduce" takes an input string as 
its argument. It interprets the key and calculates the total in 
the iterator before calling the private data member function
"export." Export will simply write the data in the correct format
to the output file path destination.

*/

// Header Guard
#ifndef REDUCE_H
#define REDUCE_H

// include the iostream and fstream name spaces
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept> // contains runtime_error
#include <boost/log/trivial.hpp>

// using the ofstream class from the standard name space.
using std::ofstream;
using std::string;
using std::to_string;
using std::ios_base;
using std::runtime_error;

class Reduce {
public: 
	// Public Data Member Functions
	
	// Constructor takes a pointer to an output file path as an argument. 
	Reduce(string* outputFilePath);

	
	// get a pointer to the output file path
	string* getOutputFilePath();

	// set the output file path
	void setOutputFilePath(string* outputFilePath);

	// sums up the iterators and calls the export method.
	void reduce(string* inputString);

	// Destructor
	virtual ~Reduce();

private:

	

	// Private Data Member Functions
	// export the data to the output file path (one entry at a time)
	void exportt(string key, size_t sum);

	// Private Data Member Variables
	string outputFilePath;
};

#endif
