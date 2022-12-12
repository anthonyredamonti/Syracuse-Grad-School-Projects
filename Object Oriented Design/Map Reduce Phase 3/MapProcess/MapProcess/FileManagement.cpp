/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
4/9/2022

FileManagement.cpp

Below is FileManagement.cpp, which is called by the Workflow class.
This class is a sub class of the "Workflow" class so the file streams can be used.
This class will allow file system access.
The is a default constructor and no data members.
The member functions include an open and close for both input and output streams.
A function fileCorrupt() to check to see if a input file is corrupt.
A function writeToTempFile() to write to an output file
A function readFromFile() to return a string of one line of rawData from the file.

*/

//Directives
#include "FileManagement.h"

//Name spaces
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::vector;

namespace filesys = boost::filesystem;

//default constructor
FileManagement::FileManagement() {}

//**********Destructor*********
FileManagement::~FileManagement() {}

//**************Working on Directory Member functions********************
vector<string> FileManagement::getAllFilesInDir(const string& dirPath, const vector<string> dirSkipList)
{
	// Create a vector of string
	vector<string> listOfFiles;

	try {
		// Check if given path exists and points to a directory
		if (filesys::exists(dirPath) && filesys::is_directory(dirPath))
		{
			// Create a Recursive Directory Iterator object and points to the starting of directory
			filesys::recursive_directory_iterator iter(dirPath);
			// Create a Recursive Directory Iterator object pointing to end.
			filesys::recursive_directory_iterator end;
			// Iterate till end
			while (iter != end)
			{
				// Check if current entry is a directory and if exists in skip list
				if (filesys::is_directory(iter->path()) &&
					(std::find(dirSkipList.begin(), dirSkipList.end(), iter->path().filename()) != dirSkipList.end()))
				{
					// Skip the iteration of current directory pointed by iterator
					// Boost Fileystsem  API to skip current directory iteration
					iter.no_push();

				}
				else
				{
					// Add the name in vector
					listOfFiles.push_back(iter->path().string());
				}
				boost::system::error_code ec;
				// Increment the iterator to point to next entry in recursive iteration
				iter.increment(ec);
				if (ec) {
					std::cerr << "Error While Accessing : " << iter->path().string() << " :: " << ec.message() << '\n';
				}
			}
		}
	}
	catch (std::system_error& e)
	{
		std::cerr << "Exception :: " << e.what();
	}
	return listOfFiles;
}

// append the contents of file one to file two.
void FileManagement::appendContents(const string fileOne, const string fileTwo) {
	
	ifstream inStreamObj;
	ofstream outStreamObj;

	// open file one.
	openFileInstream(inStreamObj, fileOne);

	// open file two.
	openFileOutstream(outStreamObj, fileTwo);

	string data{ NULL };

	// get the contents of file one and append them to file two.
	while (data != "1") {
		readFromFile(inStreamObj, data);
		outStreamObj << data << "\n";
	}

	// close both files.
	closeInputFile(inStreamObj);
	closeOutputFile(outStreamObj);
}

//Opens a file as an input stream, function parameters are a reference to input stream and string of file name to open
void FileManagement::openFileInstream(ifstream& fileStream, const string userFile)
{
	try {
		fileStream.open(userFile);
	}

	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occurred in \"FileManagement::openFileInstream\".\n";
		cout << exception.what();
		throw exception;
	}

	// catch any exception here
	catch (...) {
		cout << "\nException occurred in \"FileManagement::openFileInstream\".\n";
		throw;
	}

}

//Opens a file as an output stream, function parameters are a reference to output stream and string of file name to open
//Will append the file, and keep the contents. 
void FileManagement::openFileOutstream(ofstream& fileStream, const string& userFile)
{
	try {
		fileStream.open(userFile, std::ios_base::app);
	}

	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occurred in \"FileManagement::openFileOutstream\".\n";
		cout << exception.what();
		throw exception;
	}

	// catch any exception here
	catch (...) {
		cout << "\nException occurred in \"FileManagement::openFileOutstream\".\n";
		throw;
	}
}

//Check if open in-stream file is corrupt and did not open
void FileManagement::fileCorrupt(ifstream& fileStream)
{
	//Check to see if file failed to open
	if (fileStream.fail())
	{
		//If true, print fail to screen and EXIT
		cout << "Input file failed to open" << endl;
		exit(EXIT_FAILURE);


	}
	//else print to screen a success message
	else
	{
		cout << "Input file successfully opened." << endl;
	}

}

//To write from main input into the temporary intermediate file
void FileManagement::writeToTempFile(ofstream& fileStream, const string& data)
{
	//("jump", 1)...Example of what should be inserted into file
	fileStream << "(\"";
	fileStream << data;
	fileStream << "\", 1)\n";
}

//To write from the intermediate file into the temporary file 
void FileManagement::writeToOutputFile(ofstream& fileStream, string key, size_t sum)
{
	// write the output to the text file in the proper format.
	fileStream << "(\"" << key << "\"), " << std::to_string(sum) << "\n";

}

//To read a line of raw data from the input file
void FileManagement::readFromFile(ifstream& fileStream, string& data)
{
	//If reached the end of the file, return one
	if (fileStream.eof())
	{
		data = "1";
	}
	else
	{
		std::getline(fileStream, data);
	}
}

//Clear file of anything written.
void FileManagement::clearFile(ofstream& fileStream, const string& userFile)
{
	//Open file and then close to clear the contents
	fileStream.open(userFile);
	closeOutputFile(fileStream);
}

//close an input file
void FileManagement::closeInputFile(ifstream& fileToClose) { fileToClose.close(); }

//close an output file
void FileManagement::closeOutputFile(ofstream& fileToClose) { fileToClose.close(); }
