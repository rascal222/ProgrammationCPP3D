//
// Created by beugnon on 16/03/15.
//

#ifndef _PROGRAMMATION3D_VECTOR3_HPP_
#define _PROGRAMMATION3D_VECTOR3_HPP_

#include <ostream>

class Quaternion;

class Vector3 {
private:
    double x;
    double y;
    double z;
public:
    Vector3() : Vector3(0, 0, 0) {
    };

    Vector3(double x, double y, double z) : x(x), y(y), z(z) {
    };

    Vector(const Vector &p) : Vector3(p.getX(), p.getY(), p.getZ()) {
    };

    ~Vector3();

    /// Accessors/Mutators
    double getX() const {
        return x;
    }

    void setX(double x) {
        Vector3::x = x;
    }

    double getY() const {
        return y;
    }

    void setY(double y) {
        Vector3::y = y;
    }

    double getZ() const {
        return z;
    }

    void setZ(double z) {
        Vector3::z = z;
    }

    /// Modification on same Vector3
    void translate(const Vector3 &translation);

    void rotate(const Quaternion &rotation);

    void normalized();

    double norm() const;

    double scalar(const Vector3 &other) const;

    Vector3 cross(const Vector3 &other) const;

    double getPolarAngle(const Vector3 &other) const;

    /// Produce new Vector3
    Vector3 dot(const Vector3 &other) const;

    Vector3 div(const Vector3 &other) const;

    Vector3 add(const Vector3 &other) const;

    Vector3 sub(const Vector3 &other) const;

    Vector3 dot(const double alpha) const;

    Vector3 div(const double alpha) const;

    Vector3 projectionOnLine(const vector3 &point1, const vector3 &point2) const;

    Vector3 projectionOnVector(const vector3 &origin, const vecto3 &vector) const;

    Vector3 projectionOnPlan(const vector3 &pointInSpace, const vector3 &normal) const;

    /// Print message for ostream
    void print(std::ostream &stream) const;


    /// Operators
    Vector3 operator+(const Vector3 &vector);

    Vector3 &operator+=(const Vector3 &vector);

    Vector3 operator+(const double alpha);

    Vector3 &operator+=(const double alpha);


};

/// Operator functions
std::ostream &operator<<(std::ostream &stream, const Vector3 &vector) {
    vector.print(stream);
    return stream;
}


#endif //_PROGRAMMATION3D_VECTOR3_HPP_

