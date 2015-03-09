#ifndef PROG_3D_DISC_HPP_DEFINED
#define PROG_3D_DISC_HPP_DEFINED
#include "../core/Point.hpp"
namespace prog_3D
{

    class Disc
    {
    private :
        float rayon;
        Point center;
        int meridians;
    public:
        Disc();
        Disc(float,int,Point&);
        ~Disc();

        virtual void draw();
        virtual void draw(bool);
    };
}

#endif