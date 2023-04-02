/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
Final Project
9/18/2021

Square.h

Below is the "Square" class, which inherits from the 
abstract base class "TwoDimensionalShape." In the 
constructor, the user defines the (x, y) coordinates 
of the starting position, the length of each side, 
the spacing between generated (x, y) points, and the 
name of the square.
*/

#ifndef SQUARE_H
#define SQUARE_H

#include "TwoDimensionalShape.h"

class Square : 
	public TwoDimensionalShape
{
public:
	// ------------- PUBLIC DATA MEMBER FUNCTIONS ----------------
	
	// Constuctor used to initialize private data members.
	Square(vector<double> inputStartingPosition, double inputSideLength, string inputName); 

	// virtual destructor
	virtual ~Square();

	// defining the pure virtual function of the TwoDimensionalShape base class
	virtual void printShapeInfo();

	// resize the square
	void resize(double inputSideLength);

	//relocate the square
	void relocate(vector<double> inputCoordinates);

	// Get functions
	double getArea();
	double getCircumference();
	double getSideLength();

private:
	// -----------  PRIVATE DATA MEMBER FUNCTIONS ---------------
	void drawSquare();
	void setArea();
	void setCircumference();

	// -----------  PRIVATE DATA MEMBER VARIABLES ---------------
	double sideLength;
	double area; 
	double circumference;
};

#endif
