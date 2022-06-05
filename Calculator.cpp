#include <iostream>
#include <utility>
#include "Calculator.h"
#include "MatrixOperations/MatrixOperationManager.h"
#include "Fraction.h"
#include "Exception.h"

void Calculator::run() {

    std::cout << std::endl;
    while (true) {
        try {
            inputReader.readExpression();
            if (calculate())
                break;
            inputReader.reset();
        } catch (Exception & ex) {
            std::cout << ex.what() << std::endl;
        }
//        std::cout << "Calculating finished." << std::endl << std::endl;
        std::cout << "--------------------------------------------------------------------------------" << std::endl << std::endl;
    }
}

bool Calculator::calculate() {
//    std::cout << "Calculating..." << std::endl;
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
            throw Exception("Unknown command");
    }
}

void Calculator::addNewVariable() {
    if (inputReader.getRows() <= 0 || inputReader.getColumns() <= 0)
        throw Exception("ERROR: Matrix rows and columns size value can be only a positive integer");

    readMatrixValues(inputReader.getRows() * inputReader.getColumns());
    std::shared_ptr<Matrix> matrix = MatrixOperationManager::Create(inputReader.getRows(), inputReader.getColumns(),matrix_values);
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
        throw Exception("ERROR: Matrix with specified name wasn't found");
}

void Calculator::createIdentityMatrix() {
    //TODO: check for n*n size
    if (inputReader.getRows() != inputReader.getColumns())
        throw Exception("ERROR: Identity matrix should be a square (has size N x N)");
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
    if (lhs == variables.end())
        throw Exception("ERROR: Matrix with name " + std::to_string(inputReader.getSecondMatrixName()) + " doesn't exists");
    if (rhs == variables.end())
        throw Exception("ERROR: Matrix with name " + std::to_string(inputReader.getThirdMatrixName()) + " doesn't exists");


    if (lhs->second->getSize().second != rhs->second->getSize().second)
        throw Exception("ERROR: Matrices should have same column size for this operation");

    this->variables[inputReader.getFirstMatrixName()] =
            MatrixOperationManager::MatrixMergeByRows(lhs->second,rhs->second);

}

void Calculator::mergeByColumns() {
    //TODO: check for existing matrices
    //TODO: check for valid sizes of matrices
    auto lhs = this->variables.find(inputReader.getSecondMatrixName());
    auto rhs = this->variables.find(inputReader.getThirdMatrixName());

    //TODO: exception here
    if (lhs == variables.end())
        throw Exception("ERROR: Matrix with name " + std::to_string(inputReader.getSecondMatrixName()) + " doesn't exists");
    if (rhs == variables.end())
        throw Exception("ERROR: Matrix with name " + std::to_string(inputReader.getThirdMatrixName()) + " doesn't exists");


    if (lhs->second->getSize().first != rhs->second->getSize().first)
        throw Exception("ERROR: Matrices should have same row size for this operation");

    this->variables[inputReader.getFirstMatrixName()] =
            MatrixOperationManager::MatrixMergeByColumns(lhs->second,rhs->second);

}

void Calculator::cut() {
    //TODO: check for valid sizes

    auto mtrx = this->variables.find(inputReader.getSecondMatrixName());

    //TODO: exception here
    if (mtrx == variables.end())
        throw Exception("ERROR: Matrix with name " + std::to_string(inputReader.getSecondMatrixName()) + " doesn't exists");


    if (inputReader.getRowFrom() < 0 || inputReader.getRowFrom() >= mtrx->second->getSize().first)
        throw Exception("ERROR: Position out of range");
    if (inputReader.getColumnFrom() < 0 || inputReader.getColumnFrom() >= mtrx->second->getSize().second)
        throw Exception("ERROR: Position out of range");

    if (inputReader.getRows() <= 0 || inputReader.getColumns() <= 0)
        throw Exception("ERROR: Matrix rows and columns size value can be only a positive integer");

    if (inputReader.getRows() > mtrx->second->getSize().first - inputReader.getRowFrom())
        throw Exception("ERROR: Too large size of the final matrix");
    if (inputReader.getColumns() > mtrx->second->getSize().second - inputReader.getColumnFrom())
        throw Exception("ERROR: Too large size of the final matrix");

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

    if (lhs == variables.end())
        throw Exception("ERROR: Matrix with name " + std::to_string(inputReader.getSecondMatrixName()) + " doesn't exists");
    if (rhs == variables.end())
        throw Exception("ERROR: Matrix with name " + std::to_string(inputReader.getThirdMatrixName()) + " doesn't exists");

    if (lhs->second->getSize().first != rhs->second->getSize().first ||
        lhs->second->getSize().second != rhs->second->getSize().second)
        throw Exception("ERROR: Matrix sizes do not match");

    this->variables[inputReader.getFirstMatrixName()] = lhs->second + rhs->second;
}

