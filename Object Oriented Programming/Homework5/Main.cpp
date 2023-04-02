/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
HW #5
8/19/2021

Main.cpp

The following program creates an instance of the TrajectoryCommands
class. After the user provides the counts/rev of the encoder, they
will be prompted for the values to enter in the trajectory parameters.
The program will create four properly formatted ASCII commands to
send to the drive over serial at 9600 baud and store them in a vector.
The program will display a list of parameter names along with their
parameter ID's and then output the properly formatted ASCII commands
to the console. 

*/

#include "TrajectoryCommands.h"  // defines the TrajectoryCommands class

// importing objects from the C++ standard library
using std::cin;
using std::cout;

// print "SU" for Syracuse University on the console
void printSyracuseBanner(); 

int main() {

	// initialize local variables
	int inputCommandedPosition{ 0 };
	int inputCommandedVelocity{ 0 };
	int inputCommandedAccel{ 0 };
	int inputCommandedDecel{ 0 };
	int inputEncoderCountsPerRev{ 0 };
	int inputIsValid{ 0 };
	int* accelPntr{ NULL };
	int* decelPntr{ NULL };
	string* parameterIdPntr{ NULL };
	string* parameterNamePntr{ NULL };

	// load local variable addresses into pointers
	accelPntr = &inputCommandedAccel;
	decelPntr = &inputCommandedDecel;

	TrajectoryCommands trajCommObj; // create an instance of the trajectory commands class

	// print Syracuse Banner
	printSyracuseBanner();

	// information about program
	cout << "\nWelcome to the Trajectory Commands Program!" <<
		"\nA servo drive controls a servo motor and" <<
		"\nis commonly used in motion control applications." <<
		"\nThe following program asks the user for values" <<
		"\nto write to the trajectory parameters of a servo" <<
		"\ndrive. The program will display the parameter" <<
		"\nnames with their ID's."
		"\nThe program then displays the properly"  <<
		"\nformatted ASCII commands to transmit over the" <<
		"\nserial port to the drive.\n\n";

	// prompt the user for the encoder counts per rev.
	cout << "\nPlease enter the encoder counts per revolution: ";
	cin >> inputEncoderCountsPerRev;
	inputIsValid = trajCommObj.setEncoderCountsPerRev(inputEncoderCountsPerRev); // pass by value

	// If the user entered an invalid value, prompt the user for 
    // the encoder counts per rev again.
	while (inputIsValid == -1) {
		cout << "\nPlease re-enter the counts per revolution: ";
		cin >> inputEncoderCountsPerRev;
		inputIsValid = trajCommObj.setEncoderCountsPerRev(inputEncoderCountsPerRev); // pass by value
	}

	// prompt the user for the commanded position
	cout << "Please enter the commanded position in units of counts: ";
	cin >> inputCommandedPosition;
	trajCommObj.setCommandedPosition(inputCommandedPosition); // pass by reference

	// prompt the user for the commanded velocity in units of RPM
	cout << "Please enter the commanded velocity in units of RPM: ";
	cin >> inputCommandedVelocity;
	inputIsValid = trajCommObj.setCommandedVelocity(inputCommandedVelocity); // pass by reference

	// If the user entered an invalid value, prompt the user for 
	// the commanded velocity again.
	while (inputIsValid == -1) {
		cout << "\nPlease re-enter the commanded velocity in units of RPM: ";
		cin >> inputCommandedVelocity;
		inputIsValid = trajCommObj.setCommandedVelocity(inputCommandedVelocity); // pass by reference
	}

	// prompt the user for the commanded acceleration in units of RPS^2
	cout << "Please enter the commanded acceleration in units of RPS^2: ";
	cin >> inputCommandedAccel;
	inputIsValid = trajCommObj.setCommandedAccel(accelPntr);                     // pass by pointer

	// If the user entered an invalid value, prompt the user for 
	// the commanded acceleration again.
	while(inputIsValid == -1){
		cout << "\nPlease re-enter the commanded acceleration in units of RPS^2: ";
		cin >> inputCommandedAccel;
		inputIsValid = trajCommObj.setCommandedAccel(accelPntr);                 // pass by pointer
	}

	// prompt the user for the commanded deceleration in units of RPS^2
	cout << "Please enter the commanded deceleration in units of RPS^2: ";
	cin >> inputCommandedDecel;
	inputIsValid = trajCommObj.setCommandedDecel(decelPntr);                     // pass by pointer

	// If the user entered an invalid value, prompt the user for 
	// the commanded deceleration again.
	while (inputIsValid == -1) {
		cout << "\nPlease re-enter the commanded deceleration in RPS^2: ";
		cin >> inputCommandedDecel;
		inputIsValid = trajCommObj.setCommandedDecel(decelPntr);                 // pass by pointer
	}

	// print the parameter names with their ID's
	for (int i = 0; i < numberOfParameters; i++) {                              // for loop
		parameterNamePntr = trajCommObj.getAsciiParameterNameArray(i);          // returns a pointer to a string
		parameterIdPntr = trajCommObj.getAsciiParameterIdArray(i);              // returns a pointer to a string
		cout << "\nThe ASCII Parameter ID for " << *parameterNamePntr << " is " << *parameterIdPntr << '.'; // dereferencing string pointers
	}

	trajCommObj.printCommands(); // display the formatted ASCII commands to the user
}

// Print "SU" for Syracuse University on the console.
void printSyracuseBanner() {
	cout 
		<< "                   .-----------.            .----.          .----.\n"
		<< "                 /             |            |    |          |    |\n"
		<< "                /    .---------*            |    |          |    |\n"
		<< "               .    /                       |    |          |    |\n"
		<< "               |   |                        |    |          |    |\n"
		<< "               |    .                       |    |          |    |\n"
		<< "                .    *-------.              |    |          |    |\n"
		<< "                 *.            *            |    |          |    |\n"
		<< "                   *----.       *           |    |          |    |\n"
		<< "                          .      *          |    |          |    |\n"
		<< "                          |      |          |    |          |    |\n"
		<< "                         /       /          |    |          |    |\n"
		<< "                .-------*       *           *     *--------*     /\n"
		<< "                |             *              *                  / \n"
		<< "                *----------*                   *--------------*   \n\n";
}