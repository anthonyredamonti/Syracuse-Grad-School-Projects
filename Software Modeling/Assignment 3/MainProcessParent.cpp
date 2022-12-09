/*
 * Anthony Redamonti
 * Professor Gregory Wagner
 * CSE 681 Software Modeling
 * Assignment 3
 * 8/24/2022
 *
 * Main.cpp
 * 
 * The following program defines a parent process that creates 2 child processes.
 * The parent will pass as arguments a file path to a text file and a processes 
 * ID. The child process will count the number of words in the file and print the
 * number of words along with its process ID.
 */

#include <iostream>
#include <string>
#include <thread>
#include <fstream>
#include <Windows.h>

using std::endl;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::string;
using std::thread;

int main(){

	// there are two seperate files. One for each process.
    string file1 = "CompleteWorksOfShakespeare1.txt";
    string file2 = "CompleteWorksOfShakespeare2.txt";
	string fileArray[2]; 
	fileArray[0] = file1;
	fileArray[1] = file2;

	// create the processes in a loop.
	for (int i = 0; i < 2; i++) {

		//************Start the processes**************
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		// create an array to hold the file.
		wchar_t wCharArray[100];

		// local variable for iterating through character array.
		int index{ 0 };
		for (int j = 0; j < fileArray[i].size(); j++) {
			wCharArray[j] = fileArray[i][index];
			index = index + 1;
		}

		wCharArray[index] = ' ';
		index = index + 1;

		// insert the process ID.
		wCharArray[index] = i+1;
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
			L"C:\\Users\\aredamonti\\projects\\Software Modeling\\Assignment3\\Assignment3Process\\x64\\Debug\\Assignment3Process.exe",
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
			return -6;
		}

		// Close process and thread handles. 
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
}