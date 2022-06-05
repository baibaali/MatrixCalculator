#include <iostream>
#include <utility>
#include "Calculator.h"
#include "MatrixOperations/MatrixOperationManager.h"
#include "Fraction.h"

void Calculator::run() {

    while (true) {
        std::cout << "--------------------------------------------------------------------------------" << std::endl;
        inputReader.readExpression();
        if (calculate())
            break;
        inputReader.reset();
        std::cout << "Calculating finished." << std::endl << std::endl;
        std::cout << "--------------------------------------------------------------------------------" << std::endl;
    }
}

bool Calculator::calculate() {
    std::cout << "Calculating..." << std::endl;
    switch(inputReader.getCurrentOperation()){
        case SCAN:
            addNewVariable();
            return false;
        case PRINT:
            printMatrix();
            return false;
        case IDENTITY:
            createIdentityMatrix();
            return false;
        case MERGE_BY_ROWS:
            mergeByRows();
            return false;
        case MERGE_BY_COLUMNS:
            mergeByColumns();
            return false;
        case CUT:
        case CUT_DEFAULT:
            cut();
            return false;
        case ADDITION:
            addition();
            break;
        case SUBTRACTION:
            subtraction();
            return false;
        case MULTIPLICATION_BY_SCALAR:
            multiplicationByScalar();
            return false;
        case MULTIPLICATION:
            multiplication();
            return false;
        case GEM:
            gem(false);
            return false;
        case GEM_COMMENTED:
            gem(true);
            return false;
        case DETERMINANT:
            determinant();
            return false;
        case RANK:
            rank();
            return false;
        case INVERSION:
            inversion();
            return false;
        case EXIT:
            return true;
        default:
            return false;
    }
}

void Calculator::addNewVariable() {
    readMatrixValues(inputReader.getRows() * inputReader.getColumns());
    std::shared_ptr<Matrix> matrix = MatrixOperationManager::Create(inputReader.getRows(), inputReader.getColumns(), matrix_values);
    this->variables[inputReader.getFirstMatrixName()] = std::move(matrix);
    matrix_values.clear();
}

void Calculator::printMatrix() const {
    auto it = variables.find(inputReader.getFirstMatrixName());
    if (it != variables.end()) {
        std::cout << it->first
                  << "["
                  << it->second->getSize().first
                  << "]["
                  << it->second->getSize().second
                  << "]:"
                  << std::endl;

        it->second->print();
    }
    else
        std::cout << "Matrix with specified name doesn't exists." << std::endl;
}

void Calculator::createIdentityMatrix() {
    //TODO: check for n*n size
    this->variables[inputReader.getFirstMatrixName()] = MatrixOperationManager::CreateIdentity(inputReader.getRows());
}

void Calculator::readMatrixValues(int count) {
    Fraction value;
    for (int i = 0; i < count; i++)
    {
        std::cin >> value;
        matrix_values.push_back(value);
    }
}

void Calculator::mergeByRows() {
    //TODO: check for existing matrices
    //TODO: check for valid sizes of matrices
    auto lhs = this->variables.find(inputReader.getSecondMatrixName());
    auto rhs = this->variables.find(inputReader.getThirdMatrixName());

    //TODO: exception . here
    if (lhs == variables.end() || rhs == variables.end())
        return;

    this->variables[inputReader.getFirstMatrixName()] =
            MatrixOperationManager::MatrixMergeByRows(lhs->second,rhs->second);

}

void Calculator::mergeByColumns() {
    //TODO: check for existing matrices
    //TODO: check for valid sizes of matrices
    auto lhs = this->variables.find(inputReader.getSecondMatrixName());
    auto rhs = this->variables.find(inputReader.getThirdMatrixName());

    //TODO: exception here
    if (lhs == variables.end() || rhs == variables.end())
        return;

    this->variables[inputReader.getFirstMatrixName()] =
            MatrixOperationManager::MatrixMergeByColumns(lhs->second,rhs->second);

}

void Calculator::cut() {
    //TODO: check for valid sizes

    auto mtrx = this->variables.find(inputReader.getSecondMatrixName());

    //TODO: exception here
    if (mtrx == variables.end())
        return;

    this->variables[inputReader.getFirstMatrixName()] =
            MatrixOperationManager::MatrixCut(mtrx->second,
                                              std::make_pair(inputReader.getRowFrom(), inputReader.getColumnFrom()),
                                              std::make_pair(inputReader.getRows(), inputReader.getColumns())
                                              );

}

void Calculator::addition() {
    //TODO: check for existing matrices
    //TODO: check for valid sizes of matrices
    auto lhs = this->variables.find(inputReader.getSecondMatrixName());
    auto rhs = this->variables.find(inputReader.getThirdMatrixName());

    //TODO: exception here
    if (lhs == variables.end() || rhs == variables.end())
        return;

    this->variables[inputReader.getFirstMatrixName()] = lhs->second + rhs->second;
}

void Calculator::subtraction() {
    //TODO: check for existing matrices
    //TODO: check for valid sizes of matrices
    auto lhs = this->variables.find(inputReader.getSecondMatrixName());
    auto rhs = this->variables.find(inputReader.getThirdMatrixName());

    //TODO: exception here
    if (lhs == variables.end() || rhs == variables.end())
        return;

    this->variables[inputReader.getFirstMatrixName()] = lhs->second - rhs->second;
}

void Calculator::multiplicationByScalar() {
    auto mtrx = this->variables.find(inputReader.getSecondMatrixName());

    //TODO: exception here
    if (mtrx == variables.end())
        return;

    this->variables[inputReader.getFirstMatrixName()] = mtrx->second * inputReader.getScalar();
}

void Calculator::multiplication() {
    //TODO: check scalar for non-null denominator
    //TODO: check for valid sizes
    auto lhs = this->variables.find(inputReader.getSecondMatrixName());
    auto rhs = this->variables.find(inputReader.getThirdMatrixName());

    //TODO: exception here
    if (lhs == variables.end() || rhs == variables.end())
        return;

    this->variables[inputReader.getFirstMatrixName()] = lhs->second * rhs->second;
}

void Calculator::gem(bool withComments) {
    //TODO: check for valid size n*n
    auto mtrx = this->variables.find(inputReader.getFirstMatrixName());

    //TODO: exception here
    if (mtrx == variables.end())
        return;

    auto result = MatrixOperationManager::MatrixGem(mtrx->second, withComments);

    std::cout << "Matrix after GEM:" << std::endl;
    result->print();
    std::cout << std::endl;

}

void Calculator::determinant() {
    //TODO: check for valid size n*n
    auto mtrx = this->variables.find(inputReader.getFirstMatrixName());

    //TODO: exception here
    if (mtrx == variables.end())
        return;

    auto result = MatrixOperationManager::MatrixDeterminant(mtrx->second);
    std::cout << "Matrix determinant is: " << result << std::endl;
}

void Calculator::rank() {
    auto mtrx = this->variables.find(inputReader.getFirstMatrixName());

    //TODO: exception here
    if (mtrx == variables.end())
        return;

    auto result = MatrixOperationManager::MatrixRank(mtrx->second);
    std::cout << "Matrix rank is: " << result << std::endl;
}

void Calculator::inversion() {
    auto mtrx = this->variables.find(inputReader.getFirstMatrixName());

    //TODO: exception here
    if (mtrx == variables.end())
        return;

    auto result = MatrixOperationManager::MatrixInversion(mtrx->second);
    std::cout << "Matrix inversion is: " << std::endl;
    std::cout << result->getSize().first << " " << result->getSize().second << std::endl;
    result->print();
}
