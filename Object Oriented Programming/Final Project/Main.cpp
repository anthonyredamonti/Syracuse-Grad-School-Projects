/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
Final Project
9/18/2021

Main.cpp

The following program creates instances of classes that inherit
from the TwoDimensionalShape class. The instances (objects) are
created inside of the vector, twoDimensionalShapesVector. The 
vector contains pointers of the same type as the abstract base 
class "twoDimensionalShape" that are pointing to the derived
class objects. The pure virtual function "printShapeInfo()" is
called on each pointer. A dynamic down-cast is attempted for
each pointer in the vector. If the down-cast matches the
derived class type, the (x, y) points of the shape are exported
to the appropriate .CSV file.

*/

#include <iostream>   // needed for the standard library
#include <iomanip>    // needed for setw() and setfill()
#include <fstream>    // needed for writing to a file

#include "TwoDimensionalShape.h"  // defines the abstract base class, "TwoDimensionalShape."
#include "Square.h"    // defines the derived "Square" class
#include "Circle.h"    // defines the derived "Circle" class.
#include "Heart.h"	   // defines the derived "Heart" class

// importing objects from the C++ standard library
using std::cin;
using std::cout;
using std::setw;
using std::setfill;
using std::ofstream;
using std::to_string;
using std::numeric_limits;
using std::streamsize;

// print "SU" for Syracuse University on the console
void printSyracuseBanner(); 

// create a .CSV file using the given file name and export all of the 
// (x, y) points to the file
void exportPointsToFile(string fileName, vector<vector<double>>* pointsPntr);

