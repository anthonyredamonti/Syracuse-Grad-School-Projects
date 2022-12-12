/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
5/28/2022

Heartbeat.h

*/

// Header Guard
#ifndef HEARTBEAT_H
#define HEARTBEAT_H

// include the iostream and fstream namespaces
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept> // contains runtime_error
#include <boost/log/trivial.hpp>

// using the ofstream class from the standard namespace.
using std::cout;
using std::ofstream;
using std::ifstream;
using std::string;
using std::runtime_error;
using std::to_string;
using std::getline;
using std::endl;

class Heartbeat {
public:
	// Public Data Member Functions

	// default contructor
	Heartbeat();

	// receive the messages from the map heartbeat threads and wait for them to finish.
	void waitForMapToFinish();

	// receive the messages from the reduce heartbeat threads and wait for them to finish.
	void waitForReduceToFinish();

	// Destructor
	virtual ~Heartbeat();

private:

	// total number of the files found in the directory
	int totalNumberOfFiles{ 0 };

	// are the mapping threads done?
	bool mappingDone{ false };

	// are the reduce threads done?
	bool reducingDone{ false };

	//Pre-condition: None.
	//Post-condition: None.
	//Receive heartbeats from the map processes.
	void receiveMapHeartbeatsThread(int portNumberOffset, const char* ipAddress);

	//Pre-condition: None.
	//Post-condition: None.
	//Receive heartbeats from the reduce processes.
	void receiveReduceHeartbeatsThread(int portNumberOffset, const char* ipAddress);
};

#endif
