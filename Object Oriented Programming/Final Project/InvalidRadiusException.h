/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
Final Project
9/18/2021

InvalidRadiusException.h

Below is the "InvalidRadiusException" class, which inherits from the
runtime_error class.

Certain functions will throw this exception when an arc's radius is
not greater than zero.

*/

#ifndef INVALIDRADIUSEXCEPTION_H
#define INVALIDRADIUSEXCEPTION_H

#include <stdexcept> // contains runtime_error
using std::runtime_error;

// inherits from the runtime_error class
class InvalidRadiusException : public runtime_error {
public:

	// Constuctor
	InvalidRadiusException() :
		// initialization list calls base class constructor
		runtime_error{ "Radius must be greater than zero." } {}
};

#endif
