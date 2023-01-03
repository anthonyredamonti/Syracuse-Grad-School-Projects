// Anthony Redamonti
// 10-9-2020
//
// Please use the gcc compiler to complile this file.
// After navigating to the correct project folder, the following commands were
// performed via the terminal on a Linux (Ubuntu) operating system to compile
// and run the program:
//
// gcc ./q2.c -o q2
// ./q2 5
//
// output:
// +
// **
// +++
// ****
// +++++
//
// Unix platform is supported. No Windows specific libraries or functions were used.
//
// The following is my solution to question 2 from homework 1.
// The user will supply a command line argument in the form of an integer.
// The program will behave as described in the problem statement of the homework
// by printing out a specific pattern of '+' and '*' characters.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void flip_flop(int number, int* style){
   if(*style == 0){
      for(int i = 0; i < number; i++){
         printf("+");
      }
      *style = 1;
   }
   else{
      for(int i = 0; i < number; i++){
         printf("*");
      }
      *style = 0;
   }
   printf("\n");   
}

int main(int argc, char *argv[]) { 
   if(argc == 2){
      char* a = argv[1];
      int N = atoi(a); // convert the string argument to an integer
      int style = 0;
      int* pntr = &style;
      for(int i = 1; i <= N; i++){
         flip_flop(i, pntr);
      }
   }
   else if(argc > 2){
      //printf("Please only enter one integer as an argument.\n");
   }
   else{
      //printf("Please enter at least one integer as an argument.\n");
   }
   return 0;
}
