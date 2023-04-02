#pragma once
#include <stdexcept>

class DivideByZeroException : public std::runtime_error {
public:
	DivideByZeroException()	: 
		std::runtime_error("attempt to divide by zero") {}
};