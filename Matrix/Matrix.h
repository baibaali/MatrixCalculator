#pragma once

#include <memory>
#include <vector>

enum OPERATION {
    NONE,
    SCAN,
    ASSIGN,
    ADDITION,
    SUBTRACTION,
    MULTIPLYING,
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

class Matrix {
    std::pair <int, int> size;
    int output_width;
    double m_sparsity;
public:

    Matrix();

    Matrix(int rows, int columns, int output_width, double m_sparsity);

    virtual std::shared_ptr<Matrix> clone() const = 0;

    std::shared_ptr<Matrix> operator+ (const Matrix & other) const;

    std::shared_ptr<Matrix> operator- (const Matrix & other) const;

    std::shared_ptr<Matrix> operator* (const Matrix & other) const;

    std::shared_ptr<Matrix> operator* (double scalar) const;

    virtual std::shared_ptr<Matrix> add (const Matrix & other) const = 0;

    virtual std::shared_ptr<Matrix> subtract (const Matrix & other) const = 0;

    virtual std::shared_ptr<Matrix> multiply (const Matrix & other) const = 0;

    virtual std::shared_ptr<Matrix> multiply (double scalar) const = 0;

    virtual std::shared_ptr<Matrix> findInversion () const = 0;

    virtual std::shared_ptr<Matrix> findDeterminant () const = 0;

    virtual std::shared_ptr<Matrix> findRank () const = 0;

    virtual std::shared_ptr<Matrix> gaussEliminate (bool withComments) const;

    virtual std::shared_ptr<Matrix> gaussEliminateCommon () const = 0;

    virtual std::shared_ptr<Matrix> gaussEliminateDescribed () const = 0;

    virtual std::vector<double> merge_by_rows (const std::shared_ptr<Matrix> other) const = 0;

    virtual std::vector<double> merge_by_columns (const std::shared_ptr<Matrix> other) const = 0;

    virtual std::shared_ptr<Matrix> cut (std::pair<int, int> pos, std::pair<int, int> size) const = 0;

    virtual std::vector<double> getMatrixElementsAsVector () const = 0;

    virtual void makeIdentity() = 0;

    std::pair <int, int> getSize() const;

    static double sparsity(const std::vector<double> & matrix_elements, int elements_count);

    static double sparsity(int rows, int columns);

    virtual void print() const = 0;

    int getOutputWidth() const;

    void setOutputWidth(double number);

    double getMSparsity() const;

    void setMSparsity(double mSparsity);
};
