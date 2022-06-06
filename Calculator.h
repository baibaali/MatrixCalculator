#pragma once

#include <map>
#include "InputReader.h"

/**
 * The main class of a program. All the logic and events handling
 */
class Calculator {
    InputReader inputReader;
    std::vector<Fraction> matrix_values;
    std::map<char, std::shared_ptr<Matrix>> variables;
public:

    /**
     * Starts the calculator
     */
    void run();

    /**
     * Evaluating the expression from user
     * @return True if exit command was provided
     */
    bool calculate();

    /**
     * Creates new matrix variable
     */
    void addNewVariable();

    /**
     * Prints the matrix
     */
    void printMatrix() const;

    /**
     * Creates an identity matrix
     */
    void createIdentityMatrix();

    /**
     * Read matrix from input
     * @param count - Count of matrix elements
     */
    void readMatrixValues(int count);

    /**
     * Merge two matrices by rows
     */
    void mergeByRows();

    /**
     * Merge two matrices by columns
     */
    void mergeByColumns();

    /**
     * Cut matrix
     */
    void cut();

    /**
     * Add two matrices
     */
    void addition();

    /**
     * Subtract two matrices
     */
    void subtraction();

    /**
     * Multiply matrix by scalar
     */
    void multiplicationByScalar();

    /**
     * Multiply matrix by matrix
     */
    void multiplication();

    /**
     * Convert matrix in Upper Triangular Form
     * @param withComments - Flag, that displays if comments should be displayed
     */
    void gem(bool withComments);

    /**
     * Finds matrix determinant
     */
    void determinant();

    /**
     * Finds matrix rank
     */
    void rank();

    /**
     * Finds matrix inversion
     */
    void inversion();

    /**
     * Reads matrix from file
     */
    void readMatrixFromFile();

    /**
     * Saves matrix to file
     */
    void saveMatrix();
};
