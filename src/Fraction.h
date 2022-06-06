#pragma once

#include <ostream>
#include <istream>

/**
 * Class, that represents custom data type.
 */
class Fraction {
    long long int numerator;
    long long int denominator;

public:

    /**
     * Default constructor
     */
    Fraction() : numerator(1), denominator(1) {};

    /**
     * Constructor
     * @param numerator - Fraction numerator
     * @param denominator - Fraction denominator (if not provided, than 1 is default value for it)
     */
    Fraction(long long int numerator, long long int denominator = 1);

    /**
     * Default destructor
     */
    ~Fraction() = default;

    /**
     * Fraction addition
     * @param lhs - First fraction
     * @param rhs - Second fraction
     * @return The new fraction, that is the result of addition
     */
    friend Fraction operator+(const Fraction & lhs, const Fraction & rhs);

    /**
     * Assignee addition. Add two fractions and save the result in the left of operands
     * @param lhs - First fraction
     * @param rhs - Second fraction
     * @return The lhs, that stores the result of addition of two fractions
     */
    friend Fraction operator+=(Fraction & lhs, const Fraction & rhs);

    /**
     * Addition method that used in operator+
     * @param rhs - The second fraction of addition
     * @return New fraction - the result of addition
     */
    Fraction add(const Fraction & rhs) const;

    /**
     * Fraction subtraction
     * @param lhs - First fraction
     * @param rhs - Second fraction
     * @return The new fraction, that is the result of subtraction
     */
    friend Fraction operator-(const Fraction & lhs, const Fraction & rhs);

    /**
     * Assignee subtraction. Subtract two fractions and save the result in the left of operands
     * @param lhs - First fraction
     * @param rhs - Second fraction
     * @return The lhs, that stores the result of subtraction of two fractions
     */
    friend Fraction operator-=(Fraction & lhs, const Fraction & rhs);

    /**
     * Subtraction method that used in operator-
     * @param rhs - The second fraction of addition
     * @return New fraction - the result of addition
     */
    Fraction subtract(const Fraction & rhs) const;

    /**
     * Fraction multiplication
     * @param lhs - First fraction
     * @param rhs - Second fraction
     * @return The new fraction, that is the result of multiplication
     */
    friend Fraction operator*(const Fraction & lhs, const Fraction & rhs);

    /**
     * Multiplication method that used in operator*
     * @param rhs - The second fraction of multiplication
     * @return New fraction - the result of multiplication
     */
    Fraction multiply(const Fraction & rhs) const;

    /**
     * Multiplication by int from the right
     * @param lhs - Fraction
     * @param num - Integer value
     * @return The new fraction, that is the result of multiplication
     */
    friend Fraction operator*(const Fraction & lhs, const long long int num);

    /**
     * Multiplication by int from the left
     * @param num - Integer value
     * @param lhs - Fraction
     * @return The new fraction, that is the result of multiplication
     */
    friend Fraction operator*(const long long int num, const Fraction & lhs);

    /**
     * Multiplication method that used in operator*, when multiplying by int
     * @param num - Integer value
     * @return New fraction - the result of multiplication
     */
    Fraction multiply(const long long int num) const;

    /**
     * Assignee multiplication. Multiplies two fractions and save the result in the left of operands
     * @param lhs - First fraction
     * @param rhs - Second fraction
     * @return The lhs, that stores the result of multiplication of two fractions
     */
    friend Fraction operator*=(Fraction & lhs, const Fraction & rhs);

    /**
     * Fraction division
     * @param lhs - First fraction
     * @param rhs - Second fraction
     * @return New fraction - result of division
     */
    friend Fraction operator/(const Fraction & lhs, const Fraction & rhs);

    /**
     * Division method that used in operator/
     * @param rhs - Second fraction
     * @return The new fraction - result of division
     */
    Fraction divide(const Fraction & rhs) const;

    /**
     * Division by integer
     * @param lhs - Fraction
     * @param num - Integer value
     * @return New fraction - result of division
     */
    friend Fraction operator/(const Fraction & lhs, const long long int num);

    /**
     * Division method that used in operator/, when divide by int
     * @param num - Integer value
     * @return The new fraction - result of division
     */
    Fraction divide(const long long int num) const;

    /**
     * Operator for reading Fraction objects from stdin
     * @param is - Input stream
     * @param fraction - Fraction to be reed
     * @return std::istream &
     */
    friend std::istream & operator>>(std::istream & is, Fraction & fraction);

    /**
     * Operator for printing Fraction objects to stdout
     * @param os - Output stream
     * @param fraction - Fraction to be print
     * @return std::ostream &
     */
    friend std::ostream & operator<<(std::ostream & os, const Fraction & fraction);

    /**
     * Equality operator
     * @param rhs - Second fraction
     * @return Result of comparing
     */
    bool operator==(const Fraction &rhs) const;

    /**
     * Not equals operator
     * @param rhs - Second fraction
     * @return Result of comparing
     */
    bool operator!=(const Fraction &rhs) const;

    /**
     * Computes the width of fraction number (count of symbols needed to display the fraction)
     * @return Fraction width
     */
    int getWidth() const;

    /**
     * Returns fraction's numerator
     * @return Numerator
     */
    long long int getNumerator() const;

    /**
     * Sets fraction's numerator to the given value
     * @param numerator - Value of numerator
     */
    void setNumerator(int numerator);

    /**
     * Returns fraction's denominator
     * @return Denominator
     */
    long long int getDenominator() const;

    /**
     * Sets fraction's denominator to the given value
     * @param denominator - Value of denominator
     */
    void setDenominator(long long int denominator);

private:

    /**
     * Convert fraction into a common form
     */
    void normalize();

};
