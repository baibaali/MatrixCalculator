cmake_minimum_required(VERSION 3.17)
project(baibaali)

set(CMAKE_CXX_STANDARD 17)

add_executable(semestral src/main.cpp src/Calculator.cpp src/Calculator.h src/Matrix/Matrix.cpp src/Matrix/Matrix.h
        src/Matrix/SparseMatrix.cpp src/Matrix/SparseMatrix.h src/Matrix/DenseMatrix.cpp src/Matrix/DenseMatrix.h
        src/MatrixOperations/MatrixOperationManager.cpp src/MatrixOperations/MatrixOperationManager.h
        src/InputReader.cpp src/InputReader.h src/Fraction.cpp src/Fraction.h src/Exception.cpp src/Exception.h)