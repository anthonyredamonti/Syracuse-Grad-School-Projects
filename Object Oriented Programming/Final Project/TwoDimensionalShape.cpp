/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
Final Project
9/18/2021

TwoDimensionalShape.cpp

Below is the "TwoDimensionalShape" class, which is the
abstract base class for creating two dimensional shapes.

Any shape can be formed by a series of lines, or arcs,
or more commonly both. The functions "addLine" and
"addArc" give the user the ability to draw any shape.
The function "addPoint" can be used to jump to a new
(x, y) point when defining the shape.

The shape will be defined through a multidimensional
vector of type double. The the first vector in the
multidimensional vector will hold the x-axis
coordinates of the shape, and the second will hold the
y-axis coordinates of the shape.

The function "printShapeInfo" is defined in the base
class as pure virtual and therefore, must be defined
by any derived class.

There is a default constructor, which sets the 
maximum dimension to 2 and initializes the "name" and 
"pointsVector" private data member variables.

The starting point of the shape is located at the 
first position in each of the vectors inside of the
multidimensional vector: 
starting position x = pointsVector[0][0]
starting position y = pointsVector[1][0]

*/

#include "TwoDimensionalShape.h"

// The Shape constructor which initializes the private data members
TwoDimensionalShape::TwoDimensionalShape()
	: dimension{ 2 },
	name{ "" }
{
	// initialize the points vector with two vectors, each containing 0.0.
	vector<double> zeroVector = { 0.0 };
	for (int i = 0; i < dimension; i++) {
		pointsVector.push_back(zeroVector);
	}
}

// virtual destructor
TwoDimensionalShape::~TwoDimensionalShape(){
	// empty the points vector
	pointsVector.clear();
}

// retrieve the number of dimensions supported (2 dimensions)
int TwoDimensionalShape::getDimension() {
	return dimension;
}

// return a pointer to the multi-dimensional vector holding all position data for this shape
vector<vector<double>>* TwoDimensionalShape::getPositionVector() {
	vector<vector<double>>* pointsVectorPntr = &pointsVector;
	return(pointsVectorPntr);
}

// the base class version of the pure virtual "printShapeInfo" function.
void TwoDimensionalShape::printShapeInfo() {
	cout << "\nTWO DIMENSIONAL SHAPE BASE CLASS printShapeInfo() CALLED"
		"\nName: " << getName() <<
		"\nMaximum Dimension Supported: " << dimension;
}

// add a target distination in 2 dimensions (2 dimensional point)
void TwoDimensionalShape::addPoint(vector<double> xAndYCoordinates) {
	// check the user input
	if (xAndYCoordinates.size() != 2) {
		cout << "\nException occured in \"TwoDimensionalShape::addPoint\" function.\n";
		throw InvalidVectorFormatException{};
	}
	else {
		// Push new x,y coordinates into the points vector.
		for (int i = 0; i < dimension; i++) {
			pointsVector[i].push_back(xAndYCoordinates[i]);
		}
	}
}

// Add a two dimensional line segement to the shape's multidimensional vector.
void TwoDimensionalShape::addLine(vector<double> destinationPosition) {
	// check the user input
	if (destinationPosition.size() != 2) {
		cout << "\nException occured in \"TwoDimensionalShape::addLine\" function.\n";
		throw InvalidVectorFormatException{};
	}

	// if the distance between the current position and destination position 
	// is 0, print error message and throw exception.
	else if (getDistance(getEndingPosition(), destinationPosition) == 0.0) {
		cout << "\nException occured in \"TwoDimensionalShape::addLine\" function.\n";
		throw InvalideLineLengthException{};
	}

	else {
		// initialize local variables
		vector<double> currentPosition{ 0.0, 0.0 };
		vector<double> deltaPosition{ 0.0, 0.0 };
		double absoluteDistance{ 0.0 };
		double spacing{ 0.0 };
		double initialAngleRadians{ 0.0 };

	    // get the (x, y) coordinates of the current position. 
		currentPosition = getEndingPosition();

		try {
			// find the absolute distance between the two points
			absoluteDistance = getDistance(currentPosition, destinationPosition);
		}
		// catch exception handled in exception class here
		catch (const runtime_error& exception) {
			cout << "\nException occured in \"TwoDimensionalShape::addLine\" function.\n";
			cout << exception.what();
			throw exception;
		}
		// catch any exception here
		catch (...) {
			cout << "\nException occured in \"TwoDimensionalShape::addLine\" function.\n";
			throw;
		}

		// set the spacing between (x, y) points equal to 1/100 times the absolute distance of the line
		spacing = absoluteDistance / 100;

		// find the target position relative to the point (0, 0)
		// by finding the deltaX and deltaY points
		for (int i = 0; i < dimension; i++) {
			deltaPosition[i] = destinationPosition[i] - currentPosition[i];
		}

		// use the atan2 function to accurately retrieve the current angle (orientation of the current position)
		initialAngleRadians = atan2(deltaPosition[1], deltaPosition[0]);

		// append the points using the angle of the line and the scaling factor.
		for (double i = spacing; i <= absoluteDistance; i = i + spacing) {
			pointsVector[0].push_back(currentPosition[0] + (i * (cos(initialAngleRadians))));
			pointsVector[1].push_back(currentPosition[1] + (i * (sin(initialAngleRadians))));
		}
	}
}

