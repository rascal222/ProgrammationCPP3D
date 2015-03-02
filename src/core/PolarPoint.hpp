#ifndef PROG_3D_POLAR_POINT_HPP
#define PROG_3D_POLAR_POINT_HPP
#include "Point.hpp"
namespace prog_3D
{
    class PolarPoint
    {
    private :
        Point local;
        float angleTau;
        float anglePhi;
        float rayon;

    public:
        PolarPoint();
        PolarPoint(const Point& local,float angleTau,float anglePhi,float rayon);
        virtual ~PolarPoint();

        Point& getLocal();
        float getAnglePhi() const;
        float getAngleTau() const;
        float getRayon() const;

        virtual Point toCartesian() const;
    };

}

#endif