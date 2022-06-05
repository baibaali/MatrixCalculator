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

    DenseMatrix gem_matrix = DenseMatrix(*this);
    DenseMatrix identity = DenseMatrix(*this);
    identity.makeIdentity();

    std::cout << "++++++++++"<<std::endl;
    identity.print();
    std::cout << "++++++++++"<<std::endl;
    Fraction multiply;
    for (int column = 0; column < gem_matrix.getSize().second; column++){
        if(gem_matrix.isColumnNull(column))
            continue;
        if (gem_matrix.at(column, column) == 0) {
            for (int temp_row = column + 1; temp_row < gem_matrix.getSize().first; temp_row++) {
                if (gem_matrix.at(temp_row, column) != 0) {
                    gem_matrix.swap_rows(column, temp_row);
                    identity.swap_rows(column, temp_row);

                    std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
                    gem_matrix.print();
                    std::cout << std::endl;
                    identity.print();
                    std::cout << std::endl;
                    std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;

                    break;
                }
            }
        }

        multiply = 1 / gem_matrix.at(column, column);
        gem_matrix.multiplyRowByScalar(column, multiply);
        identity.multiplyRowByScalar(column, multiply);

        std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
        gem_matrix.print();
        std::cout << std::endl;
        identity.print();
        std::cout << std::endl;
        std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;

        for (int temp_row = column + 1; temp_row < gem_matrix.getSize().first; temp_row++){
            if (gem_matrix.at(temp_row, column) == 0)
                continue;
            Fraction multiply = gem_matrix.at(temp_row, column) / gem_matrix.at(column, column);
            gem_matrix.subtractTwoRows(temp_row, column, multiply);
            identity.subtractTwoRows(temp_row, column, multiply);

            std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
            gem_matrix.print();
            std::cout << std::endl;
            identity.print();
            std::cout << std::endl;
            std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
        }

    }

    for (int column = gem_matrix.getSize().second - 1; column >= 0; column--){
        if (gem_matrix.at(column, column) == 0) {
            std::cout << "Inversion doesn't exists" << std::endl;
            break;
        }
        for (int temp_row = column - 1; temp_row >= 0; temp_row--){
            if (gem_matrix.at(temp_row, column) == 0)
                continue;
            Fraction multiply = gem_matrix.at(temp_row, column) / gem_matrix.at(column, column);
            gem_matrix.subtractTwoRows(temp_row, column, multiply);
            identity.subtractTwoRows(temp_row, column, multiply);

            std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
            gem_matrix.print();
            std::cout << std::endl;
            identity.print();
            std::cout << std::endl;
            std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
        }
    }

    for (int pos = 0; pos < identity.getSize().first; pos++){
        Fraction scalar = 1 / gem_matrix.at(pos, pos);
        for (int column = 0; column < gem_matrix.getSize().second; column++) {
            gem_matrix.setCellValue(pos, column, gem_matrix.at(pos, column) * scalar);
            identity.setCellValue(pos, column, identity.at(pos, column) * scalar);
        }
    }

    std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
    gem_matrix.print();
    std::cout << std::endl;
    identity.print();
    std::cout << std::endl;
    std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;

    return identity.clone();
}

std::shared_ptr<Matrix> DenseMatrix::gaussEliminate(bool withComments) const {

    DenseMatrix gem_matrix = DenseMatrix(*this);

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
                    if (withComments){
                        std::cout << "Swapping rows r" << column + 1 << " and r" << temp_row + 1 << std::endl;
                        gem_matrix.print();
                        std::cout << std::endl;
                    }
                    break;
                }
            }
        }
        for (int temp_row = column + 1; temp_row < gem_matrix.getSize().first; temp_row++) {
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

//    for (int i = 1; i < gem_matrix.getSize().first; i++){
//        if (gem_matrix.isRowNull(i - 1)) {
//            for (int j = i; j < gem_matrix.getSize().first; j++){
//                if (!gem_matrix.isRowNull(j)) {
//                    gem_matrix.swap_rows(i - 1, j);
//                    break;
//                }
//            }
//        }
//    }

    if (swap_counts % 2 == 1)
        gem_matrix.multiplyRowByScalar(0, -1);


    return gem_matrix.clone();

}

void DenseMatrix::makeIdentity() {
    matrix.clear();
    matrix = std::vector<std::vector<Fraction>>(this->getSize().first, std::vector<Fraction>(this->getSize().second, 0));
    for (int pos = 0; pos < this->getSize().first; pos++)
        matrix[pos][pos] = 1;
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
        this->setOutputWidth(temp_res);
    }
}

void DenseMatrix::multiplyRowByScalar(int row, Fraction scalar) {
    for (int column = 0; column < this->getSize().second; column++)
        this->setCellValue(row, column, this->at(row, column) * scalar);
}

std::shared_ptr<Matrix> DenseMatrix::transposition() const {
    DenseMatrix transposed = DenseMatrix(*this);

    for (int row = 0; row < this->getSize().first; row++) {
        for (int column = 0; column < this->getSize().second; column++) {
            transposed.setCellValue(column, row, this->at(row, column));
        }
    }

    return transposed.clone();
}



