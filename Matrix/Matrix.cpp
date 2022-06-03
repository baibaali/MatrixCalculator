#include "Matrix.h"
#include <cmath>

Matrix::Matrix(int rows, int columns, int output_width) {
    size.first = rows;
    size.second = columns;
    this->output_width = output_width;
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

