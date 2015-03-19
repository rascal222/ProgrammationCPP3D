#ifndef PROG_3D_SPHERE_HPP_DEFINED
#define PROG_3D_SPHERE_HPP_DEFINED
#include "../core/Point.hpp"
#include "Shape.hpp"

namespace prog_3D
{

    class Sphere : public Shape
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


        float getRayon() const {
            return rayon;
        }

        void setRayon(float rayon) {
            Sphere::rayon = rayon;
        }

        Point const &getCenter() const {
            return center;
        }

        void setCenter(Point const &center) {
            Sphere::center = center;
        }

        int getMeridians() const {
            return meridians;
        }

        void setMeridians(int meridians) {
            Sphere::meridians = meridians;
        }

        int getParalleles() const {
            return paralleles;
        }

        void setParalleles(int paralleles) {
            Sphere::paralleles = paralleles;
        }

        virtual void draw();
        virtual void draw(bool);

        virtual double equation(const Point &point);
    };
}

#endif
