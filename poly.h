// Lab1
// file poly.h
// Polynomial class for ADT Polynomials
// Author:  Sean Lai
// Date:    April 9, 2014
// Class:   CSS343 - Dr. Carol Zander

#include <fstream>
#include <iostream>
#ifndef POLY_H
#define POLY_H

using namespace std;

//---------------------------------------------------------------------------
// Poly class:  Contains array of polynomial coefficients with index as degree
//   Features:
//   -- allows input and output of the polynomial
//   -- allows for comparison of 2 polynomials, element by element
//   -- allows for assignment of polynomials
//   -- degree is part of the class, which is the highest power in polynomial
//   -- allows add, subtract, multiply two polynomials
//   -- able to set or add new coefficients
//
// Implementation and assumptions:
//   -- size of zero degree polynomial is defaulted if no parameter input
//   -- coefficients and degree must be integers
//   -- degree will only allow positive integers
//   -- inputting coefficients and degree must in sets of two, (coef, degree)
//   -- inputting (-1, -1) will end the input, no typechecking.
//   -- will not output zero coefficients, unless all coefficients are zero
//---------------------------------------------------------------------------

class Poly
{
    friend ostream &operator<<(ostream&, const Poly&); // operator << output
    friend istream& operator>>(istream&, Poly&);       // operator >> input
    
    private:
    int *coefficients;  // int array to store the coefficients
    int degree;         // highest degree of the polynomial
    
    public:
    Poly();           // the default constructor
    Poly(int, int);   // initialize a polynomial with coefficient and degree
    Poly(Poly&);      // the copy constructor
    Poly(int);        // initiate polynomial with int coefficient at degree zero
    ~Poly();          // destructor

    int getCoeff(int); // returns the coefficients
    void setCoeff(int, int); // sets coefficient at target degree
    void addCoeff(int, int); // adds coefficient at target degree
    
    
    Poly operator+(const Poly&);    // operator + overload. Adds two poly
    Poly operator-(const Poly&);    // opeartor - overload. Subtract two poly
    Poly operator*(const Poly&);    // operator * overload. Multiply two poly
    Poly operator=(const Poly&);    // operator = , assignment operator
    Poly operator+=(const Poly&);   // current object add and assignment
    Poly operator-=(const Poly&);   // current object subtract and assignment
    Poly operator*=(const Poly&);   // current object multiply and assignment
    bool operator==(const Poly&);   // return true if two poly are equal
    bool operator!=(const Poly&);   // return true if two poly are different

};

#endif
