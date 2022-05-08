#include "DenseMatrix.h"

std::shared_ptr<Matrix> DenseMatrix::clone() const {
    return std::make_shared<DenseMatrix>(*this);
}

std::shared_ptr<Matrix> DenseMatrix::add(const Matrix &other) {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> DenseMatrix::subtract(const Matrix &other) {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> DenseMatrix::multiply(const Matrix &other) {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> DenseMatrix::multiply(int scalar) {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> DenseMatrix::findInversion() {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> DenseMatrix::findDeterminant() {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> DenseMatrix::findRank() {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> DenseMatrix::gaussEliminate(bool withComments) {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> DenseMatrix::merge(const Matrix &other) {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> DenseMatrix::cut(const Matrix &other, int row, int col, int dimension) {
    return std::shared_ptr<Matrix>();
}
