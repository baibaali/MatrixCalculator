#pragma once
#include <string>
#include <vector>
#include "Matrix/Matrix.h"

class InputReader {

    std::string string_expression;

    std::vector<std::pair<OPERATION, std::vector<std::string>>> expressions;

public:

    void readExpression();

    bool parseExpression();

    OPERATION getOperation(const std::string & expr) const;

    std::vector<std::pair<OPERATION, std::vector<std::string>>> & getExpressions();
};
