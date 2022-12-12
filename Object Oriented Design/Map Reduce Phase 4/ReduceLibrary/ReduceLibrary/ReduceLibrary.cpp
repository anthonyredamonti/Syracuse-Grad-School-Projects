/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
4/9/2022

ReduceLibrary.cpp

Below is the ReduceLibrary.cpp.
The Reduce class is called by the Workflow class.
The constructor takes the output file path as an argument.
The public data member function "reduce" takes an input string as
its argument. It interprets the key and calculates the total in
the iterator before calling the private data member function
"export." Export will simply write the data in the correct format
to the output file path destination.

*/

// ReduceLibrary.cpp : Defines the exported functions for the DLL.
//#include "pch.h"
#include "framework.h"
#include "ReduceLibrary.h"

// sums up the iterators and calls the export method.
// inputString is in form ("apple", [1, 1, 1, 1])
REDUCELIBRARY_API void Reduce(string& outputFilePath, string& inputString) {
	try {
		// create a delimiter to find. Find the open bracket "[" character.
		string openBracket = "\", [";

		// create a delimiter to find. Find the closed bracket "]" character.
		string closedBracket = "])";

		// create a substring of just the iterator (all 1's).
		string iterator = (inputString).substr((inputString).find(openBracket), (inputString).find(closedBracket));

		// calculate the number of 1's
		size_t numberOfOnes = (iterator.length() - 4) / 3;

		// find the position of the "\", [" string.
		size_t position = (inputString).find("\", [");

		// extract the key
		string key = (inputString).substr(2, position - 2);

		// export the data to the output file path.
		ReduceExport(outputFilePath, key, numberOfOnes);
	}

	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occurred in \"Reduce::Reduce\" method.\n";
		cout << exception.what();
		throw exception;
	}

	// catch any exception here
	catch (...) {
		BOOST_LOG_TRIVIAL(warning) << "Exception occurred in \"Reduce::Reduce\" method.";
		throw;
	}
}

// export the data to the output file path (one entry at a time)
void ReduceExport(string& outputFilePath, string key, size_t sum) {
	try {
		//Initiate an output stream
		ofstream outputFileStream;

		// open the file output stream on the output file
		outputFileStream.open(outputFilePath, std::ios_base::out | std::ios_base::app);

		//Write to the temp file with the given word
		//FileStreamSystem.writeToOutputFile(outputFileStream, key, sum);
		outputFileStream << "(\"" << key << "\"), " << std::to_string(sum) << endl;

		//Close file when complete
		outputFileStream.close();
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
