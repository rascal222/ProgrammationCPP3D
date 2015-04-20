#include "Vector.hpp"
#include "Point.hpp"
#include <cmath>
#include <ostream>
#include <iostream>


namespace prog_3D
{
    Vector const Vector::ZERO(0,0,0);
    Vector const Vector::ONE(1,1,1);
    Vector const Vector::UP(0,1,0);
    Vector const Vector::DOWN(0,-1,0);
    Vector const Vector::FORWARD(1,0,0);
    Vector const Vector::BACK(-1,0,0);
    Vector const Vector::LEFT(0,0,-1);
    Vector const Vector::RIGHT(0,0,1);


    Vector::Vector() :Vector(0,0,0) {}

    Vector::Vector(const Point& p1,const Point& p2)
    {
        this->x = p2.getX() - p1.getX();
        this->y = p2.getY() - p1.getY();
        this->z = p2.getZ() - p1.getZ();
    }

    Vector::Vector(double x, double y, double z) : x(x),y(y),z(z) {}

    Vector::Vector(Vector& p) : Vector(p.getX(),p.getY(),p.getZ()) {}

    Vector::Vector(const Vector &p) : Vector(p.getX(),p.getY(),p.getZ()) {}

    Vector::~Vector() {}

    double Vector::getX() const
    {
        return this->x;
    }

    double Vector::getY() const
    {
        return this->y;
    }

    double Vector::getZ() const
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

    double Vector::norm() const
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

    double Vector::scalar(const Vector& vector) const
    {
        return getX()*vector.getX()+ getY()*vector.getY()+ getZ()*vector.getZ();
    }

    Vector Vector::cross(const Vector& vector) const
    {
        std::cout << getY()<< std::endl;
        double x = getY()* vector.getZ() - getZ()* vector.getY();
        double y = getZ()* vector.getX() - getX()* vector.getZ();
        double z = getX()* vector.getY() - getY()* vector.getX();
        Vector v(x,y,z);
        return v;
    }

    double Vector::getAngle(const Vector& vector) const
    {
        Vector v1(vector);
        Vector v2(*this);
        v1.normalize();
        v2.normalize();
        return acos(v1.scalar(v2) / (v1.norm()*v2.norm()));
    }

    void Vector::print(std::ostream& stream) const
    {
        stream << "Vector{"<<getX()<<","<<getY()<<","<<getZ()<<"}";
    }
    Vector& Vector::operator*= (double d)
    {
        setX(getX()*d);
        setY(getY()*d);
        setZ(getZ()*d);
        return *this;
    }

    Vector& Vector::operator/= (double d)
    {
        setX(getX()/d);
        setY(getY()/d);
        setZ(getZ()/d);
        return *this;
    }

    //functions


    std::ostream& operator<<( std::ostream &stream, Vector const& vector)
    {
        vector.print(stream);
        return stream;
    }

    Vector operator*(double d,Vector const& vector)
    {
        Vector v(
                d * vector.getX(),
                d* vector.getY(),
                d* vector.getZ()
        );
        return v;
    }

    Vector operator*(Vector const& vector, double d) {
        Vector v(
                d * vector.getX(),
                d* vector.getY(),
                d* vector.getZ()
        );
        return v;
    }

    Vector operator/(double d,Vector const& vector)
    {
        Vector v(
                d / vector.getX(),
                d / vector.getY(),
                d / vector.getZ()
        );
        return v;
    }

    Vector operator/(Vector const& vector, double d) {
        Vector v(
                d / vector.getX(),
                d/ vector.getY(),
                d/ vector.getZ()
        );
        return v;
    }

}