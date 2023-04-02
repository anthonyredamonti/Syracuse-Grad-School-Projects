#pragma once
#include <stdexcept>

class NumberTooLargeException : public std::runtime_error {
public:
	NumberTooLargeException() : 
		std::runtime_error("number is too large") {}
};