int main() {

	// print Syracuse Banner
	printSyracuseBanner();

	// information about program
	cout << "Welcome to the Two Dimensional Shape Program!\n" <<
		    "The following program asks the user for information\n" <<
		    "to create a circle, square, and heart.\n" <<
			"The (x, y) points of each shape are exported to three\n" <<
			"seperate .CSV files, which can be used to graph the\n" <<
			"data. After creating the three CSV files and exporting\n" <<
			"the data, the program will end.";

	// create a base class pointer to be used later. Initialize it to NULL.
	TwoDimensionalShape* baseClassPntr{ NULL };
	vector<TwoDimensionalShape*> twoDimensionalShapesVector;

	// create local variables to be used in the circleObj constructor
	// initialize them with default values
	vector<double> circleStartingPosition{ 0.0, 0.0 };
	double circleRadius{ 0.0 };
	string circleName{ "" };

	// create local variables to be used in the squareObj constructor
	vector<double> squareStartingPosition{ 0.0, 0.0 };
	double squareSideLength{ 0.0 };
	string squareName{ "" };

	// create local variables to be used in the heartObj constructor
	vector<double> heartStartingPosition{ 0.0, 0.0 };
	string heartName{ "" };
	
	// -----------------      ASK USER FOR CIRCLE INFO  -------------------- //

	// ask the user for the starting coordinates of the circle
	cout << "\n\nPlease enter the starting (x, y) coordinates for" <<
		"\nthe circle's left most edge." << 
		"\nX Coordinate: ";
	cin >> circleStartingPosition[0];

	// check that the user entered a valid X coordinate
	while (cin.fail()) {
		cout << "Please enter a valid double value." <<
				"\nX Coordinate: ";
		//clear the error
		cin.clear();
		//discard invalid characters
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> circleStartingPosition[0];
	}

	// ask the user for the starting Y coordinate
	cout << "Y Coordinate: ";
	cin >> circleStartingPosition[1];

	// check that the user entered a valid Y coordinate
	while (cin.fail()) {
		cout << "Please enter a valid double value." <<
			"\nY Coordinate: ";
		//clear the error
		cin.clear();
		//discard invalid characters
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> circleStartingPosition[1];
	}

	// ask the user for the radius of the circle
	cout << "Please enter a radius for the circle." << 
		"\nRadius: ";
	cin >> circleRadius;

	// check that the user entered a valid radius
	while (cin.fail() || circleRadius <= 0) {
		cout << "Please enter a valid double value greater than zero." <<
			"\nRadius: ";
		//clear the error
		cin.clear();
		//discard invalid characters
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> circleRadius;
	}

	// ask the user for the name of the circle
	cout << "Please enter a name for the circle." <<
		"\nName: ";
	cin >> circleName;

	// check that the user entered a valid string 
	while (cin.fail()) {
		cout << "Please enter a valid string value." <<
			"\nName: ";
		//clear the error
		cin.clear();
		//discard invalid characters
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> circleName;
	}

	// -----------------      ASK USER FOR SQUARE INFO  -------------------- //

	// ask the user for the starting coordinates of the square
	cout << "\nPlease enter the starting (x, y) coordinates for" <<
		"\nthe bottom left corner of the square." <<
		"\nX Coordinate: ";
	cin >> squareStartingPosition[0];

	// check that the user entered a valid X coordinate
	while (cin.fail()) {
		cout << "Please enter a valid double value." <<
			"\nX Coordinate: ";
		//clear the error
		cin.clear();
		//discard invalid characters
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> squareStartingPosition[0];
	}

	// ask the user for the starting Y coordinate
	cout << "Y Coordinate: ";
	cin >> squareStartingPosition[1];

	// check that the user entered a valid Y coordinate
	while (cin.fail()) {
		cout << "Please enter a valid double value." <<
			"\nY Coordinate: ";
		//clear the error
		cin.clear();
		//discard invalid characters
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> squareStartingPosition[1];
	}

	// ask the user for one side of the square
	cout << "Please enter the length for one side of the square." <<
		"\nLength: ";
	cin >> squareSideLength;

	// check that the user entered a valid side length
	while (cin.fail() || squareSideLength <= 0) {
		cout << "Please enter a valid double value greater than zero." <<
			"\nLength: ";
		//clear the error
		cin.clear();
		//discard invalid characters
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> squareSideLength;
	}

	// ask the user for the name of the square
	cout << "Please enter a name for the square." <<
		"\nName: ";
	cin >> squareName;

	// check that the user entered a valid string 
	while (cin.fail()) {
		cout << "Please enter a valid string value." <<
			"\nName: ";
		//clear the error
		cin.clear();
		//discard invalid characters
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> squareName;
	}

	// -----------------  ASK USER FOR HEART INFO  -------------------- //

	// ask the user for the starting coordinates of the heart
	cout << "\nPlease enter the starting (x, y) coordinates for" <<
		"\nthe bottom tip of the heart." <<
		"\nX Coordinate: ";
	cin >> heartStartingPosition[0];

	// check that the user entered a valid X coordinate
	while (cin.fail()) {
		cout << "Please enter a valid double value." <<
			"\nX Coordinate: ";
		//clear the error
		cin.clear();
		//discard invalid characters
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> heartStartingPosition[0];
	}

	// ask the user for the starting Y coordinate
	cout << "Y Coordinate: ";
	cin >> heartStartingPosition[1];

	// check that the user entered a valid Y coordinate
	while (cin.fail()) {
		cout << "Please enter a valid double value." <<
			"\nY Coordinate: ";
		//clear the error
		cin.clear();
		//discard invalid characters
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> heartStartingPosition[1];
	}

	// ask the user for the name of the heart
	cout << "Please enter a name for the heart." <<
		"\nName: ";
	cin >> heartName;

	// check that the user entered a valid string 
	while (cin.fail()) {
		cout << "Please enter a valid string value." <<
			"\nName: ";
		//clear the error
		cin.clear();
		//discard invalid characters
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> heartName;
	}

	try {

		// create and initialize three new shapes
		Circle circleObj(circleStartingPosition, circleRadius, circleName);
		Square squareObj(squareStartingPosition, squareSideLength, squareName);
		Heart heartObj(heartStartingPosition, heartName);
		
		// vector of base class pointers to derived class objects
		twoDimensionalShapesVector = { &circleObj, &squareObj, &heartObj };

		// record the size of the vector
		size_t vectorSize = twoDimensionalShapesVector.size();

		for (int i = 0; i < vectorSize; i++) {
		
			// assign the base class pointer to the derived object
			baseClassPntr = twoDimensionalShapesVector[i];
		
			// call the derived class's "printShapeInfo" function (pure virtual)
			baseClassPntr->printShapeInfo();

			cout << '\n';
		
			// retrieve the address location of the multidimensional position vector
			vector<vector<double>>* positionVectorPntr = baseClassPntr->getPositionVector();

			// attempt to downcast the base class pointer
			Circle* circlePntr = dynamic_cast<Circle*>(baseClassPntr);

			// if the base class pointer is pointing to a circle object,
			// export all of its (x, y) points to the appropriate .csv file.
			if (circlePntr != nullptr) {
				string fileName = ("CirclePoints.csv");
				exportPointsToFile(fileName, positionVectorPntr);
			}

			// attempt to downcast the base class pointer
			Square* squarePntr = dynamic_cast<Square*>(baseClassPntr);

			// if the base class pointer is pointing to a square object,
			// export all of its (x, y) points to the appropriate .csv file.
			if (squarePntr != nullptr) {
				string fileName = "SquarePoints.csv";
				exportPointsToFile(fileName, positionVectorPntr);
			}

			// attempt to downcast the base class pointer
			Heart* heartPntr = dynamic_cast<Heart*>(baseClassPntr);

			// if the base class pointer is pointing to a heart object,
			// export all of its (x, y) points to the appropriate .csv file.
			if (heartPntr != nullptr) {
				string fileName = "HeartPoints.csv";
				exportPointsToFile(fileName, positionVectorPntr);
			}
		}
	}
	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occured in \"Main::main\" function.\n";
		cout << exception.what();
		throw exception;
	}
	// catch any exception here
	catch (...) {
		cout << "\nException occured in \"Main::main\" function.\n";
		throw;
	}
}

// create a .CSV file using the given file name and export all of the 
// (x, y) points to the file
void exportPointsToFile(string fileName, vector<vector<double>>* pointsPntr) {
	
	// create an excel (.csv) file to send position data
	ofstream excelFile;
	excelFile.open(fileName);
	excelFile << "X Coordinate,Y Coordinate\n";

	// write all of the points to the file
	for (int i = 0; i < (*pointsPntr)[0].size(); i++) {
		excelFile << to_string((*pointsPntr)[0][i]) << ',' << to_string((*pointsPntr)[1][i]) << '\n';
	}

	// close the excel file
	excelFile.close();
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