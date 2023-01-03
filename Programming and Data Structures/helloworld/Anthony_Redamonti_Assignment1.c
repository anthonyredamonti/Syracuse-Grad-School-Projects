// This is my first program in C
#include <stdio.h>

struct User
{
   /* data */
   char first_and_last_name[20];
   char street_name[20]; // 2nd Avenue
   char street_number[10]; // could be 1252B
   char zip_code[20]; // could be 33701-4313 for example
   char state_province[20];
   char country[20];
   char city[20];
};

int main() {
   
   struct User new_user = {"John Doe", "Main St", "123B", "01232-4132", "Massachusetts", "United States", "Boston"};
   
   return 0;
}
