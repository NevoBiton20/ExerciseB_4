#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <string>
#include <iostream>
#include <cmath>

// Class for representing complex numbers
using namespace std;
class Complex
{
    private:
        double im;
        double re;
    
    public:

        Complex(double imaginary, double real) : im(imaginary), re(real) {} // Constructor by two double number

        Complex(const Complex& other) : im(other.getIm()), re(other.getRe()) {} // Copy constructor used for heap operation

        double getIm() const // Returns imaginary part of this complex number
        {
            return im;
        }

        double getRe() const // Returns real part of this complex number
        {
            return re;
        }

        string toString() const // To string function for this complex number
        {
            string imaginary = to_string(im);
            string real = to_string(re);
            imaginary.erase ( imaginary.find_last_not_of('0') + 1, string::npos);
            imaginary.erase ( imaginary.find_last_not_of('.') + 1, string::npos);

            real.erase (real.find_last_not_of('0') + 1, string::npos);
            real.erase (real.find_last_not_of('.') + 1, string::npos);

            if(imaginary=="1")
            {
                return real + " + " +  "i";
            }
            return real + " + " + imaginary + "i";
        }

        double magnitude() const // Function to calculate this complex number magnitude
        {
            return sqrt(pow(re,2) + pow(im,2));  // a: real,  b: imaginary.  sqrt(a^2 + b^2)
        }

        // Comparison operators
        friend bool operator==(const Complex &first,const Complex &second); 
        friend bool operator!=(const Complex &first,const Complex &second);
        friend bool operator<(const Complex &first,const Complex &second);
        friend bool operator>(const Complex &first,const Complex &second);
        friend bool operator<=(const Complex &first,const Complex &second);
        friend bool operator>=(const Complex &first,const Complex &second);

        friend ostream& operator<<(ostream& os, const Complex& cmp); // << operator for cout a complex number
};
#endif