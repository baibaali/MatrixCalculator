#include "Matrix.h"

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
