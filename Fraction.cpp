#include "Fraction.h"
#include <algorithm>
#include <cmath>

Fraction::Fraction(int numerator, int denominator)  : numerator(numerator), denominator(denominator) {
    normalize();
}

void Fraction::normalize() {
        //TODO: exception if denominator == 0
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
    int fraction_gcd = std::__gcd(numerator, denominator);
    this->numerator = this->numerator / fraction_gcd;
    this->denominator = this->denominator / fraction_gcd;
}

Fraction operator+(const Fraction & lhs, const Fraction & rhs) {
    return lhs.add(rhs);
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

Fraction Fraction::subtract(const Fraction &rhs) const {
    int temp_numerator = (this->numerator * rhs.denominator - rhs.numerator * this->denominator);
    int temp_denominator = (this->denominator * rhs.denominator);
    int fraction_gcd = std::__gcd(temp_denominator, temp_numerator);
    return Fraction(temp_numerator / fraction_gcd, temp_denominator / fraction_gcd);
}

Fraction operator*(const Fraction & lhs, const Fraction & rhs) {
    return lhs.multiply(rhs);
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