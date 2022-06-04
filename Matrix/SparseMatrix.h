#pragma once

#include <map>
#include "Matrix.h"

class SparseMatrix : public Matrix {
    std::map <std::pair<int, int>, double> matrix;
public:
    SparseMatrix() = default;

    SparseMatrix(const std::vector<double> & values, int rows, int columns, double sparsity);

    SparseMatrix(int rows, int columns, double sparsity);

    ~SparseMatrix() = default;

    std::shared_ptr<Matrix> clone() const override;

    std::shared_ptr<Matrix> subtract (const Matrix & other) const override;

    std::shared_ptr<Matrix> multiply (const Matrix & other) const override;

    std::shared_ptr<Matrix> multiply (double scalar) const override;

    std::shared_ptr<Matrix> findInversion () const override;

    std::shared_ptr<Matrix> findDeterminant () const override;

    std::shared_ptr<Matrix> findRank () const override;

    std::shared_ptr<Matrix> gaussEliminateCommon () const override;

    std::shared_ptr<Matrix> gaussEliminateDescribed () const override;

    double at(int row, int column) const override;

    void makeIdentity() override;

};
