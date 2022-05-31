#pragma once
#include <string>
#include <vector>
#include <map>
#include "Matrix/Matrix.h"

class InputReader {

    std::string user_input;

    int rows, columns;
    int row_from, column_from;

    char first_matrix_name;
    char second_matrix_name;
    char third_matrix_name;

    OPERATION current_operation;

    std::map<OPERATION, std::string> regex {
            {SCAN, R"([\s]*(SCAN|Scan|scan)[\s]+[A-Z][\s]*\[[\s]*[1-9]+[\s]*\][\s]*\[[\s]*[1-9]+[\s]*\][\s]*)"},
            {IDENTITY, R"([\s]*[A-Z][\s]*\[[\s]*[1-9]+[\s]*\][\s]*\[[\s]*[1-9]+[\s]*\][\s]*(=)[\s]*(1)[\s]*)"},
            {MERGE, R"([\s]*[A-Z][\s]*(=)[\s]*(MERGE|Merge|merge)[\s]+[A-Z][\s]+[A-Z][\s]*)"},
            {GEM, R"([\s]*(GEM|Gem|gem)[\s]+[A-Z][\s]*)"},
            {GEM_COMMENTED, R"([\s]*(GEM|Gem|gem)[\s]+[A-Z][\s]+(-v))"},
            {CUT_DEFAULT, R"([\s]*[A-Z][\s]*(=)[\s]*(CUT|Cut|cut)[\s]+[A-Z][\s]*\[[\s]*[1-9]+[\s]*\][\s]*\[[\s]*[1-9]+[\s]*\][\s]*)"},
            {CUT, R"([\s]*[A-Z][\s]*(=)[\s]*(CUT|Cut|cut)[\s]+[A-Z][\s]*\[[\s]*[1-9]+[\s]*\][\s]*\[[\s]*[1-9]+[\s]*\][\s]+([\s]*\([\s]*[0-9]+[\s]*,[\s]*[0-9]+[\s]*\))[\s]*)"},
            {PRINT, R"([\s]*(PRINT|Print|print)[\s]+[A-Z][\s]*)"},
            {DETERMINANT, R"([\s]*(DET|Det|det)[\s]+[A-Z][\s]*)"},
            {INVERSION, R"([\s]*(INV|Inv|inv)[\s]+[A-Z][\s]*)"},
            {RANK, R"([\s]*(RANK|Rank|rank)[\s]+[A-Z][\s]*)"},
    };

//    std::vector<std::string> regex = {
//            R"([\s]*(SCAN|Scan|scan)[\s]+[A-Z][\s]*\[[\s]*[1-9]+[\s]*\][\s]*\[[\s]*[1-9]+[\s]*\][\s]*)",
//            R"([\s]*[A-Z][\s]*\[[\s]*[1-9]+[\s]*\][\s]*\[[\s]*[1-9]+[\s]*\][\s]*(=)[\s]*(1)[\s]*)",
//            R"([\s]*[A-Z][\s]*(=)[\s]*(MERGE|Merge|merge)[\s]+[A-Z][\s]+[A-Z][\s]*)",
//            R"([\s]*(GEM|Gem|gem)[\s]+[A-Z][\s]*)",
//            R"([\s]*(GEM|Gem|gem)[\s]+[A-Z][\s]+(-v))",
//            R"([\s]*[A-Z][\s]*(=)[\s]*(CUT|Cut|cut)[\s]+[A-Z][\s]*\[[\s]*[1-9]+[\s]*\][\s]*\[[\s]*[1-9]+[\s]*\][\s]*)",
//            R"([\s]*[A-Z][\s]*(=)[\s]*(CUT|Cut|cut)[\s]+[A-Z][\s]*\[[\s]*[1-9]+[\s]*\][\s]*\[[\s]*[1-9]+[\s]*\][\s]+([\s]*\([\s]*[0-9]+[\s]*,[\s]*[0-9]+[\s]*\))[\s]*)",
//            R"([\s]*(PRINT|Print|print)[\s]+[A-Z][\s]*)",
//            R"([\s]*(DET|Det|det)[\s]+[A-Z][\s]*)",
//            R"([\s]*(INV|Inv|inv)[\s]+[A-Z][\s]*)",
//            R"([\s]*(RANK|Rank|rank)[\s]+[A-Z][\s]*)"
//    };

    std::vector<std::pair<OPERATION, std::vector<std::string>>> expressions;

public:

    InputReader();

    void readExpression();

    bool parseExpression(OPERATION operation);

    OPERATION getOperation(const std::string & expr) const;

    std::vector<std::pair<OPERATION, std::vector<std::string>>> & getExpressions();
};