/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
HW #4 - Exercise 6.57-6.61
8/13/2021

ComputerAssistedInstruction.cpp

Below is the "ComputerAssistedInstruction" class, which
teaches the user various levels of arithmetic. The user
will set the arithmetic type and difficulty level before
beginning.

The setQuestion() public data member function generates
a new question and returns that question to the user.
The setQuestion() function calls the helper function
updateRandNum1AndRandNum2() to set private data members
randomNumber1 and randomNumber2. It also calls helper
function calculateCorrectAnswer() to calculate the 
correct answer to the new question.

The rand() function is limited by RAND_MAX, which is 
library-dependent but is guaranteed to be at least 
32767. Therefore, the private data member variable,
maxDifficultyLevel, is set to 5 (5 digits max).

*/

#include <ctime> // needed for time() function
#include <iostream>
#include <string> // needed for to_string()
#include <vector> // needed for string operator vector
#include "ComputerAssistedInstruction.h"

using std::cout;
using std::endl;
using std::to_string;
using std::vector;

// The BarChart constructor which initializes the private data members
// and seeds the pseudo-random number generator
ComputerAssistedInstruction::ComputerAssistedInstruction()
	: programQuestion{ "" }, 
	programResponse{ "" },
	numberOfQuestionsToAsk{ 10 },
	totalCorrectAnswers{ 0 },
	totalIncorrectAnswers{ 0 },
	difficultyLevel{ 0 },
	correctAnswer{ 0 },
	randomNumberMax{ 0 },
	randomNumberMin{ 0 },
	userAnswer{ 0 },
	randomNumber1{ 0 },
	randomNumber2{ 0 },
	minDifficultyLevel{ 1 }, // initialize minimum difficulty value to 1
	maxDifficultyLevel{ 5 }, // initialize minimum difficulty value to 5
	arithmeticType{ 0 },
	minArithmeticType{ 1 },  // initialize minimum arithmetic type to 1
	maxArithmeticType{ 5 },   // initialize maximum arithmetic type to 5
	arithmeticTypeFiveFlag{ false }
{
	srand(time(0)); // seed the pseudo-random number generator with the current time in seconds
}

// retrieve the response from the program
string ComputerAssistedInstruction::getProgramAdvice() {
	string advice;
	double percentageCorrect{ 0 };
	double totalCorrectDouble = totalCorrectAnswers;
	percentageCorrect = totalCorrectDouble / numberOfQuestionsToAsk;
	
	if (percentageCorrect < 0.75) {
		advice = "Please ask your teacher for extra help.";
	}
	else {
		advice = "Congratulations, you are ready to go to the next level!";
	}
	return(advice);
}

// call updateProgramResponse and return the updated response from the program
string ComputerAssistedInstruction::getProgramResponse() {
	updateProgramResponse();
	return(programResponse);
}

// switch statement used to select a random program response.
void ComputerAssistedInstruction::updateProgramResponse() {
	// there are four valid responses for correct answers and four valid responses 
	// for incorrect answers.
	int randomNumber = createRandomNumber(1, 4); 
	// User entered a correct answer.
	if (isUserCorrect()) {
		switch (randomNumber) {
		case 1:
			programResponse = "Very good!";
			break;
		case 2:
			programResponse = "Excellent!";
			break;
		case 3:
			programResponse = "Nice work!";
			break;
		case 4:
			programResponse = "Keep up the good work!";
			break;
		default:
			programResponse = "Internal Error: Random Number Generator is broken.";
		}
	}
	// User entered an incorrect answer.
	else {
		switch (randomNumber) {
		case 1:
			programResponse = "No. Please try again.";
			break;
		case 2:
			programResponse = "Wrong. Try once more.";
			break;
		case 3:
			programResponse = "Don't give up!";
			break;
		case 4:
			programResponse = "No. Keep trying.";
			break;
		// if default case is hit, there is an error.
		default:
			programResponse = "Internal Error: Random Number Generator is broken.";
		}
	}
}

// set the number of questions to ask the user. Default to 10 on startup.
void ComputerAssistedInstruction::setNumberOfQuestionsToAsk(int inputNumberOfQuestions) {
	// user entered invalid input
	if (inputNumberOfQuestions < 1) {
		cout << "\nPlease ask at least one question to the user.\n";
		return;
	}
	// user entered valid input
	else {
		numberOfQuestionsToAsk = inputNumberOfQuestions;
	}
}

// retrieve the number of questions to ask the user
int ComputerAssistedInstruction::getNumberOfQuestionsToAsk() {
	return(numberOfQuestionsToAsk);
}

// retrieve the question
string ComputerAssistedInstruction::getQuestion() {
	return(programQuestion);
}

