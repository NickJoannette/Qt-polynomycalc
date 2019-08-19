#ifndef DIVISIONBYZEROPOLYNOMIALEXCEPTION_H
#define DIVISIONBYZEROPOLYNOMIALEXCEPTION_H

#include <exception>
#include <string>

class DivisionByZeroPolynomialException : public std::exception
{
public:
	// Override what() function to return the message
	const char * what() const noexcept { return message.c_str(); }

private:
	std::string message = "The denominator polynomial of the rational evaluated to zero.";

};

#endif