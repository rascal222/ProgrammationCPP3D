#ifndef PROG_3D_CYLINDER_HPP_
#define PROG_3D_CYLINDER_HPP_
#include "../core/Point.hpp"
namespace prog_3D
{

    class Cylinder
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
    };
}

#endif