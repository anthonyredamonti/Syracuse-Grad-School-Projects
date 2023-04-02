/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
Final Project
9/18/2021

Heart.cpp

Below is the "Heart" class, which inherits from the
abstract base class "TwoDimensionalShape." In the
constructor, the user defines the (x, y) coordinates
of the starting position and the name of the heart.

The function "printShapeInfo" is defined in the base
class as pure virtual and therefore, must be defined
by any derived class.

*/

#include "Heart.h"

// The Heart constructor which initializes the private data members
Heart::Heart(vector<double> inputStartingPosition, string inputName) {
	// If the two dimensional input starting position vector is not properly formatted,
	// terminate the constructor
	if (inputStartingPosition.size() != 2) {
		cout << "\nException occured in \"Heart::Heart\" constructor.\n";
		throw InvalidVectorFormatException{}; // terminate constructor
	}

	setName(inputName); // call the setName function inherited from the Shape class
	setStartingPosition(inputStartingPosition); // set the starting position in the Shape base class

	try {
		drawHeart(); // draw the heart using the given starting position and radius
	}
	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occured in \"Heart::Heart\" constructor.\n";
		cout << exception.what();
		throw exception;
	}
	// catch any exception here
	catch (...) {
		cout << "\nException occured in \"Heart::Heart\" constructor.\n";
		throw;
	}
}

// Heart class destructor
Heart::~Heart() {
	// nothing to do at this time
}

// draw the heart using the addLine and addArc inherited functions from the Shape base class (abstract).
void Heart::drawHeart() {

	// initialize local variables
	vector<double> currentPosition{ 0.0, 0.0 };
	vector<double> startingPosition{ 0.0, 0.0 };
	vector<double> nextDestination{ 0.0, 0.0 };
	vector<double> arcCenter{ 0.0, 0.0 };
	double size{ 0 };
	double fortyFiveDegreesInRadians{ 0 };

	// get the first positions in each dimension. Create a heart starting from there.
	startingPosition = getStartingPosition();

	// used to scale the size of the heart
	size = 400.0;
	
	try{
		// convert 45 degrees to radians
		fortyFiveDegreesInRadians = convertDegreesToRadians(45);

		// next destination vector 
		nextDestination = { startingPosition[0] - (size * cos(fortyFiveDegreesInRadians)), startingPosition[1] + (size * sin(fortyFiveDegreesInRadians)) };
		addLine(nextDestination);

		// update the current position vector
		currentPosition = getEndingPosition();

		// the first 180 degree arc
		arcCenter = { currentPosition[0] + (((3 * size) / 8) * cos(fortyFiveDegreesInRadians)), currentPosition[1] + (((3 * size) / 8) * sin(fortyFiveDegreesInRadians)) };
		addArc(arcCenter, -180);

		// update the current position vector
		currentPosition = getEndingPosition();

		// move down to meet next half
		nextDestination = { currentPosition[0] + ((size / 4) * cos(fortyFiveDegreesInRadians)), currentPosition[1] - ((size / 4) * sin(fortyFiveDegreesInRadians)) };
		addLine(nextDestination);

		// update the current position vector
		currentPosition = getEndingPosition();

		// begin second half of heart. Move up before beginning next arc segment
		nextDestination = { currentPosition[0] + ((size / 4) * cos(fortyFiveDegreesInRadians)), currentPosition[1] + ((size / 4) * sin(fortyFiveDegreesInRadians)) };
		addLine(nextDestination);

		// update the current position vector
		currentPosition = getEndingPosition();

		// the second 180 degree arc
		arcCenter = { currentPosition[0] + (((3 * size) / 8) * cos(fortyFiveDegreesInRadians)), currentPosition[1] - (((3 * size) / 8) * sin(fortyFiveDegreesInRadians)) };
		addArc(arcCenter, -180);

		// next destination vector equals the starting position vector
		nextDestination = { startingPosition[0], startingPosition[1] };
		addLine(nextDestination);
	}
	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occured in \"Heart::drawHeart\" function.\n";
		cout << exception.what();
		throw exception;
	}
	// catch any exception here
	catch (...) {
		cout << "\nException occured in \"Heart::drawHeart\" function.\n";
		throw;
	}
}

// relocate the heart by updating the starting position using the 
// provided input coordinates.
void Heart::relocate(vector<double> inputCoordinates) {
	// check the validity of the user input
	if (inputCoordinates.size() != 2) {
		cout << "\nException occured in \"Heart::relocate\" function.\n";
		throw InvalidVectorFormatException{}; // terminate function
	}
	else{
		// initialize local variables
		vector<vector<double>>* positionsPntr{ NULL };

		// retrieve the pointer to the multidimensional position vector
		positionsPntr = getPositionVector();

		// clear out the previous points
		positionsPntr->clear();

		// reinitialize the multidimensional vector with {0, 0}		
		for (int i = 0; i < getDimension(); i++) {
			(*positionsPntr).push_back({ 0 });
		}

		// set the starting position to the input coordinates
		setStartingPosition(inputCoordinates);

		try {
			// redraw the heart
			drawHeart();
		}
		// catch exception handled in exception class here
		catch (const runtime_error& exception) {
			cout << "\nException occured in \"Heart::relocate\" function.\n";
			cout << exception.what();
			throw exception;
		}
		// catch any exception here
		catch (...) {
			cout << "\nException occured in \"Heart::relocate\" function.\n";
			throw;
		}
	}
}

// print the information of the shape. Defines the pure virtual function of the base class.
void Heart::printShapeInfo() {
	
	// initialize local variable
	vector<double> startingPosition{ 0.0, 0.0 };

	// get the starting position
	startingPosition = getStartingPosition();

	// print the name and the starting (x, y) coordinates of the heart
	cout << "\nHEART DERIVED CLASS printShapeInfo() CALLED"
		"\nName: " << getName() <<
		"\nStarting (x, y) Coordinates: (" << setprecision(2) << fixed << startingPosition[0] << ", " << startingPosition[1] << ')';
}

// convert the input degrees to radians.
double Heart::convertDegreesToRadians(double inputDegrees) {

	// initialize local variable
	double radians{ 0.0 };

	// try calculation
	try {
		radians = inputDegrees * (PI_CONST / 180);
	}

	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occured in \"Heart::convertDegreesToRadians\" function.\n";
		cout << exception.what();
		throw exception;
	}
	// catch any exception here
	catch (...) {
		cout << "\nException occured in \"Heart::convertDegreesToRadians\" function.\n";
		throw;
	}
	// return the answer in radians
	return radians;
}