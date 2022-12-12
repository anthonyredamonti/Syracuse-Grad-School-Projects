/*

Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
4/9/2022

Heartbeat.cpp

*/

#define  _WIN32_WINNT   0x0601

// Directives
//#include <Windows.h>
#include <thread>
#include <iostream>
#include <vector>
#include <WS2tcpip.h>
#include "Heartbeat.h"

//Name spaces
using std::cout;
using std::cerr;
using std::cin;
using std::string;
using std::ofstream;
using std::ifstream;
using std::runtime_error;
using std::thread;
using std::vector;

namespace logging = boost::log;
namespace keywords = boost::log::keywords;

// Stub Process constructor
Heartbeat::Heartbeat()
{
	// nothing to do at this time.
}

// initialize the threads and wait for them to finish.
void Heartbeat::waitForMapToFinish() {

	try {
		// string array of IP addresses.
		string ipAddressArray[2] = { "127.0.0.3", "127.0.0.4" };
		int portArray[2] = { 8002, 8003 };

		int filesProcessesSoFar{ 0 };
		int totalFilesCopy{ 0 };

		// a vector of threads
		vector<thread> heartbeatThreadVec1;

		// create the threads and push them into the vector
		// Begin the heartbeats thread. Start receiving heartbeat messages from the mapping processes.
		for (int i = 0; i < 2; i++) {
			int portNum = portArray[i];
			const char* ipAddress = ipAddressArray[i].c_str();
			thread threadObj([this, portNum, ipAddress] {this->receiveMapHeartbeatsThread(portNum, ipAddress); });
			heartbeatThreadVec1.push_back(std::move(threadObj));
		}

		// Wait for begin heartbeat messages to stop. (wait for mapping processes to finish.)
		// Iterate over the thread vector
		for (std::thread& th : heartbeatThreadVec1)
		{
			// If thread Object is Joinable then Join that thread.
			if (th.joinable())
				th.join();
		}


		filesProcessesSoFar = filesProcessesSoFar + 1;
		totalFilesCopy = totalNumberOfFiles;

		while (filesProcessesSoFar < totalFilesCopy) {
			// a vector of threads
			vector<thread> heartbeatThreadVec1;

			// create the threads and push them into the vector
			// Begin the heartbeats thread. Start receiving heartbeat messages from the mapping processes.
			for (int i = 0; i < 2; i++) {
				int portNum = portArray[i];
				const char* ipAddress = ipAddressArray[i].c_str();
				thread threadObj([this, portNum, ipAddress] {this->receiveMapHeartbeatsThread(portNum, ipAddress); });
				heartbeatThreadVec1.push_back(std::move(threadObj));
			}

			// Wait for begin heartbeat messages to stop. (wait for mapping processes to finish.)
			// Iterate over the thread vector
			for (std::thread& th : heartbeatThreadVec1)
			{
				// If thread Object is Joinable then Join that thread.
				if (th.joinable())
					th.join();
			}

			filesProcessesSoFar = filesProcessesSoFar + 1;
		}
	}
	
	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "Exception occurred in \"Controller::Heartbeat\"." << endl;
		cout << exception.what();
		throw exception;
	}

	// catch any exception here
	catch (...)
	{
		BOOST_LOG_TRIVIAL(fatal) << "Error in controller. Program will shutdown";
		throw;
	}	
};

