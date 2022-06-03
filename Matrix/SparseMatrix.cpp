#include "SparseMatrix.h"
#include <iostream>
#include <iomanip>

SparseMatrix::SparseMatrix(int rows, int columns, double sparsity) : Matrix(rows, columns, 1, sparsity) {}

SparseMatrix::SparseMatrix(const std::vector<double> &values, int rows, int columns, double sparsity) : Matrix(rows, columns, 1, sparsity) {
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

std::vector<double> SparseMatrix::merge_by_rows (const std::shared_ptr<Matrix> other) const {
    std::vector<double> thisVec = this->getMatrixElementsAsVector();
    std::vector<double> otherVec = other->getMatrixElementsAsVector();
    thisVec.insert(thisVec.end(), otherVec.begin(), otherVec.end());
    return thisVec;
}

std::vector<double> SparseMatrix::merge_by_columns (const std::shared_ptr<Matrix> other) const {
    std::vector<double> thisVec = this->getMatrixElementsAsVector();
    std::vector<double> otherVec = other->getMatrixElementsAsVector();
    std::vector<double> result;

    for (int row = 0; row < this->getSize().first; row++) {
        for (int column = 0; column < this->getSize().second; column++) {
            if (matrix.count(std::make_pair(row, column)) == 0)
                result.push_back(0);
            else
                result.push_back(matrix.find(std::make_pair(row, column))->second);
        }
        for (int column = 0; column < other->getSize().second; column++) {
            if (matrix.count(std::make_pair(row, column)) == 0)
                result.push_back(0);
            else
                result.push_back(matrix.find(std::make_pair(row, column))->second);
        }
    }

    thisVec.insert(thisVec.end(), otherVec.begin(), otherVec.end());
    return thisVec;
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

void SparseMatrix::makeIdentity() {
    for (int i = 0; i < this->getSize().first; i++)
        this->matrix[std::make_pair(i, i)] = 1;
}

std::vector<double> SparseMatrix::getMatrixElementsAsVector() const {
    std::vector<double> result;
    for (int row = 0; row < this->getSize().first; row++){
        for (int column = 0; column < this->getSize().second; column++){
            if (matrix.count(std::make_pair(row, column)) == 0)
                result.push_back(0);
            else
                result.push_back(matrix.find(std::make_pair(row, column))->second);
        }
    }
    return result;
}

double SparseMatrix::at(int row, int column) const {
    if (matrix.count(std::make_pair(row, column)) == 0)
        return 0;
    else
        return matrix.find(std::make_pair(row, column))->second;
}
