#pragma once

#include <vector>
#include "Matrix.h"
#include "../Fraction.h"

/**
 * Represents a dense matrix. Inherited from Matrix abstract class
 */
class DenseMatrix : public Matrix {
    std::vector<std::vector<Fraction>> matrix;
public:

    /**
     * Default constructor
     */
    DenseMatrix() = default;

    /**
     * Matrix constructor, that creates a matrix from a given values
     * @param values - Matrix elements values
     * @param rows - Matrix rows count
     * @param columns - Matrix columns count
     * @param sparsity - Matrix sparsity
     */
    DenseMatrix(const std::vector<Fraction> & values, int rows, int columns, double sparsity);

    /**
     * Matrix constructor, that creates an empty instance of a matrix, with given size
     * @param rows - Matrix rows count
     * @param columns - Matrix columns count
     * @param sparsity - Matrix sparsity
     */
    DenseMatrix(int rows, int columns, double sparsity);

    /**
     * Default destructor
     */
    ~DenseMatrix() = default;

    /**
     * Creates a shared_ptr to instance of a DenseMatrix class
     * @return shared_ptr to object of a DenseMatrix class
     */
    std::shared_ptr<Matrix> clone() const override;

    /**
     * Multiplies matrix by scalar
     * @param scalar - scalar value
     * @return The new matrix, that is the result of a multiplication
     */
    std::shared_ptr<Matrix> multiply (Fraction scalar) const override;

    /**
     * Finds matrix inversion
     * @return New matrix, that is the result of a inversion operation
     */
    std::shared_ptr<Matrix> inversion () const override;

    /**
     * Transpose the matrix
     * @return New matrix, that is the result of transposition
     */
    std::shared_ptr<Matrix> transposition () const override;

    /**
     * Convert matrix to Upper Triangle Form
     * @param withComments - Flag, that represents if comments should be displayed
     * @return New matrix, that is in Upper Triangle Form
     */
    std::shared_ptr<Matrix> gaussEliminate (bool withComments) const override;

    /**
     * Returns the element of a matrix on a given position
     * @param row - Element's row position
     * @param column - Element's column position
     * @return Element on a given position
     */
    Fraction at(int row, int column) const override;

    /**
     * Makes identity matrix from this matrix
     */
    void makeIdentity() override;

    /**
     * Assignee a zero value into the matrix element on the given position (Changes the current matrix)
     * @param row - Row number
     * @param column - Column number
     */
    void makeCellNull(int row, int column) override;

    /**
     * Assignee a given value into the matrix element on the given position (Changes the current matrix)
     * @param row - Row number
     * @param column - Column number
     * @param value - Value, that will be assigned
     */
    void setCellValue(int row, int column, const Fraction value) override;

    /**
     * Subtract the second row from a first row multiple times (Changes the current matrix)
     * @param first - The row from which subtract
     * @param second - The row to be subtracted
     * @param multiple - How much times the second row will be subtracted from the first row
     */
    void subtractTwoRows(int first, int second, const Fraction multiple) override;

    /**
     * Multiplies the given row by a scalar (Changes the current matrix)
     * @param row - Row number
     * @param scalar - Scalar value
     */
    void multiplyRowByScalar(int row, Fraction scalar) override;
};
