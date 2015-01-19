#ifndef PROG_3D_VECTOR_HPP_DEFINED
#define PROG_3D_VECTOR_HPP_DEFINED
#include <ostream>

#include "core-declaration.hpp"

namespace prog_3D {


    class Vector {
    private:
        double x;
        double y;
        double z;

    public:
        Vector();

        Vector(double x, double y, double z);

        Vector(Point& p1, Point& p2);

        Vector(Vector& p);

        virtual ~Vector();

        void setX(double x);

        void setY(double y);

        void setZ(double z);

        double getX();

        double getY();

        double getZ();

        double norm();

        double normalize();

        double scalar(Vector vector);

        Vector cross(Vector vector);

        double getAngle(Vector vector);

    };

    std::ostream &operator<<( std::ostream &stream, Vector& vector);
    Vector& operator* (double x,Vector& y);

}

#endif