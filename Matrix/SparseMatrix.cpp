#include "SparseMatrix.h"

std::shared_ptr<Matrix> SparseMatrix::clone() const {
    return std::make_shared<SparseMatrix>(*this);
}

std::shared_ptr<Matrix> SparseMatrix::add(const Matrix &other) {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> SparseMatrix::subtract(const Matrix &other) {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> SparseMatrix::multiply(const Matrix &other) {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> SparseMatrix::multiply(int scalar) {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> SparseMatrix::findInversion() {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> SparseMatrix::findDeterminant() {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> SparseMatrix::findRank() {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> SparseMatrix::gaussEliminate(bool withComments) {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> SparseMatrix::merge(const Matrix &other) {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> SparseMatrix::cut(const Matrix &other, int row, int col, int dimension) {
    return std::shared_ptr<Matrix>();
}

