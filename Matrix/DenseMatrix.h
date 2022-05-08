#pragma once

#include <vector>
#include "Matrix.h"

class DenseMatrix : public Matrix {
    std::vector<std::vector<int>> matrix;
public:

    DenseMatrix();

    ~DenseMatrix();

    std::shared_ptr<Matrix> clone() const override;

    std::shared_ptr<Matrix> add (const Matrix & other) override;

    std::shared_ptr<Matrix> subtract (const Matrix & other) override;

    std::shared_ptr<Matrix> multiply (const Matrix & other) override;

    std::shared_ptr<Matrix> multiply (int scalar) override;

    std::shared_ptr<Matrix> findInversion () override;

    std::shared_ptr<Matrix> findDeterminant () override;

    std::shared_ptr<Matrix> findRank () override;

    std::shared_ptr<Matrix> gaussEliminate (bool withComments) override;

    std::shared_ptr<Matrix> merge (const Matrix & other) override;

    std::shared_ptr<Matrix> cut (const Matrix & other, int row, int col, int dimension) override;
};
