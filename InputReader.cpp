#include <iostream>
#include "InputReader.h"
#include <regex>

InputReader::InputReader() {
    rows = columns = 0;
    first_matrix_name = second_matrix_name = 0;
    current_operation = NONE;
};

void InputReader::readExpression() {
    std::cout << "Input expression:" << std::endl;

    std::regex scan;

    std::getline( std::cin, user_input );

    for (auto & exp : regex)
    {
        scan = std::regex(exp.second);
        if (std::regex_match(user_input, scan)) {
//            std::cout << std::to_string(exp.first) << std::endl;
            parseExpression(exp.first);
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

bool InputReader::parseExpression(OPERATION operation) {
    std::cout << "Parsing expression..." << std::endl;
    switch (operation) {
        case NONE:
            current_operation = NONE;
            std::cout << "Pattern doesn't match" << std::endl;
            break;
        case SCAN:
            current_operation = SCAN;
            sscanf(user_input.c_str(), " SCAN %c [ %d ] [ %d ]", &first_matrix_name, &rows, &columns);
            printf("SCAN %c[%d][%d]\n", first_matrix_name, rows, columns);
            break;
        case IDENTITY:
            sscanf(user_input.c_str(), " %c [ %d ] [ %d ] = 1", &first_matrix_name, &rows, &columns);
            printf("%c[%d][%d] = 1\n", first_matrix_name, rows, columns);
            break;
        case MERGE:
            if ( sscanf(user_input.c_str(), " %c = MERGE %c %c", &first_matrix_name, &second_matrix_name, &third_matrix_name) != 3 )
                if (sscanf(user_input.c_str(), " %c = Merge %c %c", &first_matrix_name, &second_matrix_name, &third_matrix_name) != 3)
                    sscanf(user_input.c_str(), " %c = merge %c %c", &first_matrix_name, &second_matrix_name, &third_matrix_name);
            printf("%c = MERGE %c %c\n", first_matrix_name, second_matrix_name, third_matrix_name);
            break;
        case GEM:
            if ( sscanf(user_input.c_str(), " GEM %c", &first_matrix_name) != 1 )
                if (sscanf(user_input.c_str(), " Gem %c", &first_matrix_name) != 1)
                    sscanf(user_input.c_str(), " gem %c", &first_matrix_name);
            printf("GEM %c\n", first_matrix_name);
            break;
        case GEM_COMMENTED:
            if ( sscanf(user_input.c_str(), " GEM %c -v", &first_matrix_name) != 1 )
                if (sscanf(user_input.c_str(), " Gem %c -v", &first_matrix_name) != 1)
                    sscanf(user_input.c_str(), " gem %c -v", &first_matrix_name);
            printf("GEM %c -v\n", first_matrix_name);
            break;
        case CUT_DEFAULT:
            if ( sscanf(user_input.c_str(), " %c = CUT %c [ %d ] [ %d ]", &first_matrix_name, &second_matrix_name, &rows, &columns) != 4 )
                if ( sscanf(user_input.c_str(), " %c = Cut %c [ %d ] [ %d ]", &first_matrix_name, &second_matrix_name, &rows, &columns) != 4 )
                    sscanf(user_input.c_str(), " %c = cut %c [ %d ] [ %d ]", &first_matrix_name, &second_matrix_name, &rows, &columns);
            printf("%c = CUT %c[%d][%d]\n", first_matrix_name, second_matrix_name, rows, columns);
            break;
        case CUT:
            if ( sscanf(user_input.c_str(), " %c = CUT %c [ %d ] [ %d ] ( %d , %d )", &first_matrix_name, &second_matrix_name, &rows, &columns, &row_from, &column_from) != 6 )
                if ( sscanf(user_input.c_str(), " %c = Cut %c [ %d ] [ %d ] ( %d , %d )", &first_matrix_name, &second_matrix_name, &rows, &columns, &row_from, &column_from) != 6 )
                    sscanf(user_input.c_str(), " %c = cut %c [ %d ] [ %d ] ( %d , %d )", &first_matrix_name, &second_matrix_name, &rows, &columns, &row_from, &column_from);
            printf("%c = CUT %c[%d][%d] (%d,%d)\n", first_matrix_name, second_matrix_name, rows, columns, row_from, column_from);
            break;
        case PRINT:
            if ( sscanf(user_input.c_str(), " PRINT %c", &first_matrix_name) != 1 )
                if (sscanf(user_input.c_str(), " Print %c", &first_matrix_name) != 1)
                    sscanf(user_input.c_str(), " print %c", &first_matrix_name);
            printf("PRINT %c\n", first_matrix_name);
            break;
        case DETERMINANT:
            if ( sscanf(user_input.c_str(), " DET %c", &first_matrix_name) != 1 )
                if (sscanf(user_input.c_str(), " Det %c", &first_matrix_name) != 1)
                    sscanf(user_input.c_str(), " det %c", &first_matrix_name);
            printf("DET %c\n", first_matrix_name);
            break;
        case INVERSION:
            if ( sscanf(user_input.c_str(), " INV %c", &first_matrix_name) != 1 )
                if (sscanf(user_input.c_str(), " Inv %c", &first_matrix_name) != 1)
                    sscanf(user_input.c_str(), " inv %c", &first_matrix_name);
            printf("INV %c\n", first_matrix_name);
            break;
        case RANK:
            if ( sscanf(user_input.c_str(), " RANK %c", &first_matrix_name) != 1 )
                if (sscanf(user_input.c_str(), " Rank %c", &first_matrix_name) != 1)
                    sscanf(user_input.c_str(), " rank %c", &first_matrix_name);
            printf("RANK %c\n", first_matrix_name);
            break;
    }
    return false;
}

OPERATION InputReader::getOperation(const std::string & expr) const {
    return INVERSION;
}

std::vector<std::pair<OPERATION, std::vector<std::string>>> &InputReader::getExpressions() {
    return expressions;
}
