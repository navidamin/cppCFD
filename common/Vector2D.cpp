#include "Vector2D.h"


// Constructor to initialize the vector
Vector2D::Vector2D(double x_val = 0, double y_val = 0) : x(x_val), y(y_val) {}

// Overloading the * operator for scalar multiplication (Vector * double)
Vector2D Vector2D::operator*(double scalar) const {
    return Vector2D(x * scalar, y * scalar);
}

// Overloading the * operator for scalar multiplication (double * Vector) (friend function)
friend Vector2D Vector2D::operator*(double scalar, const Vector& v) {
    return Vector2D(v.x * scalar, v.y * scalar);
}

// Overloading the * operator for scalar multiplication (Vector2D * int)
Vector2D Vector2D::operator*(int scalar) const {
    return Vector2D(x * scalar, y * scalar);
}

// Overloading the * operator for scalar multiplication (int * Vector2D) (friend function)
friend Vector2D Vector2D::operator*(int scalar, const Vector2D& v) {
    return Vector2D(v.x * scalar, v.y * scalar);
}

// Overload the * operator for dot product (Vector2D * Vector2D)
double Vector2D::operator*(const Vector2D& v) const {
    return x * v.x + y * v.y; // Dot product
}

// Overload the ^ operator for cross product (Vector2D ^ Vector2D)
Vector3D Vector2D::operator^(const Vector2D& v) const {
    return Vector3D(
        0, // i component
        0, // j component
        x * v.y - y * v.x  // k component
    );
}

// Overload << operator for printing the Vector2D
friend std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

