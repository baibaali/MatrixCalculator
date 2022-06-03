#pragma once

#include <map>
#include "InputReader.h"

class Calculator {
    InputReader inputReader;
    std::map<char, std::shared_ptr<Matrix>> variables;
public:
    void run();

    void calculate();

    void addNewVariable(char name, std::shared_ptr<Matrix> matrix);

};
