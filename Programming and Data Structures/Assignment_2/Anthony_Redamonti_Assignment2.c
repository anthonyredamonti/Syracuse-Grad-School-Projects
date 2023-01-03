// Anthony Redamonti
// 7-15-2020
// This is Assignment 2 for Week 2 written in C.

#include <stdio.h>

// Note that the number 0 is a multiple of every number and is considered even.

// function and variable declarations
int Power_Using_For_Loop(int x, int y); 
int Power_Using_While_Loop(int x, int y);
void Parity_And_MultipleOf5_Checker(int num);
int i;

// Use a "for" loop to calculate x^y
int Power_Using_For_Loop(int x, int y){
   int result = 1;
   for(i = 0; i < y; i++){
      result *= x;
   }
   return(result);
}

// Use a "while" loop to calculate x^y
int Power_Using_While_Loop(int x, int y){
   int result = 1;
   while(y>0){
      result *= x;
      y--;
   }
   return(result);
}

// Use "if" and "else" statements to check parity and afterwards use an "if" statement to check if it is a multiple of 5.
void Parity_And_MultipleOf5_Checker(int num){
   if(num%2 == 0){
      printf("This is even!\n");
   }
   else{
      printf("This is odd!\n");
   }
   if(num%5 == 0){
      printf("This number is a multiple of 5!\n");
   }
}

// Use "for" loops to test a range of numbers for each function.
int main() {
   int test;

   // Test numbers 0-4 in the Power_Using_For_Loop function. Should output 1,2,4,8,16
   for (i = 0; i < 5; i++){
      test = Power_Using_For_Loop(2,i);
      printf("For loop used to calculate 2^%d. Answer is: %d\n", i, test);
   }

   // Test numbers 0-4 in the Power_Using_While_Loop function. Should output 1,2,4,8,16
   for (i = 0; i < 5; i++){
      test = Power_Using_While_Loop(2,i);
      printf("While loop used to calculate 2^%d. Answer is: %d\n", i, test);
   }

   // Test numbers 0-19 in the Parity_And_MultipleOf5_Checker function.
   for(i = 0; i < 20; i++){
      printf("Parity and Multiple Of 5 Checker(%d)\n", i);
      Parity_And_MultipleOf5_Checker(i);
   }
   return 0;
}

/*

To create a new project in Visual Studio Code, create a new project folder and insert an empty source file in the folder.
Then open the folder in Visual Studio Code. After writing the source file, click Run > Start Debugging (or press F5).
Visual Studio will then do the following automatically: 

(1) "Task - gcc.exe build active file" to create "Anthony_Redamonti_Assignment2.exe" file.
(2) "Run cppdbg" debugger type defined by the Microsoft C/C++ extension on "Anthony_Redamonti_Assignment2.exe".
(3) Display the results of the debugger in Windows PowerShell in the terminal.

The terminal in Visual Studio Code reads the following:

PS C:\Users\aredamonti\projects\Assignment_2>  & 'c:\Users\aredamonti\.vscode\extensions\ms-vscode.cpptools-0.28.3\debugAdapters\bin\WindowsDebugLauncher.exe' '--stdin=Microsoft-MIEngine-In-h2hperqn.3wv' '--stdout=Microsoft-MIEngine-Out-c2rr2c5k.qs5' '--stderr=Microsoft-MIEngine-Error-c2fgw2ua.gov' '--pid=Microsoft-MIEngine-Pid-qofeqzel.fe5' '--dbgExe=C:\Program Files (x86)\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\gdb.exe' '--interpreter=mi'
For loop used to calculate 2^0. Answer is: 1
For loop used to calculate 2^1. Answer is: 2
For loop used to calculate 2^2. Answer is: 4
For loop used to calculate 2^3. Answer is: 8
For loop used to calculate 2^4. Answer is: 16
While loop used to calculate 2^0. Answer is: 1
While loop used to calculate 2^1. Answer is: 2
While loop used to calculate 2^2. Answer is: 4
While loop used to calculate 2^3. Answer is: 8
While loop used to calculate 2^4. Answer is: 16
Parity and Multiple Of 5 Checker(0)
This is even!
This number is a multiple of 5!
Parity and Multiple Of 5 Checker(1)
This is odd!
Parity and Multiple Of 5 Checker(2)
This is even!
Parity and Multiple Of 5 Checker(3)
This is odd!
Parity and Multiple Of 5 Checker(4)
This is even!
Parity and Multiple Of 5 Checker(5)
This is odd!
This number is a multiple of 5!
Parity and Multiple Of 5 Checker(6)
This is even!
Parity and Multiple Of 5 Checker(7)
This is odd!
Parity and Multiple Of 5 Checker(8)
This is even!
Parity and Multiple Of 5 Checker(9)
This is odd!
Parity and Multiple Of 5 Checker(10)
This is even!
This number is a multiple of 5!
Parity and Multiple Of 5 Checker(11)
This is odd!
Parity and Multiple Of 5 Checker(12)
This is even!
Parity and Multiple Of 5 Checker(13)
This is odd!
Parity and Multiple Of 5 Checker(14)
This is even!
Parity and Multiple Of 5 Checker(15)
This is odd!
This number is a multiple of 5!
Parity and Multiple Of 5 Checker(16)
This is even!
Parity and Multiple Of 5 Checker(17)
This is odd!
Parity and Multiple Of 5 Checker(18)
This is even!
Parity and Multiple Of 5 Checker(19)
This is odd!

*/
