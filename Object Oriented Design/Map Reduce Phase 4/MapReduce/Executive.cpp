/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
4/9/2022

Executive.cpp

Below is Executive.cpp file.
This file has the main() function.
It will print to screen a banner message for the user.
Prompt the user to input three directories: input, temporary, and output.
It will then create a Workflow class object with these file directories.


*/


//Directives
#include "Workflow.h"
#include <Windows.h>

#include <iostream>
#include <string>
#include <fstream>

#include <boost/timer/timer.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

//Name spaces
using std::cout;
using std::cin;
using std::string;

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
//Initiate variables to hold the names of the directory locations
const string inputFileName{ "C:\\Users\\Colton Wilson\\Desktop\\CIS687 OOD\\Project4\\MapReduce_Project_Phase-4-two\\shakespeare" };
const string intermediateFileName{ "C:\\Users\\Colton Wilson\\Desktop\\CIS687 OOD\\Project4\\MapReduce_Project_Phase-4-two\\Results\\Temp" };
const string outputFileName{ "C:\\Users\\Colton Wilson\\Desktop\\CIS687 OOD\\Project4\\MapReduce_Project_Phase-4-two\\Results\\Output" };

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

	

	// convert the data to a string
	string processNumber = argv[0];


	// store the process number.
	string whatToDo = argv[1];

	//Banner Message
	cout << "*************************************************************************************"
		<< "\n*\t\t\tWelcome to the MapReduce!                                    *"
		<< "\n*----------------------------------------------------------------------------------- *"
		<< "\n*This program will allow a user to input their input directory                       *"
		<< "\n*where text files are stored and will ultimately produce a single output file that   *"
		<< "\n*contains a list of words and their associated counts in the originating input files.*"
		<< "\n**************************************************************************************"
		<< "\n*                               Example input                                        *"
		<< "\n*------------------------------------------------------------------------------------*"
		<< "\n* Input File Directory: c:\\...\\chosen_file.txt                                       *"
		<< "\n* Intermediate File Directory: c:\\...\\chosen_file.txt                                *"
		<< "\n* Output File Directory: chosen_file.txt                                             *"
		<< "\n**************************************************************************************";
	cout.flush();



	Workflow workFlow(inputFileName, intermediateFileName, outputFileName, stoi(whatToDo), stoi(processNumber));

}//End of Program
