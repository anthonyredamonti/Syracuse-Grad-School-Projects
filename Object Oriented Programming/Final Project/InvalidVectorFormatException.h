/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
Final Project
9/18/2021

InvalidVectorFormatException.h

Below is the "InvalidVectorFormatException" class, which inherits from the
runtime_error class.

Certain functions will throw this exception when a vector's length
is not 2.

*/

#ifndef INVALIDVECTORFORMATEXCEPTION_H
#define INVALIDVECTORFORMATEXCEPTION_H

#include <stdexcept> // contains runtime_error
using std::runtime_error;

// inherits from the runtime_error class
class InvalidVectorFormatException : public runtime_error {
public:

	// Constuctor
	InvalidVectorFormatException() :
		// initialization list calls base class constructor
		runtime_error{ "Vector size is not 2." } {}
};

#endif
