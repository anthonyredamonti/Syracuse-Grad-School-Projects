/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
5/29/2022

MapProcess.cpp

Below is MapProcess.cpp, which is called by the MapProcess Main function.
The constructor takes the input file path, intermediate file path, process number,
and thread number as arguments.
The private data member function "mapThread" call the map method in the
MapLibrary DLL.

*/

// Directives
#include "FileManagement.h"
#include "MapProcess.h"
#include <thread>
#include <Windows.h>

//Name spaces
using std::cout;
using std::cin;
using std::string;
using std::ofstream;
using std::ifstream;
using std::runtime_error;
using std::thread;

namespace logging = boost::log;
namespace keywords = boost::log::keywords;

// Reduce constructor
MapProcess::MapProcess(string inputFilePath, string intermediateFilePath, string processNumber, string numberOfThreads)
{
	// convert the string to an int
	int numberOfThreadsInt = std::stoi(numberOfThreads);

	// retrieve the size of the intermediate file path.
	int intermediateFilePathSize = intermediateFilePath.size();

	// alter the intermediate file path.
	string alteredIntermediateFilePath = intermediateFilePath.substr(0, intermediateFilePathSize - 4) + processNumber + intermediateFilePath.substr(intermediateFilePathSize - 4);

	// assign pointers to the files.
	string* inputFilePntr = &inputFilePath;
	string* intermediateFilePathPntr = &alteredIntermediateFilePath;

	// initialize local variables
	ofstream outputFileStream;

	//Open file and then close to clear the contents
	outputFileStream.open(alteredIntermediateFilePath);
	outputFileStream.close();

	// Create local variables. Input file stream object
	ifstream inputFileStreamObj;
	string line;
	string entryString{ NULL };
	string* entryStrPntr{ NULL };

	// create a vector for all of the strings
	vector<string> allStringsVector;

	// an empty multidimensional vector of strings for the map threads
	vector<vector<string>> multiDimensionalStringVector;
	vector<string> threadStringVector;

	// put an empty string vector into the multidimensional string vector for each thread.
	for (int i = 0; i < numberOfThreadsInt; i++) {
		multiDimensionalStringVector.push_back(threadStringVector);
	}

	try {

		// open the intermediate file
		try {

			inputFileStreamObj.open(*inputFilePntr);
		}

		// catch exception handled in exception class here
		catch (const runtime_error& exception) {
			cout << "\nException occurred in \"MapProcess::Main\".\n";
			cout << exception.what();
			throw exception;
		}

		// catch any exception here
		catch (...) {
			cout << "\nException occurred in \"MapProcess::Main\".\n";
			throw;
		}

		// assign the entry string pointer
		entryStrPntr = &entryString;

		// get the first line from the file.
		while (getline(inputFileStreamObj, line)) 
		{
			// push the string into the vector
			allStringsVector.push_back(line);

		}

		// divide all the strings among the threads equally.
		int numberOfStringPerThread = allStringsVector.size() / numberOfThreadsInt;
		int remainderOfStrings = allStringsVector.size() % numberOfThreadsInt;
		int allStringsVecIndex{ 0 };

		for (int i = 0; i < numberOfThreadsInt; i++) {
			for (int j = 0; j < numberOfStringPerThread; j++) {

				// push the element from the allStringsVector into the correct string vector for each thread
				multiDimensionalStringVector[i].push_back(allStringsVector[allStringsVecIndex]);

				// increment the index.
				allStringsVecIndex = allStringsVecIndex + 1;
			}
		}

		// push the remainder of the strings onto the first thread's vector
		for (int i = 0; i < remainderOfStrings; i++) {
			multiDimensionalStringVector[0].push_back(allStringsVector[allStringsVecIndex]);
			allStringsVecIndex = allStringsVecIndex + 1;
		}

		// a vector of threads
		vector<thread> threadVector;

		// create the threads and push them into the vector
		for (int i = 0; i < numberOfThreadsInt; i++) {
			string tempOutPath = alteredIntermediateFilePath;
			vector<string> tempVec = multiDimensionalStringVector[i];
			thread threadObj([this, tempOutPath, i, tempVec] {this->mapThread(tempOutPath, i + 1, tempVec); });
			threadVector.push_back(std::move(threadObj));
		}

		// Iterate over the thread vector
		for (std::thread& th : threadVector)
		{
			// If thread Object is Joinable then Join that thread.
			if (th.joinable()) {
				th.join();
			}
		}
		

		// combine the files so that there is one for each process.
		for (int i = 0; i < numberOfThreadsInt; i++) {

			// get the size of the output file path
			int intermedFilePathSize = alteredIntermediateFilePath.size();

			// add the process number of the end of the output file path.
			string newIntermedThreadFilePath = alteredIntermediateFilePath.substr(0, intermedFilePathSize - 4) + std::to_string(i + 1) + alteredIntermediateFilePath.substr(intermedFilePathSize - 4);

			FileManagement fileManagementObjLocal;

			// append all of the contents from this thread to the main process file.
			fileManagementObjLocal.appendContents(newIntermedThreadFilePath, alteredIntermediateFilePath);

			// erase the file contents and delete the file.
			const char* interThreadFileChar = newIntermedThreadFilePath.c_str();

		
		}
	}

	// catch any exception here
	catch (...)
	{
		BOOST_LOG_TRIVIAL(fatal) << "Error in Workflow class inputIsFile function. Program will shutdown";
		throw;
	}
}

// Virtual Destructor
MapProcess::~MapProcess() {
	// nothing to do at this time.
}

// creates a new thread to call the Reduce method in the ReduceLibrary DLL.
void MapProcess::mapThread(string intermediateFilePath, int threadNumber, vector<string> stringVector) {
	try {
		HINSTANCE mapLibraryHandle;
		funcMap Map;
		const wchar_t* libName = L"MapLibrary";

		mapLibraryHandle = LoadLibraryEx(libName, NULL, NULL);   // Handle to DLL

		// perform the following if the mapLibraryHandle is not NULL
		if (mapLibraryHandle != NULL) {

			Map = (funcMap)GetProcAddress(mapLibraryHandle, "Map");

			// get the size of the output file path
			int intermediateFilePathSize = intermediateFilePath.size();

			// add the process number of the end of the output file path.
			string newIntermediateFilePath = intermediateFilePath.substr(0, intermediateFilePathSize - 4) + std::to_string(threadNumber) + intermediateFilePath.substr(intermediateFilePathSize - 4);

			// call reduce on each string in the vector
			for (int i = 0; i < stringVector.size(); i++) 
			{
				Map(newIntermediateFilePath, stringVector[i]);
			}

			// Free the handle to the MapLibrary DLL.
			FreeLibrary(mapLibraryHandle);
		}
		else {
			BOOST_LOG_TRIVIAL(fatal) << "Error loading MapLibrary DLL in mapThread. Program will shutdown.";
			throw;
		}
	}
	// catch any exception here
	catch (...)
	{
		BOOST_LOG_TRIVIAL(fatal) << "Error in MapProcess::mapThread method. Program will shutdown";
		throw;
	}
}
