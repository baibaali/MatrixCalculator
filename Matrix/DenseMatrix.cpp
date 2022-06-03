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

std::shared_ptr<Matrix> DenseMatrix::add(const Matrix &other) const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> DenseMatrix::subtract(const Matrix &other) const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> DenseMatrix::multiply(const Matrix &other) const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> DenseMatrix::multiply(double scalar) const {
    return std::shared_ptr<Matrix>();
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

void DenseMatrix::print() const {
    std::pair<int, int> size = this->getSize();
    for (int row = 0; row < size.first; row++){
        std::cout << "| ";
        for (int column = 0; column < size.second; column++){
            std::cout << std::setw(this->getOutputWidth()) << this->at(row, column) << " ";
        }
        std::cout << "|" << std::endl;
    }
}

void DenseMatrix::makeIdentity() {
    for (int i = 0; i < this->getSize().first; i++)
        for (int j = 0; j < this->getSize().second; j++) {
            this->matrix[i].push_back(0);
            if (i == j)
                matrix[i][j] = 1;
        }
}

std::vector<double> DenseMatrix::getMatrixElementsAsVector() const {
    std::vector<double> result;
    for (auto & x : matrix){
        for (auto & y : x)
            result.push_back(y);
    }
    return result;
}

double DenseMatrix::at(int row, int column) const {
    return matrix[row][column];
}


