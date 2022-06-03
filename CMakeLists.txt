cmake_minimum_required(VERSION 3.17)
project(baibaali)

set(CMAKE_CXX_STANDARD 17)

add_executable(semestral main.cpp Calculator.cpp Calculator.h Matrix/Matrix.cpp Matrix/Matrix.h
        Matrix/SparseMatrix.cpp Matrix/SparseMatrix.h Matrix/DenseMatrix.cpp Matrix/DenseMatrix.h
        MatrixOperations/MatrixOperationManager.cpp MatrixOperations/MatrixOperationManager.h
        InputReader.cpp InputReader.h )