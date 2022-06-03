#pragma once

#include <map>
#include "Matrix.h"

class SparseMatrix : public Matrix {
    std::map <std::pair<int, int>, double> matrix;
public:
    SparseMatrix() = default;

    SparseMatrix(const std::vector<double> & values, int rows, int columns);

    ~SparseMatrix() = default;

    std::shared_ptr<Matrix> clone() const override;

    std::shared_ptr<Matrix> add (const Matrix & other) const override;

    std::shared_ptr<Matrix> subtract (const Matrix & other) const override;

    std::shared_ptr<Matrix> multiply (const Matrix & other) const override;

    std::shared_ptr<Matrix> multiply (double scalar) const override;

    std::shared_ptr<Matrix> findInversion () const override;

    std::shared_ptr<Matrix> findDeterminant () const override;

    std::shared_ptr<Matrix> findRank () const override;

    std::shared_ptr<Matrix> gaussEliminateCommon () const override;

    std::shared_ptr<Matrix> gaussEliminateDescribed () const override;

    std::shared_ptr<Matrix> merge (const Matrix & other) const override;

    std::shared_ptr<Matrix> cut (std::pair<int, int> pos, std::pair<int, int> size) const override;

    void print() const override;
};
