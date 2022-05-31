#pragma once
#include <string>
#include <vector>
#include "Matrix/Matrix.h"

class InputReader {

    std::string string_expression;

    std::vector<std::string> regex = {
            R"([\s]*(SCAN|Scan|scan)[\s]+[A-Z][\s]*\[[\s]*[1-9]+[\s]*\][\s]*\[[\s]*[1-9]+[\s]*\][\s]*)",
            R"([\s]*[A-Z][\s]*\[[\s]*[1-9]+[\s]*\][\s]*\[[\s]*[1-9]+[\s]*\][\s]*(=)[\s]*(1)[\s]*)",
            R"([\s]*[A-Z][\s]*(=)[\s]*(MERGE|Merge|merge)[\s]+[A-Z][\s]+[A-Z][\s]*)",
            R"([\s]*(GEM|Gem|gem)[\s]+[A-Z][\s]*)",
            R"([\s]*(GEM|Gem|gem)[\s]+[A-Z][\s]+(-v))",
            R"([\s]*[A-Z][\s]*(=)[\s]*(CUT|Cut|cut)[\s]+[A-Z][\s]*\[[\s]*[1-9]+[\s]*\][\s]*\[[\s]*[1-9]+[\s]*\][\s]*)",
            R"([\s]*[A-Z][\s]*(=)[\s]*(CUT|Cut|cut)[\s]+[A-Z][\s]*\[[\s]*[1-9]+[\s]*\][\s]*\[[\s]*[1-9]+[\s]*\][\s]+([\s]*\([\s]*[0-9]+[\s]*,[\s]*[0-9]+[\s]*\))[\s]*)",
            R"([\s]*(PRINT|Print|print)[\s]+[A-Z][\s]*)",
            R"([\s]*(DET|Det|det)[\s]+[A-Z][\s]*)",
            R"([\s]*(INV|Inv|inv)[\s]+[A-Z][\s]*)",
            R"([\s]*(RANK|Rank|rank)[\s]+[A-Z][\s]*)"
    };

    std::vector<std::pair<OPERATION, std::vector<std::string>>> expressions;

public:

    void readExpression();

    bool parseExpression();

    OPERATION getOperation(const std::string & expr) const;

    std::vector<std::pair<OPERATION, std::vector<std::string>>> & getExpressions();
};