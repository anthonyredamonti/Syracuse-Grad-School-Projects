/*
Anthony Redamonti
Professor Jonathan S. Weissman
CIS 554 - M401 Object Oriented Programming C++
Syracuse University
HW #4 - Exercise 6.57-6.61
8/13/2021

ComputerAssistedInstruction.h

Below is the "ComputerAssistedInstruction" class, which
teaches the user various levels of arithmetic. The user
will set the arithmetic type and difficulty level before
beginning. 
*/

#ifndef COMPUTERASSISTEDINSTRUCTION
#define COMPUTERASSISTEDINSTRUCTION
#include<vector>

using std::string;

class ComputerAssistedInstruction {
public:
	// ------------- PUBLIC DATA MEMBER FUNCTIONS ----------------

	ComputerAssistedInstruction(); // Constuctor used to initialize private data members.

	// "Get/Set" functions.
	void setQuestion(); // generates a new question
	string getQuestion();
	void setUserAnswer(int inputAnswer);
	int getUserAnswer();
	int setDifficultyLevel(int inputDifficulty);
	int getDifficultyLevel();
	int getMaxDifficultyLevel();
	int getMinDifficultyLevel();
	int setArithmeticType(int inputType);
	int getArithmeticType();
	int getNumberOfQuestionsToAsk();
	void setNumberOfQuestionsToAsk(int inputNumberOfQuestions);

	bool isUserCorrect(); // checks if users answer is correct
	string getProgramResponse(); // returns the program response to the user
	string getProgramAdvice(); // after user is finished answering questions, program gives advice to user
	void resetForNextUser(); // resets two private data member variables for next user
	void incrementCorrectAnswerCounter(); // increment the correct answer counter
	void incrementIncorrectAnswerCounter(); // increment the incorrect answer counter

private:
	// -----------  PRIVATE DATA MEMBER FUNCTIONS ---------------
	int powerFunc(int base, int exponent); // returns base^exponent
    int createRandomNumber(int min, int max); // returns a random number in the range min to max (inclusive)
	bool isInputDifficultyLevelValid(int inputDifficultyLevel); // checks validity of user input
	bool isInputArithmeticTypeValid(int inputArithmeticType); // checks validity of user input
	void calculateRandomNumberRange(); // calculates the range of the random numbers (randomNumber1 and randomNumber2)
	void updateRandNum1AndRandNum2(); // generates new random numbers (randomNumber1 and randomNumber2)
	void calculateCorrectAnswer(); // calculates the correct answer to the question
	void updateProgramResponse(); // updates the program response to the answer of each question

	// -----------  PRIVATE DATA MEMBER VARIABLES ---------------
	string programQuestion;
	string programResponse;
	int correctAnswer;
	int totalCorrectAnswers;
	int totalIncorrectAnswers;
	int numberOfQuestionsToAsk;
	int userAnswer;
	int randomNumber1;
	int randomNumber2;
	int difficultyLevel; // 1 to 5
	int maxDifficultyLevel; 
	int minDifficultyLevel;  
	int arithmeticType; // 1 = addition. 2 = subtraction. 3 = multiplication. 4 = division. 5 = random (1-4).
	int maxArithmeticType;
	int minArithmeticType;
	int randomNumberMin; // the random integers shall be no less than this value
	int randomNumberMax; // the random integers shall be no greater than this value
	bool arithmeticTypeFiveFlag; // flag used for arithmetic type 5
};

#endif
