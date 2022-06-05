#include "DenseMatrix.h"
#include <iostream>
#include <iomanip>

DenseMatrix::DenseMatrix(int rows, int columns, double sparsity) : Matrix(rows, columns, 1, sparsity) {}

DenseMatrix::DenseMatrix(const std::vector<Fraction> & values, int rows, int columns, double sparsity) : Matrix(rows, columns, 1, sparsity) {
    for (int i = 0; i < rows; i++) {
        matrix.emplace_back(values.begin() + i * columns, values.begin() + (i + 1) * columns);
        for (auto & x: matrix[i])
            this->setOutputWidth(x);
    }
}

std::shared_ptr<Matrix> DenseMatrix::clone() const {
    return std::make_shared<DenseMatrix>(*this);
}

std::shared_ptr<Matrix> DenseMatrix::multiply(Fraction scalar) const {
    DenseMatrix result = DenseMatrix(*this);
    for (int row = 0; row < result.getSize().first; row++) {
        for (int column = 0; column < result.getSize().second; column++) {
            result.matrix[row][column] *= scalar;
        }
    }
    return result.clone();
}

std::shared_ptr<Matrix> DenseMatrix::inversion() const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> DenseMatrix::determinant() const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> DenseMatrix::rank() const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> DenseMatrix::gaussEliminateCommon () const {

    DenseMatrix gem_matrix = DenseMatrix(*this);

    std::cout << "Matrix before GEM:" << std::endl;
    gem_matrix.print();
    std::cout << std::endl << "Matrix after GEM:" << std::endl;

    for (int column = 0; column < gem_matrix.getSize().second; column++){
        if(gem_matrix.isColumnNull(column))
            continue;
        if (gem_matrix.at(column, column) == 0) {
            for (int temp_row = column + 1; temp_row < gem_matrix.getSize().first; temp_row++) {
                if (gem_matrix.at(temp_row, column) != 0) {
                    gem_matrix.swap_rows(column, temp_row);
                    break;
                }
            }
        }
        for (int temp_row = column + 1; temp_row < gem_matrix.getSize().first; temp_row++){
            if (gem_matrix.at(temp_row, column) == 0)
                continue;
            gem_matrix.subtractTwoRows(temp_row, column, gem_matrix.at(temp_row, column) / gem_matrix.at(column, column));
        }
    }

    for (int pos = 0; pos < gem_matrix.getSize().first; pos++){
        if (gem_matrix.at(pos, pos).getDenominator() != 1)
            gem_matrix.multiplyRowByScalar(pos, gem_matrix.at(pos, pos).getDenominator());
    }

    return gem_matrix.clone();

}

std::shared_ptr<Matrix> DenseMatrix::gaussEliminateDescribed () const {
    return std::shared_ptr<Matrix>();
}

void DenseMatrix::makeIdentity() {
    for (int i = 0; i < this->getSize().first; i++)
        for (int j = 0; j < this->getSize().second; j++) {
            this->matrix[i].push_back(0);
            if (i == j)
                matrix[i][j] = 1;
        }
}

Fraction DenseMatrix::at(int row, int column) const {
    return matrix[row][column];
}

void DenseMatrix::makeCellNull(int row, int column) {
    this->matrix[row][column] = 0;
}

void DenseMatrix::setCellValue(int row, int column, const Fraction value) {
    this->matrix[row][column] = value;
}

void DenseMatrix::subtractTwoRows(int first, int second, const Fraction multiple) {
    Fraction temp_res;
    for (int column = 0; column < this->getSize().second; column++) {
        temp_res = this->at(first, column) - multiple * this->at(second, column);
        this->matrix[first][column] = temp_res;
    }
}

void DenseMatrix::multiplyRowByScalar(int row, int scalar) {
    for (int column = 0; column < this->getSize().second; column++)
        this->setCellValue(row, column, this->at(row, column) * scalar);
}



