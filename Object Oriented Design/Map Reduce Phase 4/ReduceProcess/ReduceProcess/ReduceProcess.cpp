/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
6/7/2022

ReduceProcess.cpp

Below is ReduceProcess.cpp, which is called by the ReduceProcess Main function.
The constructor takes the intermediate file path, output file path, process number,
and thread number as arguments.
The private data member function "reduceThread" call the reduce method in the 
ReduceLibrary DLL.

*/

// Directives
#include "Sorting.h"
#include "ReduceProcess.h"
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
ReduceProcess::ReduceProcess(string intermediateFilePath, string outputFilePath, string processNumber, string numberOfThreads)
{
	// convert the process number to an integer
	int processNumberInt = std::stoi(processNumber);

	// convert the string to an int
	int numberOfThreadsInt = std::stoi(numberOfThreads);

	// retrieve the size of the output 
	int outputFilePathSize = outputFilePath.size();

	// alter the output file path.
	string alteredOutputFilePath = outputFilePath.substr(0, outputFilePathSize - 4) + processNumber + outputFilePath.substr(outputFilePathSize - 4);

	// assign pointers to the files.
	string* intermediateFilePathPntr = &intermediateFilePath;
	string* outputFilePathPntr = &alteredOutputFilePath;

	// initialize local variables
	ofstream outputFileStream;

	//Open file and then close to clear the contents
	outputFileStream.open(alteredOutputFilePath);
	outputFileStream.close();

	// create an instance of the Sorting class.
	Sorting sortingObj(intermediateFilePathPntr);

	// Create local variables. Input file stream object
	ifstream inputFileStreamObj;
	string line;
	string entryString{ NULL };
	string* entryStrPntr{ NULL };

	// create a delimiter to find the following string: ")"
	string closedParenthesis{ ")" };
	string openParenthesis{ "(" };
	size_t openPos{ NULL };
	size_t closedPos{ NULL };

	// create a vector for all of the strings
	vector<string> allStringsVector;

	// an empty multidimensional vector of strings for the reduce threads
	vector<vector<string>> multiDimensionalStringVector;
	vector<string> threadStringVector;

	// put an empty string vector into the multidimensional string vector for each thread.
	for (int i = 0; i < numberOfThreadsInt; i++) {
		multiDimensionalStringVector.push_back(threadStringVector);
	}

	try {
		// format the file.
		sortingObj.format();

		// inform the user.
		cout << "\nWorkflow is now parsing the intermediate file and calling the Reduce class on each entry." << endl;

		// open the intermediate file
		try {
			inputFileStreamObj.open(*intermediateFilePathPntr);
		}

		// catch exception handled in exception class here
		catch (const runtime_error& exception) {
			cout << "\nException occurred in \"ReduceProcess::Main\".\n";
			cout << exception.what();
			throw exception;
		}

		// catch any exception here
		catch (...) {
			cout << "\nException occurred in \"ReduceProcess::Main\".\n";
			throw;
		}

		// assign the entry string pointer
		entryStrPntr = &entryString;

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

				// if the open and closed parentheses were found, pass the substring to the reduce class.
				if ((openPos != string::npos) && (closedPos != string::npos)) {

					// extract the entry. 
					entryString = line.substr(openPos, (closedPos - openPos) + 1);

					// push the string into the vector
					allStringsVector.push_back(entryString);
				}

				// update the offset into the line for the next search.
				offset = closedPos + 1;

				// Find the position of the next open parenthesis. 
				openPos = line.find(openParenthesis, offset);
			}
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
			string tempOutPath = alteredOutputFilePath;
			vector<string> tempVec = multiDimensionalStringVector[i];
			thread threadObj([this, tempOutPath, i, tempVec] {this->reduceThread(tempOutPath, i + 1, tempVec); });
			threadVector.push_back(std::move(threadObj));
		}

		// a vector for the heartbeat thread.
		vector<thread> heartbeatThreadVec;

		// begin heartbeat thread.
		for (int i = 0; i < 1; i++) {
			int procNum = processNumberInt;
			thread heartbeatThread([this, procNum] {this->heartbeatThread(procNum); });
			heartbeatThreadVec.push_back(std::move(heartbeatThread));
		}

		// Iterate over the thread vector
		for (std::thread& th : threadVector)
		{
			// If thread Object is Joinable then Join that thread.
			if (th.joinable())
				th.join();
		}

		// after completion, update the boolean value
		done = true;

		// Iterate over the thread vector
		for (std::thread& th : heartbeatThreadVec)
		{
			// If thread Object is Joinable then Join that thread.
			if (th.joinable())
				th.join();
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
ReduceProcess::~ReduceProcess() {
	// nothing to do at this time.
}

// creates a new thread to call the Reduce method in the ReduceLibrary DLL.
void ReduceProcess::reduceThread(string outputFilePath, int threadNumber, vector<string> stringVector) {
	try {
		// Load the Reduce constructor from the ReduceLibrary DLL
		HINSTANCE reduceDllHandle;
		funcReduce Reduce;
		const wchar_t* reduceLibraryName = L"C:\\Users\\antho\\OneDrive\\Documents\\Projects\\ReduceProcess\\ReduceLibrary.dll";

		// Load the library (DLL).
		reduceDllHandle = LoadLibraryEx(reduceLibraryName, NULL, NULL);   // Handle to DLL

		// perform the following if the DLL was able to be loaded.
		if (reduceDllHandle != NULL) {

			// Load the Reduce constructor from the DLL.
			Reduce = (funcReduce)GetProcAddress(reduceDllHandle, "Reduce");

			// get the size of the output file path
			int outputFilePathSize = outputFilePath.size();

			// add the process number of the end of the output file path.
			string newOutputFilePath = outputFilePath.substr(0, outputFilePathSize - 4) + std::to_string(threadNumber) + outputFilePath.substr(outputFilePathSize - 4);

			// call reduce on each string in the vector
			for (int i = 0; i < stringVector.size(); i++) {

				// pass the string to the reduce method from the Reduce class.
				Reduce(newOutputFilePath, stringVector[i]);
			}

			// Free the handle to the ReduceLibrary DLL.
			FreeLibrary(reduceDllHandle);
		}
		else {
			BOOST_LOG_TRIVIAL(fatal) << "Error loading ReduceLibrary DLL in reduceThread. Program will shutdown.";
			throw;
		}
	}
	// catch any exception here
	catch (...)
	{
		BOOST_LOG_TRIVIAL(fatal) << "Error in ReduceProcess::reduceThread method. Program will shutdown";
		throw;
	}
}

// Heartbeat thread that sends heartbeat message every 5 seconds.
void ReduceProcess::heartbeatThread(int processNumber) {
	try {

		int portNumber{ 0 };
		string ipAddress{ "NULL" };

		cout << "Process Number: " << processNumber << endl;

		// update the port number based on the process number.
		portNumber = 8003 + processNumber;

		// alter the ip address based on the process number.
		if (processNumber == 1) { ipAddress = "127.0.0.5"; }
		else if (processNumber == 2) { ipAddress = "127.0.0.6";	}
		else { 
			// nothing to do at this time. 
		}

		cout << "Port Number: " << portNumber << endl;
		cout << "IP address: " << ipAddress;

		// initialize local variables
		WSADATA winSockData;
		int errWsaStartUp;
		int errWsaCleanUp;

		SOCKET reduceProcSocket;
		int errCloseSocket;

		// address of the server 
		struct sockaddr_in controllerAddress;
		int errConnect;

		int errSend;
		char sendBuffer[512] = "Reducing in progress";
		char finishedBuffer[40] = "Reducing complete";
		int sizeOfSendBuffer = strlen(sendBuffer) + 1;
		int sizeOfFinishedBuffer = strlen(finishedBuffer) + 1;

		// call the startup function
		errWsaStartUp = WSAStartup(MAKEWORD(2, 2), &winSockData);
		if (errWsaStartUp != 0) {
			cout << "WSAStartup failed." << endl;
		}

		// create the socket
		reduceProcSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (reduceProcSocket == INVALID_SOCKET) {
			cout << "TCP Client Socket Creation Failed." << endl;
		}

		// convert the ip address to a constant char *
		const char* ipAddConst = ipAddress.c_str();

		// populate the structure.
		controllerAddress.sin_family = AF_INET; // TCP/IP
		controllerAddress.sin_addr.s_addr = inet_addr(ipAddConst);
		controllerAddress.sin_port = htons(portNumber);

		// establish the connection to the specified socket.
		while (connect(reduceProcSocket, (SOCKADDR*)&controllerAddress, sizeof(controllerAddress)) == SOCKET_ERROR) {

			cout << "Reduce process thread (client) waiting to connect to controller process (server)." << endl;

			// insert delay before part 2
			std::this_thread::sleep_for(std::chrono::seconds(10));
		}

		// while loop: while we are not done, keep sending heartbeat message: "Reducing in progress."
		while (!done) {
			// wait for command from the controller process.
			errSend = send(reduceProcSocket, sendBuffer, sizeOfSendBuffer, 0);
			if (errSend == SOCKET_ERROR) {
				cout << "Reduce process (heartbeat thread) failed to send data to the controller process." << endl;
			}

			// sleep for 5 seconds.
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}

		// wait for command from the controller process.
		errSend = send(reduceProcSocket, finishedBuffer, sizeOfFinishedBuffer, 0);
		if (errSend == SOCKET_ERROR) {
			cout << "Reduce process (heartbeat thread) failed to send data to the controller process." << endl;
		}

		// close the socket 
		errCloseSocket = closesocket(reduceProcSocket);
		if (errCloseSocket == SOCKET_ERROR) {
			cout << "Client process failed to close the socket." << endl;
		}

		// call the clean up method from the Windows Socket API
		errWsaCleanUp = WSACleanup();
		if (errWsaCleanUp == SOCKET_ERROR) {
			cout << "WSACleanup method failed in client process." << endl;
		}

		// print message that the stub process is exiting.
		cout << "Reduce process (heartbeat thread) is done" << endl;
	}

	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "Exception occurred in \"ReduceProcess::heartbeatThread\"." << endl;
		cout << exception.what();
		throw exception;
	}

	// catch any exception here
	catch (...)
	{
		BOOST_LOG_TRIVIAL(fatal) << "Error in Reduce Process Heartbeat Thread. Program will shutdown";
		throw;
	}
}
