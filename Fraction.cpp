#include "Fraction.h"
#include <algorithm>
#include <cmath>

Fraction::Fraction(int numerator, int denominator)  : numerator(numerator), denominator(denominator) {
    normalize();
}

void Fraction::normalize() {
        //TODO: exception if denominator == 0
    if (numerator == 0) {
        denominator = 1;
        return;
    }
    if (numerator < 0 && denominator < 0)
    {
        numerator = abs(numerator);
        denominator = abs(denominator);
    }
    else if (numerator < 0 || denominator < 0){
        numerator = abs(numerator);
        denominator = abs(denominator);
        numerator *= -1;
    }
    int fraction_gcd = abs(std::__gcd(numerator, denominator));
    this->numerator = this->numerator / fraction_gcd;
    this->denominator = this->denominator / fraction_gcd;

}

Fraction operator+(const Fraction & lhs, const Fraction & rhs) {
    return lhs.add(rhs);
}

Fraction operator+=(Fraction & lhs, const Fraction & rhs) {
    lhs.numerator = (lhs.numerator * rhs.denominator + rhs.numerator * lhs.denominator);
    lhs.denominator = (lhs.denominator * rhs.denominator);
    lhs.normalize();
    return lhs;
}

Fraction Fraction::add(const Fraction &rhs) const {
    int temp_numerator = (this->numerator * rhs.denominator + rhs.numerator * this->denominator);
    int temp_denominator = (this->denominator * rhs.denominator);
    int fraction_gcd = std::__gcd(temp_denominator, temp_numerator);
    return Fraction(temp_numerator / fraction_gcd, temp_denominator / fraction_gcd);
}

Fraction operator-(const Fraction & lhs, const Fraction & rhs) {
    return lhs.subtract(rhs);
}

Fraction operator-=(Fraction & lhs, const Fraction & rhs) {
    lhs.numerator = (lhs.numerator * rhs.denominator - rhs.numerator * lhs.denominator);
    lhs.denominator = (lhs.denominator * rhs.denominator);
    lhs.normalize();
    return lhs;
}

Fraction Fraction::subtract(const Fraction &rhs) const {
    int temp_numerator = (this->numerator * rhs.denominator - rhs.numerator * this->denominator);
    int temp_denominator = (this->denominator * rhs.denominator);
    int fraction_gcd = std::__gcd(temp_denominator, temp_numerator);
    return Fraction(temp_numerator / fraction_gcd, temp_denominator / fraction_gcd);
}

Fraction operator*(const Fraction & lhs, const Fraction & rhs) {
    return lhs.multiply(rhs);
}

Fraction operator*=(Fraction & lhs, const Fraction &rhs) {
    lhs.denominator *= rhs.denominator;
    lhs.numerator *= rhs.numerator;
    lhs.normalize();
    return lhs;
}

Fraction Fraction::multiply(const Fraction &rhs) const {
    int temp_numerator = (this->numerator * rhs.numerator);
    int temp_denominator = (this->denominator * rhs.denominator);
    int fraction_gcd = std::__gcd(temp_denominator, temp_numerator);
    return Fraction(temp_numerator / fraction_gcd, temp_denominator / fraction_gcd);
}

Fraction operator*(const Fraction & lhs, const int num) {
    return lhs.multiply(num);
}

Fraction operator*(const int num, const Fraction & lhs) {
    return lhs.multiply(num);
}

Fraction Fraction::multiply(const int num) const {
    int temp_numerator = (this->numerator * num);
    int fraction_gcd = std::__gcd(this->denominator, temp_numerator);
    return Fraction(temp_numerator / fraction_gcd, this->denominator / fraction_gcd);
}

Fraction operator/(const Fraction & lhs, const Fraction & rhs) {
    return lhs.divide(rhs);
}

Fraction Fraction::divide(const Fraction &rhs) const {
    int temp_numerator = (this->numerator * rhs.denominator);
    int temp_denominator = (this->denominator * rhs.numerator);
    int fraction_gcd = std::__gcd(temp_denominator, temp_numerator);
    return Fraction(temp_numerator / fraction_gcd, temp_denominator / fraction_gcd);
}

Fraction operator/(const Fraction & lhs, const int num) {
    return lhs.divide(num);
}

Fraction Fraction::divide(const int num) const {
    int temp_denominator = (this->denominator * num);
    int fraction_gcd = std::__gcd(this->numerator, temp_denominator);
    return Fraction(temp_denominator / fraction_gcd, this->numerator / fraction_gcd);
}

std::ostream & operator<<(std::ostream & os, const Fraction & fraction) {
    os << fraction.numerator;
    if (fraction.denominator != 1)
        os << '/' << fraction.denominator;
    return os;
}

std::istream & operator>>(std::istream & is, Fraction & fraction) {
    int numerator;
    int denominator = 1;
    int peeked_char;

    is >> numerator; //get the numerator
    is >> std::ws;
    peeked_char = is.peek(); //peek at next character

    if(is && peeked_char == '/') { //if next character is a /
        is.get(); //skip the / character
        is >> std::ws;
        peeked_char = is.peek();
        is >> denominator;
//        if (is && peeked_char == '-')

    }

    if (is) { //if we succeeded is reading
        //TODO: denominator == 0 ? exception (maybe in Fraction constructor)
        fraction = Fraction(numerator, denominator);
    }
    return is;
}

int Fraction::getWidth() const {
    bool isNegative = numerator < 0;
    // +1 for first log, +1 for second, +1 for '/' sign and +1 if number is negative
    return log10(numerator) + log10(denominator) + 3 + isNegative;
}

bool Fraction::operator==(const Fraction &rhs) const {
    Fraction lhs = *this;
    Fraction temp_rhs = rhs;
    lhs.normalize();
    temp_rhs.normalize();
    return lhs.numerator == temp_rhs.numerator &&
           lhs.denominator == temp_rhs.denominator;
}

bool Fraction::operator!=(const Fraction &rhs) const {
    return !(rhs == *this);
}

