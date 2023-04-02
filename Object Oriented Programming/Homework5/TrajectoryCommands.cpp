/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
HW #5
8/19/2021

TrajectoryCommands.cpp

Below is the TrajectoryCommands class. It is used to create properly
formatted ASCII commands for the user. The user can send these
commands to a servo drive to load a trajectory ready for execution.

There are two constructors: default and initialization constructor.
User units are converted to drive units using the two functions: 
convertRpsToCountsPerSecSquared() and convertRpmToCountsPerSec().

The user must enter values within an established range for each
parameter. The user must enter non-negative values no greater than 
maxVelocity, maxAccel, and maxDecel.
*/

#include "TrajectoryCommands.h"
#include <iomanip>    // needed for setw() and setfill()

using std::cout;
using std::to_string;
using std::setfill;
using std::setw;

// The TrajectoryCommands default constructor
TrajectoryCommands::TrajectoryCommands():
	commandedPosition{ 0 },
	commandedVelocity{ 0 },
	commandedAccel{ 0 },
	commandedDecel{ 0 },
	encoderCountsPerRev{ 0 },
	maxAccel{ 5000 },   // max accel in units of RPS^2
	maxDecel{ 5000 },   // max decel in units of RPS^2
	maxVelocity{ 5000 } // max velocity in units of RPM
{
	setParameters();
}

// The TrajectoryCommands constructor which initializes the private data members
TrajectoryCommands::TrajectoryCommands(int inputEncoderCountsPerRev, int inputPosition, int inputVelocity, int inputAcceleration, int inputDeceleration) :
	encoderCountsPerRev{ inputEncoderCountsPerRev },
	commandedPosition{ inputPosition },
	commandedVelocity{ inputVelocity },
	commandedAccel{ inputAcceleration },
	commandedDecel{ inputDeceleration },
	maxAccel{ 5000 },   // max accel in units of RPS^2
	maxDecel{ 5000 },   // max decel in units of RPS^2
	maxVelocity{ 5000 } // max velocity in units of RPM
{
	setParameters();
}

// populate the ASCII parameter array with ASCII parameter ID's
void TrajectoryCommands::setParameters() {
	asciiParameterIdArray = { "0xca", "0xcb", "0xcc", "0xcd" };
	asciiParameterNameArray = { "Commanded Position", "Commanded Velocity", "Commanded Acceleration", "Commanded Deceleration" };
}

// virtual destructor
TrajectoryCommands::~TrajectoryCommands(){
	// nothing to do at this time.
}

// retrieve the commanded position
int TrajectoryCommands::getCommandedPosition() {
	return commandedPosition;
}

// set the commanded position
void TrajectoryCommands::setCommandedPosition(int& inputCommandedPosition) {
	commandedPosition = inputCommandedPosition;
	createAsciiCommand(0, commandedPosition);
}

// retrieve the commanded velocity
int TrajectoryCommands::getCommandedVelocity() {
	return commandedVelocity;
}

// set the commanded velocity
int TrajectoryCommands::setCommandedVelocity(int& inputCommandedVelocity) {
	if (isVelocityValid(inputCommandedVelocity)) {
		inputCommandedVelocity = convertRpmToCountsPerSec(inputCommandedVelocity);
		commandedVelocity = inputCommandedVelocity;
		createAsciiCommand(1, commandedVelocity);
		return 1;
	}
	else {
		cout << "\nPlease enter a commanded velocity between 0 and " << maxVelocity << '.';
		return -1;
	}
}

// retrieve the maximum acceleration
int TrajectoryCommands::getCommandedAccel() {
	return commandedAccel;
}

// set the maximum acceleration
int TrajectoryCommands::setCommandedAccel(int* inputMaxAccel) {
	if (isAccelValid(*inputMaxAccel)) {
		*inputMaxAccel = convertRpsToCountsPerSecSquared(*inputMaxAccel);
		commandedAccel = *inputMaxAccel;
		createAsciiCommand(2, commandedAccel);
		return 1; // success
	}
	else {
		cout << "\nPlease enter a commanded acceleration between 0 and " << maxAccel << '.';
		return -1; // error
	}
}

// retrieve the maximum deceleration
int TrajectoryCommands::getCommandedDecel() {
	return commandedDecel;
}

