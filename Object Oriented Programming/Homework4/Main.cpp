/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
HW #4 - Exercise 6.57-6.61
8/13/2021

Main.cpp

The following program is a Computer Assisted Instruction (CAI) program.
It will ask the user for the arithmetic type and difficulty to
practice. After the user has provided ten answers, the program will
tell the user if they are ready for the next level and reset for the 
next user.

At the beginning of the program, enter any number that is not -1 to
begin the game or -1 to quit.

The range of valid arithmetic types is from 1 to 5.
The range of valid difficulty levels is from 1 to 5. 
*/

#include <iostream>   // needed for the standard library
#include <iomanip>    // needed for setw() and setfill()
#include "ComputerAssistedInstruction.h"  // defines the ComputerAssistedInstruction class

// importing objects from the C++ standard library
using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::setfill;

// print "SU" for Syracuse University on the console
void printSyracuseBanner(); 

int main() {

	// initialize local variables
	int keepPlaying{ 0 };
	int inputType{ 0 };
	int inputDifficulty{ 0 };
	int inputIsValid{ 0 };
	string question{ "" };
	string programResponse{ "" };
	string advice{ "" };
	int answer{ 0 };
	
	// print Syracuse Banner
	printSyracuseBanner();

	// information about program
	cout << "Welcome to the Computer Assisted Instruction program!\n" <<
		"The following program asks the user for the type of\n" <<
		"arithmetic to practice and the difficulty level.\n\n" <<
		"The user will be asked a question and prompted for\n" <<
		"an answer. Once the user has provided 10 answers, the\n" <<
		"program will provide feedback on their performance.\n" << 
		"The program will then start from the beginning.\n\n";

	// create new Cai Chart object 
	ComputerAssistedInstruction caiObj;

	caiObj.setNumberOfQuestionsToAsk(10); // ask 10 questions

	// create a while loop checking if the user wants to keep playing
	// after each use.
	cout << "Enter any number to play the game, except -1.\n"
		<< "Enter -1 to quit: ";
	cin >> keepPlaying;

	// if the user enters -1, end the program.
	while (keepPlaying != -1) {

		// display the arithmetic type options
		cout << "\nPlease select a type of arithmetic to practice.\n"
			<< "Enter a number from 1 to 5 signifying the\n"
			<< "arithmetic type.\n\n"
			<< setfill(' ') << setw(21) << "1 = Addition\n"
			<< setfill(' ') << setw(24) << "2 = Subtraction\n"
			<< setfill(' ') << setw(27) << "3 = Multiplication\n"
			<< setfill(' ') << setw(21) << "4 = Division\n"
			<< setfill(' ') << setw(23) << "5 = Random Mix\n";

		// prompt the user for the arithmetic type
		cout << "\nPlease enter an arithmetic type: ";
		cin >> inputType;
		inputIsValid = caiObj.setArithmeticType(inputType);

		// If the user entered an invalid value, prompt the user for 
		// the arithmetic type again
		while (inputIsValid == -1) {
			cout << "\nPlease enter an arithmetic type: ";
			cin >> inputType;
			inputIsValid = caiObj.setArithmeticType(inputType);
		}

		inputIsValid = 0; // reset inputIsValid (local variable)

		// prompt the user for the difficulty level
		cout << "\nPlease enter a difficulty level from " << caiObj.getMinDifficultyLevel() <<
			" to " << caiObj.getMaxDifficultyLevel() << ": ";
		cin >> inputDifficulty;
		inputIsValid = caiObj.setDifficultyLevel(inputDifficulty);

		// If the user entered an invalid value, prompt the user for 
		// the difficulty level again
		while (inputIsValid == -1) {
			// prompt the user for the difficulty level
			cout << "\nPlease enter a difficulty level from " << caiObj.getMinDifficultyLevel() <<
				" to " << caiObj.getMaxDifficultyLevel() << ": ";
			cin >> inputDifficulty;
			inputIsValid = caiObj.setDifficultyLevel(inputDifficulty);
		}

		caiObj.setQuestion(); // generate a question

		// ask the user 10 questions
		for (int i = 0; i < caiObj.getNumberOfQuestionsToAsk(); i++) {
			question = caiObj.getQuestion(); // get the question
			cout << question << '\n';        // print it to console
			cout << "Enter answer: ";
			cin >> answer;                   // collect answer
			caiObj.setUserAnswer(answer);    // set answer

			programResponse = caiObj.getProgramResponse(); // get the program response

			// display the response
			cout << programResponse << '\n';

			// if user is correct, generate a new question to ask
			if (caiObj.isUserCorrect()) {
				caiObj.incrementCorrectAnswerCounter(); // increment correct answer counter
				caiObj.setQuestion(); // generate new question
			}
			// if user is incorrect, increment incorrect answer counter
			else {
				caiObj.incrementIncorrectAnswerCounter();
			}
		}

		advice = caiObj.getProgramAdvice(); // Get the advice of the program (analysis of user performance).
		cout << advice << '\n';

		caiObj.resetForNextUser(); // Reset the correct answer counter for the next user.

		// Ask the user if they would like to play again.
		cout << "\nEnter any number to play again, except -1."
			<< "\nEnter -1 to quit: ";
		cin >> keepPlaying;
	}
}

// Print "SU" for Syracuse University on the console.
void printSyracuseBanner() {
	cout 
		<< "                   .-----------.            .----.          .----.\n"
		<< "                 /             |            |    |          |    |\n"
		<< "                /    .---------*            |    |          |    |\n"
		<< "               .    /                       |    |          |    |\n"
		<< "               |   |                        |    |          |    |\n"
		<< "               |    .                       |    |          |    |\n"
		<< "                .    *-------.              |    |          |    |\n"
		<< "                 *.            *            |    |          |    |\n"
		<< "                   *----.       *           |    |          |    |\n"
		<< "                          .      *          |    |          |    |\n"
		<< "                          |      |          |    |          |    |\n"
		<< "                         /       /          |    |          |    |\n"
		<< "                .-------*       *           *     *--------*     /\n"
		<< "                |             *              *                  / \n"
		<< "                *----------*                   *--------------*   \n\n";
}