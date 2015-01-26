#ifndef AXIS_HPP_DEFINED
#define AXIS_HPP_DEFINED
#include "core-declaration.hpp"

namespace prog_3D
{
    class Axis
    {
    private:
        Point p;
        Vector n;
    public:
        Axis(Point&, Vector&);
        virtual ~Axis();

        Point& getPoint();
        Vector& getVector();

        void setPoint(Point&);
        void setVector(Vector&);

        static const Axis OX;
        static const Axis OY;
        static const Axis OZ;
    };
}

#endif