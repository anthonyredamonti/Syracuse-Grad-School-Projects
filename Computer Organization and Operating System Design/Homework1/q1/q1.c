// Anthony Redamonti
// 10-9-2020
//
// Please use the gcc compiler to complile this file.
// After navigating to the correct project folder, the following commands were
// performed via the terminal on a Linux (Ubuntu) operating system to compile
// and run the program:
//
// gcc ./q1.c -o q1
// ./q1 
//
// Unix platform is supported. No Windows specific libraries or functions were used.
//
// The following is my solution to question 1 from homework 1.
// It asks for the radius of a circle. 
// It then calculates and prints the diameter, circumference and area of the circle.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

int main() {
   
   float radius;
   printf("Please enter a radius: ");
   scanf("%f", &radius);
   printf("\n");

   float diameter = 2*radius;
   printf("Diameter: %.2f\n", diameter);

   float circumference = (2*PI*radius);
   printf("Circumference: %.2f\n", circumference);

   float radius_pow2 = radius*radius;
   float area = radius_pow2*PI;
   printf("Area: %.2f\n", area);

   return 0;
}
