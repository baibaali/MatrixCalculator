#pragma once

#include <memory>
#include "../Matrix/Matrix.h"
#include "../Matrix/SparseMatrix.h"
#include "../Matrix/DenseMatrix.h"
#include "../Fraction.h"

/**
 * Simple matrix operations manager class.
 * Class is used for executing matrix operations
 */
class MatrixOperationManager {

public:

    /**
     * Creates new Dense or Sparse matrix
     * @param rows - Matrix rows count
     * @param columns - Matrix columns count
     * @param values - Matrix elements as a vector
     * @return shared_ptr to a new instance of DenseMatrix or SparseMatrix class
     */
    static std::shared_ptr<Matrix> Create (int rows, int columns, const std::vector<Fraction> & values);

    /**
     * Creates identity matrix
     * @param rows - Matrix rows count
     * @return shared_ptr to a new instance of DenseMatrix or SparseMatrix class, that represent identity matrix
     */
    static std::shared_ptr<Matrix> CreateIdentity(int rows);

    /**
     * Matrix addition method
     * @param lhs - First matrix
     * @param rhs - Second matrix
     * @return shared_ptr to a new instance of (Dense/Sparse)Matrix class, that is the result of addition
     */
    static std::shared_ptr<Matrix> MatrixAddition (const std::shared_ptr<Matrix> lhs, const std::shared_ptr<Matrix> rhs);

    /**
    * Matrix subtraction method
    * @param lhs - Matrix from which subtract
    * @param rhs - Matrix, that will be subtracted
    * @return shared_ptr to a new instance of (Dense/Sparse)Matrix class, that is the result of subtraction
    */
    static std::shared_ptr<Matrix> MatrixSubtraction (const std::shared_ptr<Matrix> lhs, const std::shared_ptr<Matrix> rhs);

    /**
    * Matrix multiplication by matrix method
    * @param lhs - First matrix
    * @param rhs - Second matrix
    * @return shared_ptr to a new instance of (Dense/Sparse)Matrix class, that is the result of multiplication
    */
    static std::shared_ptr<Matrix> MatrixMultiplication (const std::shared_ptr<Matrix> lhs, const std::shared_ptr<Matrix> rhs);

    /**
    * Matrix multiplication by scalar method
    * @param mtrx - First matrix
    * @param scalar - Scalar value
    * @return shared_ptr to a new instance of (Dense/Sparse)Matrix class, that is the result of multiplication
    */
    static std::shared_ptr<Matrix> MatrixMultiplication (const std::shared_ptr<Matrix> mtrx, Fraction scalar);

    /**
     * Finds matrix inversion
     * @param mtrx - Matrix to be inverted
     * @return shared_ptr to a new instance of (Dense/Sparse)Matrix class, that is the result of inversion
     */
    static std::shared_ptr<Matrix> MatrixInversion (const std::shared_ptr<Matrix> mtrx);

    /**
     * Finds matrix determinant
     * @param mtrx - Matrix
     * @return Matrix determinant
     */
    static Fraction MatrixDeterminant (const std::shared_ptr<Matrix> mtrx);

    /**
     * Finds matrix rannk
     * @param mtrx - Matrix
     * @return Matrix rank
     */
    static int MatrixRank (const std::shared_ptr<Matrix> mtrx);

    /**
     * Convert matrix into Upper Triangular Form
     * @param mtrx - Matrix to be converted
     * @param withComments - Flag, that represents if comments should be provided
     * @return shared_ptr to a new instance of (Dense/Sparse)Matrix class, that is the result of GEM
     */
    static std::shared_ptr<Matrix> MatrixGem (const std::shared_ptr<Matrix> mtrx, bool withComments);

    /**
     * Merge one matrix down to the other matrix.
     * Result matrix is matrix that has (count of rows of first matrix + count of rows of second matrix) rows and same columns count as the original matrix.
     * Second matrix is upended down to the first one
     * @param lhs - First matrix
     * @param rhs - Second matrix
     * @return shared_ptr to a new instance of (Dense/Sparse)Matrix class, that is the result of merge operation
     */
    static std::shared_ptr<Matrix> MatrixMergeByRows (const std::shared_ptr<Matrix> lhs, const std::shared_ptr<Matrix> rhs);

    /**
     * Merge one matrix to the right side of the other matrix.
     * Result matrix is matrix that has (count of columns of first matrix + count of columns of second matrix) columns and same rows count as the original matrix.
     * Second matrix is upended right to the first one
     * @param lhs - First matrix
     * @param rhs - Second matrix
     * @return shared_ptr to a new instance of (Dense/Sparse)Matrix class, that is the result of merge operation
     */
    static std::shared_ptr<Matrix> MatrixMergeByColumns (const std::shared_ptr<Matrix> lhs, const std::shared_ptr<Matrix> rhs);

    /**
     * Cut the sub-matrix from a given matrix
     * @param mtrx - Matrix to cut from
     * @param pos - From which position starts cutting
     * @param size - The size of the result sub-matrix
     * @return shared_ptr to a new instance of (Dense/Sparse)Matrix class, that is the result of cut operation
     */
    static std::shared_ptr<Matrix> MatrixCut (const std::shared_ptr<Matrix> mtrx, std::pair <int, int> pos, std::pair<int, int> size);

private:

    /**
     * Creates instance of SparseMatrix or DenseMatrix based on matrix sparsity
     * @param values - Matrix elements as vector
     * @param rows - Matrix rows count
     * @param columns - Matrix columns count
     * @param sparsity - Matrix sparsity
     * @return shared_ptr to a new instance of (Dense/Sparse)Matrix class
     */
    static std::shared_ptr<Matrix> createMatrixBasedOnSparsity(const std::vector<Fraction> & values, int rows, int columns, double sparsity);
};
