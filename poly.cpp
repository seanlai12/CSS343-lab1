// Lab1
// file poly.cpp
// source code for ADT Polynomials
// Author:  Sean Lai
// Date:    April 9, 2014
// Class:   CSS343 - Dr. Carol Zander

#ifndef POLY_CPP
#define POLY_CPP
#include <iostream>
#include <fstream>
#include <algorithm>
#include "poly.h"

using namespace std;


// ---------------------------------------------------------------------------
// Poly
// Default constructor for class Array
// Creates a Poly with coefficients and degree zero, one element
Poly::Poly()
{
	degree = 0;
	coefficients = new int[degree + 1]();
	coefficients[0] = 0;
}

// ---------------------------------------------------------------------------
// Poly
// Parameter is the zero degree coefficient
// Creates a Poly with int coef as coefficient at zero degree
Poly::Poly(int coef)
{
    degree = 0;
    coefficients = new int[degree + 1]();
    coefficients[0] = coef;
}

// ---------------------------------------------------------------------------
// Poly
// Parameter is the coefficient and degree respectively
// Creates a Poly with int coef as coefficient at int deg degree
// Degree must be positive integer
Poly::Poly(int coef, int deg)
{
    if (deg >= 0)
    {
    degree = deg;
    coefficients = new int[degree + 1]();
    coefficients[deg] = coef;
    }
    
}

// ---------------------------------------------------------------------------
// Poly
// Copy constructor
// Creates a Poly equals to the target Poly
Poly::Poly(Poly& other)
{
    degree = other.degree; // Copy the degree of the target
    coefficients = new int[degree + 1]();
    for (int i=0; i < degree + 1; i++)
    {
        coefficients[i] = other.coefficients[i];
    }
}

// ---------------------------------------------------------------------------
// Poly
// Destructor
// Frees allocated memory
Poly::~Poly()
{
    delete [] coefficients;
    coefficients = NULL;
}

// ---------------------------------------------------------------------------
// getCoeff
// Parameter is the degree
// Returns the coeffient at the degree parameter.
// Degree must be within the highest power of the Poly and positive number
// Otherwise returns zero.
int Poly::getCoeff(int deg)
{
    if (degree < deg || deg < 0)
    {
        return 0;
    }
    
    return coefficients[deg];
}

// ---------------------------------------------------------------------------
// setCoeff
// Parameter is coefficient and degree respectively, integers
// Sets the coefficient element at degree parameter with the new coefficient
// The size of array will enlarge if parameter degree is bigger than original
// Will ignore if negative input of degree
void Poly::setCoeff(int coef, int deg)
{
    if (deg >= 0)
    {
        if (deg > degree) // array will enlarge only if input is larger
        {
            int* temp = new int[deg + 1]();
            for (int i = 0; i < degree + 1; i++)
            {
                temp[i] = coefficients[i];
            }
            delete [] coefficients; // Deletes the original
            coefficients = temp;
            degree = deg;
            coefficients[deg] = coef;
        }
        else // Size stays the same
        {
            coefficients[deg] = coef;
        }
    }
}

// ---------------------------------------------------------------------------
// setCoeff
// Parameter is coefficient and degree respectively, integers
// Adds the coefficient element at degree parameter with the input coefficient
// The size of array will enlarge if parameter degree is bigger than original
// Will ignore if negative input of degree
void Poly::addCoeff(int coef, int deg)
{
    if (deg >= 0)
    {
        if (deg > degree)
        {
            int* temp = new int[deg + 1]();
            for (int i = 0; i < degree + 1; i++)
            {
                temp[i] = coefficients[i];
            }
            delete [] coefficients; // Deletes the original
            coefficients = temp;
            degree = deg;
            coefficients[deg] += coef;
        }
        else
        {
            coefficients[deg] += coef;
        }
    }
}

//----------------------------------------------------------------------------
// operator+
// overloaded +: addition of 2 Poly, Every coefficients at existing degrees
// new degree will be higher of the two Polys
Poly Poly::operator+(const Poly& other)
{
    int temp;
    int deg = max(this->degree, other.degree);// Uses max to find higher degree
    Poly res(0, deg); // Creates a Poly with the higher degree
    if (this->degree < other.degree) // Case if other Poly is smaller degree
    {
        temp = this->degree;
        for (int i=0; i < temp+1; i++)
        {
            res.coefficients[i] = this->coefficients[i] + other.coefficients[i];
        }
        
        for (int i=temp+1; i < deg+1; i++)
        {
            res.coefficients[i] = other.coefficients[i]; // Fills in
        }
    }
    else if (this->degree > other.degree)// Case if other Poly is bigger degree
    {
        temp = other.degree;
        for (int i=0; i < temp+1; i++)
        {
            res.coefficients[i] = this->coefficients[i] + other.coefficients[i];
        }
        
        for (int i=temp+1; i < deg+1; i++)
        {
            res.coefficients[i] = this->coefficients[i]; // Fills in
        }
    }
    
    else // If two highest degrees are equal
    {
        for (int i=0; i < deg + 1; i++)
        {
            res.coefficients[i] = this->coefficients[i] + other.coefficients[i];
        }
    }
    
    return res;
}