// initialize the threads and wait for them to finish.
void Heartbeat::waitForReduceToFinish() {

	try {

		// string array of IP addresses.
		string ipAddressArray[2] = { "127.0.0.5", "127.0.0.6" };
		int portArray[2] = { 8004, 8005 };
		
		//int filesProcessesSoFar{ 0 };
		//int totalFilesCopy{ 0 };

		//totalFilesCopy = totalNumberOfFiles;

		//while (filesProcessesSoFar < totalFilesCopy) {
			
			// a vector of threads
			vector<thread> heartbeatThreadVec1;

			// create the threads and push them into the vector
			// Begin the heartbeats thread. Start receiving heartbeat messages from the mapping processes.
			for (int i = 0; i < 2; i++) {
				int portNum = portArray[i];
				const char* ipAddress = ipAddressArray[i].c_str();
				thread threadObj([this, portNum, ipAddress] {this->receiveReduceHeartbeatsThread(portNum, ipAddress); });
				heartbeatThreadVec1.push_back(std::move(threadObj));
			}

			// Wait for begin heartbeat messages to stop. (wait for mapping processes to finish.)
			// Iterate over the thread vector
			for (std::thread& th : heartbeatThreadVec1)
			{
				// If thread Object is Joinable then Join that thread.
				if (th.joinable())
					th.join();
			}

			//filesProcessesSoFar = filesProcessesSoFar + 1;
		//}
	}

	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "Exception occurred in \"Controller::Heartbeat\"." << endl;
		cout << exception.what();
		throw exception;
	}

	// catch any exception here
	catch (...)
	{
		BOOST_LOG_TRIVIAL(fatal) << "Error in controller heartbeat. Program will shutdown";
		throw;
	}
};

//Pre-condition: None.
//Post-condition: None.
//Receive heartbeats from the map processes.
void Heartbeat::receiveMapHeartbeatsThread(int inputPortNumber, const char* ipAddress) {
	try {

		// port number
		int portNumber = inputPortNumber;
		
		//Initialize winsock
		WSADATA wsData;
		WORD ver = MAKEWORD(2, 2);

		int wsOk = WSAStartup(ver, &wsData);
		if (wsOk != 0)
		{
			cerr << "Can't Initialize winsock! Quitting" << endl;
			return;
		}

		//Create a socket
		SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
		if (listening == INVALID_SOCKET)
		{
			cerr << "Can't create a socket! Quitting" << endl;
			return;
		}

		//Bind the ip address and port to a socket
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(portNumber);
		hint.sin_addr.S_un.S_addr = INADDR_ANY;// Could also use inet_pton

		bind(listening, (sockaddr*)&hint, sizeof(hint));

		//Tell winsock the socket is for listening
		listen(listening, SOMAXCONN);

		//wait for a connection
		sockaddr_in client;
		int clientSize = sizeof(client);

		SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
		if (clientSocket == INVALID_SOCKET)
		{
			cerr << "Can't create a client socket! Quitting" << endl;
			return;
		}

		char host[NI_MAXHOST];  //Client's remote name
		CHAR service[NI_MAXSERV];//Service (i.e. port) the client is connect on

		ZeroMemory(host, NI_MAXHOST); //same as memset(host, 0, NI_MAXHOST);
		ZeroMemory(service, NI_MAXSERV);

		if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
		{
			cout << host << " connected on port " << service << endl;
		}
		else
		{
			inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
			cout << host << " connected on port " <<
				ntohs(client.sin_port) << endl;
		}


		//Close listening socket
		closesocket(listening);

		//While loop: accept and echo message back to client
		char buf[4096];
		string recievedString;

		ZeroMemory(buf, 4096);

		//Wait for client to send data
		int bytesReceived = recv(clientSocket, buf, 4096, 0);
		if (bytesReceived == SOCKET_ERROR)
		{
			cerr << "Error in rec(). Quitting" << endl;
		}
		if (bytesReceived == 0)
		{
			cout << "Client disconnected " << endl;
		}

		// record the heartbeat message.
		string heartbeatMessage = buf;

		int counter{ 0 };

		// while we have not received the "Mapping complete" message, and we do not have an error, keep receiving heartbeat messages.
		while ((heartbeatMessage != "Mapping complete") && (bytesReceived != SOCKET_ERROR)) {
			cout << "Controller heartbeat thread received heartbeat message: " << heartbeatMessage << endl;

			// only perform the following operation once.
			if (counter == 0) {
				string startDelimiter = "Files Found: ";

				// create a substring of just the total number of files found.
				string numFilesStr = (heartbeatMessage).substr((heartbeatMessage).find(startDelimiter) + 13);

				// convert the string to an integer. Update the totalNumerOfFiles int.
				totalNumberOfFiles = stoi(numFilesStr);

				counter = 1;
			}

			// receive the next message from the mapping process.
			bytesReceived = recv(clientSocket, buf, 4096, 0);
			heartbeatMessage = buf;
		}

		// if there was an error reading the heartbeat message, display that here.
		if (bytesReceived == SOCKET_ERROR) {
			cout << "Controller heartbeat thread received an error reading heartbeat message." << endl;
		}

		//close the socket
		closesocket(clientSocket);

		//Cleanup winsock
		WSACleanup();
	}

	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "Error in controller heartbeat thread. Program will shutdown" << endl;
		cout << exception.what();
		throw exception;
	}

	// catch any exception here
	catch (...)
	{
		BOOST_LOG_TRIVIAL(fatal) << "Error in controller heartbeat thread. Program will shutdown";
		throw;
	}
}

