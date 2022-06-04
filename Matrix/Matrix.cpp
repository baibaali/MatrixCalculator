#include "Matrix.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include "../MatrixOperations/MatrixOperationManager.h"

Matrix::Matrix(int rows, int columns, int output_width, double m_sparsity) {
    size.first = rows;
    size.second = columns;
    this->output_width = output_width;
    this->m_sparsity = m_sparsity;
}

std::shared_ptr<Matrix> operator+(const std::shared_ptr<Matrix> lhs, const std::shared_ptr<Matrix> rhs) {
    return MatrixOperationManager::MatrixAddition(lhs, rhs);
}

std::shared_ptr<Matrix> operator-(const std::shared_ptr<Matrix> lhs, const std::shared_ptr<Matrix> rhs) {
    return MatrixOperationManager::MatrixSubtraction(lhs, rhs);
}

std::shared_ptr<Matrix> operator*(const std::shared_ptr<Matrix> lhs, double scalar) {
    return MatrixOperationManager::MatrixMultiplication(lhs, scalar);
}

//std::shared_ptr<Matrix> operator*(double scalar) {
//    return this->multiply(scalar);
//}

std::pair<int, int> Matrix::getSize() const {
    return this->size;
}

std::shared_ptr<Matrix> Matrix::gaussEliminate(bool withComments) const {
    return withComments ? this->gaussEliminateDescribed() : this->gaussEliminateCommon();
}

double Matrix::sparsity(const std::vector<double> &matrix_elements, int elements_count) {

    double zero_values = 0;

    for (int i = 0; i < elements_count; i++)
        zero_values += (matrix_elements[i] == 0);

    return (zero_values / elements_count);
}

int Matrix::getOutputWidth() const {
    return output_width;
}

void Matrix::setOutputWidth(double number) {
    int width = int(log10(number)) + 1;
    if (width > output_width)
        output_width = width;
}

Matrix::Matrix() {
    output_width = 1;
}

double Matrix::sparsity(int rows, int columns) {
    return ((rows * 1.0) / (rows * columns));
}

double Matrix::getMSparsity() const {
    return m_sparsity;
}

void Matrix::setMSparsity(double mSparsity) {
    m_sparsity = mSparsity;
}

std::vector<double> Matrix::merge_by_rows(const std::shared_ptr<Matrix> other) const {
    std::vector<double> thisVec = this->getMatrixElementsAsVector();
    std::vector<double> otherVec = other->getMatrixElementsAsVector();
    thisVec.insert(thisVec.end(), otherVec.begin(), otherVec.end());
    return thisVec;
}

std::vector<double> Matrix::merge_by_columns(const std::shared_ptr<Matrix> other) const {
    std::vector<double> result;

    for (int row = 0; row < this->getSize().first; row++) {
        for (int column = 0; column < this->getSize().second; column++) {
            result.push_back(this->at(row, column));
        }
        for (int column = 0; column < other->getSize().second; column++) {
            result.push_back(other->at(row, column));
        }
    }

    return result;
}

std::vector<double> Matrix::cut(std::pair<int, int> pos, std::pair<int, int> m_size) const {
    std::vector<double> result;
    for (int row = pos.first; row < pos.first + m_size.first; row++) {
        for (int column = pos.second; column < pos.second + m_size.second; column++) {
            result.push_back(this->at(row, column));
        }
    }
    return result;
}

void Matrix::print() const {
    for (int row = 0; row < size.first; row++){
        std::cout << "| ";
        for (int column = 0; column < size.second; column++){
            std::cout << std::setw(this->getOutputWidth()) << this->at(row, column) << " ";
        }
        std::cout << "|" << std::endl;
    }
}

std::vector<double> Matrix::getMatrixElementsAsVector() const {
    std::vector<double> result;
    for (int row = 0; row < this->getSize().first; row++){
        for (int column = 0; column < this->getSize().second; column++){
            result.push_back(this->at(row, column));
        }
    }
    return result;
}

std::vector<double> Matrix::add(const std::shared_ptr<Matrix> other) const {
    std::vector<double> result;
    for (int row = 0; row < size.first; row++) {
        for (int column = 0; column < size.second; column++)
            result.push_back(this->at(row, column) + other->at(row, column));
    }
    return result;
}

std::vector<double> Matrix::subtract(const std::shared_ptr<Matrix> other) const {
    std::vector<double> result;
    for (int row = 0; row < size.first; row++) {
        for (int column = 0; column < size.second; column++)
            result.push_back(this->at(row, column) - other->at(row, column));
    }
    return result;
}


