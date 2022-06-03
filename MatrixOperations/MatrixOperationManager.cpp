#include "MatrixOperationManager.h"

std::shared_ptr<Matrix> MatrixOperationManager::Create(int rows, int columns, const std::vector<double> &values) {
    if ( Matrix::sparsity(values, rows * columns) >= 0.75 )
    {
        SparseMatrix matrix = SparseMatrix(values, rows, columns);
        return matrix.clone();
    } else {
        DenseMatrix matrix = DenseMatrix(values, rows, columns);
        return matrix.clone();
    }
}

std::shared_ptr<Matrix> MatrixOperationManager::MatrixAddition(const Matrix &lhs, const Matrix &rhs) {
    return lhs + rhs;
}

std::shared_ptr<Matrix> MatrixOperationManager::MatrixSubtraction(const Matrix &lhs, const Matrix &rhs) {
    return lhs - rhs;
}

std::shared_ptr<Matrix> MatrixOperationManager::MatrixMultiplication(const Matrix &lhs, const Matrix &rhs) {
    return lhs * rhs;
}

std::shared_ptr<Matrix> MatrixOperationManager::MatrixMultiplication(const Matrix &mtrx, double scalar) {
    return mtrx * scalar;
}

std::shared_ptr<Matrix> MatrixOperationManager::MatrixInversion(const Matrix &mtrx) {
    return mtrx.findInversion();
}

std::shared_ptr<Matrix> MatrixOperationManager::MatrixDeterminant(const Matrix &mtrx) {
    return mtrx.findDeterminant();
}

std::shared_ptr<Matrix> MatrixOperationManager::MatrixRank(const Matrix &mtrx) {
    return mtrx.findRank();
}

std::shared_ptr<Matrix> MatrixOperationManager::MatrixGem(const Matrix &mtrx, bool withComments) {
    return mtrx.gaussEliminate(withComments);
}

std::shared_ptr<Matrix> MatrixOperationManager::MatrixMerge(const Matrix &lhs, const Matrix &rhs) {
    return lhs.merge(rhs);
}

std::shared_ptr<Matrix>
MatrixOperationManager::MatrixCut(const Matrix &mtrx, std::pair<int, int> pos, std::pair<int, int> size) {
    return mtrx.cut(pos, size);
}

