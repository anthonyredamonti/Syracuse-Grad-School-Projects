// Anthony Redamonti
// 10-9-2020
//
// Please use the gcc compiler to complile this file.
// After navigating to the correct project folder, the following commands were
// performed via the terminal on a Linux (Ubuntu) operating system to compile
// and run the program:
//
// gcc ./q5.c -o q5
// ./q5 
//
// Unix platform is supported. No Windows specific libraries or functions were used.
//
// The following is my solution to question 5 from homework 1.
// The program is a calculator created in accordance with the problem statement.
// To end the program, hit the Enter key on the keyboard.
//

#include <stdlib.h>
#include <stdio.h>

// The is_0_to_9 function returns 1 if the character is a digit from 0-9 or is a negative sign '-'.
// The function returns 0 otherwise.
int is_0_to_9(char input){
      char array[11] = {'0','1','2','3','4','5','6','7','8','9','-'}; // '-' for negative numbers
      for(int i = 0; i < 11; i++){
            if(array[i]==input){
                  return 1;
            }
      }
      return 0;
}

// The is_operator function returns 1 if the character is in the array of mathematical operators.
// The function returns 0 otherwise.
int is_operator(char input){
      char array[5] = {'+','-','*','/','%'};
      for(int i = 0; i < 5; i++){
            if(array[i]==input){
                  return 1;
            }
      }
      return 0;
}

int main() { 

   char operator;
   int int1, int2;
   
   while(1 == 1){

      char input[100];
      fgets(input, 100, stdin); // get the user input. Limit user input to 100 characters.
      
      // first check if the user hit to Enter key. If so, exit the loop and end the program.
      if (input[0] == '\n') 
      {
          break;
      }

      int index = 0; // create a variable for indexing through the character array

      // find the start of the first number
      while(is_0_to_9(input[index])!=1){
            index += 1;
            if(index == 100){
                  break;
            }
      }

      // put the first number into the temp1 array
      char temp1[25];
      int temp1_index = 0;
      while(is_0_to_9(input[index])==1){
            // accept the first negative sign but do not accept any others
            if((temp1_index!=0)&&(input[index]=='-')){
                  break;
            }
            temp1[temp1_index] = input[index];
            temp1_index += 1;
            index += 1;
            if((index == 100)||(temp1_index==25)){
                  break;
            }
      }

      temp1[temp1_index] = '\0'; // insert the null character
      int1 = atoi(temp1);        // convert the array to an integer

      // find the index of the operator
      while(is_operator(input[index])!=1){
            index += 1;
            if(index == 100){
                  break;
            }
      }

      operator = input[index]; // the next character must be the operator
      index += 1;

      // find the index of the second number
      while(is_0_to_9(input[index])!=1){
            index += 1;
            if(index == 100){
                  break;
            }
      }

      // put the second number into the temp2 array
      char temp2[25];
      int temp2_index = 0;
      while(is_0_to_9(input[index])==1){
            temp2[temp2_index] = input[index];
            temp2_index += 1;
            index += 1;
            if((index == 100)||(temp2_index==25)){
                  break;
            }
      }

      temp2[temp2_index] = '\0'; // insert the null character
      int2 = atoi(temp2);        // convert the array to an integer

      // use a switch case statement to perform the correct math function
      switch(operator)
      {
         case '+':
               printf("%d\n", int1+int2);
               break;
         case '-':
               printf("%d\n", int1-int2);
               break;
         case '*':
               printf("%d\n", int1*int2);
               break;
         case '/':
               if(int2 == 0){
                  //printf("Do not divide by zero!\n");
                  break;
               }
               printf("%d\n", int1/int2);
               break;
         case '%':
               printf("%d\n", int1%int2);
               break;
         default:
               //printf("Error: Bad operator.\n");
               break;
      }
   }
   return 0;
}