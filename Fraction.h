#pragma once

#include <ostream>
#include <istream>

class Fraction {
    int numerator;
    int denominator;

public:
    Fraction() : numerator(1), denominator(1) {};

    Fraction(int numerator, int denominator = 1);

    ~Fraction() = default;

    friend Fraction operator+(const Fraction & lhs, const Fraction & rhs);
    friend Fraction operator+=(Fraction & lhs, const Fraction & rhs);
    Fraction add(const Fraction & rhs) const;

    friend Fraction operator-(const Fraction & lhs, const Fraction & rhs);
    friend Fraction operator-=(Fraction & lhs, const Fraction & rhs);
    Fraction subtract(const Fraction & rhs) const;

    friend Fraction operator*(const Fraction & lhs, const Fraction & rhs);
    Fraction multiply(const Fraction & rhs) const;

    friend Fraction operator*(const Fraction & lhs, const int num);
    friend Fraction operator*(const int num, const Fraction & lhs);
    Fraction multiply(const int num) const;

    friend Fraction operator*=(Fraction & lhs, const Fraction & rhs);

    friend Fraction operator/(const Fraction & lhs, const Fraction & rhs);
    Fraction divide(const Fraction & rhs) const;

    friend Fraction operator/(const Fraction & lhs, const int num);
    Fraction divide(const int num) const;

    friend std::istream & operator>>(std::istream & is, Fraction & fraction);

    friend std::ostream & operator<<(std::ostream & os, const Fraction & fraction);

    bool operator==(const Fraction &rhs) const;

    bool operator!=(const Fraction &rhs) const;

    int getWidth() const;

private:

    void normalize();

};
