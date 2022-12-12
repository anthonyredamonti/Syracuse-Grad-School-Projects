#define  _WIN32_WINNT   0x0601

#include <iostream>
#include <string>
#include <thread>
#include <WS2tcpip.h>
#include <vector>
#pragma comment(lib, "ws2_32.lib")

#include "Heartbeat.h"

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::thread;

// function declarations.
int startStub1();
int startStub2();

void main()
{
	// create a heartbeat object.
	Heartbeat heartbeatObj;

	// create both stub processes.
	if (startStub1() < 0) { return; }
	if (startStub2() < 0) { return; }

	cout << "Welcome to the MapReduce Controller" << endl;

	//*******************************First Socket***********************************

	string ipAddress = "127.0.0.1";  //IP Address of the server
	int port = 54000;					//Listening port # of the server

	//Initialize Winsock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		cerr << "Can't start winsock, ERR #" << wsResult << endl;
		return;
	}


	//Create Socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}


	//Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);


	//Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return;
	}

	//Do-While loop to send and receive data
	char buf[4096];
	string userInput;
	string returnMessage = "";

	userInput = "2 0";

	if (userInput.size() > 0)		//Make sure user has typed in something
	{
		//send the text (begin mapping)
		int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
		if (sendResult != SOCKET_ERROR)
		{
			heartbeatObj.waitForMapToFinish();
		}
	}

	//Gracefully close down everything
	closesocket(sock);
	WSACleanup();

	//*******************************Second Socket***********************************

	port = 55000;					//Listening port # of the server

	//Initialize Winsock
	wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		cerr << "Can't start winsock, ERR #" << wsResult << endl;
		return;
	}


	//Create Socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}


	//Fill in a hint structure
	hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);


	//Connect to server
	connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return;
	}

	userInput = "2 1";

	if (userInput.size() > 0)		//Make sure user has typed in something
	{
		//send the text
		int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
		if (sendResult != SOCKET_ERROR)
		{
			heartbeatObj.waitForReduceToFinish();
		}
	}

	//Gracefully close down everything
	closesocket(sock);
	WSACleanup();

}

// start the stub 1 process.
int startStub1() {
	//************Start the process**************
	// 
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	// create an array to hold an integer in string form.
	wchar_t wCharArray[10];

	// local variable for iterating through character array.
	int index{ 0 };

	// end the string with the null character
	wCharArray[index] = 0;

	// convert the process number in string form to LPWSTR
	LPWSTR allArgsLpwstr = wCharArray;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// Start the child process. 
	if (!CreateProcess(
		L"C:\\Users\\antho\\OneDrive\\Documents\\Projects\\Stub1\\x64\\Debug\\Stub1.exe",
		allArgsLpwstr,  // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi)            // Pointer to PROCESS_INFORMATION structure
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return -1;
	}

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return 0;
}

// start the stub 2 process.
int startStub2() {
	//************Start the process**************
	// 
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	// create an array to hold an integer in string form.
	wchar_t wCharArray[10];

	// local variable for iterating through character array.
	int index{ 0 };

	// end the string with the null character
	wCharArray[index] = 0;

	// convert the process number in string form to LPWSTR
	LPWSTR allArgsLpwstr = wCharArray;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// Start the child process. 
	if (!CreateProcess(
		L"C:\\Users\\antho\\OneDrive\\Documents\\Projects\\Stub2\\x64\\Debug\\Stub2.exe",
		allArgsLpwstr,  // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi)            // Pointer to PROCESS_INFORMATION structure
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return -1;
	}

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return 0;
}
