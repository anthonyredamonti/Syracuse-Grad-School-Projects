/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
4/9/2022

Sorting.cpp

Below is Sorting.cpp, which is called by the Workflow class.
The constructor takes the intermediate file path as an argument.
The public data member function "format" will format the data for
the Reduce class.

Example input data: ("a", 1), ("the", 1), ("is", 1), ("the", 1), ("a", 1)
Example output data: ("a", [1, 1]), ("the", [1, 1]), ("is", [1])

*/

// Directives
#include "Sorting.h"

// Reduce constructor
Sorting::Sorting(string* inputOutputFilePath) : 
	originalWordListLength{ 0 } 
{
	// update the private data member variable
	intermediateFilePath = *inputOutputFilePath;
}

// Virtual Destructor
Sorting::~Sorting() {

	// clear the wordList
	wordVector.clear();
}

// swap the two words
void Sorting::swap(word* wordPntr1, word* wordPntr2) {

	try {
		// declare local variable
		word tempWord;

		// initialize local variable
		tempWord = *wordPntr1;

		// assign wordPntr1 to wordPntr2
		*wordPntr1 = *wordPntr2;

		// assign wordPntr2 to temp
		*wordPntr2 = tempWord;
	}

	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occurred in \"Sorting::swap\" method.\n";
		cout << exception.what();
		throw exception;
	}

	// catch any exception here
	catch (...) {
		BOOST_LOG_TRIVIAL(warning) << "Exception occurred in \"Sorting::swap\" method.";
		throw;
	}
}

// return a reference to the intermediate file path.
string* Sorting::getIntermediateFilePath() {
	return(&intermediateFilePath);
}

// set the reference to the intermediate file path
void Sorting::setIntermediateFilePath(string* inputIntermediateFilePath) {
	intermediateFilePath = *inputIntermediateFilePath;
}

// Formats the data for the Reduce class.
// Example input data: ("a", 1), ("the", 1), ("is", 1), ("the", 1), ("a", 1)
// Example output data : ("a", [1, 1]), ("the", [1, 1]), ("is", [1])
void Sorting::format() {

	// Create local variables. Input file stream object
	ifstream inputFileStreamObj;
	ofstream outputFileStreamObj;
	string line;
	string key{ NULL };

	// create a delimiter to find. Find the following string: ", 1),".
	string closedParenthesis{ ")" };
	string openParenthesis{ "(" };
	size_t openPos{ NULL };
	size_t closedPos{ NULL };
	word wordObj;

	// try reading the file and adding all words to the data structure (vector).
	try {

		// display message to user.
		cout << "\nSorting has begun. Words are being discovered." << endl;

		// open the intermediate file
		inputFileStreamObj.open(intermediateFilePath);

		// get the first line from the file.
		while (getline(inputFileStreamObj, line)) {

			// find the position of the first open parenthesis
			openPos = line.find(openParenthesis);

			// offset for the find method of the string class.
			size_t offset{ 0 };

			// while there are words in this line, keep extracting them.
			while (openPos != string::npos) {

				// find the position of the closed parenthesis
				closedPos = line.find(closedParenthesis, offset);

				// if the open and closed parentheses were found, add the word to the vector.
				if ((openPos != string::npos) && (closedPos != string::npos)) {

					// extract the first key from the line.
					key = line.substr(openPos + 2, closedPos - openPos - 6);

					// load the temporary word.
					wordObj.key = key;
					wordObj.numberOfOccurrences = 1;

					// push it onto the linked list.
					wordVector.push_back(wordObj);
				}

				// update the offset into the line for the next search.
				offset = closedPos + 1;

				// Find the position of the next open parenthesis. 
				openPos = line.find(openParenthesis, offset);
			}
		}

		// close the file
		inputFileStreamObj.close();

	}

	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occurred in \"Sorting::format\" method when reading data from file.\n";
		cout << exception.what();
		throw exception;
	}

	// catch any exception here
	catch (...) {
		BOOST_LOG_TRIVIAL(warning) << "Exception occurred in \"Sorting::format\" method when reading data from file.";
		throw;
	}

	// erase the contents of the file by opening an output file stream object.
	outputFileStreamObj.open(intermediateFilePath);

	// close the output file stream object.
	outputFileStreamObj.close();

	// inform the user of the number of words found.
	cout << "\nThe number of words found in the intermediate file: " << wordVector.size();
	cout << "\nThese words are now being searched for duplicate entries." << endl;

	// if the number of words is zero, return
	if (wordVector.size() == 0) {
		
		// inform the user that sorting has finished.
		cout << "\nSorting has finished." << endl;
		return;
	}

	// Try to write the data back to the intermediate file in the correct
	// format for the reduce class. Example: ("is", [1, 1, 1])
	try {

		// declare local variables.
		size_t i{ 0 };
		
		// iterate to second to last element
		while (i < wordVector.size() - 1) {

			// declare local variables
			size_t j{ i + 1 };

			// iterate through to the last element
			while (j < wordVector.size()) {

				// if the words have the same key, swap the element 
				if (wordVector[i].key == wordVector[j].key) {

					// swap the matching word with the next word 
					swap(&wordVector[i + wordVector[i].numberOfOccurrences], &wordVector[j]);

					//update number of occurrences
					wordVector[i].numberOfOccurrences = wordVector[i].numberOfOccurrences + 1;
				}

				// increment variable j.
				j = j + 1;

			}

			// increment variable i.
			i = i + wordVector[i].numberOfOccurrences;
		}

		// now the vector is sorted so that it looks like:
		// {{ "a", numberOfOccurrences = 3 }, { "a", numberOfOccurrences = 1 }, { "a", numberOfOccurrences = 1 },
		// { "blah", numberOfOccurrences = 2 }, { "blah", numberOfOccurrences = 1 }}

		// update the originalWordListLength
		originalWordListLength = wordVector.size();

		// reformat file
		outputFileStreamObj.open(intermediateFilePath);

		// number of words per line
		int wordsPerLine{ 7 };
		int counter{ 0 };

		// initialize local variables
		size_t ii{ 0 };

		// perform the following operation on the entire list.
		while (ii < wordVector.size()) {
			
			// write the output to the text file in the proper format.
			outputFileStreamObj << "(\"" << wordVector[ii].key << "\", [";

			// output the correct number of 1's.
			for (int jj = 0; jj < wordVector[ii].numberOfOccurrences - 1; jj++) {
				outputFileStreamObj << "1, ";
			}

			// send the last 1 and ending bracket.
			outputFileStreamObj << "1])";

			// if there are more words to output, send a comma and a space
			if (ii != wordVector.size() - wordVector[ii].numberOfOccurrences) {
				outputFileStreamObj << ", ";
			}

			// increment the counter
			counter = counter + 1;

			// if the counter == wordsPerLine, begin a new line and reset the counter.
			if (counter == wordsPerLine) {
				outputFileStreamObj << "\n";

				// reset the counter.
				counter = 0;
			}

			// increment ii variable
			ii = ii + wordVector[ii].numberOfOccurrences;
		}

		// close the file.
		outputFileStreamObj.close();

		// inform the user that sorting has finished.
		cout << "\nSorting has finished." << endl;
	}

	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occurred in \"Sorting::format\" method when writing data to file.\n";
		cout << exception.what();
		throw exception;
	}

	// catch any exception here
	catch (...) {
		BOOST_LOG_TRIVIAL(warning) << "Exception occurred in \"Sorting::format\" method when writing data to file.";
		throw;
	}
}
