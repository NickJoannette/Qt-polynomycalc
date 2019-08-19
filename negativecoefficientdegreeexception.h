#ifndef NEGATIVECOEFFICIENTDEGREEEXCEPTION_H
#define NEGATIVECOEFFICIENTDEGREEEXCEPTION_H

#include <exception>
#include <string>

class NegativeCoefficientDegreeException : public std::exception
{
public:
	// Override what() function to return the message
	const char * what() const noexcept { return message.c_str(); }

private:
	std::string message = "The degree of the index 'n' was negative.";

};

#endif