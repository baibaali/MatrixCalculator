#include "MatrixOperationManager.h"

std::shared_ptr<Matrix> MatrixOperationManager::Create(int rows, int columns, const std::vector<Fraction> &values) {
    return createMatrixBasedOnSparsity(values, rows, columns, Matrix::sparsity(values, rows * columns));
}

std::shared_ptr<Matrix> MatrixOperationManager::CreateIdentity(int rows) {
   SparseMatrix matrix = SparseMatrix(rows, rows, Matrix::sparsity(rows, rows));
   matrix.makeIdentity();
   return matrix.clone();
}

std::shared_ptr<Matrix> MatrixOperationManager::MatrixAddition(const std::shared_ptr<Matrix> lhs, const std::shared_ptr<Matrix> rhs) {
    std::vector<Fraction> result = lhs->add(rhs);
    return createMatrixBasedOnSparsity(result, lhs->getSize().first, lhs->getSize().second, Matrix::sparsity(result, lhs->getSize().first * lhs->getSize().second));
}

std::shared_ptr<Matrix> MatrixOperationManager::MatrixSubtraction(const std::shared_ptr<Matrix> lhs, const std::shared_ptr<Matrix> rhs) {
    std::vector<Fraction> result = lhs->subtract(rhs);
    return createMatrixBasedOnSparsity(result, lhs->getSize().first, lhs->getSize().second, Matrix::sparsity(result, lhs->getSize().first * lhs->getSize().second));
}

std::shared_ptr<Matrix> MatrixOperationManager::MatrixMultiplication(const std::shared_ptr<Matrix> lhs, const std::shared_ptr<Matrix> rhs) {
    std::vector<Fraction> result = lhs->multiply(rhs);
    return createMatrixBasedOnSparsity(result, lhs->getSize().first, rhs->getSize().second,
                                Matrix::sparsity(result, lhs->getSize().first * rhs->getSize().second));
}

std::shared_ptr<Matrix> MatrixOperationManager::MatrixMultiplication(const std::shared_ptr<Matrix> mtrx, Fraction scalar) {
    return mtrx->multiply(scalar);
}

std::shared_ptr<Matrix> MatrixOperationManager::MatrixInversion(const std::shared_ptr<Matrix> mtrx) {
    return mtrx->inversion();
}

Fraction MatrixOperationManager::MatrixDeterminant(const std::shared_ptr<Matrix> mtrx) {
    return mtrx->gaussEliminate(false)->determinant();
}

int MatrixOperationManager::MatrixRank(const std::shared_ptr<Matrix> mtrx) {
    return mtrx->gaussEliminate(false)->rank();
}

std::shared_ptr<Matrix> MatrixOperationManager::MatrixGem(const std::shared_ptr<Matrix> mtrx, bool withComments) {
    std::shared_ptr<Matrix> res = mtrx->gaussEliminate(withComments);
    return res;
}

std::shared_ptr<Matrix> MatrixOperationManager::MatrixMergeByRows(const std::shared_ptr<Matrix> lhs, const std::shared_ptr<Matrix> rhs) {
    std::vector<Fraction> result = lhs->merge_by_rows(rhs);
    return createMatrixBasedOnSparsity(result, lhs->getSize().first + rhs->getSize().first, lhs->getSize().second, lhs->getMSparsity() + rhs->getMSparsity());
}

std::shared_ptr<Matrix> MatrixOperationManager::MatrixMergeByColumns(const std::shared_ptr<Matrix> lhs, const std::shared_ptr<Matrix> rhs) {
    std::vector<Fraction> result = lhs->merge_by_columns(rhs);
    return createMatrixBasedOnSparsity(result, lhs->getSize().first, lhs->getSize().second + rhs->getSize().second, lhs->getMSparsity() + rhs->getMSparsity());
}

std::shared_ptr<Matrix>
MatrixOperationManager::MatrixCut(const std::shared_ptr<Matrix> mtrx, std::pair<int, int> pos, std::pair<int, int> size) {
    std::vector<Fraction> result = mtrx->cut(pos, size);
    return createMatrixBasedOnSparsity(result, size.first, size.second, Matrix::sparsity(result, size.first * size.second));
}

std::shared_ptr<Matrix>
MatrixOperationManager::createMatrixBasedOnSparsity(const std::vector<Fraction> &values, int rows, int columns, double sparsity) {
    if ( sparsity >= 0.75 )
    {
        SparseMatrix matrix = SparseMatrix(values, rows, columns, sparsity);
        return matrix.clone();
    } else {
        DenseMatrix matrix = DenseMatrix(values, rows, columns, sparsity);
        return matrix.clone();
    }
}

