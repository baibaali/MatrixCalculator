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

double Matrix::sparsity(const std::vector<int> &matrix_elements, int elements_count) {

    double non_zero_values = 0;

    for (int i = 0; i < elements_count; i++)
        non_zero_values += (matrix_elements[i] != 0);

    return (non_zero_values / elements_count);

}
