#include "InputReader.h"

void InputReader::readExpression() {
    return;
}

bool InputReader::parseExpression() {
    return false;
}

OPERATION InputReader::getOperation(const std::string & expr) const {
    return INVERSION;
}

std::vector<std::pair<OPERATION, std::vector<std::string>>> &InputReader::getExpressions() {
    return expressions;
}
