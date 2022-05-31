#pragma once

#include <map>
#include "InputReader.h"

class Calculator {
    std::map<std::string, std::shared_ptr<Matrix>> variables;
public:
    void run();

    void calculate();

};
