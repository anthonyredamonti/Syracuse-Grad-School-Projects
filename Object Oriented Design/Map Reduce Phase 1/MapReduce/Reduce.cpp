/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
4/9/2022

Reduce.cpp

Below is the Reduce.cpp. 
The Reduce class is called by the Workflow class.
The constructor takes the output file path as an argument.
The public data member function "reduce" takes an input string as
its argument. It interprets the key and calculates the total in
the iterator before calling the private data member function
"export." Export will simply write the data in the correct format
to the output file path destination.

*/

// Directives
#include "Reduce.h"
#include "FileManagement.h"

// Reduce constructor
Reduce::Reduce(string* inputOutputFilePath) {
	
	// update the private data member variable
	outputFilePath = *inputOutputFilePath;
}

// Virtual Destructor
Reduce::~Reduce() {

}

// return a reference to the output file path.
string* Reduce::getOutputFilePath() {
	return(&outputFilePath);
}

// set the reference to the output file path
void Reduce::setOutputFilePath(string* inputOutputFilePath) {
	outputFilePath = *inputOutputFilePath;
}

// sums up the iterators and calls the export method.
// inputString is in form ("apple", [1, 1, 1, 1])
void Reduce::reduce(string* inputString) {

	try {
		// create a delimiter to find. Find the open bracket "[" character.
		string openBracket = "\", [";

		// create a delimiter to find. Find the closed bracket "]" character.
		string closedBracket = "])";

		// create a substring of just the iterator (all 1's).
		string iterator = (*inputString).substr((*inputString).find(openBracket), (*inputString).find(closedBracket));

		// calculate the number of 1's
		size_t numberOfOnes = (iterator.length() - 4) / 3;

		// find the position of the "\", [" string.
		size_t position = (*inputString).find("\", [");

		// extract the key
		string key = (*inputString).substr(2, position - 2);

		// export the data to the output file path.
		exportt(key, numberOfOnes);
	}

	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occurred in \"Reduce::reduce\" method.\n";
		cout << exception.what();
		throw exception;
	}

	// catch any exception here
	catch (...) {
		BOOST_LOG_TRIVIAL(warning) << "Exception occurred in \"Reduce::reduce\" method.";
		throw;
	}
}

// export the data to the output file path (one entry at a time)
void Reduce::exportt(string key, size_t sum) {
	
	try {
		//Initiate an output stream
		ofstream outputFileStream;

		//Create an object of the FileManagement class
		FileManagement FileStreamSystem;

		//Open the stream with the output file
		FileStreamSystem.openFileOutstream(outputFileStream, outputFilePath);

		//Write to the temp file with the given word
		FileStreamSystem.writeToOutputFile(outputFileStream, key, sum);

		//Close file when complete
		FileStreamSystem.closeOutputFile(outputFileStream);
	}

	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occurred in \"Reduce::exportt\" method.\n";
		cout << exception.what();
		throw exception;
	}

	// catch any exception here
	catch (...) {
		BOOST_LOG_TRIVIAL(warning) << "Exception occurred in \"Reduce::exportt\" method.";
		throw;
	}
}
