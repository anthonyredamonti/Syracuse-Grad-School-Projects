/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
6/7/2022

Main.cpp

The Stub 2 process will parse the command line arguments.
It will create a MapReduce.exe process and pass the arguments
to the process.

*/

#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <Windows.h>
#include <vector>

#pragma comment (lib, "ws2_32.lib")

using std::cerr;
using std::cout;
using std::endl;
using std::string;

// function definition.
void sendMessage(string message, SOCKET sock);

int main(int argc, char* argv[])
{
	//Initialize winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		cerr << "Can't Initialize winsock! Quitting" << endl;
		return -1;
	}

	//Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		cerr << "Can't create a socket! Quitting" << endl;
		return -2;
	}

	//Bind the ip address and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(55000);
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
		return -3;
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

	while (true)
	{
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
			break;
		}


		recievedString = string(buf, 0, bytesReceived);
		int n = recievedString.length();


		// declaring character array
		char char_array[4];

		// copying the contents of the
		// string to char array
		strcpy_s(char_array, recievedString.c_str());



		//************Start the processes**************
		// 
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		// create an array to hold an integer in string form.
		wchar_t wCharArray[10];

		// local variable for iterating through character array.
		int index{ 0 };

		cout << "\n" << char_array[0] << "\n";
		wCharArray[index] = char_array[0];
		index = index + 1;

		// insert a space
		wCharArray[index] = ' ';
		index = index + 1;

		cout << "\n" << char_array[2] << "\n";
		wCharArray[index] = char_array[2];
		index = index + 1;

		// end the string with the null character
		wCharArray[index] = 0;

		// convert the process number in string form to LPWSTR
		LPWSTR allArgsLpwstr = wCharArray;

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		// Start the child process. 
		if (!CreateProcess(
			L"C:\\Users\\antho\\OneDrive\\Documents\\Projects\\MapReduce\\x64\\Debug\\MapReduce.exe",
			allArgsLpwstr,        // Command line
			NULL,           // Process handle not inheritable
			NULL,           // Thread handle not inheritable
			FALSE,          // Set handle inheritance to FALSE
			0,              // No creation flags
			NULL,           // Use parent's environment block
			NULL,           // Use parent's starting directory 
			&si,            // Pointer to STARTUPINFO structure
			&pi)           // Pointer to PROCESS_INFORMATION structure
			)
		{
			printf("CreateProcess failed (%d).\n", GetLastError());
			return -4;
		}


		// Wait until child process exits.
		WaitForSingleObject(pi.hProcess, INFINITE);

		DWORD exit_code;
		GetExitCodeProcess(pi.hProcess, &exit_code);
		if (exit_code == STILL_ACTIVE) {
			cout << " Process is still active";
		}

		// Close process and thread handles. 
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		break;
	}

	//Echo message back to client
	sendMessage("Reduce is Done", clientSocket);

	//close the socket
	closesocket(clientSocket);

	//Cleanup winsock
	WSACleanup();

}

void sendMessage(string message, SOCKET sock)
{
	//send the message
	int sendResult = send(sock, message.c_str(), message.size() + 1, 0);

}
