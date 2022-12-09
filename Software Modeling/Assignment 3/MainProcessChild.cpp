/*
 * Anthony Redamonti
 * Professor Gregory Wagner
 * CSE 681 Software Modeling
 * Assignment 3
 * 8/24/2022
 *
 * The following program defines a child process that is called by a parent 
 * process. The parent process passes 2 arguments to the child process: an 
 * input file path (must be .txt extension) and a process ID.
 * 
 * The child process will count the words in the file and display it to the
 * console along with its process ID.
 *
 */

#include <iostream>
#include <fstream>
#include <string>

using std::endl;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::string;
using std::stoi;

int main(int argc, char* argv[])
{
    // convert the data to a string
    string inputFile = argv[0];

    // process ID
    string processIDStr = argv[1];
    char lastChar = processIDStr[processIDStr.length() - 1];

    ifstream ifstreamObj;
    string data;
    
    // parse the input text file. Count the number of words.
    try {
        ifstreamObj.open(inputFile);
        int numberOfWords{ 0 };
        while (!ifstreamObj.eof()) {
            std::getline(ifstreamObj, data);
            for (int i = 0; i < data.length(); i++) {
                if (data.at(i) == ' ') {
                    numberOfWords = numberOfWords + 1;
                }
            }
        }

        // display the number of words to the user.
        printf("Process %d finished. %d words found.\n", lastChar, numberOfWords);
    }
    catch (std::exception exceptionObj) {
        cout << "Exception: " << exceptionObj.what() << endl;
    }
}