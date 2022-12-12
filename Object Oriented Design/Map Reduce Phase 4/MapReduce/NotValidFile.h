/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
4/9/2022

NotValidFile.h

Below is the "NotValidFile" class.
This is an exception handler if user inputs a bad file



*/
// Header Guard
#ifndef NOTVALIDFILE_H
#define NOTVALIDFILE_H

//Directives
#include <stdexcept> //stdexcept header contains runtime_error


class NotValidFile : public std::runtime_error
{
public:

	//constructor specifies default error message
	NotValidFile()
		: std::runtime_error{ "Not a valid file directory/location." } {}


};

#endif