//Pre-condition: None.
//Post-condition: None.
//Receive heartbeats from the reduce processes.
void Heartbeat::receiveReduceHeartbeatsThread(int inputPortNumber, const char* ipAddress) {
	try {

		// port number
		int portNumber = inputPortNumber;

		cout << portNumber << endl;

		//Initialize winsock
		WSADATA wsData;
		WORD ver = MAKEWORD(2, 2);

		int wsOk = WSAStartup(ver, &wsData);
		if (wsOk != 0)
		{
			cerr << "Can't Initialize winsock! Quitting" << endl;
			return;
		}

		//Create a socket
		SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
		if (listening == INVALID_SOCKET)
		{
			cerr << "Can't create a socket! Quitting" << endl;
			return;
		}

		//Bind the ip address and port to a socket
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(portNumber);
		hint.sin_addr.S_un.S_addr = INADDR_ANY;// Could also use inet_pton

		bind(listening, (sockaddr*)&hint, sizeof(hint));

		//Tell winsock the socket is for listening
		listen(listening, SOMAXCONN);

		//wait for a connection
		sockaddr_in client;
		int clientSize = sizeof(client);

		SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
		if (clientSocket == INVALID_SOCKET)
		{
			cerr << "Can't create a client socket! Quitting" << endl;
			return;
		}

		char host[NI_MAXHOST];  //Client's remote name
		CHAR service[NI_MAXSERV];//Service (i.e. port) the client is connect on

		ZeroMemory(host, NI_MAXHOST); //same as memset(host, 0, NI_MAXHOST);
		ZeroMemory(service, NI_MAXSERV);

		if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
		{
			cout << host << " connected on port " << service << endl;
		}
		else
		{
			inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
			cout << host << " connected on port " <<
				ntohs(client.sin_port) << endl;
		}


		//Close listening socket
		closesocket(listening);

		//While loop: accept and echo message back to client
		char buf[4096];
		string recievedString;

		ZeroMemory(buf, 4096);

		//Wait for client to send data
		int bytesReceived = recv(clientSocket, buf, 4096, 0);
		if (bytesReceived == SOCKET_ERROR)
		{
			cerr << "Error in rec(). Quitting" << endl;
		}
		if (bytesReceived == 0)
		{
			cout << "Client disconnected " << endl;
		}

		// record the heartbeat message.
		string heartbeatMessage = buf;

		// while we have not received "Reducing complete" or "Mapping complete" messages, and we do not have an error, keep receiving heartbeat messages.
		while ((heartbeatMessage != "Reducing complete") && (bytesReceived != SOCKET_ERROR)) {
			cout << "Controller heartbeat thread received heartbeat message: " << heartbeatMessage << endl;
			bytesReceived = recv(clientSocket, buf, 4096, 0);
			heartbeatMessage = buf;
		}

		// if there was an error reading the heartbeat message, display that here.
		if (bytesReceived == SOCKET_ERROR) {
			cout << "Controller heartbeat thread received an error reading heartbeat message." << endl;
		}

		//close the socket
		closesocket(clientSocket);

		//Cleanup winsock
		WSACleanup();
	}

	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "Error in controller heartbeat thread. Program will shutdown" << endl;
		cout << exception.what();
		throw exception;
	}

	// catch any exception here
	catch (...)
	{
		BOOST_LOG_TRIVIAL(fatal) << "Error in controller heartbeat thread. Program will shutdown";
		throw;
	}
}

// Virtual Destructor
Heartbeat::~Heartbeat() {
	// nothing to do at this time.
}