//----------------------------------------------------------------------------
// operator-
// overloaded -: subtraction of 2 Poly, Every coefficients at existing degrees
// new degree will be higher of the two Polys
Poly Poly::operator-(const Poly& other)
{
    int temp;
    int deg = max(this->degree, other.degree);// Uses max to find higher degree
    Poly res(0, deg); // Creates a Poly with the higher degree
    if (this->degree < other.degree) // Case if other Poly is smaller degree
    {
        temp = this->degree;
        for (int i=0; i < temp+1; i++)
        {
            res.coefficients[i] = this->coefficients[i] - other.coefficients[i];
        }
        for (int i=temp+1; i < deg+1; i++)
        {
            res.coefficients[i] = -(other.coefficients[i]); // Fills in
        }
    }
    else if (this->degree > other.degree)//Case if other Poly is bigger degree
    {
        temp = other.degree;
        for (int i=0; i < temp+1; i++)
        {
            res.coefficients[i] = this->coefficients[i] - other.coefficients[i];
        }
        for (int i=temp+1; i < deg+1; i++)
        {
            res.coefficients[i] = this->coefficients[i]; // Fills in
        }
    }
    
    else // If both degrees equal
    {
        for (int i=0; i < deg + 1; i++)
        {
            res.coefficients[i] = this->coefficients[i] - other.coefficients[i];
        }
    }
    
    return res;
}

//----------------------------------------------------------------------------
// operator*
// overloaded *: multiplication of 2 Poly.
// new degree will be set with the highest coeffient product degree
Poly Poly::operator*(const Poly& other)
{
    Poly res; // Creates an empty Poly
    int resultCoeff = 0;
    int resultDegree = 0;
    
    for(int i = 0; i <= this->degree; i++)
    {
        for(int j = 0; j <= other.degree; j++) // Finds results using for loops
        {
            resultCoeff = this->coefficients[i] * other.coefficients[j];
            resultDegree = i+j;
            res.addCoeff(resultCoeff, resultDegree); // Add elements
        }
    }
    
    return res;
}

//----------------------------------------------------------------------------
// operator=
// overloaded =: current Poly = parameter Poly
Poly Poly::operator=(const Poly& other)
{
    if (*this == other) { // If the two Poly are equal, return original.
        return *this;
    }
    
    int deg = other.degree;
    this->degree = other.degree;
    int* temp = new int[deg + 1]();
    
    for (int i=0; i < deg + 1; i++)
    {
        temp[i] = other.coefficients[i];
    }
    delete [] coefficients;
    coefficients = temp;
    
    return *this;
}

//----------------------------------------------------------------------------
// operator+=
// overloaded +=: current Poly = current Poly + parameter Poly
Poly Poly::operator+=(const Poly& other)
{
    int tempIndex;
    int deg = max(this->degree, other.degree); // Finds highest power
    
    if (this->degree < other.degree)
    {
        int* temp = new int[deg + 1]();
        for (int i = 0; i < degree + 1; i++)
        {
            temp[i] = coefficients[i];
        }
        delete [] coefficients;
        coefficients = temp;
        degree = deg;
    }
    
    if (this->degree < other.degree)
    {
        tempIndex = this->degree;
        
        for (int i=0; i < tempIndex+1; i++)
        {
            
            this->coefficients[i] += other.coefficients[i];
        }
        
        for (int i=tempIndex+1; i < deg+1; i++)
        {
            this->coefficients[i] = other.coefficients[i];
        }
    }
    else if (this->degree > other.degree)
    {
        tempIndex = other.degree;
        
        for (int i=0; i < tempIndex+1; i++)
        {
            this->coefficients[i] += other.coefficients[i];
        }
        
        for (int i=tempIndex+1; i < deg+1; i++)
        {
            this->coefficients[i] = this->coefficients[i];
        }
    }
    else // If two degrees equal
    {
        for (int i=0; i < deg + 1; i++)
        {
            this->coefficients[i] += other.coefficients[i];
        }
    }
    
    return *this;
}

