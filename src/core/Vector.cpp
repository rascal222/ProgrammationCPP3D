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

    double Vector::norme()
    {
        return sqrt(pow(getX(),2)+ pow(getY(), 2)+ pow(getZ(),2));
    }

    double Vector::normalize()
    {
        double n = norme();
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
    Vector Vector::vectorial(Vector vector)
    {
        double x = getY()* vector.getZ() - getZ()* vector.getY();
        double y = getZ()* vector.getX() - getX()* vector.getZ();
        double z = getX()* vector.getY() - getY()* vector.getX();
        return *new Vector(x,y,z);
    }

    double Vector::getAngle(Vector vector)
    {
        return acos(scalar(vector) / (norme()*vector.norme()));
    }



    Vector& Vector::operator* (double x)
    {
        Vector rslt(0,0,0);
        rslt.setX(getX()*x);
        rslt.setY(getY()*x);
        rslt.setZ(getZ()*x);
        return rslt;
    }

    Vector& Vector::operator/ (double x)
    {
        Vector rslt(0,0,0);
        rslt.setX(getX()/x);
        rslt.setY(getY()/x);
        rslt.setZ(getZ()/x);
        return rslt;
    }

    Vector& Vector::operator+ (Vector& vector)
    {
        Vector rslt(0,0,0);
        rslt.setX(getX()+vector.getX());
        rslt.setY(getY()+vector.getY());
        rslt.setZ(getZ()+vector.getZ());
        return rslt;
    }

    Vector& Vector::operator- (Vector& vector)
    {
        Vector rslt(0,0,0);
        rslt.setX(getX()-vector.getX());
        rslt.setY(getY()-vector.getY());
        rslt.setZ(getZ()-vector.getZ());
        return rslt;
    }

    std::ostream& operator<<( std::ostream &stream, Vector& vector)
    {
        stream << "{"<<vector.getX()<<","<<vector.getY()<<","<<vector.getZ()<<"}";
        return stream;
    }

    Vector& operator* (double x,Vector& y)
    {
        Vector rslt(0,0,0);
        rslt.setX(y.getX()*x);
        rslt.setY(y.getY()*x);
        rslt.setZ(y.getZ()*x);
        return rslt;
    }

}