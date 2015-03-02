#include "PolarPoint.hpp"
#include <cmath>
#include <iostream>

namespace prog_3D
{
    PolarPoint::PolarPoint(): PolarPoint(Point::Origin,0.f,0.f,0.f){}

    PolarPoint::PolarPoint(const Point& local,float angleTau,float anglePhi,float rayon)
    {
        this->local=local;
        this->anglePhi=anglePhi;
        this->angleTau=angleTau;
        this->rayon=rayon;
    }
    PolarPoint::~PolarPoint()
    {

    }

    Point& PolarPoint::getLocal()
    {
        return local;
    }

    float PolarPoint::getAnglePhi() const
    {
        return anglePhi;
    }

    float PolarPoint::getAngleTau() const
    {
        return angleTau;
    }

    float PolarPoint::getRayon() const
    {
        return rayon;
    }

    Point PolarPoint::toCartesian() const
    {
        Point p;
        p.setX(local.getX()+ (double) getRayon()* sin(getAnglePhi())*cos(getAngleTau()));
        p.setY(local.getY()+ (double) getRayon()*sin(getAnglePhi())*sin(getAngleTau()));
        p.setZ(local.getZ()+ (double) getRayon()*cos(getAnglePhi()));
        return p;
    }
}