// get user answer
int ComputerAssistedInstruction::getUserAnswer() {
	return(userAnswer);
}

// set user answer
void ComputerAssistedInstruction::setUserAnswer(int inputAnswer) {
	userAnswer = inputAnswer;
}

// Retrieve the maximum difficulty level allowed in the game.
int ComputerAssistedInstruction::getMaxDifficultyLevel() {
	return(maxDifficultyLevel);
}

// Retrieve the minimum difficulty level allowed in the game.
int ComputerAssistedInstruction::getMinDifficultyLevel() {
	return(minDifficultyLevel);
}

// get the private data member arithmeticType
int ComputerAssistedInstruction::getArithmeticType() {
	return(arithmeticType);
}

// set the private data member arithmeticType
// check if user input is valid.
int ComputerAssistedInstruction::setArithmeticType(int inputArithmeticType) {
	if (!isInputArithmeticTypeValid(inputArithmeticType)) {
		cout << "The arithmetic type " << inputArithmeticType << " is outside the range of acceptable values.\n"
			<< "Please only enter valid values in range " << minArithmeticType << " to " << maxArithmeticType << "." << endl;
		return(-1); // error number
	}

	// The input arithmetic type is valid. 
	// Set the private data member arithmeticType to the input value.
	else {
		arithmeticType = inputArithmeticType;
		return(1); // success
	}
}

// check if the user entered a valid arithmetic type
bool ComputerAssistedInstruction::isInputArithmeticTypeValid(int inputArithmeticType) {
	// If input >= minArithmeticType and input <= maxArithmeticType, input is valid.
	// Return true.
	if ((inputArithmeticType >= minArithmeticType) && (inputArithmeticType <= maxArithmeticType)) {
		return(true);
	}
	// Return false for invalid input.
	else {
		return(false);
	}
}

// get the private data member difficultyLevel
int ComputerAssistedInstruction::getDifficultyLevel() {
	return(difficultyLevel);
}

// set the private data member difficultyLevel and call calculateRandomIntegerRange().
// check if user input is valid.
int ComputerAssistedInstruction::setDifficultyLevel(int inputDifficultyLevel) {
	if (!isInputDifficultyLevelValid(inputDifficultyLevel)) {
		cout << "The difficulty level " << inputDifficultyLevel << " is outside the range of acceptable values.\n"
			<< "Please only enter valid values in range " << minDifficultyLevel << " to " << maxDifficultyLevel << "." << endl;
		return(-1); // error number
	}

	// The input difficulty level is valid. 
	// Set the private data member difficultyLevel to the input value.
	else {
		difficultyLevel = inputDifficultyLevel;
		return(1); // success
	}
}

// Check if the user entered a valid difficulty level.
bool ComputerAssistedInstruction::isInputDifficultyLevelValid(int inputDifficultyLevel) {
	// If input >= minDifficultyLevel and input <= maxDifficultyLevel, input is valid.
	// Return true.
	if ((inputDifficultyLevel >= minDifficultyLevel) && (inputDifficultyLevel <= maxDifficultyLevel)) {
		return(true);
	}
	// Return false for invalid input.
	else {
		return(false);
	}
}

// simple power function that calculates base^exponent and returns answer (type int)
int ComputerAssistedInstruction::powerFunc(int base, int exponent) {
	int answer{ 1 };
	for (int i = 0; i < exponent; i++) {
		answer = answer * base;
	}
	return(answer);
}

// Generate a random number in the range min to max (inclusive).
int ComputerAssistedInstruction::createRandomNumber(int min, int max) {
	
	// initialize local variables
	int randomInt{ 0 };
	int difference{ 0 };

	difference = max - min; // difference between max and min values
	randomInt = rand(); // generate random integer

	// tailor random number so that it is within the desired range
	randomInt = (randomInt % (difference + 1)) + min;
	return(randomInt);
}

