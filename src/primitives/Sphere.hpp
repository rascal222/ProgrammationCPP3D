#ifndef PROG_3D_SPHERE_HPP_DEFINED
#define PROG_3D_SPHERE_HPP_DEFINED
#include "../core/Point.hpp"
namespace prog_3D
{

    class Sphere
    {
    private :
        float rayon;
        Point center;
        int meridians;
        int paralleles;
    public:
        Sphere();
        Sphere(float,int,int,Point&);
        ~Sphere();

        virtual void draw();
        virtual void draw(bool);
    };
}

#endif