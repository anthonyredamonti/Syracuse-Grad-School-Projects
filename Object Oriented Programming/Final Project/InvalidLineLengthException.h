/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
Final Project
9/18/2021

InvalidLineLengthException.h

Below is the "InvalidLineLengthException" class, which inherits from the
runtime_error class.

Certain functions will throw this exception when a line's length is not 
greater than zero.

*/

#ifndef INVALIDLINELENGTHEXCEPTION_H
#define INVALIDLINELENGTHEXCEPTION_H

#include <stdexcept> // contains runtime_error
using std::runtime_error;

// inherits from the runtime_error class
class InvalideLineLengthException : public runtime_error {
public:

	// Constuctor
	InvalideLineLengthException() :
		// initialization list calls base class constructor
		runtime_error{ "The length of the line must be greater than zero." } {}
};

#endif
