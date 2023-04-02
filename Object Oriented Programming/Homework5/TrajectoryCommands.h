/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
HW #5
8/19/2021

TrajectoryCommands.h

Below is the TrajectoryCommands class. It is used to create properly 
formatted ASCII commands for the user. The user can send these
commands to a servo drive to load a trajectory ready for execution.

*/

#ifndef TRAJECTORYCOMMANDS
#define TRAJECTORYCOMMANDS
#include<vector>
#include<string>
#include<array>
#include<iostream>

#define numberOfParameters 4 // four parameters

using std::string;
using std::array;
using std::vector;

class TrajectoryCommands {
public:
	// ------------- PUBLIC DATA MEMBER FUNCTIONS ----------------
	
	// Default Constructor
	TrajectoryCommands();

	// Initialization Constuctor: used to initialize private data members.
	TrajectoryCommands(int inputEncoderCountsPerRev, int inputPosition, int inputVelocity, int inputAcceleration, int inputDeceleration);

	// virtual destructor
	virtual ~TrajectoryCommands();

	// "Get/Set" functions.
	int getEncoderCountsPerRev();
	int setEncoderCountsPerRev(int inputEncoderCountsPerRev);       // pass by value
	int getCommandedPosition();
	void setCommandedPosition(int& inputCommandedPosition);         // pass by reference
	int getCommandedVelocity();
	int setCommandedVelocity(int& inputCommandedVelocity);          // pass by reference
	int getCommandedAccel();
	int setCommandedAccel(int* inputMaxAccel);                      // pass by pointer
	int getCommandedDecel();
	int setCommandedDecel(int* inputMaxDecel);                      // pass by pointer
	string* getAsciiParameterIdArray(int index);
	string* getAsciiParameterNameArray(int index);
	
	void printCommands(); // print properly formatted ASCII commands    --- uses range based for loop

private:
	// -----------  PRIVATE DATA MEMBER FUNCTIONS ---------------
	void createAsciiCommand(int index, int value);
	void setParameters();
	bool isEncoderCountsPerRevValid(int inputEncoderCountsPerRev);
	bool isVelocityValid(int inputVelocityCommand);
	bool isAccelValid(int inputAccelCommand);
	bool isDecelValid(int inputDecelCommand);
	int convertRpmToCountsPerSec(int inputRpm);        // convert RPM to 0.1 counts/sec units
	int convertRpsToCountsPerSecSquared(int inputRps); // convert RPS^2 to 0.1 counts/sec^2 units

	// -----------  PRIVATE DATA MEMBER VARIABLES ---------------
	int commandedPosition;
	int commandedVelocity;
	int commandedAccel;
	int commandedDecel;
	int maxVelocity;
	int maxAccel;
	int maxDecel;
	int encoderCountsPerRev;
	vector<string> asciiCommandsVector;                          // vector of formatted ASCII commands
	array<string, numberOfParameters> asciiParameterIdArray;     // array of parameter ID's
	array<string, numberOfParameters> asciiParameterNameArray;   // array of parameter names
};

#endif
