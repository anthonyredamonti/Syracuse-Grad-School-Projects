# MapReduce_Project_Phase-1
# Requirements

  * Visual Studio 2022
  * Boost 1.79.0 or newer

## Install Boost

For help on installing Boost the following sources were used. 

-[Walkthrough Video](https://www.youtube.com/watch?v=5afpq2TkOHc&t=451s)
<br>
-[Online Guide](https://levelup.gitconnected.com/the-definite-guide-on-compiling-and-linking-boost-c-libraries-for-visual-studio-projects-c79464d7282d)


## Build

Clone the repository and its submodules.

To be able to use the GitHub API, you'll need to:

- [Register a new developer application](https://github.com/settings/developers) in your profile
- Create an environment variable `GitHubVS_ClientID` with your `Client ID`
- Create an environment variable `GitHubVS_ClientSecret` with your `Client Secret`

Execute `build.cmd`

If not using the Github API, You'll need to:

-Click on the green code drop down
<br>
-Select the 'Download ZIP' option
<br>
-Move downloaded file to preferred location.
<br>
-Open Visual Studio
<br>
-Select 'Open Project'
<br>
-Select the 'MapReduce.sln'
<br>

## Logs
Logs can be viewed at the following location:

-logResult.log
-File will be located in the project folder.

## Boost Unit Testing
Program has test.cpp file for BOOST unit testing. 
<br>
If BOOST Unit testing is not active on machine, review guide below on set-up.
<br>
-[Online Guide](https://docs.microsoft.com/en-us/visualstudio/test/how-to-use-boost-test-for-cpp?view=vs-2022)


# Sample Execution & Output

Program will ask for directory locations for an input file, intermediate file, and output file. 
<br>
Note: If a file location is inside the project folder, only the file name is needed. 
<br>
Note: If no intermediate.txt or output.txt is given, then a default .txt file will be given. 

```
Input File Directory: c:\...\chosen_file.txt
Intermediate File Directory: c:\...\chosen_file.txt 
Output File Directory: chosen_file.txt

```

Messages that will be shown during program
```


Sorting has begun. Words are being discovered.

The number of words found in the intermediate file: (# words in input file)

These words are now being searched for duplicate entries.

Sorting has finished.

Workflow is now parsing the intermediate file and calling the Reduce class on each entry.

Success. Program will now terminate.

Time to complete program: (seconds took to complete program)

```

output *simliar* to (if using the shakespeare folder)

Intermediate File
```
("hawking", [1, 1, 1]), ("gladly", [1, 1, 1, 1, 1]), ("appliance", [1, 1]), ("ambitions", [1]), ("publisher", [1]), ("distill", [1, 1, 1]), ("hindering", [1]), 
```

Output File

```
("act"), 128
("his"), 2464
("calendar"), 4
("endeavours"), 4
("wound"), 24
("you"), 7175
("the"), 11273
```
'SUCCESS.txt' will also be produced at output file location.
