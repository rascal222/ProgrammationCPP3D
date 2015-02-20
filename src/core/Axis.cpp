#include "Axis.hpp"
namespace prog_3D
{
    const Axis Axis::OX(Point::Origin,Vector::RIGHT);
    const Axis Axis::OY(Point::Origin,Vector::UP);
    const Axis Axis::OZ(Point::Origin,Vector::FORWARD);

    Axis::Axis(Point& p1, Vector& v1)
    {
        this->p=p1;
        this->n=v1;
    }

    Axis::Axis(const Point& p1, const Vector& v1)
    {
        p=(p1);
        n=(v1);
    }

    Axis::~Axis()
    {

    }

    Point& Axis::getPoint()
    {
        return this->p;
    }
    Vector& Axis::getVector()
    {
        return this->n;
    }

    void Axis::setPoint(Point& p1)
    {
        this->p=p1;
    }
    void Axis::setVector(Vector&v1)
    {
        this->n=v1;
    }
}