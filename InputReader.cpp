#include <iostream>
#include "InputReader.h"
#include <regex>

void InputReader::readExpression() {
    std::cout << "Input expression:" << std::endl;
    int rows, columns;
    char name;
    std::string ui; /** user input */
//    std::string exp = R"([\s]*(SCAN)[\s]+[A-Z][\s]*\[[\s]*[1-9]+[\s]*\][\s]*\[[\s]*[1-9]+[\s]*\][\s]*)";

    std::regex scan;

    std::getline( std::cin, ui );

    for (auto & exp : regex)
    {
        scan = std::regex(exp);
        if (std::regex_match(ui, scan)) {
            std::cout << exp << std::endl;
//            std::cout << ui << std::endl;
//            sscanf(ui.c_str(), " SCAN %c [ %d ] [ %d ]", &name, &rows, &columns);
//            printf("SCAN %c[%d][%d]\n", name, rows, columns);
        }
    }


//    if (std::regex_match(ui, scan)) {
////        std::cout << ui << std::endl;
//        sscanf(ui.c_str(), " SCAN %c [ %d ] [ %d ]", &name, &rows, &columns);
//        printf("SCAN %c[%d][%d]\n", name, rows, columns);
//    } else
//        std::cout << "Pattern doesn't match" << std::endl;
}

bool InputReader::parseExpression() {
    std::cout << "Parsing expression..." << std::endl;
    return false;
}

OPERATION InputReader::getOperation(const std::string & expr) const {
    return INVERSION;
}

std::vector<std::pair<OPERATION, std::vector<std::string>>> &InputReader::getExpressions() {
    return expressions;
}
