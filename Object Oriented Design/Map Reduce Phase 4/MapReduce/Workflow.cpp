/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
6/7/2022

Workflow.cpp

---Note: This file does include the BOOST library in order to compile.

Below is Workflow.cpp, which is called by the  main() in Executive.cpp.
The constructor takes three string directory names and saves the strings into private data members.
The constructor will then tie together all the header files with supporting logic.
The public data member functions are setters and getters for each data member.

*/

//Constant R, how many buckets are being used
int RMAX{ 0 };
const int TMAX{ 5 };

//Directives
#include "Workflow.h"
#include "FileManagement.h"
#include "NotValidFile.h"

using std::to_string;

//default constructor
Workflow::Workflow() {}
//WorkFlow constructor with three parameters
Workflow::Workflow(string inputFile, string intermediateFile, string outputFile, int toDO, int processNumber)
{
	checkFilesValid(inputFile, intermediateFile, outputFile);

	startProgram(getInputFileLocation(), getIntermediateFileLocation(), getOutputFileLocation(), toDO, processNumber);
}

//**********Destructor*********
Workflow::~Workflow() {}

//**********Member Function**********


void Workflow::startProgram(string inputFile, string intermediateFile, string outputFile, int toDo, int processNumber)
{
	RMAX = processNumber;

	// update the number of files found in the input directory.
	getNumberOfFilesFound(inputFile);

	if (toDo == 0)
	{
		//<-----------------Part 1------------------------------------------>

		//Create an input and output stream class
		ifstream inputFileStream;
		ofstream ofStreamObj;

		//Create an object of the FileManagement class
		FileManagement FileStreamSystem;

		if (boost::filesystem::is_directory(inputFile))
		{
			// insert all of the files in the directory inside a vector of strings.
			vector<string> listOfFiles = FileStreamSystem.getAllFilesInDir(inputFile);

			for (auto str : listOfFiles)
			{
				cout << str << endl;
			}

			cout << "*************************************************************************************" << endl;
			//Open the input file and connect to the in stream. Then double check to make sure file is not corrupt
			for (auto str : listOfFiles)
			{
				//Banner Message
				cout << "*************************************************************************************"
					<< "\nMap process created for: " << str << "\n\n";
				cout.flush();
				partition(str, intermediateFile);
			}


		}// end if/else if input is directory
		else
		{
			//Banner Message
			cout << "*************************************************************************************"
				<< "\nMap process created for: " << inputFile << "\n\n";
			cout.flush();
			partition(inputFile, intermediateFile);


		}//End of if/else if input is a file

		// insert delay before part 2
		std::this_thread::sleep_for(std::chrono::seconds(10));

	}
	else
	{
		//<-----------------Part 2------------------------------------------>

		//Create an input and output stream class
		ifstream inputFileStream;
		ofstream ofStreamObj;

		//Create an object of the FileManagement class
		FileManagement FileStreamSystem;

		// a vector to store handles to the processes
		vector<HANDLE> processHandleVector;
		vector<HANDLE> processThreadVector;

		// create the Reduce processes.
		for (int i = 0; i < RMAX; i++) {

			// create an array of process handlers.
			HANDLE* processesHandle;

			// allocate memory for the process handle array.
			processesHandle = (HANDLE*)malloc(RMAX * sizeof(HANDLE));

			// declare the startup info and process information objects.
			STARTUPINFO si;
			PROCESS_INFORMATION pi;

			// convert the process number to a string
			string processNumber = std::to_string(i + 1);

			// convert the thread number to a string
			string threadNumber = std::to_string(TMAX);

			// create an array to hold an integer in string form.
			wchar_t wCharArray[255];

			// local variable for iterating through character array.
			int index{ 0 };

			int intermedFilePathSize = intermediateFile.size();

			// add the process number of the end of the intermediate file path.
			string newIntermediateFilePath = intermediateFile.substr(0, intermedFilePathSize - 4) + std::to_string(i + 1) + intermediateFile.substr(intermedFilePathSize - 4);

			// populate the character array with the new intermediate file path
			for (int i = 0; i < newIntermediateFilePath.size(); i++)
			{
				if (newIntermediateFilePath[i] == ' ')
				{
					wCharArray[index] = '\n';
				}
				else
				{
					wCharArray[index] = newIntermediateFilePath[i];
				}
				index = index + 1;
			}

			// insert a space
			wCharArray[index] = ' ';
			index = index + 1;

			// populate the character array with the output file path
			for (int i = 0; i < outputFile.size(); i++)
			{
				if (outputFile[i] == ' ')
				{
					wCharArray[index] = '\n';
				}
				else
				{
					wCharArray[index] = outputFile[i];
				}
				index = index + 1;
			}

			// insert a space
			wCharArray[index] = ' ';
			index = index + 1;

			// insert the process number into the wCharArray
			for (int i = 0; i < processNumber.size(); i++) {
				wCharArray[index] = processNumber[i];
				index = index + 1;
			}

			// insert a space
			wCharArray[index] = ' ';
			index = index + 1;

			// insert the thread number into the wCharArray
			for (int i = 0; i < threadNumber.size(); i++) {
				wCharArray[index] = threadNumber[i];
				index = index + 1;
			}

			// insert a space
			wCharArray[index] = ' ';
			index = index + 1;

			string numberOfFilesFoundStr = std::to_string(numberOfFilesFound);

			// insert the thread number into the wCharArray
			for (int i = 0; i < numberOfFilesFoundStr.size(); i++) {
				wCharArray[index] = numberOfFilesFoundStr[i];
				index = index + 1;
			}

			// end the string with the null character
			wCharArray[index] = 0;

			// convert the process number in string form to LPWSTR
			LPWSTR allArgsLpwstr = wCharArray;

			// zero the memory of the startup info object.
			ZeroMemory(&si, sizeof(si));

			// assign the size of the structure (cb) to the size of the object.
			si.cb = sizeof(si);

			// zero the memory of the process information object.
			ZeroMemory(&pi, sizeof(pi));

			// assign the processes handle array with this handle
			processesHandle[i] = pi.hProcess;

			// Start the child process. 
			if (!CreateProcess(
				L"C:\\Users\\antho\\OneDrive\\Documents\\Projects\\ReduceProcess\\x64\\Debug\\ReduceProcess.exe",   // No module name (use command line)
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
				//return -1;
			}

			// add the process to the process vectors
			processHandleVector.push_back(pi.hProcess);
			processThreadVector.push_back(pi.hThread);
		}

		// wait for all of the processes in the vector to finish
		for (int i = 0; i < processHandleVector.size(); i++) {

			// Wait until all child processes exit.
			//WaitForMultipleObjects(RMAX, processesHandleMap, TRUE, INFINITE);
			WaitForSingleObject(processHandleVector[i], INFINITE);

			// Close process and thread handles. 
			CloseHandle(processHandleVector[i]);
			CloseHandle(processThreadVector[i]);
		}

		int intermediateFileNameSize = intermediateFile.size();
		int outputFileSize = outputFile.size();



		// delete the temporary files.
		for (int i = 1; i <= RMAX; i++)
		{
			// add the correct extension to the files based on their process number.
			string newIntermedFileName = intermediateFile.substr(0, intermediateFileNameSize - 4) + std::to_string(i) + intermediateFile.substr(intermediateFileNameSize - 4);
			string newOutputFileName = outputFile.substr(0, outputFileSize - 4) + std::to_string(i) + outputFile.substr(outputFileSize - 4);

			// convert strings to const char* for remove method.
			const char* interFileChar = newIntermedFileName.c_str();
			const char* outputFileChar = newOutputFileName.c_str();

			//Open file and then close to clear the contents
			ofStreamObj.open(newIntermedFileName);
			ofStreamObj.close();
			remove(interFileChar);
			ofStreamObj.open(newOutputFileName);
			ofStreamObj.close();
			remove(outputFileChar);
		}

		// delete the temporary files.
		for (int i = 1; i <= RMAX; i++)
		{
			for (int j = 1; j <= TMAX; j++)
			{
				// add the correct extension to the files based on their process number.
				string newIntermedFileName = intermediateFile.substr(0, intermediateFileNameSize - 4) + std::to_string(i) + std::to_string(j) + intermediateFile.substr(intermediateFileNameSize - 4);

				// convert strings to const char* for remove method.
				const char* interFileChar = newIntermedFileName.c_str();

				//Open file and then close to clear the contents
				ofStreamObj.open(newIntermedFileName);
				ofStreamObj.close();
				remove(interFileChar);


			}

		}

		//open stream for the output file
		ofstream ofstreamObj;
		//clear the file
		FileStreamSystem.clearFile(ofStreamObj, outputFile);

		//save the size of output file
		int outputFileNameSize = outputFile.size();

		//vectors to store word and count
		vector<string>wordVec;
		vector<int>countVec;
		vector<string>wordCheckVec;
		vector<int>countCheckVec;

		string word;
		string number;


		//Combine output files
		for (int i = 1; i <= RMAX; i++) {
			for (int j = 1; j <= TMAX; j++) {
				// add the correct extension to the files based on their process number.
				string newOutputFileName = outputFile.substr(0, outputFileNameSize - 4) + std::to_string(i) + std::to_string(j) + outputFile.substr(outputFileNameSize - 4);

				//open the stream and the file to read from
				ifstream ifstreamObj;
				FileStreamSystem.openFileInstream(ifstreamObj, newOutputFileName);

				if (i == 1)
				{
					while (std::getline(ifstreamObj, word, ','))
					{
						wordVec.push_back(word);
						std::getline(ifstreamObj, number);
						countVec.push_back(stoi(number));
					}
				}
				else
				{

					while (std::getline(ifstreamObj, word, ','))
					{
						wordCheckVec.push_back(word);
						std::getline(ifstreamObj, number);
						countCheckVec.push_back(stoi(number));
					}

					for (int i = 0; i < wordVec.size(); i++)
					{
						for (int j = 0; j < wordCheckVec.size(); j++)
						{
							if (wordVec[i] == wordCheckVec[j])
							{
								countVec[i] = countVec[i] + countCheckVec[j];
								wordCheckVec.erase(wordCheckVec.begin() + j);
								countCheckVec.erase(countCheckVec.begin() + j);
								j--;
							}

						}

					}
					for (int k = 0; k < wordCheckVec.size(); k++)
					{
						wordVec.push_back(wordCheckVec[k]);
						countVec.push_back(countCheckVec[k]);
					}

					wordCheckVec.clear();
					countCheckVec.clear();

				}

				// convert strings to const char* for remove method.
				const char* outputFileChar = newOutputFileName.c_str();

				//close the input file
				FileStreamSystem.closeInputFile(ifstreamObj);

				//Open file and then close to clear the contents
				ofStreamObj.open(newOutputFileName);
				ofStreamObj.close();
				remove(outputFileChar);
			}
		}

		// open output file to write to
		FileStreamSystem.openFileOutstream(ofstreamObj, outputFile);

		cout << "word size: " << wordVec.size() << '\n';
		cout << "count. size: " << countVec.size() << '\n';


		for (int i = 0; i < wordVec.size(); i++)
		{
			ofstreamObj << wordVec[i] << ", " << to_string(countVec[i]) << endl;
		}

		// Close the output.txt file.
		FileStreamSystem.closeOutputFile(ofstreamObj);


		//Check if there was a directory path
		if (getOutputFileDirectoryLocation() == "")
		{
			// Print the SUCCESS.txt file to output directory.
			FileStreamSystem.openFileOutstream(ofstreamObj, "SUCCESS.txt");

		}
		else
		{
			// Print the SUCCESS.txt file to output directory.
			FileStreamSystem.openFileOutstream(ofstreamObj, getOutputFileDirectoryLocation() + "\\SUCCESS.txt");
		}

		// Close the SUCCESS.txt file.
		FileStreamSystem.closeOutputFile(ofstreamObj);


		// insert delay
		std::this_thread::sleep_for(std::chrono::seconds(10));

		cout << "\nSuccess. Program will now terminate." << endl;
	}
}

// Workflow::partition method. 
void Workflow::partition(const string& inputFile, const string& intermediateFile)
{
	// declare local variables
	FileManagement fileManagementObj;
	ofstream ofStreamObj;
	ifstream ifStreamObj;

	//Clear all intermediate files
	int inputFileNameSize = inputFile.size();

	// container for strings 
	vector<string> stringVector;
	vector<string> alteredInputFileNamesVector;

	//Initiate a variable to hold raw data given by the input file
	string data{ "Unknown" };

	// open the ifsteam object on the input file.
	fileManagementObj.openFileInstream(ifStreamObj, inputFile);

	// divide the file into smaller files of equal size.

	//Keep collecting data until the end of file and get a return of "1"
	while (data != "1")
	{
		//Get a line of data from the input file
		fileManagementObj.readFromFile(ifStreamObj, data);

		// push the data into the string vector.
		if (data != "1")
		{
			stringVector.push_back(data);
		}
	}

	ifStreamObj.close(); // close the input file stream object.

	// create file names for the smaller input files
	for (int i = 0; i < RMAX; i++) {

		// add the process number to the input file name.
		string newInputFileName = inputFile.substr(0, inputFileNameSize - 4) + std::to_string(i + 1) + inputFile.substr(inputFileNameSize - 4);

		// push the altered name on the alteredFileNamesVector
		alteredInputFileNamesVector.push_back(newInputFileName);
	}

	int vectorIndex{ 0 };

	// for each process, create a file.
	for (int i = 0; i < RMAX; i++) {

		// open a file output stream on the new input file
		fileManagementObj.openFileOutstream(ofStreamObj, alteredInputFileNamesVector[i]);

		// insert the correct number of strings into the file.
		for (int j = 0; j < stringVector.size() / RMAX; j++) {

			// insert a line of data into the file
			fileManagementObj.writeToOutputFile(ofStreamObj, stringVector[vectorIndex]);
			vectorIndex = vectorIndex + 1;
		}

		// close the ofstream operator.
		fileManagementObj.closeOutputFile(ofStreamObj);
	}

	// number of strings remaining to be written in the vector.
	int remainingStrings = stringVector.size() - vectorIndex;

	// open a file output stream on the new input file
	fileManagementObj.openFileOutstream(ofStreamObj, alteredInputFileNamesVector[0]);

	// write the remaining strings to the first file.
	for (int i = 0; i < remainingStrings; i++) {

		// insert a line of data into the file
		fileManagementObj.writeToOutputFile(ofStreamObj, stringVector[vectorIndex]);
		vectorIndex = vectorIndex + 1;
	}

	// close the ofstream operator.
	fileManagementObj.closeOutputFile(ofStreamObj);

	// a vector to store handles to the processes
	vector<HANDLE> processHandleVector;
	vector<HANDLE> processThreadVector;

	// create the Map Processes.
	for (int i = 0; i < RMAX; i++)
	{
		// create an array of process handlers.
		HANDLE* processesHandleMap;

		// declare the startup info and process information objects.
		STARTUPINFO siMap;
		PROCESS_INFORMATION piMap;

		// allocate memory for the process handle array.
		processesHandleMap = (HANDLE*)malloc(RMAX * sizeof(HANDLE));

		// convert the process number to a string
		string processNumber = std::to_string(i + 1);

		// convert the thread number to a string
		string threadNumber = std::to_string(TMAX);

		// create an array to hold an integer in string form.
		wchar_t wCharArray[750];

		// local variable for iterating through character array.
		int index{ 0 };

		// record the input file name size.
		int inputFilePathSize = inputFile.size();

		// add the process number to the file name.
		string alteredFileName = inputFile.substr(0, inputFilePathSize - 4) + std::to_string(i + 1) + inputFile.substr(inputFilePathSize - 4);

		// populate the character array with the input file path
		for (int j = 0; j < alteredFileName.size(); j++)
		{
			if (alteredFileName[j] == ' ')
			{
				wCharArray[index] = '\n';
			}
			else
			{
				wCharArray[index] = alteredFileName[j];
			}

			index = index + 1;
		}

		// insert a space
		wCharArray[index] = ' ';
		index = index + 1;

		// populate the character array with the intermediate file path
		for (int j = 0; j < intermediateFile.size(); j++)
		{
			if (intermediateFile[j] == ' ')
			{
				wCharArray[index] = '\n';
			}
			else
			{
				wCharArray[index] = intermediateFile[j];
			}
			index = index + 1;
		}

		// insert a space
		wCharArray[index] = ' ';
		index = index + 1;


		// insert the process number into the wCharArray
		for (int j = 0; j < processNumber.size(); j++) {
			wCharArray[index] = processNumber[j];
			index = index + 1;
		}

		// insert a space
		wCharArray[index] = ' ';
		index = index + 1;

		// insert the thread number into the wCharArray
		for (int i = 0; i < threadNumber.size(); i++) {
			wCharArray[index] = threadNumber[i];
			index = index + 1;
		}

		// insert a space
		wCharArray[index] = ' ';
		index = index + 1;

		string numberOfFilesFoundStr = std::to_string(numberOfFilesFound);

		// insert the thread number into the wCharArray
		for (int i = 0; i < numberOfFilesFoundStr.size(); i++) {
			wCharArray[index] = numberOfFilesFoundStr[i];
			index = index + 1;
		}

		// end the string with the null character
		wCharArray[index] = 0;

		// convert the process number in string form to LPWSTR
		LPWSTR allArgsLpwstr = wCharArray;

		// zero the memory of the startup info object.
		ZeroMemory(&siMap, sizeof(siMap));

		// assign the size of the structure (cb) to the size of the object.
		siMap.cb = sizeof(siMap);

		// zero the memory of the process information object.
		ZeroMemory(&piMap, sizeof(piMap));

		// Start the child process. 
		if (!CreateProcess(
			L"C:\\Users\\antho\\OneDrive\\Documents\\Projects\\MapProcess\\x64\\Debug\\MapProcess.exe",   // No module name (use command line)
			allArgsLpwstr,        // Command line
			NULL,           // Process handle not inheritable
			NULL,           // Thread handle not inheritable
			FALSE,          // Set handle inheritance to FALSE
			0,              // No creation flags
			NULL,           // Use parent's environment block
			NULL,           // Use parent's starting directory 
			&siMap,            // Pointer to STARTUPINFO structure
			&piMap)           // Pointer to PROCESS_INFORMATION structure
			)
		{
			printf("CreateProcess failed (%d).\n", GetLastError());
			//return -1;
		}

		// add the process to the process vectors
		processHandleVector.push_back(piMap.hProcess);
		processThreadVector.push_back(piMap.hThread);
	}

	// wait for all of the processes in the vector to finish
	for (int i = 0; i < processHandleVector.size(); i++) {

		// Wait until all child processes exit.
		//WaitForMultipleObjects(RMAX, processesHandleMap, TRUE, INFINITE);
		WaitForSingleObject(processHandleVector[i], INFINITE);

		// Close process and thread handles. 
		CloseHandle(processHandleVector[i]);
		CloseHandle(processThreadVector[i]);
	}

	// delete the temporary files.
	for (int i = 1; i <= RMAX; i++)
	{
		// add the correct extension to the files based on their process number.
		string newInputFileName = inputFile.substr(0, inputFileNameSize - 4) + std::to_string(i) + inputFile.substr(inputFileNameSize - 4);

		// convert strings to const char* for remove method.
		const char* inFileChar = newInputFileName.c_str();

		//Open file and then close to clear the contents
		ofStreamObj.open(newInputFileName);
		ofStreamObj.close();
		remove(inFileChar);
	}
}

// Get File Name from a Path with or without extension
void Workflow::separateOutputPath(const string userInputFile, const string& fileType)
{
	try {
		// Create a Path object from File Path
		boost::filesystem::path pathObj(userInputFile);

		// set the path of the user submitted file
		boost::filesystem::path p(userInputFile);

		//get the parent path
		boost::filesystem::path dir = p.parent_path();

		if (fileType == "output")
		{
			//set data member as a string to remember the path
			setOutputFileDirectoryLocation(dir.string());
		}
		else
		{
			//set data member as a string to remember the path
			setIntermediateFileDirectoryLocation(dir.string());
		}
	}
	// catch any exception here
	catch (...)
	{
		BOOST_LOG_TRIVIAL(fatal) << "Error in Workflow class separateOutputPath function. Program will shutdown";
		throw;
	}
}

//Verify if the input directory given is valid
//Keep asking until valid file is given
void Workflow::checkFilesValid(string& inputFile, string& intermediateFile, string& outputFile)
{
	//----------------Verify if file directories are valid--------------
	while (validInputFile == false)
	{
		//try block to attempt to the input file directory
		try {
			setInputFileLocation(inputFile);
		}
		//If not valid then throw exception
		catch (const NotValidFile& notValidFileException) {
			cout << "\nException occurred: "
				<< notValidFileException.what() << endl;
		}
		//Ask user for another input file directory
		if (validInputFile == false)
		{
			cout << "\nPlease enter a valid input file directory.\n"
				<< "Input File Directory: ";
			std::getline(cin, inputFile);
		}
	}

	//Get path to intermediate output directory
	//separateOutputPath(intermediateFile, "intermediate");
	while (validIntermediateFile == false)
	{
		//try block to attempt to the input file directory
		try {

			setIntermediateFileLocation(intermediateFile);
		}
		//If not valid then throw exception
		catch (const NotValidFile& notValidFileException) {
			cout << "\nException occurred: "
				<< notValidFileException.what() << endl;
		}
		//Ask user for another input file directory
		if (validIntermediateFile == false)
		{
			cout << "\nPlease enter a valid temporary intermediate file directory.\n"
				<< "Intermediate File Directory: ";
			std::getline(cin, intermediateFile);
		}
	}

	//Get path to final output directory
	//separateOutputPath(outputFile, "output");
	while (validOutputFile == false)
	{
		//try block to attempt to the input file directory
		try {
			setOutputFileLocation(outputFile);
		}
		//If not valid then throw exception
		catch (const NotValidFile& notValidFileException) {
			cout << "\nException occurred: "
				<< notValidFileException.what() << endl;
		}
		//Ask user for another input file directory
		if (validOutputFile == false)
		{
			cout << "\nPlease enter a valid final output file directory.\n"
				<< "Output File Directory: ";
			std::getline(cin, outputFile);
		}
	}
}

//Check if the input file is valid
bool Workflow::checkIfFIle(const string& userInputFile)
{
	// Create a Path object from given path string
	boost::filesystem::path pathObj(userInputFile);
	// Check if path exists and is of a regular file
	if (!boost::filesystem::exists(pathObj) && (!boost::filesystem::is_regular_file(pathObj) || !boost::filesystem::is_directory(pathObj)))
	{
		BOOST_LOG_TRIVIAL(warning) << "Input Directory does not exist.";
		return true;
	}
	return false;
}

//Check if the output file is valid
bool Workflow::checkOfFIle(const string& userInputFile, const string& fileType)
{
	// Create a Path object from given path string
	boost::filesystem::path pathObj(userInputFile);
	// Check if path exists
	if (boost::filesystem::exists(pathObj))
	{
		return false;
	}
	else
	{
		//Check to see if the last file is a .txt 
		if (userInputFile.substr(userInputFile.find_last_of(".") + 1) == "txt")
		{
			//Separate if it does from file
			separateOutputPath(userInputFile, fileType);

			if (fileType == "output")
			{
				if (!(getOutputFileDirectoryLocation() == ""))
				{
					boost::filesystem::create_directories(getOutputFileDirectoryLocation());
				}

			}
			else
			{
				if (!(getIntermediateFileDirectoryLocation() == ""))
				{
					cout << getIntermediateFileDirectoryLocation();
					boost::filesystem::create_directories(getIntermediateFileDirectoryLocation());
				}
			}
			return false;
		}
		else
		{
			BOOST_LOG_TRIVIAL(warning) << "Program must write to a '.txt' file location.";
			return true;
		}
	}
}

string Workflow::updateString(string origional, string toAdd)
{
	int strLength = origional.size();
	return origional.substr(0, strLength - 4) + toAdd + origional.substr(strLength - 4);
}

//**********Setters**********
// Set the input file location.
void Workflow::setInputFileLocation(const string& userInputFile)
{
	//Verify input call to checkIfFile()
	if (checkIfFIle(userInputFile))
	{
		//If return true then throw exception
		throw NotValidFile{}; //terminate function

	}
	//If false then insert into inputFileLocation 
	else
	{
		inputFileLocation = userInputFile;
		//update validInputFile
		validInputFile = true;
	}
}

// Set the intermediate file location.
void Workflow::setIntermediateFileLocation(const string& userIntermediateFile)
{
	string intermediateFileToCheck = userIntermediateFile;

	//Verify input call to checkIfFile()
	if (checkOfFIle(intermediateFileToCheck, "intermediate"))
	{
		//If return true then throw exception
		throw NotValidFile{}; //terminate function

	}
	//If false then insert into inputFileLocation 
	else
	{
		// Create a Path object from given path string
		boost::filesystem::path pathObj(intermediateFileToCheck);
		//Check if using a file and not a directory
		if (intermediateFileToCheck.substr(intermediateFileToCheck.find_last_of(".") + 1) != "txt")
		{

			intermediateFileToCheck = intermediateFileToCheck + "\\Intermediate.txt";
			BOOST_LOG_TRIVIAL(warning) << "Directory must include a '.txt' file to write to at the end. Will write a Intermediate.txt in same directory. ";

		}

		//Separate if it does from file
		separateOutputPath(intermediateFileToCheck, "intermediate");

		//intermediateFileLocation = userIntermediateFile;
		intermediateFileLocation = intermediateFileToCheck;
		//update validInputFile
		validIntermediateFile = true;
	}
}

// Set the output file location.
void Workflow::setOutputFileLocation(const string& userOutputFile)
{
	string outputFileToCheck = userOutputFile;

	//Verify input call to checkIfFile()
	if (checkOfFIle(outputFileToCheck, "output"))
	{

		//If return true then throw exception
		throw NotValidFile{}; //terminate function

	}
	//If false then insert into inputFileLocation 
	else
	{

		// Create a Path object from given path string
		boost::filesystem::path pathObj(outputFileToCheck);
		//Check if using a file and not a directory
		if (outputFileToCheck.substr(outputFileToCheck.find_last_of(".") + 1) != "txt")
		{
			outputFileToCheck = outputFileToCheck + "\\Output.txt";
			BOOST_LOG_TRIVIAL(warning) << "Directory must include a '.txt' file to write to at the end. Will write a Output.txt in same directory. ";


		}
		//Separate if it does from file
		separateOutputPath(outputFileToCheck, "output");
		outputFileLocation = outputFileToCheck;
		//update validInputFile
		validOutputFile = true;

	}
}

void Workflow::setIntermediateFileDirectoryLocation(const string& userOutputFile) { intermediateFileDirectoryLocation = userOutputFile; }

// Set the output file directory location.
void Workflow::setOutputFileDirectoryLocation(const string& userOutputFile) { outputFileDirectoryLocation = userOutputFile; }


//**********Getters**********

// Get the input file location.
const string Workflow::getInputFileLocation(void) { return inputFileLocation; }

// Get the intermediate file location.
const string Workflow::getIntermediateFileLocation(void) { return intermediateFileLocation; }

// Get the output file location.
const string Workflow::getOutputFileLocation(void) { return outputFileLocation; }

const string Workflow::getIntermediateFileDirectoryLocation(void) { return intermediateFileDirectoryLocation; }

// Get the output file directory location.
const string Workflow::getOutputFileDirectoryLocation(void) { return outputFileDirectoryLocation; }

// Get the bool if input file is valid. 
const bool  Workflow::getValidInputFile(void) { return validInputFile; }

// Get the bool if intermediate file is valid. 
const bool  Workflow::getValidIntermediateFile(void) { return validIntermediateFile; }

// Get the bool if output file is valid. 
const bool  Workflow::getValidOutputFile(void) { return validOutputFile; }

// Get the number of files found in the input directory.
void Workflow::getNumberOfFilesFound(string inputFile) {
	
	//Create an object of the FileManagement class
	FileManagement FileStreamSystem;

	if (boost::filesystem::is_directory(inputFile))
	{
		// insert all of the files in the directory inside a vector of strings.
		vector<string> listOfFiles = FileStreamSystem.getAllFilesInDir(inputFile);

		for (auto str : listOfFiles)
		{
			numberOfFilesFound = numberOfFilesFound + 1;
		}
	}

	else {
		numberOfFilesFound = 1;
	}
}
