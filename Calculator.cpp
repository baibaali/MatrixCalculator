#include <iostream>
#include <utility>
#include "Calculator.h"

void Calculator::run() {

    while (true) {
        inputReader.readExpression();
//        inputReader.parseExpression();
        calculate();
        std::cout << "Calculating finished." << std::endl << std::endl;
    }
}

void Calculator::calculate() {
    std::cout << "Calculating..." << std::endl;
    switch(inputReader.getCurrentOperation()){
        case SCAN:
            addNewVariable(inputReader.getFirstMatrixName(), inputReader.getMatrix());
            break;
        case PRINT:
            printMatrix(inputReader.getFirstMatrixName());
            break;
        default:
            break;
    }
}

void Calculator::addNewVariable(char name, std::shared_ptr<Matrix> matrix) {
    this->variables[name] = std::move(matrix);
}

void Calculator::printMatrix(char name) const {
    auto it = variables.find(name);
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

