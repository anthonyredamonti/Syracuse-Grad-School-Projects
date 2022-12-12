/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 3
5/15/2022

Main.cpp

Below is Main.cpp file.
This file has the main() function for the MapProcess.exe file.

It takes 3 command line arguments.
- InputFilePath
- Process Number

The process number ranges from 1 to the defined max number of processes.

*/

#define  _WIN32_WINNT   0x0601

//Directives
#include <Windows.h>

#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>

#include <boost/timer/timer.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include "FileManagement.h"
#include "MapProcess.h"


//Name spaces
using std::cout;
using std::cin;
using std::string;
using std::ofstream;
using std::ifstream;
using std::runtime_error;


namespace logging = boost::log;
namespace keywords = boost::log::keywords;



void init_logging()
{
	logging::register_simple_formatter_factory<logging::trivial::severity_level, char>("Severity");

	logging::add_file_log(
		keywords::file_name = "logResult.log",
		keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] [%ProcessID%] [%LineID%] %Message%"
	);

	logging::core::get()->set_filter
	(
		logging::trivial::severity >= logging::trivial::info
	);

	logging::add_common_attributes();
}

int main(int argc, char* argv[])
{
	init_logging();

	std::this_thread::sleep_for(std::chrono::seconds(1));

	//Boost logging used to log errors, warnings, info, fatals etc.
	BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
	BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
	BOOST_LOG_TRIVIAL(info) << "An informational severity message";
	BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
	BOOST_LOG_TRIVIAL(error) << "An error severity message";
	BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

	/* set console output codepage to UTF-8 */
	if (!SetConsoleOutputCP(CP_UTF8)) {
		std::cerr << "error: unable to set UTF-8 codepage.\n";
		return 1;
	}

	//Initiate variables to hold the names of the directory locations
	string inputFileName{ "Unknown" };
	string intermediateFileName{ "Unknown" };
	string outputFileName{ "Unknown" };

	// Mapping
	// convert the data to a string
	string inputFile = argv[0];

	//convert data back
	for (int i = 0; i < inputFile.size(); i++)
	{
		if (inputFile[i] == '\n')
		{
			inputFile[i] = ' ';
		}
		else
		{
			inputFile[i] = inputFile[i];
		}

	}

	// store the process number.
	string processNumber = argv[2];

	// convert the intermediate file path to a string
	string intermediateFilePath = argv[1];

	// convert the number of threads to a string
	string numberOfThreads = argv[3];

	//convert file path back to normal
	for (int i = 0; i < intermediateFilePath.size(); i++)
	{
		if (intermediateFilePath[i] == '\n')
		{
			intermediateFilePath[i] = ' ';
		}
		else
		{
			intermediateFilePath[i] = intermediateFilePath[i];
		}

	}

	// create a ReduceProcess object and call its constructor.
	MapProcess MapProcessObj(inputFile, intermediateFilePath, processNumber, numberOfThreads);

}//End of Program

	
