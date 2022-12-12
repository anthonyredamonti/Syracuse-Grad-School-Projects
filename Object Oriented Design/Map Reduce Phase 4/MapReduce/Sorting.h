/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
4/9/2022

Sorting.h

Below is the "Sorting" class, which is called by the Workflow class.
The constructor takes the intermediate file path as an argument.
The public data member function "format" will format the data for
the Reduce class.

Example input data: ("a", 1), ("the", 1), ("is", 1), ("the", 1), ("a", 1)
Example output data: ("a", [1, 1]), ("the", [1, 1]), ("is", [1])

*/

// Header Guard
#ifndef SORTING_H
#define SORTING_H

// include the iostream and fstream namespaces
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept> // contains runtime_error
#include <boost/log/trivial.hpp>

// using the ofstream class from the standard namespace.
using std::cout;
using std::ofstream;
using std::ifstream;
using std::string;
using std::vector;
using std::runtime_error;
using std::to_string;
using std::getline;
using std::endl;


class Sorting {
public:
	// Public Data Member Functions

	// Constructor takes a pointer to the intermediate file path as an argument. 
	Sorting(string* intermediateFilePath);

	// get a pointer to the intermediate file path
	string* getIntermediateFilePath();

	// set the intermediate file path
	void setIntermediateFilePath(string* intermediateFilePath);

	// formats the data for the Reduce class.
	void format();

	// Destructor
	virtual ~Sorting();

private:

	// a private struct "word"
	struct word {
		string key;
		int numberOfOccurrences;
	};

	// a vector of all collected words
	vector<word> wordVector;

	// Private Data Member Variables
	string intermediateFilePath;

	// record the original word list length.
	size_t originalWordListLength;
	
	// swap two words in the vector
	void swap(word* wordPntr1, word* wordPntr2);

};

#endif
