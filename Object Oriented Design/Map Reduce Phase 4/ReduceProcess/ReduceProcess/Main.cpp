/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
5/28/2022

Main.cpp

Below is Main.cpp file.
This file has the main() function for the ReduceProcess.exe file.

It takes 4 command line arguments.
- IntermediateFilePath
- OutputFilePath
- Process Number
- Number of threads to create.

The process number ranges from 1 to the defined max number of processes.

*/

#define  _WIN32_WINNT   0x0601

//Directives
#include <Windows.h>
#include <thread>
#include <iostream>
#include <string>
#include <fstream>

#include <boost/timer/timer.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include "Sorting.h"
#include "ReduceProcess.h"

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

	//Start timer
	boost::timer::auto_cpu_timer t(3, "%w seconds\n");

	//Initiate variables to hold the names of the directory locations
	string inputFileName{ "Unknown" };
	string intermediateFileName{ "Unknown" };
	string outputFileName{ "Unknown" };

	//Banner Message
	cout << "*************************************************************************************"
		<< "\n\t\t\tReduce process created.";
	cout.flush();

	//<-----------------Part 2------------------------------------------>
	// Sorting and Reducing

	// convert the file path to a string
	string intermediateFilePath = argv[0];

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
	
	// store the process number.
	string processNumber = argv[2];

	// convert the output file path to a string
	string outputFilePath = argv[1];

	// convert the number of threads to a string
	string numberOfThreads = argv[3];

	//convert filepath back to normal
	for (int i = 0; i < outputFilePath.size(); i++)
	{
		if (outputFilePath[i] == '\n')
		{
			outputFilePath[i] = ' ';
		}
		else
		{
			outputFilePath[i] = outputFilePath[i];
		}
	}	

	// create a ReduceProcess object and call its constructor.
	ReduceProcess ReduceProcessObj(intermediateFilePath, outputFilePath, processNumber, numberOfThreads);

}//End of Program
