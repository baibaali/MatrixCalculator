#pragma once

#include <map>
#include "InputReader.h"

class Calculator {
    InputReader inputReader;
    std::vector<Fraction> matrix_values;
    std::map<char, std::shared_ptr<Matrix>> variables;
public:
    void run();

    bool calculate();

    void addNewVariable();

    void printMatrix() const;

    void createIdentityMatrix();

    void readMatrixValues(int count);

    void mergeByRows();

    void mergeByColumns();

    void cut();

    void addition();

    void subtraction();

    void multiplicationByScalar();

    void multiplication();

    void gem(bool withComments);

    void determinant();

    void rank();

    void inversion();
};