// set the starting (x, y) coordinates of the shape
void TwoDimensionalShape::setStartingPosition(vector<double> inputStartingCoordinates) {
	// check the user input. Vector must be of size 2.
	if (inputStartingCoordinates.size() != 2) {
		cout << "\nException occured in \"TwoDimensionalShape::setStartingPosition\" function.\n";
		throw InvalidVectorFormatException{};
	}
	else {
		// set the starting position
		for (int i = 0; i < dimension; i++) {
			pointsVector[i][0] = inputStartingCoordinates[i];
		}
	}
}

// Add an arc segement to the shape's multidimensional vector.
// For a counterclockwise arc, use a positive angle.
// For a clockwise arc, use a negative angle.
void TwoDimensionalShape::addArc(vector<double> inputArcCenterCoordinates, double inputAngleDegrees) {
	// check the formatting of the center vector (must be 2 dimensions)
	if (inputArcCenterCoordinates.size() != 2) {
		cout << "\nException occured in \"TwoDimensionalShape::addArc\" function.\n";
		throw InvalidVectorFormatException{}; // terminate function
	}
	// angle must be greater than zero.
	if (inputAngleDegrees == 0) {
		cout << "\nAngle must be non-zero. Arc segment not added.\n";
		return;
	}

	// check that the radius is non-zero
	if (!isRadiusNonZero(inputArcCenterCoordinates)) {
		cout << "\nException occured in \"TwoDimensionalShape::addArc\" function.\n";
		cout << "\nThe coordinates of the center must not match the current x,y location." <<
			"\nThe radius of the arc must be non-zero. Arc segment not added.";
		throw InvalidRadiusException{}; // terminate function
	}

	// initialize local variables
	vector<double> currentPosition{ 0.0, 0.0 };
	vector<double> deltaPosition{ 0.0, 0.0 };
	vector<double> inputArcCenterCoordinatesCopy{ 0.0, 0.0 };
	double radius{ 0.0 };
	double spacing{ 0.0 };
	double initialAngleRadians{ 0.0 };
	double inputAngleRadians{ 0.0 };
	double endingAngleRadians{ 0.0 };

	try {
		// compute the radius of the arc
		radius = computeRadius(inputArcCenterCoordinates);

		// set the spacing between (x, y) points to 1/10000 times the radius of the arc
		spacing = radius / 10000;

		// get the current (x,y) position 
		currentPosition = getEndingPosition();

		// create a copy of the inputCenter vector
		inputArcCenterCoordinatesCopy = inputArcCenterCoordinates;

		// first, adjust the current x,y location and the input x,y center
		// so that they are both relative to the starting x,y location. It 
		// will simplify calculations.
		for (int i = 0; i < dimension; i++) {
			currentPosition[i] = currentPosition[i] - pointsVector[i][0]; // subtract the starting point from the current location
			inputArcCenterCoordinatesCopy[i] = inputArcCenterCoordinatesCopy[i] - pointsVector[i][0]; // subtract the starting point from the arc center location
			deltaPosition[i] = currentPosition[i] - inputArcCenterCoordinatesCopy[i]; // fix the center of the arc at the (0, 0) position
		}

		// use the atan2 function to accurately retrieve the current angle (orientation of the current position)
		initialAngleRadians = atan2(deltaPosition[1], deltaPosition[0]);

		// convert the input angle from degrees to radians
		inputAngleRadians = convertDegreesToRadians(inputAngleDegrees);

		// add the current angle to the input angle
		endingAngleRadians = initialAngleRadians + inputAngleRadians;

		// the input angle serves as an upper or lower bound depending on the
		// value of the inputAngle.
		if (inputAngleDegrees < 0) {
			for (double thetaRadians = initialAngleRadians - spacing; thetaRadians >= endingAngleRadians; thetaRadians = thetaRadians - spacing) {
				// calculate and add the (x, y) point of the arc
				calculateAndAddArchPoint(inputArcCenterCoordinates, thetaRadians, radius);
			}
		}

		// the input angle was positive, so it serves as the upper bound in the for-loop
		else {
			for (double thetaRadians = initialAngleRadians + spacing; thetaRadians <= endingAngleRadians; thetaRadians = thetaRadians + spacing) {
				// calculate and add the (x, y) point of the arc
				calculateAndAddArchPoint(inputArcCenterCoordinates, thetaRadians, radius);
			}
		}
	}

	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occured in \"TwoDimensionalShape::addArc\" function.\n";
		cout << exception.what();
		throw exception;
	}
	// catch any exception here
	catch (...) {
		cout << "\nException occured in \"TwoDimensionalShape::addArc\" function.\n";
		throw;
	}
}

