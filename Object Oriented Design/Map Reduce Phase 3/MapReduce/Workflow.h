/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
4/9/2022

Workflow.h

Below is "Workflow" class, which is called by the  main() in Executive.cpp.
The constructor takes three string directory names and saves the strings into private data members.
The constructor will then tie together all the header files with supporting logic.
The public data member functions are setters and getters for each data member.


*/

// Header Guard
#ifndef WORKFLOW_H
#define WORKFLOW_H

//Directives
#include <boost/filesystem.hpp>
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <filesystem>
#include <stdexcept> // contains runtime_error
#include <boost/log/trivial.hpp>

//NameSpaces
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::vector;
using std::runtime_error;
using boost::filesystem::recursive_directory_iterator;

class Workflow
{
public:
	//default constructor
	Workflow();
	//WorkFlow constructor with three parameters: string input file directory, string temporary directory to hold intermediate output files, and string output file
	Workflow(string inputFile, string intermediateFile, string outputFile);


	//**********Member Function**********

	//Pre-condition: File is given in directory
	//Post-condition: NA
	//Will just read the contents of the one file
	void startProgram(string inputFile, string intermediateFile, string outputFile);

	//Pre-condition: outputFileLocation has been given
	//Post-condition: outputFileDirectoryLocation data member will have a value
	//Separates the directory path from the file name
	void separateOutputPath(const string userInputFile, const string& fileType);


	//Pre-condition: input, intermediate, output file directories have been declared. 
	//Post-condition: directories could be changed if not valid
	//While loops through each file until they are valid
	void checkFilesValid(string& inputFile, string& intermediateFile, string& outputFile);

	//Pre-condition: An input file is declared
	//Post-condition: input file is changed if not valid
	//Checks if the input file is valid to use
	bool checkIfFIle(const string& userInputFile);


	//Pre-condition: An output has been declared
	//Post-condition: output file changed if not valid
	//Checks if the output file is valid to use
	bool checkOfFIle(const string& userInputFile, const string& fileType);

	string updateString(string origional, string toAdd);

	//**********Setters**********

	//Pre-condition: None
	//Post-condition:inputFileLocation has value updated
	//update value in inputFileLocation
	void setInputFileLocation(const string& userInputFile);


	//Pre-condition: None
	//Post-condition:intermediateFileLocation has value updated
	//update value in intermediateFileLocation
	void setIntermediateFileLocation(const string& userIntermediateFile);


	//Pre-condition: None
	//Post-condition:outputFileLocation has value updated
	//update value in outputFileLocation
	void setOutputFileLocation(const string& userOutputFile);

	//Pre-condition: None
	//Post-condition:IntermediateFileDirectoryLocation has value updated
	//update value in IntermediateFileDirectoryLocation
	void setIntermediateFileDirectoryLocation(const string& userOutputFile);


	//Pre-condition: None
	//Post-condition:outputFileDirectoryLocation has value updated
	//update value in outputFileDirectoryLocation
	void setOutputFileDirectoryLocation(const string& userOutputFile);

	//Pre-condition: None
	//Post-condition: Divides input file amoung RMAX number of processes.
	void partition(const string& inputFile, const string& intermediateFile);

	//**********Getters**********

	//Pre-condition: inputFileLocation has a value
	//Post-condition: none
	//Return the value in inputFileLocation
	const string getInputFileLocation(void);


	//Pre-condition: intermediateFileLocation has a value
	//Post-condition: none
	//Return the value in intermediateFileLocation
	const string getIntermediateFileLocation(void);


	//Pre-condition: outputFileLocation has a value
	//Post-condition: none
	//Return the value in outputFileLocation
	const string getOutputFileLocation(void);


	//Pre-condition: intermediateFileDirectoryLocation has a value
	//Post-condition: none
	//Return the value in intermediateFileDirectoryLocation
	const string getIntermediateFileDirectoryLocation(void);


	//Pre-condition: outputFileDirectoryLocation has a value
	//Post-condition: none
	//Return the value in outputFileDirectoryLocation
	const string getOutputFileDirectoryLocation(void);

	//Pre-condition: validInputFile has a value
	//Post-condition: none
	//Return the value in validInputFile
	const bool getValidInputFile(void);


	//Pre-condition: validIntermediateFile has a value
	//Post-condition: none
	//Return the value in validIntermediateFile
	const bool getValidIntermediateFile(void);

	//Pre-condition: validOutputFile has a value
	//Post-condition: none
	//Return the value in validOutputFile
	const bool getValidOutputFile(void);

	//**********Destructor*********
	~Workflow();


private:


	//Data member to save location of input text file...just read from
	string inputFileLocation{ "Unknown" };

	//Data member to save location of intermediate file...will be written and then read
	string intermediateFileLocation{ "Unknown" };

	//Data member to save location of the output file...will be written too
	string outputFileLocation{ "Unknown" };

	//Data member to save directory information for intermediate file
	string intermediateFileDirectoryLocation{ "Unknown" };

	//Data member to save directory information for output file
	string outputFileDirectoryLocation{ "Unknown" };

	// Boolean variables that determine validity of the files.
	bool validInputFile{ false };
	bool validIntermediateFile{ false };
	bool validOutputFile{ false };

};
#endif
