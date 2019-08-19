#include "rational.h"

/*
Rational::~Rational()
{
}*/

std::ostream& operator<< (std::ostream & os, Rational & r) 
{
	// Vars used to help center the numerator & denominator based on their length
	size_t line_len, spacing;

	// Get pointers to numerator and denominator strings
	std::string const *n, *d;
	n = &(r.numerator.getStr());
	d = &(r.denominator.getStr());

	// New line for better formatting
	os << std::endl;

	// Depending on whether the numerator or denominator is a longer string, attempt to center the output of the rational; had trouble aligning perfectly
	if (d->length() >= n->length())
	{
		line_len = d->length();
		// Set spacing equal to half the difference between the length of the denominator and numerator
		spacing = line_len - n->length();
		spacing = spacing % 2 == 0 ? spacing / 2 : spacing / 2 + 1;
		// Output "spacing" # of spaces before outputting the numerator
		for (size_t i = 0; i < spacing; ++i) os << " ";
		os << r.numerator << std::endl;
		// Print the division line and then the denominator
		for (size_t i = 0; i < line_len; ++i) os << "-";
		os << std::endl << r.denominator << std::endl;
	}

	else
	{
		// Similar process as above, only inverted
		line_len = n->length();
		spacing = line_len - d->length();
		spacing = spacing % 2 == 0 ? spacing / 2 : spacing / 2 + 1;
		std::cout << r.numerator << std::endl;
		for (size_t i = 0; i < line_len; ++i) os << "-";
		os << std::endl;
		for (size_t i = 0; i < spacing; ++i) os << " ";
		os << r.denominator << std::endl;
	}

	return os;
}

double Rational::operator() (double x) const
{
	try 
	{
		// If the denominator evaluates to zero, throw an exception; else, return the evluated rational
		if (denominator(x) == 0) throw DivisionByZeroPolynomialException();
		else return (numerator(x) / denominator(x));
	}
	catch (DivisionByZeroPolynomialException & dbzpe) { throw; } // re-throw to calling function
}

