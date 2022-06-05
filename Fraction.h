#pragma once

#include <ostream>
#include <istream>

class Fraction {
    long long int numerator;
    long long int denominator;

public:
    Fraction() : numerator(1), denominator(1) {};

    Fraction(long long int numerator, long long int denominator = 1);

    ~Fraction() = default;

    friend Fraction operator+(const Fraction & lhs, const Fraction & rhs);
    friend Fraction operator+=(Fraction & lhs, const Fraction & rhs);
    Fraction add(const Fraction & rhs) const;

    friend Fraction operator-(const Fraction & lhs, const Fraction & rhs);
    friend Fraction operator-=(Fraction & lhs, const Fraction & rhs);
    Fraction subtract(const Fraction & rhs) const;

    friend Fraction operator*(const Fraction & lhs, const Fraction & rhs);
    Fraction multiply(const Fraction & rhs) const;

    friend Fraction operator*(const Fraction & lhs, const long long int num);
    friend Fraction operator*(const long long int num, const Fraction & lhs);
    Fraction multiply(const long long int num) const;

    friend Fraction operator*=(Fraction & lhs, const Fraction & rhs);

    friend Fraction operator/(const Fraction & lhs, const Fraction & rhs);
    Fraction divide(const Fraction & rhs) const;

    friend Fraction operator/(const Fraction & lhs, const long long int num);
    Fraction divide(const long long int num) const;

    friend std::istream & operator>>(std::istream & is, Fraction & fraction);

    friend std::ostream & operator<<(std::ostream & os, const Fraction & fraction);

    bool operator==(const Fraction &rhs) const;

    bool operator!=(const Fraction &rhs) const;

    int getWidth() const;

    long long int getNumerator() const;

    void setNumerator(int numerator);

    long long int getDenominator() const;

    void setDenominator(long long int denominator);

private:

    void normalize();

};
