#ifndef PARSINGUTILITIES_H
#define PARSINGUTILITIES_H

#include <string>
#include <iostream>
#include "unparseablepolynomialexception.h"

// These structs are used for returning two pieces of information simultaneously from the validDegree, validCoefficient, and validateTermForm functions during parsing
// They are intended to act as an extra fail-safe during parsing
struct formatted_term
{
	double coefficient;
	unsigned int degree;
};

struct formatted_coefficient
{
	bool valid;
	double value;
};

struct formatted_degree
{
	bool valid;
	unsigned int value;
};

//Checks if a character is a digit
template <typename T>
const bool isDigit(T & c)
{
	return !(c != '1' && c != '2' &&
		c != '3' && c != '4' &&
		c != '5' && c != '6' &&
		c != '7' && c != '8' &&
		c != '9' && c != '0');
}

template <typename T>
const bool isSign(T & c)
{
	return (c == '+' || c == '-');
}

template <typename T>
void printElements(const T & start, const T & end)
{
	for (T it = start; it < end; ++it)
		std::cout << *it << std::endl;
}

// Utility functions for validating the formatting of the inputted polynomial string during the parsing process
void removeCharFromString(std::string & s, char c);
const formatted_term validateTermForm(std::string & s);
const formatted_degree validDegree(std::string s);
const formatted_coefficient validCoefficient(std::string s);


#endif
