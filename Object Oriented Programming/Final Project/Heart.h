/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
Final Project
9/18/2021

Heart.h

Below is the "Heart" class, which inherits from the
abstract base class "TwoDimensionalShape." In the
constructor, the user defines the (x, y) coordinates
of the starting position and the name of the heart.
*/

#ifndef HEART_H
#define HEART_H

#include "TwoDimensionalShape.h"

class Heart :
	public TwoDimensionalShape
{
public:
	// ------------- PUBLIC DATA MEMBER FUNCTIONS ----------------

	// Constuctor used to initialize private data members.
	Heart(vector<double> inputStartingPosition, string inputName);

	// virtual destructor
	virtual ~Heart();

	// defining the pure virtual function of the TwoDimensionalShape base class
	virtual void printShapeInfo();

	// relocate the heart
	void relocate(vector<double> inputCoordinates);

private:
	// -----------  PRIVATE DATA MEMBER FUNCTIONS ---------------
	double convertDegreesToRadians(double degrees);
	void drawHeart();

};

#endif
