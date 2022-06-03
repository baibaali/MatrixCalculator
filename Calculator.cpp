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
        default:
            break;
    }
}

void Calculator::addNewVariable(char name, std::shared_ptr<Matrix> matrix) {
    this->variables[name] = std::move(matrix);
}

