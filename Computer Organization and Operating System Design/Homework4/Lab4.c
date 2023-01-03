// Anthony Redamonti
// 11-15-2020
//
// Please use the gcc compiler to complile this file.
// After navigating to the correct project folder, the following commands were
// performed via the terminal on a Linux (Ubuntu) operating system to compile
// and run the program:
//
// gcc ./Lab4.c -o Lab4
// ./Lab4
//
// Unix platform is supported. No Windows specific libraries or functions were used.
//
// The following is my solution for Lab 4.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <unistd.h>
//#include <sys/wait.h>
//
// int argc = number of arguments + 1
// char **argv is the argument passed to the command line(char array).
// The argument starts at the 2nd element in the array (argv[1]).
// We will take the bitstring as a command line argument.
//
int main(int argc, char **argv) {

   // Make sure we have at least one argument.
   
   if (argc < 2) {
      fprintf(stderr, "No argument found\n");
      //return -1;
   }
   
   // Get a pointer to the argument.
   char *instruction = argv[1];
   int id1 = fork();
   int id2 = fork();

   // id1 = x, id2 = y == process A
   // id1 = 0, id2 = y == process B
   // id1 = x, id2 = 0 == process 
   // if id1 == 0, the child process is being run
   if(id1 == 0){
      if(id2 == 0){
         printf("Process 0, 0");
      }
      else{
         printf("Process 0, 1");
      }
   }
   else{
      if(id2 == 0){
         printf("Process 1, 0");
      }
      else{
         printf("Process 1, 1");
      }
   }

   return 0;
}
