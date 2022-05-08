#pragma once

#include <map>
#include "InputReader.h"

class Calculator {
    std::map<std::string, Matrix> variables;
public:
    void run();

    void calculate();

};
