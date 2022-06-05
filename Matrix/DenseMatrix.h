#pragma once

#include <vector>
#include "Matrix.h"
#include "../Fraction.h"

class DenseMatrix : public Matrix {
    std::vector<std::vector<Fraction>> matrix;
public:

    DenseMatrix() = default;

    DenseMatrix(const std::vector<Fraction> & values, int rows, int columns, double sparsity);

    DenseMatrix(int rows, int columns, double sparsity);

    ~DenseMatrix() = default;

    std::shared_ptr<Matrix> clone() const override;

    std::shared_ptr<Matrix> multiply (Fraction scalar) const override;

    std::shared_ptr<Matrix> inversion () const override;

    std::shared_ptr<Matrix> determinant () const override;

    std::shared_ptr<Matrix> rank () const override;

    std::shared_ptr<Matrix> gaussEliminateCommon () const override;

    std::shared_ptr<Matrix> gaussEliminateDescribed () const override;

    Fraction at(int row, int column) const override;

    void makeIdentity() override;

    void makeCellNull(int row, int column) override;

    void setCellValue(int row, int column, const Fraction value) override;

    void subtractTwoRows(int first, int second, const Fraction multiple) override;

    void multiplyRowByScalar(int row, int scalar) override;
};
