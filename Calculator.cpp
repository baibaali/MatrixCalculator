#include <iostream>
#include <utility>
#include "Calculator.h"
#include "MatrixOperations/MatrixOperationManager.h"
#include "Fraction.h"

void Calculator::run() {

    Fraction a(1,4);
    Fraction b(3,7);

    Fraction c = a * b;
    Fraction d = a + b;
    Fraction e = a - b;
    Fraction f = a / b;

    std::cout << a << " * " << b << " = " << c << std::endl
              << a << " + " << b << " = " << d << std::endl
              << a << " - " << b << " = " << e << std::endl
              << a << " / " << b << " = " << f << std::endl;

    Fraction g = a * 4;
    Fraction h = 4 * a;

    std::cout << a << " * 4 = " << g << std::endl;
    std::cout << "4 * " << a << " = " << h << std::endl;

    Fraction i = b * 7;
    Fraction j = 7 * b;

    std::cout << b << " * 7 = " << i << std::endl;
    std::cout << "7 * " << b << " = " << j << std::endl;
//    while (true) {
//        inputReader.readExpression();
//        if (calculate())
//            break;
//        inputReader.reset();
//        std::cout << "Calculating finished." << std::endl << std::endl;
//    }
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
    double value;
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
    //TODO: check for valid sizes
    auto lhs = this->variables.find(inputReader.getSecondMatrixName());
    auto rhs = this->variables.find(inputReader.getThirdMatrixName());

    //TODO: exception here
    if (lhs == variables.end() || rhs == variables.end())
        return;

    this->variables[inputReader.getFirstMatrixName()] = lhs->second * rhs->second;
}
