// Circle.h

#pragma once
#include<string>

class Circle 
{
public:
	explicit Circle();
	explicit Circle(double input_radius);
	void GetDiameter();
	void GetCircumference();
	void GetArea();
	void SetRadius(double input_radius);
private:
	double radius;
};