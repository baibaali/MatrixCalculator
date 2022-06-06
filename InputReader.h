#pragma once
#include <string>
#include <vector>
#include <map>
#include "Matrix/Matrix.h"

/**
 * Reads and parse user input
 */
class InputReader {

    std::string user_input;

    int rows, columns;
    int row_from, column_from;
    Fraction scalar;
    int scalar_numerator, scalar_denominator;
    char first_matrix_name;
    char second_matrix_name;
    char third_matrix_name;

    OPERATION current_operation;

    std::map<OPERATION, std::string> regex {
            {SCAN, R"([\s]*(SCAN|Scan|scan)[\s]+[A-Z][\s]*\[[\s]*[-]?[0-9]+[\s]*\][\s]*\[[\s]*[-]?[0-9]+[\s]*\][\s]*)"},
            {SCANF, R"([\s]*(S|s)(C|c)(A|a)(N|n)(F|f)[\s]+[A-Z][\s]*)"},
            {SAVE, R"([\s]*(SAVE|Save|save)[\s]+[A-Z][\s]*)"},
            {IDENTITY, R"([\s]*[A-Z][\s]*\[[\s]*[-]?[0-9]+[\s]*\][\s]*\[[\s]*[-]?[0-9]+[\s]*\][\s]*(=)[\s]*(1)[\s]*)"},
            {MERGE_BY_ROWS, R"([\s]*[A-Z][\s]*(=)[\s]*(MERGE|Merge|merge)[\s]+(-r)[\s]+[A-Z][\s]+[A-Z][\s]*)"},
            {MERGE_BY_COLUMNS, R"([\s]*[A-Z][\s]*(=)[\s]*(MERGE|Merge|merge)[\s]+(-c)[\s]+[A-Z][\s]+[A-Z][\s]*)"},
            {GEM, R"([\s]*(GEM|Gem|gem)[\s]+[A-Z][\s]*)"},
            {GEM_COMMENTED, R"([\s]*(GEM|Gem|gem)[\s]+[A-Z][\s]+(-v))"},
            {CUT_DEFAULT, R"([\s]*[A-Z][\s]*(=)[\s]*(CUT|Cut|cut)[\s]+[A-Z][\s]*\[[\s]*[-]?[0-9]+[\s]*\][\s]*\[[\s]*[-]?[0-9]+[\s]*\][\s]*)"},
            {CUT, R"([\s]*[A-Z][\s]*(=)[\s]*(CUT|Cut|cut)[\s]+[A-Z][\s]*\[[\s]*[-]?[0-9]+[\s]*\][\s]*\[[\s]*[-]?[0-9]+[\s]*\][\s]+([\s]*\([\s]*[-]?[0-9]+[\s]*,[\s]*[-]?[0-9]+[\s]*\))[\s]*)"},
            {PRINT, R"([\s]*(PRINT|Print|print)[\s]+[A-Z][\s]*)"},
            {DETERMINANT, R"([\s]*(DET|Det|det)[\s]+[A-Z][\s]*)"},
            {INVERSION, R"([\s]*(INV|Inv|inv)[\s]+[A-Z][\s]*)"},
            {RANK, R"([\s]*(RANK|Rank|rank)[\s]+[A-Z][\s]*)"},
            {ADDITION, R"([\s]*[A-Z][\s]*(=)[\s]*[A-Z][\s]*(\+)[\s]*[A-Z][\s]*)"},
            {SUBTRACTION, R"([\s]*[A-Z][\s]*(=)[\s]*[A-Z][\s]*(\-)[\s]*[A-Z][\s]*)"},
            {SUBTRACTION, R"([\s]*[A-Z][\s]*(=)[\s]*[A-Z][\s]*(\-)[\s]*[A-Z][\s]*)"},
            {MULTIPLICATION_BY_SCALAR, R"([\s]*[A-Z][\s]*(=)[\s]*[-]?[0-9]+[\s]*(\*)[\s]*[A-Z][\s]*)"},
            {MULTIPLICATION_BY_SCALAR, R"([\s]*[A-Z][\s]*(=)[\s]*[-]?[0-9]+[\s]*(/)[\s]*[-]?[0-9](\*)[\s]*[A-Z][\s]*)"},
            {MULTIPLICATION, R"([\s]*[A-Z][\s]*(=)[\s]*[A-Z][\s]*(\*)[\s]*[A-Z][\s]*)"},
            {EXIT, R"([\s]*(EXIT|Exit|exit)[\s]*)"},
    };

public:

    /**
     * Constructor
     */
    InputReader();

    /**
     * Reads user input and trys to recognize it
     */
    void readExpression();

    /**
     * Parse the user input, and gets information from it
     * @param operation - Type of operation, that we get from readExpression() mthod
     * @return True - if successfully parsed, otherwise false
     */
    bool parseExpression(OPERATION operation);


//    OPERATION getOperation(const std::string & expr) const;

    /**
     * Reset the InputReader into initial state
     */
    void reset();

    /**
     * Returns the first matrix name from user input
     * @return First matrix name
     */
    char getFirstMatrixName() const;

    /**
     * Returns the current operation
     * @return Current operation
     */
    OPERATION getCurrentOperation() const;

    /**
     * Returns the count of rows of the matrix
     * @return Rows count
     */
    int getRows() const;

    /**
     * Returns the count of columns of the matrix
     * @return Columns count
     */
    int getColumns() const;

    /**
     * Returns the row, that was specified in cut operation as a position from which to cut
     * @return Row number
     */
    int getRowFrom() const;

    /**
     * Returns the column, that was specified in cut operation as a position from which to cut
     * @return Column number
     */
    int getColumnFrom() const;

    /**
     * Returns the second matrix name from user input
     * @return Second matrix name
     */
    char getSecondMatrixName() const;

    /**
     * Returns the third matrix name from user input
     * @return Third matrix name
     */
    char getThirdMatrixName() const;

    /**
     * Returns the scalar
     * @return Scalar
     */
    Fraction getScalar() const;
};