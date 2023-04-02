/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
Final Project
9/18/2021

Circle.cpp

Below is the "Circle" class, which inherits from the
abstract base class "TwoDimensionalShape." In the
constructor, the user defines the (x, y) coordinates
of the starting position, the length of the radius,
the spacing between generated (x, y) points, and the
name of the circle.

The function "printShapeInfo" is defined in the base
class as pure virtual and therefore, must be defined
by any derived class.

*/

#include "Circle.h"

// The Circle constructor which initializes the private data members
Circle::Circle(vector<double> inputStartingPosition, double inputRadius, string inputName){
	
	// If the two dimensional input starting position vector is not properly formatted,
	// terminate the constructor
	if (inputStartingPosition.size() != 2) {
		cout << "\nException occured in \"Circle::Circle\" constructor.\n";
		throw InvalidVectorFormatException{}; // terminate constructor
	}
	
	// if the input radius is not greater than zero, throw an exception.
	if (inputRadius <= 0) {
		cout << "\nException occured in \"Circle::Circle\" constructor.\n";
		throw InvalidRadiusException{}; // terminate constructor
	}

	setName(inputName); // call the setName function inherited from the Shape class

	radius = inputRadius; // set the private data member to the input value
	
	try {
		setStartingPosition(inputStartingPosition); // set the starting position in the Shape base class
	
		setArea(); // set the area private data member
		setCircumference(); // set the circumference private data member

		drawCircle(); // draw the circle using the given starting position and radius
	}
	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occured in \"Circle::Circle\" constructor.\n";
		cout << exception.what();
		throw exception;
	}
	// catch any exception here
	catch (...) {
		cout << "\nException occured in \"Circle::Circle\" constructor.\n";
		throw;
	}
}

// Circle class destructor
Circle::~Circle() {
	// nothing to do at this time
}

// draw the circle using the addArc inherited function from the Shape base class (abstract).
void Circle::drawCircle() {

	// initialize local variable
	vector<double> centerOfCircle{ 0.0, 0.0 };
	vector<double> startingPosition{ 0.0, 0.0 };

	// retrieve the starting position
	startingPosition = getStartingPosition();

	try {

		// get the first positions in each dimension. Use them to create starting position.
		// the coordinates of the center of the circle will be offset to the right of the 
		// starting position on the x-axis by a total of the radius value.
		centerOfCircle = { startingPosition[0] + radius, startingPosition[1] };

		// add the circle by using the center coordinates and a 360 degree arc.
		addArc(centerOfCircle, 360.0);
	}
	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occured in \"Circle::drawCircle\" function.\n";
		cout << exception.what();
		throw exception;
	}
	// catch any exception here
	catch (...) {
		cout << "\nException occured in \"Circle::drawCircle\" function.\n";
		throw;
	}
}

// set the area private data member using the radius.
void Circle::setArea() {

	// initialize local variable
	double radiusSquared{ 0.0 };

	try {
		// use power function
		radiusSquared = powerFunc(radius, 2);

		// return the area
		area = PI_CONST * radiusSquared;
	}
	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occured in \"Circle::setArea\" function.\n";
		cout << exception.what();
		throw exception;
	}
	// catch any exception here
	catch (...) {
		cout << "\nException occured in \"Circle::setArea\" function.\n";
		throw;
	}
}


// set the circumference private data member using the radius.
void Circle::setCircumference() {
	try {
		// update the circumference
		circumference = (2 * PI_CONST * radius);
	}
	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occured in \"Circle::setCircumference\" function.\n";
		cout << exception.what();
		throw exception;
	}
	// catch any exception here
	catch (...) {
		cout << "\nException occured in \"Circle::setCircumference\" function.\n";
		throw;
	}
}

