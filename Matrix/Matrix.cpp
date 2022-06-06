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

std::shared_ptr<Matrix> operator*(const std::shared_ptr<Matrix> lhs, Fraction scalar) {
    return MatrixOperationManager::MatrixMultiplication(lhs, scalar);
}

std::shared_ptr<Matrix> operator*(const std::shared_ptr<Matrix> lhs, const std::shared_ptr<Matrix> rhs) {
    return MatrixOperationManager::MatrixMultiplication(lhs, rhs);
}

std::pair<int, int> Matrix::getSize() const {
    return this->size;
}

Fraction Matrix::determinant() const {
    Fraction det = 1;
    for (int pos = 0; pos < this->getSize().first; pos++) {
        det *= this->at(pos, pos);
    }
    return det;
}

int Matrix::rank() const {
    int rank = 0;
    for (int row = 0; row < this->getSize().first; row++)
        rank += !this->isRowNull(row);
    return rank;
}

double Matrix::sparsity(const std::vector<Fraction> &matrix_elements, int elements_count) {

    double zero_values = 0;

    for (int i = 0; i < elements_count; i++)
        zero_values += (matrix_elements[i] == 0);

    return (zero_values / elements_count);
}

int Matrix::getOutputWidth() const {
    return output_width;
}

void Matrix::setOutputWidth(const Fraction & number) {
    int width = number.getWidth();
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

std::vector<Fraction> Matrix::merge_by_rows(const std::shared_ptr<Matrix> other) const {
    std::vector<Fraction> thisVec = this->getMatrixElementsAsVector();
    std::vector<Fraction> otherVec = other->getMatrixElementsAsVector();
    thisVec.insert(thisVec.end(), otherVec.begin(), otherVec.end());
    return thisVec;
}

std::vector<Fraction> Matrix::merge_by_columns(const std::shared_ptr<Matrix> other) const {
    std::vector<Fraction> result;

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

std::vector<Fraction> Matrix::cut(std::pair<int, int> pos, std::pair<int, int> m_size) const {
    std::vector<Fraction> result;
    for (int row = pos.first; row < pos.first + m_size.first; row++) {
        for (int column = pos.second; column < pos.second + m_size.second; column++) {
            result.push_back(this->at(row, column));
        }
    }
    return result;
}

void Matrix::print(std::ostream & os, bool decorated) const {
    for (int row = 0; row < size.first; row++){
        if (decorated)
            os << "| ";
        for (int column = 0; column < size.second; column++){
            print_ws(this->at(row, column).getWidth(), this->getOutputWidth(), os);
            os << this->at(row, column) << " ";
        }
        if (decorated)
            os << "|";
        os << std::endl;
    }
}

std::vector<Fraction> Matrix::getMatrixElementsAsVector() const {
    std::vector<Fraction> result;
    for (int row = 0; row < this->getSize().first; row++){
        for (int column = 0; column < this->getSize().second; column++){
            result.push_back(this->at(row, column));
        }
    }
    return result;
}

std::vector<Fraction> Matrix::add(const std::shared_ptr<Matrix> other) const {
    std::vector<Fraction> result;
    for (int row = 0; row < size.first; row++) {
        for (int column = 0; column < size.second; column++)
            result.push_back(this->at(row, column) + other->at(row, column));
    }
    return result;
}

std::vector<Fraction> Matrix::subtract(const std::shared_ptr<Matrix> other) const {
    std::vector<Fraction> result;
    for (int row = 0; row < size.first; row++) {
        for (int column = 0; column < size.second; column++)
            result.push_back(this->at(row, column) - other->at(row, column));
    }
    return result;
}

std::vector<Fraction> Matrix::multiply(const std::shared_ptr<Matrix> other) const {
    std::vector<Fraction> result;
    Fraction temp_result = 0;
    for (int row = 0; row < this->getSize().first; row++){
        for (int column = 0; column < other->getSize().second; column++) {
            for (int element = 0; element < this->getSize().second; element++) {
                temp_result += this->at(row, element) * other->at(element, column);
            }
            result.push_back(temp_result);
            temp_result = 0;
        }
    }
    return result;
}

bool Matrix::isColumnNull(int column) const {
    for (int row = column; row < this->getSize().first; row++)
        if (this->at(row, column) != 0)
            return false;
    return true;
}

bool Matrix::isRowNull(int row) const {
    for (int column = 0; column < this->getSize().second; column++)
        if (this->at(row, column) != 0)
            return false;
    return true;
}

void Matrix::swap_rows(int first, int second) {
    for (int column = 0; column < this->getSize().second; column++){
        Fraction temp = this->at(first, column);
        if (this->at(second, column) == 0)
            this->makeCellNull(first, column);
        else
            this->setCellValue(first, column, this->at(second, column));
        if (temp == 0)
            this->makeCellNull(second, column);
        else
            this->setCellValue(second, column, temp);
    }
}

void Matrix::print_ws(int width, int max_width, std::ostream & ostream) const {
    for (int i = width; i < max_width; i++)
        ostream << " ";
}


