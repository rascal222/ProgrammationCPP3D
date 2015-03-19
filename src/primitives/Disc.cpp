#include "Disc.hpp"
#include "../core/PolarPoint.hpp"
#include "../glWrappers/GlCoreRendering.hpp"
#include <cmath>
#include <iostream>
namespace prog_3D {

    Disc::Disc() {
        center = Point::Origin;
        rayon = 1.0f;
        meridians = 10;
    }

    Disc::Disc(float rayon,int meridians, Point& center)
    {
        this->center = center;
        this->rayon=rayon;
        this->meridians=meridians;
    }

    Disc::~Disc()
    {
    }

    void Disc::draw() {
        draw(false);
    }

    void Disc::draw(bool debug) {
        std::vector<Point> down;

        for (int i = 0; i < meridians; ++i)
        {
            double angle = 2* M_PI*i / meridians;
            double x = rayon * cos(angle) + center.getX();
            double y = rayon * sin(angle) + center.getY();

            PolarPoint p(center,0,angle,rayon);
            std::cout << p.toCartesian() << std::endl;
            down.push_back(p.toCartesian());
        }
        //Face down
        glBegin(GL_TRIANGLE_FAN);
        {
            glPoint(center);
            for(int i=0;i<meridians;++i)
                glPoint(down.at(i));
            glPoint(down.at(0));
        }
        glEnd();



    }
}