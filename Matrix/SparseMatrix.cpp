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

    SparseMatrix gem_matrix = SparseMatrix(*this);
    SparseMatrix identity = SparseMatrix(*this);
    identity.makeIdentity();

    for (int column = 0; column < gem_matrix.getSize().second; column++){
        if(gem_matrix.isColumnNull(column))
            continue;
        if (gem_matrix.at(column, column) == 0) {
            for (int temp_row = column + 1; temp_row < gem_matrix.getSize().first; temp_row++) {
                if (gem_matrix.at(temp_row, column) != 0) {
                    gem_matrix.swap_rows(column, temp_row);
                    identity.swap_rows(column, temp_row);
                    break;
                }
            }
        }
        for (int temp_row = column + 1; temp_row < gem_matrix.getSize().first; temp_row++){
            if (gem_matrix.at(temp_row, column) == 0)
                continue;
            gem_matrix.subtractTwoRows(temp_row, column, gem_matrix.at(temp_row, column) / gem_matrix.at(column, column));
            identity.subtractTwoRows(temp_row, column, identity.at(temp_row, column) / identity.at(column, column));
        }
    }
    std::cout << "GEM before transposition: " << std::endl;
    gem_matrix.print();
    std::cout << "Identity before transposition: " << std::endl;
    identity.print();
    std::shared_ptr<Matrix> transposed_gem = gem_matrix.transposition();
    std::shared_ptr<Matrix> transposed_identity = identity.transposition();
    std::cout << "GEM after transposition: " << std::endl;
    transposed_gem->print();
    std::cout << "Identity after transposition: " << std::endl;
    transposed_identity->print();


    for (int column = 0; column < transposed_gem->getSize().second; column++){
        if(transposed_gem->isColumnNull(column))
            continue;
        if (transposed_gem->at(column, column) == 0) {
            for (int temp_row = column + 1; temp_row < transposed_gem->getSize().first; temp_row++) {
                if (transposed_gem->at(temp_row, column) != 0) {
                    transposed_gem->swap_rows(column, temp_row);
                    transposed_identity->swap_rows(column, temp_row);
                    break;
                }
            }
        }
        for (int temp_row = column + 1; temp_row < transposed_gem->getSize().first; temp_row++){
            if (transposed_gem->at(temp_row, column) == 0)
                continue;
            transposed_gem->subtractTwoRows(temp_row, column, transposed_gem->at(temp_row, column) / transposed_gem->at(column, column));
            transposed_identity->subtractTwoRows(temp_row, column, transposed_identity->at(temp_row, column) / transposed_identity->at(column, column));
        }
    }

    for (int pos = 0; pos < transposed_identity->getSize().first; pos++){
        transposed_identity->multiplyRowByScalar(pos, 1 / transposed_gem->at(pos, pos));
    }

    return transposed_identity;

}

std::shared_ptr<Matrix> SparseMatrix::gaussEliminate (bool withComments) const {

    SparseMatrix gem_matrix = SparseMatrix(*this);

    int swap_counts = 0;
    if (withComments) {
        std::cout << "Matrix before GEM:" << std::endl;
        gem_matrix.print();
    }


    for (int column = 0; column < gem_matrix.getSize().second; column++){
        if(gem_matrix.isColumnNull(column))
            continue;
        if (gem_matrix.at(column, column) == 0) {
            for (int temp_row = column + 1; temp_row < gem_matrix.getSize().first; temp_row++) {
                if (gem_matrix.at(temp_row, column) != 0) {
                    gem_matrix.swap_rows(column, temp_row);
                    swap_counts++;
                    if (withComments) {
                        std::cout << "Swapping rows r" << column + 1 << " and r" << temp_row + 1 << std::endl;
                        gem_matrix.print();
                        std::cout << std::endl;
                    }
                    break;
                }
            }
        }
        for (int temp_row = column + 1; temp_row < gem_matrix.getSize().first; temp_row++){
            if (gem_matrix.at(temp_row, column) == 0)
                continue;
            if (withComments) {
                std::cout << "Subtract the " << gem_matrix.at(temp_row, column) / gem_matrix.at(column, column)
                          << " * r" << column + 1 << " from r" << temp_row + 1 << std::endl;
            }
            gem_matrix.subtractTwoRows(temp_row, column, gem_matrix.at(temp_row, column) / gem_matrix.at(column, column));
            if (withComments) {
                gem_matrix.print();
                std::cout << std::endl;
            }
        }
    }

    if (swap_counts % 2 == 1)
        gem_matrix.multiplyRowByScalar(0, -1);

    return gem_matrix.clone();

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
        if (temp_res != 0) {
            this->matrix[std::make_pair(first, column)] = temp_res;
            this->setOutputWidth(temp_res);
        }
    }
}

void SparseMatrix::multiplyRowByScalar(int row, Fraction scalar) {
    for (int column = 0; column < this->getSize().second; column++)
        if (this->at(row, column) != 0)
            this->setCellValue(row, column, this->at(row, column) * scalar);
}

std::shared_ptr<Matrix> SparseMatrix::transposition() const {
    SparseMatrix transposed = SparseMatrix(this->getSize().first, this->getSize().second, this->getMSparsity());

    for (int row = 0; row < this->getSize().first; row++) {
        for (int column = 0; column < this->getSize().second; column++) {
            if (this->at(row, column) != 0)
                transposed.setCellValue(column, row, this->at(row, column));
        }
    }

    return transposed.clone();
}
