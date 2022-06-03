#include "MatrixOperationManager.h"

std::shared_ptr<Matrix> MatrixOperationManager::Create(int rows, int columns, const std::vector<double> &values) {
    if ( Matrix::sparsity(values, rows * columns) >= 0.75 )
    {
        SparseMatrix matrix = SparseMatrix(values, rows, columns, Matrix::sparsity(values, rows * columns));
        return matrix.clone();
    } else {
        DenseMatrix matrix = DenseMatrix(values, rows, columns, Matrix::sparsity(values, rows * columns));
        return matrix.clone();
    }
}

std::shared_ptr<Matrix> MatrixOperationManager::CreateIdentity(int rows) {
   SparseMatrix matrix = SparseMatrix(rows, rows, Matrix::sparsity(rows, rows));
   matrix.makeIdentity();
   return matrix.clone();
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

std::shared_ptr<Matrix> MatrixOperationManager::MatrixMergeByRows(const std::shared_ptr<Matrix> lhs, const std::shared_ptr<Matrix> rhs) {
    std::vector<double> result = lhs->merge_by_rows(rhs);
    if ( lhs->getMSparsity() + rhs->getMSparsity() >= 0.75 )
    {
        SparseMatrix matrix = SparseMatrix(result,
                                             lhs->getSize().first + rhs->getSize().first,
                                           lhs->getSize().second,
                                           lhs->getMSparsity() + rhs->getMSparsity());
        return matrix.clone();
    } else {
        DenseMatrix matrix = DenseMatrix(result,
                                         lhs->getSize().first + rhs->getSize().first,
                                         lhs->getSize().second,
                                         lhs->getMSparsity() + rhs->getMSparsity());
        return matrix.clone();
    }
}

std::shared_ptr<Matrix> MatrixOperationManager::MatrixMergeByColumns(const std::shared_ptr<Matrix> lhs, const std::shared_ptr<Matrix> rhs) {
    std::vector<double> result = lhs->merge_by_columns(rhs);
    if ( lhs->getMSparsity() + rhs->getMSparsity() >= 0.75 )
    {
        SparseMatrix matrix = SparseMatrix(result,
                                           lhs->getSize().first,
                                           lhs->getSize().second + rhs->getSize().second,
                                           lhs->getMSparsity() + rhs->getMSparsity());
        return matrix.clone();
    } else {
        DenseMatrix matrix = DenseMatrix(result,
                                         lhs->getSize().first,
                                         lhs->getSize().second + rhs->getSize().second,
                                         lhs->getMSparsity() + rhs->getMSparsity());
        return matrix.clone();
    }
}

std::shared_ptr<Matrix>
MatrixOperationManager::MatrixCut(const Matrix &mtrx, std::pair<int, int> pos, std::pair<int, int> size) {
    return mtrx.cut(pos, size);
}

