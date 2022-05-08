#include "Calculator.h"

void Calculator::run() {

    InputReader inputReader;

    while (true) {
        inputReader.readExpression();
        inputReader.parseExpression();
        calculate();
    }

}
