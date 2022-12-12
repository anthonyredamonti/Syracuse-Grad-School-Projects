/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
5/28/2022

ReduceProcess.h

Below is ReduceProcess.cpp, which is called by the ReduceProcess Main function.
The constructor takes the intermediate file path, output file path, process number,
and thread number as arguments.
The private data member function "reduceThread" call the reduce method in the
ReduceLibrary DLL.

*/

// Header Guard
#ifndef REDUCEPROCESS_H
#define REDUCEPROCESS_H

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

// definition for reduce function in ReduceLibrary DLL.
typedef void (*funcReduce)(string, string);

class ReduceProcess {
public:
	// Public Data Member Functions

	// Constructor takes a pointer to the intermediate file path as an argument. 
	ReduceProcess(string intermediateFilePath, string outputFilePath, string processNumber, string numberOfThreads);

	// Destructor
	virtual ~ReduceProcess();

private:

	// boolean variable indicating whether the process is complete.
	bool done{ false };

	//Pre-condition: Output file path, the thread number, and a vector to strings that have been 
	// formatted by the sorting object.
	//Post-condition: The reduce thread will call the reduce method in the Reduce Library (DLL).
	void reduceThread(string outputFilePath, int threadNumber, vector<string> stringVector);

	//Pre-condition: None.
	//Post-condition: The heartbeat thread will send a heartbeat message every 5 secconds to the 
	// controller process. When reducing is complete, it will send "Reducing complete".
	void heartbeatThread(int processNumber);
};

#endif
