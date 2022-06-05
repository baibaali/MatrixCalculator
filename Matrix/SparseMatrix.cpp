#include "SparseMatrix.h"
#include <iostream>
#include <iomanip>

SparseMatrix::SparseMatrix(int rows, int columns, double sparsity) : Matrix(rows, columns, 1, sparsity) {}

SparseMatrix::SparseMatrix(const std::vector<Fraction> &values, int rows, int columns, double sparsity) : Matrix(rows, columns, 1, sparsity) {
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++) {
            if (values[i * rows + j] != 0) {
                matrix[std::make_pair(i, j)] = values[i * rows + j];
                this->setOutputWidth(values[i * rows + j]);
            }
        }
    }
}

std::shared_ptr<Matrix> SparseMatrix::clone() const {
    return std::make_shared<SparseMatrix>(*this);
}

std::shared_ptr<Matrix> SparseMatrix::multiply(Fraction scalar) const {
    SparseMatrix result = SparseMatrix(*this);
    for (auto & el : result.matrix)
        el.second *= 2;
    return result.clone();
}

std::shared_ptr<Matrix> SparseMatrix::inversion() const {
    return std::shared_ptr<Matrix>();
}

std::shared_ptr<Matrix> SparseMatrix::gaussEliminateCommon () const {

    SparseMatrix gem_matrix = SparseMatrix(*this);

    int swap_counts = 0;

    std::cout << "Matrix before GEM:" << std::endl;
    gem_matrix.print();
    std::cout << std::endl << "Matrix after GEM:" << std::endl;

    for (int column = 0; column < gem_matrix.getSize().second; column++){
        if(gem_matrix.isColumnNull(column))
            continue;
//        for (int row = 0; row < gem_matrix.getSize().first; row++){
            if (gem_matrix.at(column, column) == 0) {
                for (int temp_row = column + 1; temp_row < gem_matrix.getSize().first; temp_row++) {
                    if (gem_matrix.at(temp_row, column) != 0) {
                        gem_matrix.swap_rows(column, temp_row);
                        swap_counts++;
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

    if (swap_counts % 2 == 1)
        gem_matrix.multiplyRowByScalar(0, -1);

    return gem_matrix.clone();

//    }
}

std::shared_ptr<Matrix> SparseMatrix::gaussEliminateDescribed () const {
    return std::shared_ptr<Matrix>();
}

void SparseMatrix::makeIdentity() {
    for (int i = 0; i < this->getSize().first; i++)
        this->matrix[std::make_pair(i, i)] = 1;
}

Fraction SparseMatrix::at(int row, int column) const {
    if (matrix.count(std::make_pair(row, column)) == 0)
        return 0;
    else
        return matrix.find(std::make_pair(row, column))->second;
}

void SparseMatrix::makeCellNull(int row, int column) {
    this->matrix.erase(std::make_pair(row, column));
}

void SparseMatrix::setCellValue(int row, int column, const Fraction value) {
    this->matrix[std::make_pair(row, column)] = value;
}

void SparseMatrix::subtractTwoRows(int first, int second, const Fraction multiple) {
    Fraction temp_res;
    for (int column = 0; column < this->getSize().second; column++) {
        temp_res = this->at(first, column) - multiple * this->at(second, column);
        if (temp_res != 0)
            this->matrix[std::make_pair(first, column)] = temp_res;
    }
}

void SparseMatrix::multiplyRowByScalar(int row, int scalar) {
    for (int column = 0; column < this->getSize().second; column++)
        if (this->at(row, column) != 0)
            this->setCellValue(row, column, this->at(row, column) * scalar);
}
