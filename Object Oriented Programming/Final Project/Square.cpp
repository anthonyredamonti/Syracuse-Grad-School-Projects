/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
Final Project
9/18/2021

Square.cpp

Below is the "Square" class, which inherits from the
abstract base class "TwoDimensionalShape." In the
constructor, the user defines the (x, y) coordinates
of the starting position, the length of each side,
the spacing between generated (x, y) points, and the
name of the square.

The function "printShapeInfo" is defined in the base
class as pure virtual and therefore, must be defined
by any derived class.

*/

#include "Square.h"

// The Square constructor which initializes the private data members
Square::Square(vector<double> inputStartingPosition, double inputSideLength, string inputName) {
	// If the two dimensional input starting position vector is not properly formatted,
	// terminate the constructor
	if (inputStartingPosition.size() != 2) {
		cout << "\nException occured in \"Square::Square\" constructor.\n";
		throw InvalidVectorFormatException{}; // terminate constructor
	}

	// if the input side length is not greater than zero, throw exception.
	if (inputSideLength <= 0) {
		cout << "\nException occured in \"Square::Square\" constructor.\n";
		cout << "\nThe input side length must be greater than 0.\n";
		throw InvalideLineLengthException{}; // terminate constructor
	}

	sideLength = inputSideLength; // set the private data member to the input value

	setName(inputName); // call the setName function inherited from the Shape class

	try {
		setStartingPosition(inputStartingPosition); // set the starting position in the Shape base class
		setArea(); // set the area private data member
		setCircumference(); // set the circumference private data member
		drawSquare(); // draw the square using the given starting position and side length
	}

	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occured in \"Square::Square\" constructor.\n";
		cout << exception.what();
		throw exception;
	}
	// catch any exception here
	catch (...) {
		cout << "\nException occured in \"Square::Square\" constructor.\n";
		throw;
	}
}

// Square class destructor
Square::~Square() {
	// nothing to do at this time
}

// set the circumference private data member using the side length.
void Square::setCircumference() {
	try {
		circumference = sideLength * 4;
	}
	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occured in \"Square::setCircumference\" function.\n";
		cout << exception.what();
		throw exception;
	}
	// catch any exception here
	catch (...) {
		cout << "\nException occured in \"Square::setCircumference\" function.\n";
		throw;
	}
}

// set the area private data member using the side length.
void Square::setArea() {
	try {
		area = sideLength * sideLength; // update the area of the square
	}
	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occured in \"Square::setArea\" function.\n";
		cout << exception.what();
		throw exception;
	}
	// catch any exception here
	catch (...) {
		cout << "\nException occured in \"Square::setArea\" function.\n";
		throw;
	}
}

// resize the square using the provided input side length.
void Square::resize(double inputSideLength) {
	// check the validity of the user input side length.
	if (inputSideLength <= 0) {
		cout << "\nException occured in \"Square::resize\" function.\n";
		cout << "\nThe input side length of the square must be greater than zero.";
		throw InvalideLineLengthException{};
	}
	else {
		// initialize local variables
		vector<vector<double>>* positionsPntr{ NULL };
		vector<double> startingPosition{ 0.0, 0.0 };
		
		sideLength = inputSideLength; // set private data member variable to input value

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

			// update the area and circumference with the new side length
			setArea();
			setCircumference();

			// redraw the square
			drawSquare();
		}
		// catch exception handled in exception class here
		catch (const runtime_error& exception) {
			cout << "\nException occured in \"Square::resize\" function.\n";
			cout << exception.what();
			throw exception;
		}
		// catch any exception here
		catch (...) {
			cout << "\nException occured in \"Square::resize\" function.\n";
			throw;
		}
	}
}

// draw the square using the addLine inherited function from the Shape base class (abstract).
void Square::drawSquare() {

	// initialize local variables
	vector<double> startingPosition{ 0.0, 0.0 };
	vector<double> topLeftCorner{ 0.0, 0.0 };
	vector<double> topRightCorner{ 0.0, 0.0 };
	vector<double> bottomRightCorner{ 0.0, 0.0 };
	
	// get the starting position
	startingPosition = getStartingPosition();

	try {
		// get the first positions in each dimension. Create a square starting from there.
		// 
		// left side of square
		topLeftCorner = { startingPosition[0], startingPosition[1] + sideLength };
		addLine(topLeftCorner);

		// top side of square
		topRightCorner = { startingPosition[0] + sideLength, startingPosition[1] + sideLength };
		addLine(topRightCorner);

		// right side of square
		bottomRightCorner = { startingPosition[0] + sideLength, startingPosition[1] };
		addLine(bottomRightCorner);

		// bottom side of square
		addLine(startingPosition);
	}
	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occured in \"Square::drawSquare\" function.\n";
		cout << exception.what();
		throw exception;
	}
	// catch any exception here
	catch (...) {
		cout << "\nException occured in \"Square::drawSquare\" function.\n";
		throw;
	}
}

// retrieve the private data member "area"
double Square::getArea() {
	return(area);
}

// retrieve the private data member "circumference"
double Square::getCircumference() {
	return(circumference);
}

// retrieve the private data member "sideLength"
double Square::getSideLength() {
	return(sideLength);
}

// relocate the square by updating the starting position using the 
// provided input coordinates.
void Square::relocate(vector<double> inputCoordinates) {
	// check the validity of the user input
	if (inputCoordinates.size() != 2) {
		cout << "\nException occured in \"Square::relocate\" function.\n";
		throw InvalidVectorFormatException{};
	}
	else{
		
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
			// set the starting position to the input coordinates
			setStartingPosition(inputCoordinates);

			// redraw the square
			drawSquare();
		}
		// catch exception handled in exception class here
		catch (const runtime_error& exception) {
			cout << "\nException occured in \"Square::relocate\" function.\n";
			cout << exception.what();
			throw exception;
		}
		// catch any exception here
		catch (...) {
			cout << "\nException occured in \"Square::relocate\" function.\n";
			throw;
		}
	}
}

// print the information of the shape. Defines the pure virtual function of the base class.
void Square::printShapeInfo() {

	// initialize local variable
	vector<double> startingPosition{ 0.0, 0.0 };

	// get the starting position
	startingPosition = getStartingPosition();

	// print the shape information to the console
	cout << "\nSQUARE DERIVED CLASS printShapeInfo() CALLED"
		"\nName: " << getName() <<
		"\nSide Length: " << setprecision(2) << fixed << sideLength <<
		"\nArea: " << setprecision(2) << fixed << area <<
		"\nCircumference: " << setprecision(2) << fixed << circumference <<
		"\nStarting (x, y) Coordinates: (" << setprecision(2) << fixed << startingPosition[0] << ", " << startingPosition[1] << ')';
}