#include "Fraction.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include "Exception.h"

Fraction::Fraction(long long int numerator, long long int denominator)  : numerator(numerator), denominator(denominator) {
    normalize();
}

void Fraction::normalize() {

    if (denominator == 0)
        throw Exception("ERROR: Fraction's denominator cannot be null");

    if (numerator == 0) {
        denominator = 1;
        return;
    }
    if (numerator < 0 && denominator < 0)
    {
        numerator = llabs(numerator);
        denominator = llabs(denominator);
    }
    else if (numerator < 0 || denominator < 0){
        numerator = llabs(numerator);
        denominator = llabs(denominator);
        numerator *= -1;
    }
    long long int fraction_gcd = llabs(std::__gcd(numerator, denominator));
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
    long long int temp_numerator = (this->numerator * rhs.denominator + rhs.numerator * this->denominator);
    long long int temp_denominator = (this->denominator * rhs.denominator);
    long long int fraction_gcd = std::__gcd(temp_denominator, temp_numerator);
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
    long long int temp_numerator = (this->numerator * rhs.denominator - rhs.numerator * this->denominator);
    long long int temp_denominator = (this->denominator * rhs.denominator);
    long long int fraction_gcd = std::__gcd(temp_denominator, temp_numerator);
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
    long long int temp_numerator = (this->numerator * rhs.numerator);
    long long int temp_denominator = (this->denominator * rhs.denominator);
    long long int fraction_gcd = std::__gcd(temp_denominator, temp_numerator);
    return Fraction(temp_numerator / fraction_gcd, temp_denominator / fraction_gcd);
}

Fraction operator*(const Fraction & lhs, const long long int num) {
    return lhs.multiply(num);
}

Fraction operator*(const long long int num, const Fraction & lhs) {
    return lhs.multiply(num);
}

Fraction Fraction::multiply(const long long int num) const {
    long long int temp_numerator = (this->numerator * num);
    long long int fraction_gcd = std::__gcd(this->denominator, temp_numerator);
    return Fraction(temp_numerator / fraction_gcd, this->denominator / fraction_gcd);
}

Fraction operator/(const Fraction & lhs, const Fraction & rhs) {
    return lhs.divide(rhs);
}

Fraction Fraction::divide(const Fraction &rhs) const {
    long long int temp_numerator = (this->numerator * rhs.denominator);
    long long int temp_denominator = (this->denominator * rhs.numerator);
    long long int fraction_gcd = std::__gcd(temp_denominator, temp_numerator);
    return Fraction(temp_numerator / fraction_gcd, temp_denominator / fraction_gcd);
}

Fraction operator/(const Fraction & lhs, const long long int num) {
    return lhs.divide(num);
}

Fraction Fraction::divide(const long long int num) const {
    long long int temp_denominator = (this->denominator * num);
    long long int fraction_gcd = std::__gcd(this->numerator, temp_denominator);
    return Fraction(temp_denominator / fraction_gcd, this->numerator / fraction_gcd);
}

std::ostream & operator<<(std::ostream & os, const Fraction & fraction) {
    os << fraction.numerator;
    if (fraction.numerator == 0)
        return os;
    if (fraction.denominator != 1)
        os << '/' << fraction.denominator;
    return os;
}

std::istream & operator>>(std::istream & is, Fraction & fraction) {
    double numerator;
    long long int denominator = 1;
    long long int peeked_char;

    is >> numerator; //get the numerator
    if (is.fail()){
        is.clear();
        is.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        throw Exception("ERROR: Matrix elements can be only numbers or fractions");
    }
    while(std::isspace(is.peek()) && is.peek() != '\n')
        is.get();
    peeked_char = is.peek(); //peek at next character

    if(is && peeked_char == '/') { //if next character is a /
        is.get(); //skip the / character
        while(std::isspace(is.peek()))
            is.get();
        peeked_char = is.peek();
        is >> denominator;
        if (is.fail()){
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            throw Exception("ERROR: Matrix elements can be only numbers or fractions");
        }
//        if (is && peeked_char == '-')
    }

    if (is) { //if we succeeded is reading
        //TODO: denominator == 0 ? exception (maybe in Fraction constructor)
        fraction = Fraction(int(numerator), denominator);
    }
    return is;
}

int Fraction::getWidth() const {
    if (numerator == 0)
        return 1;
    bool isNegative = numerator < 0;
    int result = log10(llabs(numerator)) + 1;
    result += isNegative;
    if (denominator != 1)
        result += log10(denominator) + 2;
    return result;
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

long long int Fraction::getNumerator() const {
    return numerator;
}

void Fraction::setNumerator(int numerator) {
    Fraction::numerator = numerator;
}

long long int Fraction::getDenominator() const {
    return denominator;
}

void Fraction::setDenominator(long long int denominator) {
    Fraction::denominator = denominator;
}
