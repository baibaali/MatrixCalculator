#include "DenseMatrix.h"
#include <iostream>
#include <iomanip>

DenseMatrix::DenseMatrix(int rows, int columns, double sparsity) : Matrix(rows, columns, 1, sparsity) {}

DenseMatrix::DenseMatrix(const std::vector<double> & values, int rows, int columns, double sparsity) : Matrix(rows, columns, 1, sparsity) {
    for (int i = 0; i < rows; i++) {
        matrix.emplace_back(values.begin() + i * columns, values.begin() + (i + 1) * columns);
        for (auto & x: matrix[i])
            this->setOutputWidth(x);
    }
}

std::shared_ptr<Matrix> DenseMatrix::clone() const {
    return std::make_shared<DenseMatrix>(*this);
}

std::shared_ptr<Matrix> DenseMatrix::multiply(double scalar) const {
    DenseMatrix result = DenseMatrix(*this);
    for (int row = 0; row < result.getSize().first; row++) {
        for (int column = 0; column < result.getSize().second; column++) {
            result.matrix[row][column] *= scalar;
        }
    }
    return result.clone();
}

std::shared_ptr<Matrix> DenseMatrix::findInversion() const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> DenseMatrix::findDeterminant() const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> DenseMatrix::findRank() const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> DenseMatrix::gaussEliminateCommon () const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> DenseMatrix::gaussEliminateDescribed () const {
    return std::shared_ptr<Matrix>();
}

void DenseMatrix::makeIdentity() {
    for (int i = 0; i < this->getSize().first; i++)
        for (int j = 0; j < this->getSize().second; j++) {
            this->matrix[i].push_back(0);
            if (i == j)
                matrix[i][j] = 1;
        }
}

double DenseMatrix::at(int row, int column) const {
    return matrix[row][column];
}



