#ifndef AXIS_HPP_DEFINED
#define AXIS_HPP_DEFINED

#include "Point.hpp"
#include "Vector.hpp"

namespace prog_3D
{
    class Axis
    {
    private:
        Point p;
        Vector n;
    public:
        Axis(Point&, Vector&);
        Axis(const Point&, const Vector&);

        virtual ~Axis();

        Point& getPoint();
        Vector& getVector();

        void setPoint(Point&);
        void setVector(Vector&);

        virtual Point compute(double u);

        static const Axis OX;
        static const Axis OY;
        static const Axis OZ;
    };
}

#endif