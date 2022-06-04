#pragma once

#include <map>
#include "Matrix.h"

class SparseMatrix : public Matrix {
    std::map <std::pair<int, int>, Fraction> matrix;
public:
    SparseMatrix() = default;

    SparseMatrix(const std::vector<Fraction> & values, int rows, int columns, double sparsity);

    SparseMatrix(int rows, int columns, double sparsity);

    ~SparseMatrix() = default;

    std::shared_ptr<Matrix> clone() const override;

    std::shared_ptr<Matrix> multiply (Fraction scalar) const override;

    std::shared_ptr<Matrix> findInversion () const override;

    std::shared_ptr<Matrix> findDeterminant () const override;

    std::shared_ptr<Matrix> findRank () const override;

    std::shared_ptr<Matrix> gaussEliminateCommon () const override;

    std::shared_ptr<Matrix> gaussEliminateDescribed () const override;

    Fraction at(int row, int column) const override;

    void makeIdentity() override;

};
