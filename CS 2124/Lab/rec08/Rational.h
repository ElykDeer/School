/* Author: Kyle Martin
 *
 * This code was written for the class CS 2124
 *
 * This code serves as an exercise in operator overloading.
 *
 */


#ifndef RATIONAL_NUMBERS
#define RATIONAL_NUMBERS 1

#include <iostream>
#include <math.h>

namespace CS2124
{
    class Rational
    {
        //Get input! Format of input = #/#
        friend std::istream& operator>>(std::istream&, Rational&);

        //Report! Format of output = #/#
        friend std::ostream& operator<<(std::ostream&, const Rational&);

        //Check for equality!
        friend bool operator==(const Rational&, const Rational&);

    public:
        //Default constructor - set to zero
        Rational();

        //If set to a whole numbers
        Rational(int);

        //If set to a fractional numbers
        Rational(double);

        //Add to me (more more more)
        Rational& operator+=(const Rational&);

        //Pre-increment
        Rational& operator++();

        //post-increment
        Rational operator++(int);

        explicit operator bool() const;

    private:
        int greatestCommonDivisor(int, int) const;

        int numerator;
        unsigned int denominator;
    };

//Non-member, non-friend functions
    //Addition
    Rational operator+(const Rational&, const Rational&);

    //Check for inequality!
    bool operator!=(const Rational&, const Rational&);

    //pre-Decriment
    Rational& operator--(Rational&);

    //post-Decriment
    Rational operator--(Rational&, int);
}
#endif
