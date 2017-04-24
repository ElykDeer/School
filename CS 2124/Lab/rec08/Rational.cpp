#include "Rational.h"
using namespace std;

namespace CS2124
{
//Friends
    //Get input! Format of input = #/#
    istream& operator>>(istream& is, Rational& rhs)
    {
        //Create our vars
        double numer, denom;

        //Get the initial values
        char ingnore; //Ignore the slash
        is >> numer >> ingnore >> denom;

        //make sure the denominator is not negative
        if (denom < 0)
        {
            numer *= -1;
            denom *= -1;
        }

        //Simplify (just in case)
        int GCD = rhs.greatestCommonDivisor(abs(numer), denom);
        numer /= GCD;
        denom /= GCD;

        //Set Up class values
        rhs.numerator = numer;
        rhs.denominator = denom;

        return is;
    }

    //Report! Format of output = #/#
    ostream& operator<<(ostream& os, const Rational& rhs)
    {
        os << rhs.numerator << '/' << rhs.denominator;
        return os;
    }

    bool operator==(const Rational& lhs, const Rational& rhs)
        { return ((lhs.numerator == rhs.numerator) && (lhs.denominator == rhs.denominator)); }

//Public:
    //Default constructor - set to zero
    Rational::Rational() : numerator(0), denominator(1) {}

    //If set to a whole numbers
    Rational::Rational(int initVal) : numerator(initVal), denominator(1) {}

    //If set to a fractional numbers
    Rational::Rational(double initVal)
    {
        int denom = 1;

        //While initVal is still a decimal value
        while (fmod(initVal, 1.0))
        {
            initVal *= 10;
            denom *= 10;
        }

        //simplify
        int GCD = greatestCommonDivisor(initVal, denom);
        initVal /= GCD;
        denom /= GCD;

        //Set Up class values
        numerator = initVal;
        denominator = denom;
    }

    //Add to me (more more more)
    Rational& Rational::operator+=(const Rational& rhs)
    {
        //Convert the base
        denominator *= rhs.denominator;

        //Cross-multiply to scale the numerator to the new base
        numerator *= rhs.denominator;

        //Scall the other numerator, add it to me
        numerator += (rhs.numerator * (denominator/rhs.denominator));

        //simplify
        int GCD = greatestCommonDivisor(numerator, denominator);
        numerator /= GCD;
        denominator /= GCD;

        //return ourselves
        return *this;
    }

    //Pre-increment
    Rational& Rational::operator++()
    {
        numerator += denominator;
        return *this;
    }

    //post-increment
    Rational Rational::operator++(int)
    {
        Rational old = *this;
        numerator += denominator;
        return old;
    }

    //Check if zero
    Rational::operator bool() const
        { return !(numerator == 0); }


//Private
    //Provided by instructor
    int Rational::greatestCommonDivisor(int x, int y) const
    {
    	while (y != 0) {
    		int temp = x % y;
    		x = y;
    		y = temp;
    	}
    	return x;
    }

//Non-Member-Non-Friend
    Rational operator+(const Rational& lhs, const Rational& rhs)
    {
        Rational sum = lhs;
        sum += rhs;
        return sum;
    }

    //Check for inequality!
    bool operator!=(const Rational& lhs, const Rational& rhs)
    {
        return !(lhs == rhs);
    }

    //pre-decriment
    Rational& operator--(Rational& rhs)
    {
        rhs += -1;
        return rhs;
    }

    //post-decriment
    Rational operator--(Rational& lhs, int)
    {
        Rational old = lhs;
        lhs += -1;
        return old;
    }
}