// return the inputBase raised to the power of the inputExponent.
double Circle::powerFunc(double inputBase, int inputExponent) {

	// initialize local variable
	double answer{ 1 };
	try {
		// calculate answer in for-loop
		for (int i = 0; i < inputExponent; i++) {
			answer = answer * inputBase;
		}
	}
	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occured in \"Circle::powerFunc\" function.\n";
		cout << exception.what();
		throw exception;
	}
	// catch any exception here
	catch (...) {
		cout << "\nException occured in \"Circle::powerFunc\" function.\n";
		throw;
	}

	// return answer
	return answer;
}

// resize the circle using the provided input radius.
void Circle::resize(double inputRadius) {
	// check the validity of the user input
	if (inputRadius <= 0) {
		cout << "\nException occured in \"Circle::resize\" function.\n";
		throw InvalidRadiusException{}; // terminate function
	}
	else {

		// initialize local variables
		vector<vector<double>>* positionsPntr{ NULL };
		vector<double> startingPosition{ 0.0, 0.0 };
		
		radius = inputRadius; // update the radius

		// retrieve the pointer to the multidimensional position vector
		positionsPntr = getPositionVector();

		// retrieve the starting position
		startingPosition = getStartingPosition();

		// clear out the previous points
		positionsPntr->clear();

		// reinitialize the multidimensional vector with {0, 0}		
		for (int i = 0; i < getDimension(); i++) {
			(*positionsPntr).push_back({ 0 });
		}

		try {
			// set the original starting position
			setStartingPosition(startingPosition);

			// update the area and circumference with the new radius
			setArea();
			setCircumference();

			// redraw the circle
			drawCircle();
		}
		// catch exception handled in exception class here
		catch (const runtime_error& exception) {
			cout << "\nException occured in \"Circle::resize\" function.\n";
			cout << exception.what();
			throw exception;
		}
		// catch any exception here
		catch (...) {
			cout << "\nException occured in \"Circle::resize\" function.\n";
			throw;
		}
	}
}

// relocate the circle by updating the starting position using the 
// provided input coordinates.
void Circle::relocate(vector<double> inputCoordinates) {
	// check the validity of the user input
	if (inputCoordinates.size() != 2) {
		cout << "\nException occured in \"Circle::relocate\" function.\n";
		throw InvalidVectorFormatException{}; // terminate function
	}
	else {

		// initialize local variable
		vector<vector<double>>* positionsPntr{ NULL };

		// retrieve the pointer to the multidimensional position vector
		positionsPntr = getPositionVector();

		// clear out the previous points
		positionsPntr->clear();

		// reinitialize the multidimensional vector with {0, 0}		
		for (int i = 0; i < getDimension(); i++) {
			(*positionsPntr).push_back({ 0 });
		}

		try {
			// set the starting position
			setStartingPosition(inputCoordinates);

			// redraw the circle
			drawCircle();
		}
		// catch exception handled in exception class here
		catch (const runtime_error& exception) {
			cout << "\nException occured in \"Circle::relocate\" function.\n";
			cout << exception.what();
			throw exception;
		}
		// catch any exception here
		catch (...) {
			cout << "\nException occured in \"Circle::relocate\" function.\n";
			throw;
		}
	}
}

// retrieve the private data member "area"
double Circle::getArea() {
	return(area);
}

// retrieve the private data member "circumference"
double Circle::getCircumference() {
	return(circumference);
}

// retrieve the private data member "radius"
double Circle::getRadius() {
	return(radius);
}

// print the information of the shape. Defines the pure virtual function of the base class.
void Circle::printShapeInfo() {

	// initialize local variable
	vector<double> startingPosition{ 0.0, 0.0 };

	// get the starting position
	startingPosition = getStartingPosition();

	// print the shape information to the console
	cout << "\nCIRCLE DERIVED CLASS printShapeInfo() CALLED"
		"\nName: " << getName() <<
		"\nRadius: " << setprecision(2) << fixed << radius <<
		"\nArea: " << setprecision(2) << fixed << area <<
		"\nCircumference: " << setprecision(2) << fixed << circumference <<
		"\nStarting (x, y) Coordinates: (" << setprecision(2) << fixed << startingPosition[0] << ", " << startingPosition[1] << ')';
}