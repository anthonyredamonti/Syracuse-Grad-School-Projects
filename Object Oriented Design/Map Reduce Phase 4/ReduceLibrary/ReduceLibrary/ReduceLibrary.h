/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
4/9/2022

Reduce.h

Below is the "Reduce" class, which is called by the Workflow class.
The constructor takes the output file path and output string as an
argument. It interprets the key and calculates the total in the
iterator before calling the private data member function "export."
Export will simply write the data in the correct format to the
output file path destination.

*/

// ReduceLibrary.h - Contains declarations of Reduce functions
#pragma once

#define  _WIN32_WINNT   0x0601
#ifdef REDUCELIBRARY_EXPORTS
#define REDUCELIBRARY_API __declspec(dllexport)
#else
#define REDUCELIBRARY_API __declspec(dllimport)
#endif

// include the iostream and fstream name spaces
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept> // contains runtime_error
#include <boost/log/trivial.hpp>

// using the ofstream class from the standard name space.
using std::cout;
using std::ofstream;
using std::string;
using std::to_string;
using std::ios_base;
using std::runtime_error;
using std::endl;

extern "C" REDUCELIBRARY_API void Reduce(string & outputFilePath, string & inputString);
void ReduceExport(string & outputFilePath, string key, size_t sum);

