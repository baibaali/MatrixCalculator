#include "DenseMatrix.h"

std::shared_ptr<Matrix> DenseMatrix::clone() const {
    return std::make_shared<DenseMatrix>(*this);
}

std::shared_ptr<Matrix> DenseMatrix::add(const Matrix &other) const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> DenseMatrix::subtract(const Matrix &other) const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> DenseMatrix::multiply(const Matrix &other) const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> DenseMatrix::multiply(double scalar) const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> DenseMatrix::findInversion() const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> DenseMatrix::findDeterminant() const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> DenseMatrix::findRank() const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> DenseMatrix::gaussEliminateCommon () const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> DenseMatrix::gaussEliminateDescribed () const {
    return std::shared_ptr<Matrix>();
}


std::shared_ptr<Matrix> DenseMatrix::merge(const Matrix &other) const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> DenseMatrix::cut(std::pair<int, int> pos, std::pair<int, int> size) const {
    return std::shared_ptr<Matrix>();
}
