// Circle.cpp

#include "Circle.h"
#include <iostream>
#include <iomanip>

#define pi 3.14159

using std::cout;
using std::cin;
using std::endl;

Circle::Circle() {
}

Circle::Circle(double input_radius) {
	SetRadius(input_radius);
}

void Circle::SetRadius(double input_radius){
	radius = input_radius;
}

void Circle::GetDiameter() {
	cout << "Diameter of circle is: " << (2 * radius) << endl;
}

void Circle::GetArea() {
	cout << "Area of circle is: " << (pi * radius * radius) << endl;
}

void Circle::GetCircumference() {
	cout << "Circumference of circle is: " << (2 * pi * radius) << endl;
}
