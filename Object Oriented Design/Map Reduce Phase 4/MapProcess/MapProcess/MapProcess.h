/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
5/28/2022

MapProcess.h

Below is MapProcess.cpp, which is called by the MapProcess Main function.
The constructor takes the intermediate file path, output file path, process number,
and thread number as arguments.
The private data member function "mapThread" call the map method in the
MapLibrary DLL.

*/

// Header Guard
#ifndef MAPPROCESS_H
#define MAPPROCESS_H

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

// definition for Map function in MapLibrary DLL.
typedef void (*funcMap)(string, string);

class MapProcess {
public:
	// Public Data Member Functions

	// Constructor takes a pointer to the input file path as an argument. 
	MapProcess(string inputFilePath, string intermediateFilePath, string processNumber, string numberOfThreads, string numberOfFilesFound);

	// Destructor
	virtual ~MapProcess();

private:

	// boolean variable indicating whether the process is complete.
	bool done{ false };

	//Pre-condition: Intermediate file path, the thread number, and a vector to strings that have been 
	// formatted.
	//Post-condition: The map thread will call the map method in the Map Library (DLL).
	void mapThread(string intermediateFilePath, int threadNumber, vector<string> stringVector);

	//Pre-condition: None.
	//Post-condition: The heartbeat thread will send a heartbeat message every 5 secconds to the 
	//Controller process. When reducing is complete, it will send "Mapping complete".
	void heartbeatThread(int processNumber, string numberOfFilesFound);
};

#endif
