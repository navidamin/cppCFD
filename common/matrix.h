#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <cmath>

/*
 *  Class Matrix
 * A general class for definition of matrices
 * to be partent of classes: grid, velocity, ...
*/
class Matrix
{
private:
    int nRows;
    int nCols;
    std::vector<double> A;

public:
    // constructors
    Matrix();
    Matrix(int n, int m, double x = 0);

    // Operators
    Matrix& operator=(double x);
    double operator()(int i, int j) const;
    double& operator()(int i, int j);

    Matrix operator*(double scalar) const;
    Matrix operator*(int scalar) const;
    Matrix operator*(const Matrix& other);

    // Friend functions for scalar multiplication
    friend Matrix operator*(double scalar, const Matrix& M);
    friend Matrix operator*(int scalar, const Matrix& M);

    // size of matrix
    int getRows() const { return nRows; }
    int getCols() const { return nCols; }

    // Matrix manuplations
    void resize(int newRows, int newCols);
    Matrix transpose() const;

};



#endif // MATRIX_H