//----------------------------------------------------------------------------
// operator-=
// overloaded -=: current Poly = current Poly - parameter Poly
Poly Poly::operator-=(const Poly& other)
{
    int tempIndex;
    int deg = max(this->degree, other.degree); // Finds highest power
    
    if (this->degree < other.degree)
    {
        int* temp = new int[deg + 1]();
        for (int i = 0; i < degree + 1; i++)
        {
            temp[i] = coefficients[i];
        }
        delete [] coefficients;
        coefficients = temp;
        degree = deg;
    }
    
    if (this->degree < other.degree)
    {
        tempIndex = this->degree;
        
        for (int i=0; i < tempIndex+1; i++)
        {
            
            this->coefficients[i] -= other.coefficients[i];
        }
        
        for (int i=tempIndex+1; i < deg+1; i++)
        {
            this->coefficients[i] = -(other.coefficients[i]);
        }
    }
    else if (this->degree > other.degree)
    {
        tempIndex = other.degree;
        
        for (int i=0; i < tempIndex+1; i++)
        {
            this->coefficients[i] -= other.coefficients[i];
        }
        
        for (int i=tempIndex+1; i < deg+1; i++)
        {
            this->coefficients[i] = -(this->coefficients[i]);
        }
    }
    else // If two degrees equal
    {
        for (int i=0; i < deg + 1; i++)
        {
            this->coefficients[i] -= other.coefficients[i];
        }
    }
    
    return *this;
}

//----------------------------------------------------------------------------
// operator-=
// overloaded -=: current Poly = current Poly * parameter Poly
Poly Poly::operator*=(const Poly& other)
{
    int resultCoeff = 0;
    int resultDegree = 0;
    int maxDegree = 0;
    
    for(int i = 0; i <= this->degree; i++) // Looks for the highest power
    {
        for(int j = 0; j <= other.degree; j++)
        {
            resultDegree = i+j;
            maxDegree = max(maxDegree, resultDegree);
        }
    }
    int* temp = new int[maxDegree + 1](); // Creates Poly with highest power
    
    for(int i = 0; i <= this->degree; i++)
    {
        for(int j = 0; j <= other.degree; j++)
        {
            resultCoeff = this->coefficients[i] * other.coefficients[j];
            resultDegree = i+j;
            temp[i+j] += resultCoeff; // Fills in the array
        }
    }
    delete [] coefficients;
    coefficients = temp;
    degree = maxDegree;
    
    return *this;
}

//----------------------------------------------------------------------------
// operator==
// overloaded ==: true if current Poly is == Poly, otherwise false
bool Poly::operator==(const Poly& other)
{
    if (this->degree != other.degree) { // Degrees must equal to be true
        return false;
    }
    
    for (int i=0; i < other.degree + 1; i++)
    {
        if(this->coefficients[i] != other.coefficients[i])
        {
            return false;
        }
    }
    
    return true;
}

//----------------------------------------------------------------------------
// operator!=
// overloaded !=: true if current Poly is != Poly, otherwise false
bool Poly::operator!=(const Poly& other)
{
    if (this->degree != other.degree) {
        return true;
    }
    
    for (int i=0; i < other.degree + 1; i++)
    {
        if(this->coefficients[i] != other.coefficients[i])
        {
            return true;
        }
    }
    
    return false;
}

//----------------------------------------------------------------------------
// operator<<
// Prints the Poly in the format " +ax^2 +bx + c"
// Only prints " 0" if all coefficients are zero
// Otherwise always have plus or negative signs before the coefficient
ostream& operator<<(ostream &console, const Poly& target)
{
    bool allZero = true;
    
    for (int i=target.degree; i >= 0; i--)
    {
        string sign = " +";
        if(target.coefficients[i] < 0)
        {
            sign = " ";
        }
        
        if(i == 1 && target.coefficients[i] != 0)
        {
            // Degree at one does not need the power " ^"
            allZero = false;
            console << sign << target.coefficients[i] << "x";
            
        }
        else if (i == 0)
        {
            if (target.coefficients[i] != 0)
            {
            // Degree at zero does not need the variable or power " x^"
            allZero = false;
            console << sign << target.coefficients[i];
            }
        }
        else if(target.coefficients[i] != 0)
        {
            allZero = false;
            console << sign << target.coefficients[i] << "x^" << i;
        }
        
        if ((target.degree == 0 && target.coefficients[0] == 0) || allZero)
        {
            console << " " << target.coefficients[0]; // If all coef are zero
            return console;
        }
    }
    
    return console;
}

//----------------------------------------------------------------------------
// operator>>
// overloaded >>: takes 2 ints as coefficient and degree, no type checking.
// Will exit if (-1, -1) is input. Any other negative degree input will be
// ignored.
istream& operator>>(istream &input, Poly& targetPoly)
{
    bool exit = false;
    int coef;
    int degree;
    while (!exit) {
        input >> coef >> degree;
        if (coef == -1 && degree == -1) // Exit at (-1,-1)
        {
            exit = true;
        }
        else
        {
            targetPoly.setCoeff(coef, degree);
        }
    }
    return input;
}

#endif