// calculate and add a single (x, y) point to the multidimensional 
// points vector using the provided angle and radius
void TwoDimensionalShape::calculateAndAddArchPoint(vector<double> arcCenter, double angleRadians, double radius) {
	
	// initialize local variable
	double newValue{ 0.0 };
	
	try {
		// compute the new value
		newValue = radius * (cos(angleRadians));

		// add the offset (original arc center X coordinate)
		newValue = newValue + arcCenter[0];

		// add the new value to the points vector
		pointsVector[0].push_back(newValue);

		// compute the new value
		newValue = radius * (sin(angleRadians));

		// add the offset (original arc center Y coordinate)
		newValue = newValue + arcCenter[1];

		// add the new value to the points vector
		pointsVector[1].push_back(newValue);
	}
	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occured in \"TwoDimensionalShape::calculateAndAddArchPoint\" function.\n";
		cout << exception.what();
		throw exception;
	}
	// catch any exception here
	catch (...) {
		cout << "\nException occured in \"TwoDimensionalShape::calculateAndAddArchPoint\" function.\n";
		throw;
	}
}

// return the inputBase raised to the power of the inputExponent.
double TwoDimensionalShape::powerFunc(double inputBase, int inputExponent) {
	
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
		cout << "\nException occured in \"TwoDimensionalShape::powerFunc\" function.\n";
		cout << exception.what();
		throw exception;
	}
	// catch any exception here
	catch (...) {
		cout << "\nException occured in \"TwoDimensionalShape::powerFunc\" function.\n";
		throw;
	}

	// return answer
	return answer;
}

// use the absolute distance formula to compute the radius of the arc.
// return the radius.
double TwoDimensionalShape::computeRadius(vector<double> inputArcCenterCoordinates) {
	
	// initialize local variables
	vector<double> currentPosition{ 0.0, 0.0 };
	double radius{ 0.0 };
	// get the current (x, y) position
	currentPosition = getEndingPosition();

	try {
		// calculate the radius by using the absolute distance function
		radius = getDistance(currentPosition, inputArcCenterCoordinates);
	}
	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occured in \"TwoDimensionalShape::computeRadius\" function.\n";
		cout << exception.what();
		throw exception;
	}
	// catch any exception here
	catch (...) {
		cout << "\nException occured in \"TwoDimensionalShape::computeRadius\" function.\n";
		throw;
	}
	return radius; // return the radius
}

