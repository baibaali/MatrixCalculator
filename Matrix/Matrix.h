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
    MERGE,
    CUT_DEFAULT,
    CUT,
    GEM,
    GEM_COMMENTED,
    IDENTITY,
    PRINT,
};

class Matrix {
    std::pair <int, int> size;
public:

    Matrix() = default;

    Matrix(int rows, int columns);

    ~Matrix() = default;

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

    virtual std::shared_ptr<Matrix> merge (const Matrix & other) const = 0;

    virtual std::shared_ptr<Matrix> cut (std::pair<int, int> pos, std::pair<int, int> size) const = 0;

    std::pair <int, int> getSize() const;

    static double sparsity(const std::vector<double> & matrix_elements, int elements_count);

};
