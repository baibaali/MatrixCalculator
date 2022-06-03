#pragma once

#include <memory>
#include "../Matrix/Matrix.h"
#include "../Matrix/SparseMatrix.h"
#include "../Matrix/DenseMatrix.h"

class MatrixOperationManager {

public:

    static std::shared_ptr<Matrix> Create (int rows, int columns, const std::vector<double> & values);

    static std::shared_ptr<Matrix> CreateIdentity(int rows);

    static std::shared_ptr<Matrix> MatrixAddition (const Matrix & lhs, const Matrix & rhs);

    static std::shared_ptr<Matrix> MatrixSubtraction (const Matrix & lhs, const Matrix & rhs);

    static std::shared_ptr<Matrix> MatrixMultiplication (const Matrix & lhs, const Matrix & rhs);

    static std::shared_ptr<Matrix> MatrixMultiplication (const Matrix & mtrx, double scalar);

    static std::shared_ptr<Matrix> MatrixInversion (const Matrix & mtrx);

    static std::shared_ptr<Matrix> MatrixDeterminant (const Matrix & mtrx);

    static std::shared_ptr<Matrix> MatrixRank (const Matrix & mtrx);

    static std::shared_ptr<Matrix> MatrixGem (const Matrix & mtrx, bool withComments);

    static std::shared_ptr<Matrix> MatrixMerge (const Matrix & lhs, const Matrix & rhs);

    static std::shared_ptr<Matrix> MatrixCut (const Matrix & mtrx, std::pair <int, int> pos, std::pair<int, int> size);

};