// set the maximum deceleration
int TrajectoryCommands::setCommandedDecel(int* inputMaxDecel) {
	if (isDecelValid(*inputMaxDecel)) {
		*inputMaxDecel = convertRpsToCountsPerSecSquared(*inputMaxDecel);
		commandedDecel = *inputMaxDecel;
		createAsciiCommand(3, commandedDecel);
		return 1; // success
	}
	else {
		cout << "\nPlease enter a commanded deceleration between 0 and " << maxDecel << '.';
		return -1; // error
	}
}

// retrieve the encoder counts per rev
int TrajectoryCommands::getEncoderCountsPerRev() {
	return encoderCountsPerRev;
}

// set the encoder counts per rev
int TrajectoryCommands::setEncoderCountsPerRev(int inputEncoderCountsPerRev) {
	if (isEncoderCountsPerRevValid(inputEncoderCountsPerRev)) {
		encoderCountsPerRev = inputEncoderCountsPerRev;
		return 1; // success
	}
	else {
		cout << "\nPlease enter encoder counts per rev greater than zero.";
		return -1; // error
	}
};

// check if the user's input accel is valid
bool TrajectoryCommands::isAccelValid(int inputAccel) {
	if ((inputAccel >= 0) && (inputAccel <= maxAccel)) {
		return true; // valid input
	}
	else {
		return false; // invalid input
	}
}

// check if the user's input decel is valid
bool TrajectoryCommands::isDecelValid(int inputDecel) {
	if ((inputDecel >= 0) && (inputDecel <= maxDecel)) {
		return true; // valid input
	}
	else {
		return false; // invalid input
	}
}

// check if the user's input velocity is valid
bool TrajectoryCommands::isVelocityValid(int inputVel) {
	if ((inputVel >= 0) && (inputVel <= maxVelocity)) {
		return true; // valid input
	}
	else {
		return false; // invalid input
	}
}

// check if the user's input encoder counts per rev is valid
bool TrajectoryCommands::isEncoderCountsPerRevValid(int inputEncoderCountsPerRev) {
	if (inputEncoderCountsPerRev > 0) {
		return true; // valid input
	}
	else {
		return false; // invalid input
	}
}

// convert from RPS^2 to 10 counts/sec^2
int TrajectoryCommands::convertRpsToCountsPerSecSquared(int inputRps) {
	int countsPerSecSquared = (inputRps * encoderCountsPerRev) / 10;
	return(countsPerSecSquared);
}

// convert from RPM to 0.1 counts/sec
int TrajectoryCommands::convertRpmToCountsPerSec(int inputRpm) {
	int countsPerSec = (inputRpm / 60) * encoderCountsPerRev * 10;
	return(countsPerSec);
}

// properly format the ASCII command and push it in the ASCII command vector
void TrajectoryCommands::createAsciiCommand(int index, int value) {
	string asciiCommand{ "" };
	string parameterId = asciiParameterIdArray[index];
	string beginningString = "s r";
	char space = ' ';
	asciiCommand = beginningString + parameterId + space + to_string(value);
	asciiCommandsVector.push_back(asciiCommand);
}

// Use a range based loop to print each command in the vector
void TrajectoryCommands::printCommands() {
	cout << "\n\nPlease send the following ASCII commands over the serial port to the drive at 9600 baud:";
	for (string command : asciiCommandsVector) {   // range based for loop
		cout << '\n' << command;
	}
	cout << '\n';
}

// return the address of the requested index into the ASCII parameter ID array.
string* TrajectoryCommands::getAsciiParameterIdArray(int index) {
	if ((index < 0) || (index >= numberOfParameters)) {
		cout << "\nPlease request a valid index of the parameter ID array.";
		return( NULL );
	}
	else {
		string* asciiId{ NULL };
		asciiId = &asciiParameterIdArray[index];
		return(asciiId);
	}
}

// return the address of the requested index into the ASCII parameter name array.
string* TrajectoryCommands::getAsciiParameterNameArray(int index) {
	if ((index < 0) || (index >= numberOfParameters)) {
		cout << "\nPlease request a valid index of the parameter name array.";
		return(NULL);
	}
	else {
		string* parameterName{ NULL };
		parameterName = &asciiParameterNameArray[index];
		return(parameterName);
	}
}