// retrieve the (x, y) coordinates of the current location
vector<double> TwoDimensionalShape::getEndingPosition() {

	//initialize local variables
	vector<double> currentCoordinates{ 0, 0 };
	size_t xSize{ 0 };
	size_t ySize{ 0 };

	// retrieve the size of the x vector
	xSize = pointsVector[0].size();

	// retrieve the size of the y vector
	ySize = pointsVector[1].size();

	// return the current position.
	currentCoordinates = { pointsVector[0][xSize - 1], pointsVector[1][ySize - 1] };
	return currentCoordinates;
}

// retrieve the (x, y) coordinates of the current location
vector<double> TwoDimensionalShape::getStartingPosition() {

	//initialize a 2 dimensional vector with zeroes.
	vector<double> firstPosition{ 0, 0 };

	// return the current position.
	firstPosition = { pointsVector[0][0], pointsVector[1][0] };
	return firstPosition;
}

// return the absolute distance between two (x,y) points.
double TwoDimensionalShape::getDistance(vector<double> position1, vector<double> position2) {
	// check that the input vectors are 2 dimensional
	if ((position1.size() != 2) || (position2.size() != 2)) {
		cout << "\nException occured in \"TwoDimensionalShape::getDistance\" function.\n";
		throw InvalidVectorFormatException{}; // terminate function
	}
	else {
		// initialize local variables
		double answer{ 0 };
		double x1{ position1[0] };
		double x2{ position2[0] };
		double y1{ position1[1] };
		double y2{ position2[1] };

		try {
			// use the absolute distance formula to calculate the distance
			answer = sqrt((powerFunc((x2 - x1), 2) + powerFunc((y2 - y1), 2)));
		}
		// catch exception handled in exception class here
		catch (const runtime_error& exception) {
			cout << "\nException occured in \"TwoDimensionalShape::getDistance\" function.\n";
			cout << exception.what();
			throw exception;
		}
		// catch any exception here
		catch (...) {
			cout << "\nException occured in \"TwoDimensionalShape::getDistance\" function.\n";
			throw;
		}
		// return the answer
		return answer;
	}
}

// Check that the user's center of the arc is not the same as the current
// location of the shape. The radius must be non-zero.
bool TwoDimensionalShape::isRadiusNonZero(vector<double> inputArcCenterCoordinates) {

	// initialize local variables
	vector<double> currentPosition{ 0.0, 0.0 };
	bool atLeastOnePointIsDifferent{ false };

	// retrieve the current position
	currentPosition = getEndingPosition();

	// at least one dimension must have a different value
	for (int i = 0; i < dimension; i++) {
		if (currentPosition[i] != inputArcCenterCoordinates[i]) {
			atLeastOnePointIsDifferent = true;
		}
	}

	// return boolean value
	return(atLeastOnePointIsDifferent);
}

// retrieve the name of the shape (string type)
string TwoDimensionalShape::getName() {
	return(name);
}

// set the name of the shape (string type)
void TwoDimensionalShape::setName(string inputName) {
	name = inputName; // set the private data member "name" to the inputName argument.
}

// convert the input radians to degrees. 
double TwoDimensionalShape::convertRadiansToDegrees(double inputRadians) {
	
	// initialize local variable
	double degrees{ 0.0 };

	// try calculation
	try {
		degrees = inputRadians * (180 / PI_CONST);
	}
	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occured in \"TwoDimensionalShape::convertRadiansToDegrees\" function.\n";
		cout << exception.what();
		throw exception;
	}
	// catch any exception here
	catch (...) {
		cout << "\nException occured in \"TwoDimensionalShape::convertRadiansToDegrees\" function.\n";
		throw;
	}

	// return the answer in degrees
	return degrees;
}

// convert the input degrees to radians.
double TwoDimensionalShape::convertDegreesToRadians(double inputDegrees) {
	
	// initialize local variable
	double radians{ 0.0 };

	// try calculation
	try {
		radians = inputDegrees * (PI_CONST / 180);
	}
	
	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occured in \"TwoDimensionalShape::convertDegreesToRadians\" function.\n";
		cout << exception.what();
		throw exception;
	}
	// catch any exception here
	catch (...) {
		cout << "\nException occured in \"TwoDimensionalShape::convertDegreesToRadians\" function.\n";
		throw;
	}
	// return the answer in radians
	return radians;
}
