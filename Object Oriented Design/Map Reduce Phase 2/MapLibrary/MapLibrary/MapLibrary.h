/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 2
4/28/2022

Map.h

---Note: This file does include the BOOST library in order to compile.

Below is the "Map" class.
The Map class is called by the Workflow class.
The constructor will take a string reference of the file to write too and a string reference of a line of raw data.
This will then call the tokenize() function to remove punctuation, whitespace, and capitalization.
Each word will then be given to the exportt() function to be written into the output file.

Example input data:  The dog likes to jump.
Example output data: ("the", 1), ("dog", 1), ("likes", 1), ("to", 1), ("jump", 1)

*/
// MathLibrary.h - Contains declarations of math functions
#pragma once

#ifdef MAPLIBRARY_EXPORTS
#define MAPLIBRARY_API __declspec(dllexport)
#else
#define MAPLIBRARY_API __declspec(dllimport)
#endif
//Directives
#include<algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include <stdexcept> // contains runtime_error
#include<boost/tokenizer.hpp>//boost library

//Name spaces
using std::cout;
using std::string;
using std::vector;
using std::exception;
using std::runtime_error;
using boost::tokenizer;

extern "C" MAPLIBRARY_API void Map(string & fileName, string & lineOfData);
extern "C" MAPLIBRARY_API void tokenize(string & fileName, string & lineOfData);
extern "C" MAPLIBRARY_API void exportt(string & fileName, tokenizer<>::iterator & word);
