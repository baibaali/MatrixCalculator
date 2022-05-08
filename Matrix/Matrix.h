#pragma once

#include <memory>

class Matrix {
    std::pair <int, int> size;
public:

    Matrix();

    ~Matrix();

    virtual std::shared_ptr<Matrix> clone() const = 0;

    std::shared_ptr<Matrix> operator+ (const Matrix & other);

    std::shared_ptr<Matrix> operator- (const Matrix & other);

    std::shared_ptr<Matrix> operator* (const Matrix & other);

    std::shared_ptr<Matrix> operator* (int scalar);

    virtual std::shared_ptr<Matrix> add (const Matrix & other) = 0;

    virtual std::shared_ptr<Matrix> subtract (const Matrix & other) = 0;

    virtual std::shared_ptr<Matrix> multiply (const Matrix & other) = 0;

    virtual std::shared_ptr<Matrix> multiply (int scalar) = 0;

    virtual std::shared_ptr<Matrix> findInversion () = 0;

    virtual std::shared_ptr<Matrix> findDeterminant () = 0;

    virtual std::shared_ptr<Matrix> findRank () = 0;

    virtual std::shared_ptr<Matrix> gaussEliminate (bool withComments) = 0;

    virtual std::shared_ptr<Matrix> merge (const Matrix & other) = 0;

    virtual std::shared_ptr<Matrix> cut (const Matrix & other, int row, int col, int dimension) = 0;

    std::pair <int, int> getSize() const;

};
