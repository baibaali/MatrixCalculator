# MATRIX CALCULATOR
## This application will implement simple matrix calculator.

The application will be support base matrix arithmetical operations such as:

    - Addition
    - Substraction
    - Matrix multiplication by matrix
    - Matrix multiplication by scalar
    
Then, specific matrix operations such as:

    - Computing the determenatn of a matrix
    - Computing matrix rank
    - Finding matrix inversion for square matrices
    - Gauss Elimination Method
    - Matrix merge operation
    - Matrix cut operation
    
### Matrix merge operation

    This operation will merge two matrices into one.

        For example, merging two matrices 3x3 as a result will get matrix 6x3

                                         | 1 1 1 |
        | 1 1 1 |            | 2 2 2 |   | 1 1 1 |
        | 1 1 1 | merge with | 2 2 2 | = | 1 1 1 |
        | 1 1 1 |            | 2 2 2 |   | 2 2 2 |
                                         | 2 2 2 |
                                         | 2 2 2 |
                                          
### Matrix cut operation

    This operation will cut the matrix to the specified size
    
    For example, cutting matrix 5x5 from position [2, 3] to a matrix 3x3 (rows and columns indexing starts from 1):
    
        | 0 1 2 3 4 |
        | 1 2 3 4 5 |    cutting     | 3 4 5 |
        | 2 3 4 5 6 | =============> | 4 5 6 |
        | 3 4 5 6 7 |                | 5 6 7 |
        | 4 5 6 7 8 |

### Ability to store a matrix as a variable

    You can store the matrix as a variable with specified name
        Storing as a map, where the matrix name is a key and matrix itself is a value
        
### Matrix types

    There will be two types of matrices that will implement the base class of a matrix:
        - Dense matrix
        - Sparse matrix
        
    The difference between the two types of matrices lies in their representation.
    For efficient use of memory, we will store a sparse matrix in a map instead of a 2D array.