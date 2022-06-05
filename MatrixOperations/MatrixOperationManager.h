#pragma once

#include <memory>
#include "../Matrix/Matrix.h"
#include "../Matrix/SparseMatrix.h"
#include "../Matrix/DenseMatrix.h"
#include "../Fraction.h"

class MatrixOperationManager {

public:

    static std::shared_ptr<Matrix> Create (int rows, int columns, const std::vector<Fraction> & values);

    static std::shared_ptr<Matrix> CreateIdentity(int rows);

    static std::shared_ptr<Matrix> MatrixAddition (const std::shared_ptr<Matrix> lhs, const std::shared_ptr<Matrix> rhs);

    static std::shared_ptr<Matrix> MatrixSubtraction (const std::shared_ptr<Matrix> lhs, const std::shared_ptr<Matrix> rhs);

    static std::shared_ptr<Matrix> MatrixMultiplication (const std::shared_ptr<Matrix> lhs, const std::shared_ptr<Matrix> rhs);

    static std::shared_ptr<Matrix> MatrixMultiplication (const std::shared_ptr<Matrix> mtrx, Fraction scalar);

    static std::shared_ptr<Matrix> MatrixInversion (const std::shared_ptr<Matrix> mtrx);

    static Fraction MatrixDeterminant (const std::shared_ptr<Matrix> mtrx);

    static int MatrixRank (const std::shared_ptr<Matrix> mtrx);

    static std::shared_ptr<Matrix> MatrixGem (const std::shared_ptr<Matrix> mtrx, bool withComments);

    static std::shared_ptr<Matrix> MatrixMergeByRows (const std::shared_ptr<Matrix> lhs, const std::shared_ptr<Matrix> rhs);

    static std::shared_ptr<Matrix> MatrixMergeByColumns (const std::shared_ptr<Matrix> lhs, const std::shared_ptr<Matrix> rhs);

    static std::shared_ptr<Matrix> MatrixCut (const std::shared_ptr<Matrix> mtrx, std::pair <int, int> pos, std::pair<int, int> size);

private:

    static std::shared_ptr<Matrix> createMatrixBasedOnSparsity(const std::vector<Fraction> & values, int rows, int columns, double sparsity);
};
