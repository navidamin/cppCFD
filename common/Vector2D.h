#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "Vector3D.h";

class Vector2D
{
private:
    double x, y; // 2D vector components
public:
    // Constructor to initialize the vector
    Vector2D(double x_val = 0, double y_val = 0);

    // Overloading the * operator for scalar multiplication (Vector * double)
    Vector2D operator*(double scalar) const;

    // Overloading the * operator for scalar multiplication (double * Vector) (friend function)
    friend Vector2D operator*(double scalar, const Vector& v);

    // Overloading the * operator for scalar multiplication (Vector * int)
    Vector2D operator*(int scalar) const ;

    // Overloading the * operator for scalar multiplication (int * Vector) (friend function)
    friend Vector2D operator*(int scalar, const Vector2D& v) ;

    // Overload the * operator for dot product (Vector * Vector)
    double operator*(const Vector2D& v) const ;

    // Overload the ^ operator for cross product (Vector ^ Vector)
    Vector3D operator^(const Vector2D& v) const ;

    // Overload << operator for printing the vector
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v) ;
};

#endif // VECTOR2D_H
