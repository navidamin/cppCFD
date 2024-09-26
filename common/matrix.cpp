#include "matrix.h"
#include <stdexcept>

// Constructors
Matrix::Matrix() : nRows(0), nCols(0) {}

Matrix::Matrix(int n, int m, double x) : nRows(n), nCols(m), A(n * m, x) {}


// Set all matrix entries equal to a double
Matrix& Matrix::operator=(double x) {
    for (int i = 0; i < nRows * nCols; i++)
        A[i] = x;
    return *this;
}

// Access element, indexed by (row, column) [rvalue]
double Matrix::operator()(int i, int j) const {
    return A[j + i * nCols];
}

// Access element, indexed by (row, column) [lvalue]
double& Matrix::operator()(int i, int j) {
    return A[j + i * nCols];
}

// Overloading the * operator for scalar multiplication (Matrix * double)
Matrix Matrix::operator*(double scalar) const {
    Matrix result(nRows, nCols);
    for (int i = 0; i < nRows * nCols; ++i) {
        result.A[i] = A[i] * scalar;
    }
    return result;
}

// Overloading the * operator for scalar multiplication (Matrix * int)
Matrix Matrix::operator*(int scalar) const {
    // Reuse the double implementation by casting int to double
    return (*this) * static_cast<double>(scalar);
}

// Overloading the * operator for Matrix multiplication (Matrix * Matrix)
Matrix Matrix::operator*(const Matrix& other) {
    if (nCols != other.nRows) {
        throw std::invalid_argument("Matrix dimensions are not compatible for multiplication");
    }

    Matrix result(nRows, other.nCols, 0.0);  // Initialize with zeros

    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < other.nCols; ++j) {
            for (int k = 0; k < nCols; ++k) {
                result(i, j) += (*this)(i, k) * other(k, j);
            }
        }
    }

    return result;
}

// Friend function for scalar multiplication (double * Matrix)
Matrix operator*(double scalar, const Matrix& M) {
    // Reuse the member function implementation
    return M * scalar;
}

// Friend function for scalar multiplication (int * Matrix)
Matrix operator*(int scalar, const Matrix& M) {
    // Reuse the member function implementation
    return M * scalar;
}

// Resizes the matrix to new dimensions.
void Matrix::resize(int newRows, int newCols) {
    // Check for valid dimensions
    if (newRows <= 0 || newCols <= 0) {
        throw std::invalid_argument("New dimensions must be positive");
    }

    std::vector<double> newA(newRows * newCols);

    // Copy existing elements
    for (int i = 0; i < std::min(nRows, newRows); ++i) {
        for (int j = 0; j < std::min(nCols, newCols); ++j) {
            newA[j + i * newCols] = A[j + i * nCols];
        }
    }

    // Update member variables
    nRows = newRows;
    nCols = newCols;
    A = std::move(newA);
}

// Creates and returns the transpose of this matrix.
Matrix Matrix::transpose() const {
    // Create a new matrix with swapped dimensions
    Matrix result(nCols, nRows);

    // Fill the new matrix with transposed elements
    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {
             // Assign element (i,j) of this matrix to element (j,i) of the result
            result(j, i) = (*this)(i, j);
        }
    }

    return result;
}
