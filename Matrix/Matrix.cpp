#include "Matrix.h"

std::shared_ptr<Matrix> Matrix::operator+(const Matrix &other) {
    return this->add(other);
}

std::shared_ptr<Matrix> Matrix::operator-(const Matrix &other) {
    return this->subtract(other);
}

std::shared_ptr<Matrix> Matrix::operator*(const Matrix &other) {
    return this->multiply(other);
}

std::shared_ptr<Matrix> Matrix::operator*(int scalar) {
    return this->multiply(scalar);
}

std::pair<int, int> Matrix::getSize() const {
    return this->size;
}
