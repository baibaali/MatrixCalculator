#include <iostream>
#include "Calculator.h"

void Calculator::run() {

    InputReader inputReader;

    while (true) {
        inputReader.readExpression();
//        inputReader.parseExpression();
        calculate();
        std::cout << "Calculating finished." << std::endl << std::endl;
    }

}

void Calculator::calculate() {
    std::cout << "Calculating..." << std::endl;
}
