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

    friend std::shared_ptr<Matrix> operator+(const std::shared_ptr<Matrix> lhs, const std::shared_ptr<Matrix> rhs);

    std::shared_ptr<Matrix> operator- (const Matrix & other) const;

    std::shared_ptr<Matrix> operator* (const Matrix & other) const;

    std::shared_ptr<Matrix> operator* (double scalar) const;

    std::vector<double> add (const std::shared_ptr<Matrix> other) const;

    virtual std::shared_ptr<Matrix> subtract (const Matrix & other) const = 0;

    virtual std::shared_ptr<Matrix> multiply (const Matrix & other) const = 0;

    virtual std::shared_ptr<Matrix> multiply (double scalar) const = 0;

    virtual std::shared_ptr<Matrix> findInversion () const = 0;

    virtual std::shared_ptr<Matrix> findDeterminant () const = 0;

    virtual std::shared_ptr<Matrix> findRank () const = 0;

    virtual std::shared_ptr<Matrix> gaussEliminate (bool withComments) const;

    virtual std::shared_ptr<Matrix> gaussEliminateCommon () const = 0;

    virtual std::shared_ptr<Matrix> gaussEliminateDescribed () const = 0;

    std::vector<double> merge_by_rows (const std::shared_ptr<Matrix> other) const;

    std::vector<double> merge_by_columns (const std::shared_ptr<Matrix> other) const;

    std::vector<double> cut (std::pair<int, int> pos, std::pair<int, int> m_size) const;

    std::vector<double> getMatrixElementsAsVector () const;

    virtual void makeIdentity() = 0;

    std::pair <int, int> getSize() const;

    static double sparsity(const std::vector<double> & matrix_elements, int elements_count);

    static double sparsity(int rows, int columns);

    void print() const;

    int getOutputWidth() const;

    void setOutputWidth(double number);

    double getMSparsity() const;

    void setMSparsity(double mSparsity);

    virtual double at(int row, int column) const = 0;
};