// generate a new question to ask the user
void ComputerAssistedInstruction::setQuestion() {

	// used for string concatenation
	string beginningString = "How much is ";
	char questionMark = '?';

	// vector holding arithmetic operators in string form
	vector<string> stringOperatorVector = { " plus ", " minus ", " times ", " divided by " };

	string strNumber1{ "" };
	string strNumber2{ "" };

	// Generate random numbers of appropriate size
	updateRandNum1AndRandNum2();

	// convert the random numbers to strings
	strNumber1 = to_string(randomNumber1);
	strNumber2 = to_string(randomNumber2);

	// if arithmetic type = 5, pick a random question type from 1 to 4.
	if (arithmeticType == 5) {
		arithmeticTypeFiveFlag = true; // set arithmetic type 5 flag set to true
		arithmeticType = createRandomNumber(1, 4); // generate a random number from 1 to 4
	}

	// if arithmetic type = 1, only ask addition questions
	if (arithmeticType == 1) {
		// concatenate the string
		programQuestion = beginningString + strNumber1 + stringOperatorVector[0] + strNumber2 + questionMark;
	}

	// if arithmetic type = 2, only ask subtraction questions
	else if (arithmeticType == 2) {
		// concatenate the string
		programQuestion = beginningString + strNumber1 + stringOperatorVector[1] + strNumber2 + questionMark;
	}

	// if arithmetic type = 3, only ask multiplication questions
	else if (arithmeticType == 3) {
		// concatenate the string
		programQuestion = beginningString + strNumber1 + stringOperatorVector[2] + strNumber2 + questionMark;
	}

	// if arithmetic type = 4, only ask division questions
	else if (arithmeticType == 4) {
		// concatenate the string
		programQuestion = beginningString + strNumber1 + stringOperatorVector[3] + strNumber2 + questionMark;
	}

	// else arithmeticType is a non-valid value. NOT GOOD!!
	else {
		cout << "\nArithmetic Type " << arithmeticType << " is not valid!\n";
	}

	// Calculate the correct answer using the random numbers that have been generated.
	calculateCorrectAnswer();

	// if arithmetic type five was chosen first, select a new arithmetic type from 1 to 4
	if (arithmeticTypeFiveFlag == true) {
		arithmeticType = createRandomNumber(1, 4); // generate a random number from 1 to 4
	}
}

// update the private data members randomNumber1 and randomNumber2 to random numbers.
void ComputerAssistedInstruction::updateRandNum1AndRandNum2() {
	calculateRandomNumberRange(); // use difficulty level to calculate range of random integers
	randomNumber1 = createRandomNumber(randomNumberMin, randomNumberMax);
	randomNumber2 = createRandomNumber(randomNumberMin, randomNumberMax);
}

// Establishes the range of valid values for randomNumber1 and randomNumber2.
// Is called by updateRandNum1AndRandNum2().
void ComputerAssistedInstruction::calculateRandomNumberRange() {
	// random integers shall be no smaller than this value
	randomNumberMin = 1;
	// random integers shall be no larger than this value
	randomNumberMax = (powerFunc(10, difficultyLevel) - 1);
}

// calculate the correct answer
void ComputerAssistedInstruction::calculateCorrectAnswer() {
	// if arithmetic type = 1, only ask addition questions
	if (arithmeticType == 1) {
		correctAnswer = randomNumber1 + randomNumber2;
	}

	// if arithmetic type = 2, only ask subtraction questions
	else if (arithmeticType == 2) {
		correctAnswer = randomNumber1 - randomNumber2;
	}

	// if arithmetic type = 3, only ask multiplication questions
	else if (arithmeticType == 3) {
		correctAnswer = randomNumber1 * randomNumber2;
	}

	// if arithmetic type = 4, only ask division questions
	else if (arithmeticType == 4) {
		correctAnswer = randomNumber1 / randomNumber2;
	}

	// if arithmetic type = 5, pick a random question type from 1 to 4.
	else if (arithmeticType == 5) {
		// do nothing. No calculation required.
	}

	// else arithmeticType is a non-valid value. NOT GOOD!!
	else {
		cout << "\nArithmetic Type " << arithmeticType << " is not valid!\n";
	}
}

// check if the user entered the correct answer. Return true for YES and false for NO.
bool ComputerAssistedInstruction::isUserCorrect() {
	// correct answer, return true.
	if (userAnswer == correctAnswer) {
		return true;
	}
	// incorrect answer, return false.
	else {
		return false;
	}
}

// increment the correct answer counter
void ComputerAssistedInstruction::incrementCorrectAnswerCounter() {
	totalCorrectAnswers = totalCorrectAnswers + 1;
}

// increment the incorrect answer counter
void ComputerAssistedInstruction::incrementIncorrectAnswerCounter() {
	totalIncorrectAnswers = totalIncorrectAnswers + 1;
}

// reset the answer counters (private data member variables) to 0.
// Called by main function when new user begins playing.
// Also reset arithmetic type five flag for next user.
void ComputerAssistedInstruction::resetForNextUser() {
	totalCorrectAnswers = 0; // reset correct answer counter for next user.
	totalIncorrectAnswers = 0; // reset incorrect answer counter for next user.
	// if arithmetic type 5 was selected, reset the flag to false for the next user.
	if (arithmeticTypeFiveFlag == true) {
		arithmeticTypeFiveFlag = false;
	}
}