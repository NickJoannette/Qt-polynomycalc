#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "malformedpolynomialexception.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <QString>
#include <vector>
#include "parsingutilities.h"

class MainWindow;

class Polynomial {
public:
    friend class MainWindow;
	friend const Polynomial operator+ (const Polynomial&, const Polynomial&);
	friend const Polynomial operator- (const Polynomial&, const Polynomial&);
	friend const Polynomial operator* (const Polynomial& P, double z);
	friend std::istream& operator>> (std::istream &, Polynomial &);
	friend std::ostream& operator<< (std::ostream &, const Polynomial &);

	Polynomial(std::string polynomial);
	Polynomial(const Polynomial &);
	Polynomial();
	void printTerms() const; 
    const std::string & getStr() const; // Getter used by the rational class
    const QString getQStr() const;
	Polynomial& operator= (const Polynomial &);
    const Polynomial dot(const Polynomial &) const;
	double& operator[] (int n);
	double operator[] (int n) const;
	double operator() (double x) const;

    //~Polynomial(); // A custom destructor does nothing in this implementation; no dynamic memory needs to be deallocated
protected:

	// Terms of the polynomial are sorted by power in the map
	std::map<unsigned int, double> terms;
	// String of legal characters allowed in polynomial construction string
	std::string legal_chars = "0123456789.x^+- ";
	// Simplifies later operations by saving the string form of the polynomial
	std::string terms_string;

};

#endif

