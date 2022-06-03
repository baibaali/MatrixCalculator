#pragma once

#include <vector>
#include "Matrix.h"

class DenseMatrix : public Matrix {
    std::vector<std::vector<double>> matrix;
public:

    DenseMatrix() = default;

    DenseMatrix(const std::vector<double> & values, int rows, int columns, double sparsity);

    DenseMatrix(int rows, int columns, double sparsity);

    ~DenseMatrix() = default;

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

    std::shared_ptr<Matrix> cut (std::pair<int, int> pos, std::pair<int, int> size) const override;

    std::vector<double> getMatrixElementsAsVector() const override;

    double at(int row, int column) const override;

    void makeIdentity() override;

    void print() const override;
};
