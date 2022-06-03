#include "Matrix.h"

Matrix::Matrix(int rows, int columns) {
    size.first = rows;
    size.second = columns;
}

std::shared_ptr<Matrix> Matrix::operator+(const Matrix &other) const {
    return this->add(other);
}

std::shared_ptr<Matrix> Matrix::operator-(const Matrix &other) const {
    return this->subtract(other);
}

std::shared_ptr<Matrix> Matrix::operator*(const Matrix &other) const {
    return this->multiply(other);
}

std::shared_ptr<Matrix> Matrix::operator*(double scalar) const {
    return this->multiply(scalar);
}

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

