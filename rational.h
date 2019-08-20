#ifndef RATIONAL_H
#define RATIONAL_H

#include <string>
#include "polynomial.h"
#include "divisionbyzeropolynomialexception.h"

class Rational
{
public:
	// This class ALLOWS you to instantiate a Rational where the denominator polynomial is equivalent to zero (maybe it is necessary for your purpose)
	// HOWEVER, if you try to evaluate the function, it will throw a division by zero polynomial exception.

	friend std::ostream& operator<< (std::ostream &, Rational &);

	Rational(std::string n, std::string d) : numerator(Polynomial(n)), denominator(Polynomial(d)) {};
	Rational(std::string n, Polynomial& d) : numerator(Polynomial(n)), denominator(d) {};
	Rational(Polynomial& n, std::string d) : numerator(n), denominator(Polynomial(d)) {};
	Rational(Polynomial& n, Polynomial& d) : numerator(n), denominator(d) {};
	
	double operator() (double x) const;

    //~Rational();// A custom destructor does nothing in this implementation; no dynamic memory needs to be deallocated
private:
	Polynomial numerator, denominator;

};

#endif
