#pragma once

#include <memory>
#include <vector>
#include "../Fraction.h"

enum OPERATION {
    NONE,
    SCAN,
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

class Matrix {
    std::pair <int, int> size;
    int output_width;
    double m_sparsity;
public:

    Matrix();

    Matrix(int rows, int columns, int output_width, double m_sparsity);

    virtual std::shared_ptr<Matrix> clone() const = 0;

    friend std::shared_ptr<Matrix> operator+(const std::shared_ptr<Matrix> lhs, const std::shared_ptr<Matrix> rhs);

    friend std::shared_ptr<Matrix> operator-(const std::shared_ptr<Matrix> lhs, const std::shared_ptr<Matrix> rhs);

    friend std::shared_ptr<Matrix> operator* (const std::shared_ptr<Matrix> lhs, const std::shared_ptr<Matrix> rhs);

    friend std::shared_ptr<Matrix> operator* (const std::shared_ptr<Matrix> lhs, Fraction scalar);

    std::vector<Fraction> add (const std::shared_ptr<Matrix> other) const;

    std::vector<Fraction> subtract (const std::shared_ptr<Matrix> other) const;

    std::vector<Fraction> multiply (const std::shared_ptr<Matrix> other) const;

    virtual std::shared_ptr<Matrix> multiply (Fraction scalar) const = 0;

    virtual std::shared_ptr<Matrix> inversion () const = 0;

    virtual std::shared_ptr<Matrix> determinant () const = 0;

    virtual std::shared_ptr<Matrix> rank () const = 0;

    virtual std::shared_ptr<Matrix> gaussEliminate (bool withComments) const;

    virtual std::shared_ptr<Matrix> gaussEliminateCommon () const = 0;

    virtual std::shared_ptr<Matrix> gaussEliminateDescribed () const = 0;

    std::vector<Fraction> merge_by_rows (const std::shared_ptr<Matrix> other) const;

    std::vector<Fraction> merge_by_columns (const std::shared_ptr<Matrix> other) const;

    std::vector<Fraction> cut (std::pair<int, int> pos, std::pair<int, int> m_size) const;

    std::vector<Fraction> getMatrixElementsAsVector () const;

    virtual void makeIdentity() = 0;

    std::pair <int, int> getSize() const;

    static double sparsity(const std::vector<Fraction> & matrix_elements, int elements_count);

    static double sparsity(int rows, int columns);

    void print() const;

    int getOutputWidth() const;

    void setOutputWidth(const Fraction & number);

    double getMSparsity() const;

    void setMSparsity(double mSparsity);

    virtual Fraction at(int row, int column) const = 0;

    bool isColumnNull (int column);

    void swap_rows(int first, int second);

    virtual void makeCellNull(int row, int column) = 0;

    virtual void setCellValue(int row, int column, const Fraction value) = 0;

    virtual void subtractTwoRows(int first, int second, const Fraction multiple) = 0;

    virtual void multiplyRowByScalar(int row, int scalar) = 0;
};
