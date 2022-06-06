#pragma once

#include <memory>
#include <vector>
#include "../Fraction.h"

/**
 * Enum of calculator's states
 */
enum OPERATION {
    NONE,
    SCAN,
    SCANF,
    SAVE,
    ASSIGN,
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    MULTIPLICATION_BY_SCALAR,
    INVERSION,
    DETERMINANT,
    RANK,
    MERGE_BY_ROWS,
    MERGE_BY_COLUMNS,
    CUT_DEFAULT,
    CUT,
    GEM,
    GEM_COMMENTED,
    IDENTITY,
    PRINT,
    EXIT
};

/**
 * Abstract matrix class
 */
class Matrix {
    std::pair <int, int> size;
    int output_width;
    double m_sparsity;
public:

    /**
     * Default constructor
     */
    Matrix();

    /**
     * Constructor
     * @param rows - Matrix rows count
     * @param columns - Matrix columns count
     * @param output_width - Width of each element of matrix to print
     * @param m_sparsity - Sparsity of a matrix
     */
    Matrix(int rows, int columns, int output_width, double m_sparsity);

    /**
     * Clone method
     * @return shared_ptr to Dense or Sparse matrix
     */
    virtual std::shared_ptr<Matrix> clone() const = 0;

    /**
     * Matrix addition
     * @param lhs - First matrix
     * @param rhs - Second matrix
     * @return New matrix, that is the result of addition
     */
    friend std::shared_ptr<Matrix> operator+(const std::shared_ptr<Matrix> lhs, const std::shared_ptr<Matrix> rhs);

    /**
     * Matrix subtraction
     * @param lhs - First matrix
     * @param rhs - Second matrix
     * @return New matrix, that is the result of subtraction
     */
    friend std::shared_ptr<Matrix> operator-(const std::shared_ptr<Matrix> lhs, const std::shared_ptr<Matrix> rhs);

    /**
     * Multiplication by matrix
     * @param lhs - First matrix
     * @param rhs - Second matrix
     * @return New matrix, that is the result of multiplication
     */
    friend std::shared_ptr<Matrix> operator* (const std::shared_ptr<Matrix> lhs, const std::shared_ptr<Matrix> rhs);

    /**
     * Multiplication by scalar
     * @param lhs - Matrix
     * @param scalar - Scalar value
     * @return New matrix, that is the result of multiplication
     */
    friend std::shared_ptr<Matrix> operator* (const std::shared_ptr<Matrix> lhs, Fraction scalar);

    /**
     * Addition method, that used in operator+
     * @param other - The second matrix of addition
     * @return Result matrix elements as a vector of Fractions
     */
    std::vector<Fraction> add (const std::shared_ptr<Matrix> other) const;

    /**
     * Addition method, that used in operator-
     * @param other - The second matrix of subtraction
     * @return Result matrix elements as a vector of Fractions
     */
    std::vector<Fraction> subtract (const std::shared_ptr<Matrix> other) const;

    /**
     * Multiplication by matrix method, that used in operator*
     * @param other - The second matrix of multiplication
     * @return Result matrix elements as a vector of Fractions
     */
    std::vector<Fraction> multiply (const std::shared_ptr<Matrix> other) const;

    /**
     * Multiplication by scalar method, that used in operator*
     * @param scalar - The scalar value
     * @return Result matrix elements as a vector of Fractions
     */
    virtual std::shared_ptr<Matrix> multiply (Fraction scalar) const = 0;

    /**
     * Finds inversion of a matrix
     * @return New matrix, that is the result of an inversion
     */
    virtual std::shared_ptr<Matrix> inversion () const = 0;

    /**
     * Transpose matrix
     * @return New matrix, that is the result of a transposition
     */
    virtual std::shared_ptr<Matrix> transposition () const = 0;

    /**
     * Finds the determinant of a matrix
     * @return Matrix determinant
     */
    Fraction determinant () const;

    /**
     * Finds the rank of a matrix
     * @return
     */
    int rank () const;

    /**
     * Converts matrix into an Upper Triangular Form
     * @param withComments - Flag, that shows if comments should be displayed
     * @return New matrix in Upper Triangular form
     */
    virtual std::shared_ptr<Matrix> gaussEliminate (bool withComments) const = 0;

    /**
     * Merge one matrix down to the other
     * @param other - Second matrix to be merged
     * @return New matrix, that is the result of merge operation
     */
    std::vector<Fraction> merge_by_rows (const std::shared_ptr<Matrix> other) const;

