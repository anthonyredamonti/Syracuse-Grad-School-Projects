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
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
//
// int argc = number of arguments + 1
// char **argv is the argument passed to the command line(char array).
// The argument starts at the 2nd element in the array (argv[1]).
// We will take the bitstring as a command line argument.
//
int main(int argc, char *argv[]) {

   // Make sure we have at least one argument.
   
   if (argc < 2) {
      fprintf(stderr, "No argument found\n");
      //return -1;
   }
   
   int fd[3][2];
   int i;
   // creates three pipes
   for(i = 0; i < 3; i++){
      if(pipe(fd[i]) == -1){
         printf("fd[%d] failed to pipe\n", i);
         return -2;
      }
   }

   int pid1 = fork();
   if(pid1 < 0){
      printf("pid1 did not fork (process failed to create)\n");
      return -3;
   }

   // child process 1
   if(pid1 == 0){
      printf("child 1 entered\n");
      close(fd[0][1]);
      close(fd[2][0]);
      close(fd[2][1]);
      close(fd[1][0]);
      int x;
      if(read(fd[0][0], &x, sizeof(int)) < 0){
         printf("unable to read fd[0][0]\n");
         return -4;
      }
      x += 5;
      if(write(fd[1][1], &x, sizeof(int)) < 0){
         printf("unable to write to fd[1][1]\n");
         return -5;
      }

      close(fd[0][0]);
      close(fd[1][1]);
      printf("leaving child 1 process\n");

      return 0;
   }

   int pid2 = fork();
   if(pid2 < 0){
      return -6;
   }

   // child process 2
   if(pid2 == 0){
      printf("child 2 entered\n");
      close(fd[1][1]);
      close(fd[0][0]);
      close(fd[0][1]);
      close(fd[2][0]);
      int x;
      if(read(fd[1][0], &x, sizeof(int)) < 0){
         printf("unable to read fd[1][0]\n");
         return -7;
      }
      x += 5;
      if(write(fd[2][1], &x, sizeof(int)) < 0){
         printf("unable to write to fd[2][1]\n");
         return -8;
      }

      close(fd[1][0]);
      close(fd[2][1]);
      printf("leaving child 2 process\n");
      return 0;
   }

   // parent process
   printf("parent process\n");
   close(fd[2][1]);
   close(fd[1][0]);
   close(fd[1][1]);
   close(fd[0][0]);
   int x;
   printf("Input a number: ");
   scanf("%d", &x);
   if(write(fd[0][1], &x, sizeof(int)) < 0){
      return -9;
   }
   if(read(fd[2][0], &x, sizeof(int)) < 0){
      return -10;
   }
   printf("Result is: %d\n", x);
   close(fd[0][1]);
   close(fd[2][0]);

   return 0;
}
