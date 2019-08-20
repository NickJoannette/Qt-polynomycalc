#ifndef UNPARSEABLEPOLYNOMIALEXCEPTION_H
#define UNPARSEABLEPOLYNOMIALEXCEPTION_H

#include <exception>
#include <string>

class UnparseablePolynomialException : public std::exception
{
public:
	// Override what() function to return the message
	const char * what() const noexcept { return message.c_str(); }

private:
    std::string message = "The polynomial was unparseable.";

};

#endif