    /**
     * Merge one matrix to the left of the other
     * @param other - Second matrix to be merged
     * @return New matrix, that is the result of merge operation
     */
    std::vector<Fraction> merge_by_columns (const std::shared_ptr<Matrix> other) const;

    /**
     * Cuts the sub-matrix from this matrix
     * @param pos - Represents row and column of a matrix from which we starts cutting
     * @param m_size - Represents the size of sub-matrix
     * @return New matrix of size m_size, that is the result of cut operation
     */
    std::vector<Fraction> cut (std::pair<int, int> pos, std::pair<int, int> m_size) const;

    /**
     * Returns matrix elements as a vector of Fractions
     * @return Vector of matrix elements
     */
    std::vector<Fraction> getMatrixElementsAsVector () const;

    /**
     * Makes identity matrix from this matrix
     */
    virtual void makeIdentity() = 0;

    /**
     * Returns the size of a matrix
     * @return Size of a matrix
     */
    std::pair <int, int> getSize() const;

    /**
     * Returns the sparsity of a matrix (ratio of zero values of matrix to non-zero)
     * @param matrix_elements - The vector of matrix elements
     * @param elements_count - Count of matrix elements
     * @return Matrix sparsity
     */
    static double sparsity(const std::vector<Fraction> & matrix_elements, int elements_count);

    /**
     * Used to calculate the sparsity of an identity or diagonal matrix
     * @param rows - Matrix rows count
     * @param columns - Matrix columns count
     * @return Matrix sparsity
     */
    static double sparsity(int rows, int columns);

    /**
     * Print matrix
     * @param os - Output stream
     * @param decorated - Flag, that represents if decorated symbols should be displayed
     */
    void print(std::ostream & os, bool decorated) const;

    /**
     * Returns the max width of matrix elements (used for print)
     * @return Width of matrix elements
     */
    int getOutputWidth() const;

    /**
     * Sets the width of matrix elements
     * @param number
     */
    void setOutputWidth(const Fraction & number);

    /**
     * Returns the matrix sparsity
     * @return Matri sparsity
     */
    double getMSparsity() const;

    /**
     * Sets the matrix sparsity
     * @param mSparsity - New value of a sparsitu
     */
    void setMSparsity(double mSparsity);

    /**
     * Returns the element of a matrix on a given position
     * @param row - Element's row position
     * @param column - Element's column position
     * @return Element on a given position
     */
    virtual Fraction at(int row, int column) const = 0;

    /**
     * Checks if all elements in a given column are zeroes
     * @param column - Column number
     * @return True, if all elements in a column are zeroes, otherwise false
     */
    bool isColumnNull (int column) const;

    /**
     * Checks if all elements in a given row are zeroes
     * @param row - Row number
     * @return True, if all elements in a row are zeroes, otherwise false
     */
    bool isRowNull (int row) const;

    /**
     * Swaps to rows in a matrix
     * @param first - First row number
     * @param second - Second row number
     */
    void swap_rows(int first, int second);

    /**
     * Assignee a zero value into the matrix element on the given position (Changes the current matrix)
     * @param row - Row number
     * @param column - Column number
     */
    virtual void makeCellNull(int row, int column) = 0;

    /**
     * Assignee a given value into the matrix element on the given position (Changes the current matrix)
     * @param row - Row number
     * @param column - Column number
     * @param value - Value, that will be assigned
     */
    virtual void setCellValue(int row, int column, const Fraction value) = 0;

    /**
     * Subtract the second row from a first row multiple times (Changes the current matrix)
     * @param first - The row from which subtract
     * @param second - The row to be subtracted
     * @param multiple - How much times the second row will be subtracted from the first row
     */
    virtual void subtractTwoRows(int first, int second, const Fraction multiple) = 0;

    /**
     * Multiplies the given row by a scalar (Changes the current matrix)
     * @param row - Row number
     * @param scalar - Scalar value
     */
    virtual void multiplyRowByScalar(int row, Fraction scalar) = 0;

    /**
     * Prints the given count of whitespaces (used to print matrix elements)
     * @param width - Width of a current element
     * @param max_width - Maximum width of element in a matrix
     * @param ostream - Output stream to print in
     */
    void print_ws(int width, int max_width, std::ostream & ostream) const;

};
