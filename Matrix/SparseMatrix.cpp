#include "SparseMatrix.h"
#include <iostream>
#include <iomanip>

SparseMatrix::SparseMatrix(const std::vector<double> &values, int rows, int columns) : Matrix(rows, columns, 1) {
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++) {
            if (values[i * rows + j] != 0) {
                matrix[std::make_pair(i, j)] = values[i * rows + j];
                this->setOutputWidth(values[i * rows + j]);
            }
        }
    }
}

std::shared_ptr<Matrix> SparseMatrix::clone() const {
    return std::make_shared<SparseMatrix>(*this);
}

std::shared_ptr<Matrix> SparseMatrix::add(const Matrix &other) const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> SparseMatrix::subtract(const Matrix &other) const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> SparseMatrix::multiply(const Matrix &other) const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> SparseMatrix::multiply(double scalar) const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> SparseMatrix::findInversion() const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> SparseMatrix::findDeterminant() const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> SparseMatrix::findRank() const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> SparseMatrix::gaussEliminateCommon () const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> SparseMatrix::gaussEliminateDescribed () const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> SparseMatrix::merge(const Matrix &other) const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> SparseMatrix::cut(std::pair<int, int> pos, std::pair<int, int> size) const {
    return std::shared_ptr<Matrix>();
}

void SparseMatrix::print() const {
    std::pair<int, int> size = this->getSize();
    for (int row = 0; row < size.first; row++){
        std::cout << "| ";
        for (int column = 0; column < size.second; column++){
            if(matrix.count(std::make_pair(row, column)) != 0)
                std::cout << std::setw(this->getOutputWidth()) << matrix.find(std::make_pair(row, column))->second << " ";
            else {
                std::cout << std::setw(this->getOutputWidth()) << "0 ";
            }
        }
        std::cout << "|" << std::endl;
    }
}

