#include "parsingutilities.h"

void removeCharFromString(std::string & s, char c)
{
	size_t f, l, d;
	while (s.find(c) != std::string::npos)
	{
		f = s.find(c);
		l = s.find_first_not_of(c, f);
		d = l - f;
		s.erase(f, d);
	}
}

const formatted_degree validDegree(std::string s)
{
	// Remove the caret ('^') symbol from the beginning of the string; if any parts of the string are anything other than a digit after that, throw malformed exception
	// Throw malformed exception in that case
	s = s.substr(1,std::string::npos);
	for (size_t i = 0; i < s.size(); ++i) if (!isDigit(s[i])) throw MalformedPolynomialException();
	// Continue, and catch the invalid argument error if the string still cannot convert to int
	try {
		return formatted_degree{ true, unsigned(std::stoi(s)) };
	}catch (std::invalid_argument & ia){throw MalformedPolynomialException(); }
}

const formatted_coefficient validCoefficient(std::string s)
{

	size_t f, l, decimal_loc = 0;
	char sign = 0;

	// If the coefficient string begins with an explicit sign, remember it, then remove it
	if (s[0] == '+')
	{
		sign = s[0];
		s = s.substr(1, std::string::npos);
	}
	else if (s[0] == '-') 
	{
		sign = s[0];
		s = s.substr(1, std::string::npos);
	}

	// Erase the 'x' at the end of the coefficient. If there isn't one, throw a malformed exception
	if (s[s.size()-1] == 'x') s.erase(s.size() - 1);
	else throw MalformedPolynomialException();

	// Remove the decimal point if it exists
	if (s.find('.') != std::string::npos)
	{
		decimal_loc = f = s.find('.');
		l = s.find_first_not_of('.', f);
		s.erase(f, l - f);
	}

	// If any characters except digits exist after this, it was an invalid coefficient - throw a malformed exception
	// Including all relevant char types to be safe
	if (s.find_first_of("+-.^x") != std::string::npos) throw MalformedPolynomialException();

	// Else re-insert the decimal point, convert to double, add the sign back, and return the appropriate formatted_coefficient
	if (decimal_loc != 0) s.insert(decimal_loc, ".");
	if (sign != 0) s = sign + s;
	return formatted_coefficient{ true, std::stod(s) };
}

const formatted_term validateTermForm(std::string & s)
{
	size_t caret;
	size_t decimal;
	std::string degree;
	std::string coefficient;
	unsigned int deg;
	double coef;

	// Find the location of the caret ('^') character
	caret = s.find('^');
	// If a caret character didn't exist, throw malformed exception
	if (caret != std::string::npos)
	{
		// Split the string intwo two parts: the degree, and the coefficient, using the caret as a delimiter
		degree = s.substr(caret, std::string::npos);
		coefficient = s.substr(0, caret);
		// Use the appropriate functions to validate them
		formatted_coefficient fc = validCoefficient(coefficient);
		formatted_degree fd = validDegree(degree);
		// If they were valid, return them to the callign function where they are added to the terms of the polynomial. Else, throw a malformed exception
		if (fc.valid && fd.valid) return formatted_term{ fc.value, fd.value };
		else throw MalformedPolynomialException();
	}
	else throw MalformedPolynomialException();
}