void Calculator::subtraction() {
    //TODO: check for existing matrices
    //TODO: check for valid sizes of matrices
    auto lhs = this->variables.find(inputReader.getSecondMatrixName());
    auto rhs = this->variables.find(inputReader.getThirdMatrixName());

    if (lhs == variables.end())
        throw Exception("ERROR: Matrix with name " + std::to_string(inputReader.getSecondMatrixName()) + " doesn't exists");
    if (rhs == variables.end())
        throw Exception("ERROR: Matrix with name " + std::to_string(inputReader.getThirdMatrixName()) + " doesn't exists");

    if (lhs->second->getSize().first != rhs->second->getSize().first ||
        lhs->second->getSize().second != rhs->second->getSize().second)
        throw Exception("ERROR: Matrix sizes do not match");

    this->variables[inputReader.getFirstMatrixName()] = lhs->second - rhs->second;
}

void Calculator::multiplicationByScalar() {
    auto mtrx = this->variables.find(inputReader.getSecondMatrixName());

    //TODO: exception here
    if (mtrx == variables.end())
        throw Exception("ERROR: Matrix with name " + std::to_string(inputReader.getFirstMatrixName()) + " doesn't exists");

    this->variables[inputReader.getFirstMatrixName()] = mtrx->second * inputReader.getScalar();
}

void Calculator::multiplication() {
    //TODO: check scalar for non-null denominator
    //TODO: check for valid sizes
    auto lhs = this->variables.find(inputReader.getSecondMatrixName());
    auto rhs = this->variables.find(inputReader.getThirdMatrixName());

    if (lhs == variables.end())
        throw Exception("ERROR: Matrix with name " + std::to_string(inputReader.getSecondMatrixName()) + " doesn't exists");
    if (rhs == variables.end())
        throw Exception("ERROR: Matrix with name " + std::to_string(inputReader.getThirdMatrixName()) + " doesn't exists");

    if (lhs->second->getSize().second != rhs->second->getSize().first)
        throw Exception("ERROR: Matrix sizes do not match");

    this->variables[inputReader.getFirstMatrixName()] = lhs->second * rhs->second;
}

void Calculator::gem(bool withComments) {
    //TODO: check for valid size n*n
    auto mtrx = this->variables.find(inputReader.getFirstMatrixName());

    //TODO: exception here
    if (mtrx == variables.end())
        throw Exception("ERROR: Matrix with name " + std::to_string(inputReader.getFirstMatrixName()) + " doesn't exists");

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
        throw Exception("ERROR: Matrix with name " + std::to_string(inputReader.getFirstMatrixName()) + " doesn't exists");

    if (mtrx->second->getSize().first != mtrx->second->getSize().second)
        throw Exception("ERROR: Matrix should be square (has size N x N)");

    auto result = MatrixOperationManager::MatrixDeterminant(mtrx->second);
    std::cout << "Matrix determinant is: " << result << std::endl;
}

void Calculator::rank() {
    auto mtrx = this->variables.find(inputReader.getFirstMatrixName());

    if (mtrx == variables.end())
        throw Exception("ERROR: Matrix with name " + std::to_string(inputReader.getFirstMatrixName()) + " doesn't exists");

    auto result = MatrixOperationManager::MatrixRank(mtrx->second);
    std::cout << "Matrix rank is: " << result << std::endl;
}

void Calculator::inversion() {
    auto mtrx = this->variables.find(inputReader.getFirstMatrixName());

    if (mtrx == variables.end())
        throw Exception("ERROR: Matrix with name " + std::to_string(inputReader.getFirstMatrixName()) + " doesn't exists");

    if (mtrx->second->getSize().first != mtrx->second->getSize().second)
        throw Exception("ERROR: Matrix should be square (has size N x N)");

    auto result = MatrixOperationManager::MatrixInversion(mtrx->second);
    std::cout << "Matrix inversion is: " << std::endl;
    result->print();
}
