/*
 * Anthony Redamonti
 * Professor Gregory Wagner
 * CSE 681 Software Modeling
 * Assignment 3
 * 8/24/2022
 *
 * Main.cpp
 *
 * The following program creates two threads that perform the same task.
 * Each thread has its own text file containing the complete works of 
 * Shakespeare. Each thread will parse the complete works of Shakespeare 
 * and count the total number of words. Each thread will then output the 
 * total number of words along with its thread ID. 
 *
 */

#include <iostream>
#include <string>
#include <thread>
#include <fstream>

using std::endl;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::string;
using std::thread;

// Method called by the thread.
// Counts the number of words in the file and displays it to 
// the console.
void threadMethod(const char * inputFile, string threadId){
    ifstream ifstreamObj;
    string data;
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
    printf("Thread %d finished. %d words found.\n", stoi(threadId), numberOfWords);
}

int main(){

    const char* file1 = "CompleteWorksOfShakespeare1.txt";
    const char* file2 = "CompleteWorksOfShakespeare2.txt";

    // start the threads
    thread thread1(threadMethod, file1, "1");
    thread thread2(threadMethod, file2, "2");

    // main thread will wait for thread1 and thread2 to finish.
    thread1.join();
    thread2.join();    
}



