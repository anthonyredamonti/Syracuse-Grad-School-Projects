# MapReduce_Project_Phase-4
# Requirements

  * Visual Studio 2022
  * Boost 1.79.0 or newer

## Install Boost

For help on installing Boost the following sources were used. 

-[Walkthrough Video](https://www.youtube.com/watch?v=5afpq2TkOHc&t=451s)
<br>
-[Online Guide](https://levelup.gitconnected.com/the-definite-guide-on-compiling-and-linking-boost-c-libraries-for-visual-studio-projects-c79464d7282d)

## Using DLL
This program depends on the use of DLL's MapLibrary and ReduceLibrary. Please view Creating_DLLs_in_VS2017.docx on how to create and implement DLL's. 

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

## Set Up
Hard coding locations
<br>
### Map Reduce File
In Executive.cpp input the locations of the input file, intermediate file that will hold temp files and an output file location.
![executive lines](https://github.com/ColtonWilson/MapReduce_Project_Phase-4/blob/main/images/executive01.png)
In the Workflow.cpp file, set the location of the ReduceProcess.exe which can be found in the ReduceProcess file. 
![Reduce Process](https://github.com/ColtonWilson/MapReduce_Project_Phase-4/blob/main/images/workflow01.png)
In the Workflow.cpp file, set the location of the MapProcess.exe which can be found in the MapProcess file. 
![Map Process](https://github.com/ColtonWilson/MapReduce_Project_Phase-4/blob/main/images/workflow02.png)

### Map Process File
Set the location for the Map DLL which is located in the Map Library
![Map Process to Map Library](https://github.com/ColtonWilson/MapReduce_Project_Phase-4/blob/main/images/Mapprocess01.png)
### Reduce Process File
Set the location for the Reduce DLL which is located in the Reduce Library
![Reduce Process to Reduce Library](https://github.com/ColtonWilson/MapReduce_Project_Phase-4/blob/main/images/Reduceprocess01.png)

### Stub1
In the main.cpp set up the location of the MapReduce.exe which should be in the Map Reduce file
![Stub one to Map Reduce](https://github.com/ColtonWilson/MapReduce_Project_Phase-4/blob/main/images/stubone01.png)

### Stub2
In the main.cpp set up the location of the MapReduce.exe which should be in the Map Reduce file
![Stub two to Map Reduce](https://github.com/ColtonWilson/MapReduce_Project_Phase-4/blob/main/images/stubtwo01.png)

### Controller
In the main.cpp set up the location of the Stub1.exe which should be in the Stub1 file
![Controller to Stub one](https://github.com/ColtonWilson/MapReduce_Project_Phase-4/blob/main/images/controller01.png)

Will do the same for stub2 location
![Controller to Stub two](https://github.com/ColtonWilson/MapReduce_Project_Phase-4/blob/main/images/controller02.png)

## Sample Execution & Output

Program will no longer ask for directory locations for an input file, intermediate file, and output file since they are not hardcoded to the location. 
<br>
Note: If a file location is inside the project folder, only the file name is needed. 
<br>
Note: If no intermediate.txt or output.txt is given, then a default .txt file will be given. 

```
Input File Directory: c:\...\chosen_file.txt
Intermediate File Directory: c:\...\chosen_file.txt 
Output File Directory: chosen_file.txt

```
### Important to start
Go through each file solution and build each program to get the .exe made.
<br>
In order to start the program. Start running stub1 and stub 2 and there should be blank screens. As shown. Note: An alert might pop on screen, accept access. 
![stub1 and stub2 running](https://github.com/ColtonWilson/MapReduce_Project_Phase-4/blob/main/images/running01.png)
<br>
Once running, start the controller and program will begin to run. Stub one will handle the mapping of the files while Stub two will handle the reducing. 
<br>
Stub two will be blank until the reducing starts so only the Stub one and Contoller will show updates. 
<br>
In Stub one the process number and address of the socket can be seen as well as when that heartbeat is complete
![stub1 running](https://github.com/ColtonWilson/MapReduce_Project_Phase-4/blob/main/images/running02.png)
<br>
Controller will onginally show two client sockets that can not be created, these are the reduce sockets that do not get created until later. To know the Map process is working a heartbeat message will be sent to the controller from the Map process as seen below. 
![controller running part one](https://github.com/ColtonWilson/MapReduce_Project_Phase-4/blob/main/images/running03.png)
<br>
Once stub 1 is complete the stub 2 will start and begin the Reduce Process. It will show the process and address again as well as amount of words in each file and total final count of words without duplicates.
![stub2 running](https://github.com/ColtonWilson/MapReduce_Project_Phase-4/blob/main/images/running04.png)
<br>
The controller can be looked at again to see the heartbeat for the Reduce Process. Note: Stub two will also sort the words and so it will start before the controller recieves a heartbeat becuase the heartbeat is located in the Reduce Process. 
![stub2 running](https://github.com/ColtonWilson/MapReduce_Project_Phase-4/blob/main/images/running05.png)
<br>


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
