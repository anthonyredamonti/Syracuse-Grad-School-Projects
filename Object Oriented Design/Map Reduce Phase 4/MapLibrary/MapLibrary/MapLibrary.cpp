// MathLibrary.cpp : Defines the exported functions for the DLL.
//#include "pch.h"
#include "framework.h"
#include "MaPLibrary.h"

MAPLIBRARY_API void Map(string& fileName, string& lineOfData) 
{
	// attempt to tokenize the file name and line of data.
	try {
		tokenize(fileName, lineOfData);
	}

	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occurred in \"Map::Constructor\".\n";
		cout << exception.what();
		throw exception;
	}

	// catch any exception here
	catch (...) {
		cout << "\nException occurred in \"Map::Constructor\".\n";
		throw;
	}

}
MAPLIBRARY_API void tokenize(string& fileName, string& lineOfData) 
{
	try {
		//Work through the sting and make everything lower case
		std::for_each(lineOfData.begin(), lineOfData.end(), [](char& c) {
			c = ::tolower(c);
			});

		//intitate a tokenizer object with the raw data
		tokenizer<> tok(lineOfData);

		//Work through the tokenizer and call exportt() with each word
		for (tokenizer<>::iterator beg = tok.begin(); beg != tok.end(); ++beg)
		{

			exportt(fileName, beg);
		}
	}

	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occurred in \"Map::tokenize\" method.\n";
		cout << exception.what();
		throw exception;
	}
	// catch any exception here
	catch (...) {
		cout << "\nException occurred in \"Map::tokenize\" method.\n";
		throw;
	}
}
MAPLIBRARY_API void exportt(string& fileName, tokenizer<>::iterator& word)
{
	try {
		//Initiate an output stream
		std::ofstream outputFileStream;

		//Open the stream with the output file
		outputFileStream.open(fileName, std::ios_base::app);

		//Write to the temp file with the given word
		//("jump", 1)...Example of what should be inserted into file
		outputFileStream << "(\"";
		outputFileStream << *word;
		outputFileStream << "\", 1)\n";

		//Close file when complete
		outputFileStream.close();
	}

	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occurred in \"Map::exportt\" method.\n";
		cout << exception.what();
		throw exception;
	}
	// catch any exception here
	catch (...) {
		cout << "\nException occurred in \"Map::exportt\" method.\n";
		throw;
	}

}



