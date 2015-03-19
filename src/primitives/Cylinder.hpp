#ifndef PROG_3D_CYLINDER_HPP_
#define PROG_3D_CYLINDER_HPP_
#include "../core/Point.hpp"
#include "Shape.hpp"

namespace prog_3D
{

    class Cylinder : public Shape
    {
    private :
        float rayon;
        float height;
        Point center;
        int meridians;
    public:
        Cylinder();
        Cylinder(float,float,int,Point&);
        ~Cylinder();

        virtual void draw();
        virtual void draw(bool);

        virtual double equation(const Point &point);
    };
}

#endif
