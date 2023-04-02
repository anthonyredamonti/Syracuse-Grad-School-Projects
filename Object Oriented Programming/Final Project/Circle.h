/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
Final Project
9/18/2021

Circle.h

Below is the "Circle" class, which inherits from the
abstract base class "TwoDimensionalShape." In the
constructor, the user defines the (x, y) coordinates
of the starting position, the length of the radius,
the spacing between generated (x, y) points, and the
name of the circle.
*/

#ifndef CIRCLE_H
#define CIRCLE_H

#include "TwoDimensionalShape.h"

class Circle : 
	public TwoDimensionalShape
{
public:
	// ------------- PUBLIC DATA MEMBER FUNCTIONS ----------------
	
	// Constuctor used to initialize private data members.
	Circle(vector<double> startingPosition, double inputRadius, string inputName);

	// virtual destructor
	virtual ~Circle();

	// defining the pure virtual function of the TwoDimensionalShape base class
	virtual void printShapeInfo();

	// functions used to resize or relocate the circle after it has been created
	void resize(double inputRadius);
	void relocate(vector<double> inputCoordinates);

	// Get functions
	double getArea();
	double getCircumference();
	double getRadius();

private:
	// -----------  PRIVATE DATA MEMBER FUNCTIONS ---------------
	void drawCircle();
	void setArea();
	void setCircumference();
	double powerFunc(double inputBase, int inputExponent);

	// -----------  PRIVATE DATA MEMBER VARIABLES ---------------
	double area;
	double circumference;
	double radius;
};

#endif
