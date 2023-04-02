/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
Final Project
9/18/2021

TwoDimensionalShape.h

Below is the "TwoDimensionalShape" class, which is the 
abstract base class for creating two dimensional shapes.

Any shape can be formed by a series of lines, or arcs,
or more commonly both. The functions "addLine" and 
"addArc" give the user the ability to draw any shape.
The function "addPoint" can be used to jump to a new
(x, y) point when defining the shape.

The shape will be defined through a multidimensional
vector of type double. The first vector in the 
multidimensional vector will hold the x-axis 
coordinates of the shape, and the second will hold the 
y-axis coordinates of the shape.

The function "printShapeInfo" is defined in the base
class as pure virtual and therefore, must be defined
by any derived class.

*/

#ifndef TWODIMENSIONALSHAPE_H
#define TWODIMENSIONALSHAPE_H
#include<vector>
#include<iostream>
#include<iomanip>
#include<exception>
#include<string>
#include "math.h"
#include "InvalidLineLengthException.h"
#include "InvalidVectorFormatException.h"
#include "InvalidRadiusException.h"

using std::exception;
using std::vector;
using std::string;
using std::cout;
using std::setprecision;
using std::fixed;
using std::sqrt;
using std::atan2;
using std::sin;
using std::cos;
using std::abs;

#define PI_CONST 3.14159265359

class TwoDimensionalShape{
public:
	// ------------- PUBLIC DATA MEMBER FUNCTIONS ----------------

	// Constructor
	TwoDimensionalShape();

	// Virtual Destructor
	virtual ~TwoDimensionalShape();

	// Pure virtual function which prints the information of the shape
	virtual void printShapeInfo() = 0;

	// get the dimension supported for this abstract class (2)
	int getDimension();

	// add a two dimensional point to the shape
	void addPoint(vector<double> targetCoordinates);

	// add a two dimensional line to the shape
	void addLine(vector<double> targetCoordinates);
	
	// add a two dimensional arc segment to the shape
	void addArc(vector<double> inputCenterCoordinates, double inputAngle);

	// get the current starting position of the shape (first entered x,y coordinate)
	vector<double> getStartingPosition();

	// set the starting position of the shape. (x, y) coordinates.
	void setStartingPosition(vector<double> inputStartingCoordinates);

	// get the current ending position of the shape (last entered x,y coordinate)
	vector<double> getEndingPosition();

	// "Get/Set" functions.
	vector<vector<double>>* getPositionVector();
	void setName(string inputName);
	string getName();

private:
	// -----------  PRIVATE DATA MEMBER FUNCTIONS ---------------
	double convertRadiansToDegrees(double radians);
	double convertDegreesToRadians(double degrees);
	bool isRadiusNonZero(vector<double> inputCenter);
	double computeRadius(vector<double> inputCenter);
	double powerFunc(double inputBase, int inputExponent);
	double getDistance(vector<double> position1, vector<double> position2);
	void calculateAndAddArchPoint(vector<double> arcCenter, double angle, double radius);

	// -----------  PRIVATE DATA MEMBER VARIABLES ---------------
	const int dimension; // dimension of the shape. Set to 2 in constructor.
	string name;
	vector<vector<double>> pointsVector; // multidimensional vector holding x,y points
};

#endif
