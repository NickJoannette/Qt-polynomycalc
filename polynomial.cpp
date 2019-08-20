#include "polynomial.h"

Polynomial::Polynomial(const Polynomial & rhs)
{	
	terms.insert(rhs.terms.begin(), rhs.terms.end());
	terms_string = rhs.terms_string;

}

Polynomial::Polynomial()
{
	
}

Polynomial::Polynomial(std::string polynomial)
{

	std::vector<std::string> terms_to_parse;
	unsigned int term_begin = 0;
	unsigned int term_end;
	std::string temp_polynomial_str;

	try
	{
		// If the polynomial has illegal characters or no exponent caret '^' (required for all terms) throw malformed exception
		// We check for other malformed parts of the terms later
		if (polynomial.find_first_not_of(legal_chars) != std::string::npos ) throw MalformedPolynomialException();
		else
		{
			// Remove spaces
			removeCharFromString(polynomial, ' ');
			temp_polynomial_str = polynomial;
			//Get first term, whether it starts with an explicit sign symbol or nto
			term_begin = temp_polynomial_str.find_first_of(legal_chars);
			term_end = temp_polynomial_str.find_first_of("+-", term_begin + 1);
			if (term_end != std::string::npos)
			{
				terms_to_parse.push_back(temp_polynomial_str.substr(term_begin, term_end - term_begin));
				temp_polynomial_str = temp_polynomial_str.substr(term_end, std::string::npos);
			}
			else
			{
				terms_to_parse.push_back(temp_polynomial_str.substr(term_begin, temp_polynomial_str.size() - term_begin));
				term_begin = term_end;
			}

				while (term_begin != std::string::npos)
				{
					term_begin = temp_polynomial_str.find_first_of("+-");
					term_end = temp_polynomial_str.find_first_of("+-", term_begin + 1);
					if (term_end != std::string::npos)
					{
						terms_to_parse.push_back(temp_polynomial_str.substr(term_begin, term_end - term_begin));
						temp_polynomial_str = temp_polynomial_str.substr(term_end, std::string::npos);
					}

					else
					{
						terms_to_parse.push_back(temp_polynomial_str.substr(term_begin, temp_polynomial_str.size() - term_begin));
						term_begin = std::string::npos;
					}

				}
			
		}

		// Parse each term's degrees and coefficients using validateTermForm function, which calls validDegree & validCoefficient in the process
		for (std::string & term : terms_to_parse)
		{
			formatted_term f = validateTermForm(term);
			terms.insert(std::make_pair(f.degree, f.coefficient));
		}
		// Since it is assured by this point that the input polynomial string was well-formed, assign it to terms_string
		terms_string = polynomial;

	}	catch (MalformedPolynomialException & mpe) { throw; } // Catch any errors from the parsing process & re-throw to calling function
}

const std::string & Polynomial::getStr() const
{
	return terms_string;
}

const QString Polynomial::getQStr() const
{
   QString qstr = "";
    for (auto i = terms.begin(); i != terms.end(); ++i)
    {

        // Assures that if the first printed term (term with the loweste degree) is positive, no explicit '+' sign is outputted
        if (i == terms.begin()) qstr += QString::number(i->second) + "x^" + QString::number(i->first);
        else qstr += (i->second >= 0 ? "+" : "") +  QString::number(i->second) + "x^" + QString::number(i->first);
    }

    return qstr;
}


void Polynomial::printTerms() const
{
	for (auto & t : terms)
		std::cout << std::setprecision(15) <<  t.second << "x^" << t.first << std::endl;
}

/*
Polynomial::~Polynomial()
{
}
*/

// OPERATOR OVERLOADS
Polynomial& Polynomial::operator= (const Polynomial & rhs)
{
	terms.clear();
	terms.insert(rhs.terms.begin(), rhs.terms.end());
	terms_string = rhs.terms_string;
	return *this;
}


const Polynomial operator+ (const Polynomial& lhs, const Polynomial& rhs)
{
	Polynomial sum(lhs);
	std::map<unsigned int, double>::const_iterator end = sum.terms.end();
	// For all the terms in the rhs
	for (auto & i : rhs.terms)
	{	
		// If a term of that degree does not exist in the sum (lhs), insert it
		if (sum.terms.find(i.first) == end) sum.terms.insert(i);
		// Else, add the value of its coefficient to the term of that degree in the sum(lhs)
		else sum.terms.find(i.first)->second += i.second;
	}
	return sum;
}

const Polynomial operator- (const Polynomial& rhs, const Polynomial& lhs)
{
    // Similar approach as the operator + function, only inverted to fit the logic of subtraction
    Polynomial sum(rhs);
    std::map<unsigned int, double>::const_iterator end = sum.terms.end();
    for (auto & i : lhs.terms)
    {
        if (sum.terms.find(i.first) == end) sum.terms.insert(std::make_pair(i.first,-i.second));
        else {
            sum.terms.find(i.first)->second -= i.second;
            if (sum.terms.find(i.first)->second == 0) sum.terms.erase(i.first);
        }
    }
    return sum;
}

const Polynomial operator* (const Polynomial& P, double z)
{
	Polynomial product(P);
	for (auto & i: product.terms) 
	{
		i.second *= z;
	}
	return product;
}

std::istream& operator>> (std::istream & is, Polynomial & p)
{
	// Was not sure if this was the intended functionality in the instructions
	// Reads in a string and then assigns the reference polynomial p to it; if necessary, throws malformed exception through the Polynomial constructor call
	std::string s;
	std::getline(is, s);
	p = Polynomial(s);
	return is;
}

std::ostream& operator<< (std::ostream & os, const Polynomial & p)
{

	for (auto i = p.terms.begin(); i != p.terms.end(); ++i)
	{
		// Assures that if the first printed term (term with the loweste degree) is positive, no explicit '+' sign is outputted
		if (i == p.terms.begin()) os << std::setprecision(15) << i->second << "x^" << i->first;
		else os << (i->second >= 0 ? "+" : "") << std::setprecision(15) << i->second << "x^" << i->first;
	}
	return os;
}


double& Polynomial::operator[] (int n)
{
   return terms.find(n)->second;
}

double Polynomial::operator[] (int n) const
{
	// As per instructions, if the requested power is negative throw a corresponding exception
    return terms.find(n)->second;
}

double Polynomial::operator() (double x) const
{
	double result = 0;
	// Used for calculating the exponentiation
	double tmp;
	// For each term in the polynomial
	for (auto & i : terms) 
	{
		tmp = 1;
		// Multiply the value of x by itself as many times as the power of the exponent
		for (unsigned int p = 0; p < i.first; ++p) tmp *= x;
		// Add this value multiplied by the coefficient to the result
		result += tmp * i.second;
	}
	return result;
}

const Polynomial Polynomial::dot(const Polynomial & rhs) const
{
    Polynomial dot_product;

    for (auto i : terms)
        for (auto j : rhs.terms)
           {
              if (dot_product.terms.find(i.first+j.first) == dot_product.terms.end()) dot_product.terms.insert(std::make_pair(i.first + j.first, i.second * j.second));
           }

return dot_product;
}
