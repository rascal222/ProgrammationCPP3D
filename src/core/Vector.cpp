#include "Vector.hpp"
#include "Point.hpp"
#include <cmath>
#include <ostream>


namespace prog_3D
{
    Vector::Vector() :Vector(0,0,0) {}

    Vector::Vector(Point& p1, Point& p2)
    {
        this->x = p2.getX() - p1.getX();
        this->y = p2.getY() - p1.getY();
        this->z = p2.getZ() - p1.getZ();
    }

    Vector::Vector(double x, double y, double z) : x(x),y(y),z(z) {}

    Vector::Vector(Vector& p) : Vector(p.getX(),p.getY(),p.getZ()) {}

    Vector::~Vector() {}

    double Vector::getX()
    {
        return this->x;
    }

    double Vector::getY()
    {
        return this->y;
    }

    double Vector::getZ()
    {
        return this->z;
    }

    void Vector::setX(double x)
    {
        this->x =x;
    }

    void Vector::setY(double y)
    {
        this->y =y;
    }

    void Vector::setZ(double z)
    {
        this->z =z;
    }

    double Vector::norm()
    {
        return sqrt(pow(getX(),2)+ pow(getY(), 2)+ pow(getZ(),2));
    }

    double Vector::normalize()
    {
        double n = norm();
        setX(getX()/n);
        setY(getY()/n);
        setZ(getZ()/n);
        return n;
    }

    double Vector::scalar(Vector vector)
    {
        return getX()*vector.getX()+ getY()*vector.getY()+ getZ()*vector.getZ();
    }

    /// \brief cross
    Vector Vector::cross(Vector vector)
    {
        double x = getY()* vector.getZ() - getZ()* vector.getY();
        double y = getZ()* vector.getX() - getX()* vector.getZ();
        double z = getX()* vector.getY() - getY()* vector.getX();
        return *new Vector(x,y,z);
    }

    double Vector::getAngle(Vector vector)
    {
        return acos(scalar(vector) / (norm()*vector.norm()));
    }

    std::ostream& operator<<( std::ostream &stream, Vector& vector)
    {
        stream << "{"<<vector.getX()<<","<<vector.getY()<<","<<vector.getZ()<<"}";
        return stream;
    }

}