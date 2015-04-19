//
// Created by beugnon on 13/04/15.
//

#ifndef PROGRAMMATION3D_AUTOCENTER_H
#define PROGRAMMATION3D_AUTOCENTER_H

#include <cmath>
#include "../core/Point.hpp"
#include "Mesh.hpp"
#include "../core/Vector.hpp"
#include <GL/glut.h>
#include <iostream>

class AutoCenter
{
private:
    Mesh m;
    double cachedBorderSize;
    double factor;
    prog_3D::Point center;


public:
    Mesh const &getM() const {
        return m;
    }

    void setMesh(Mesh const &m) {
        AutoCenter::m = m;
    }


    double getCachedBorderSize() const {
        return cachedBorderSize;
    }


    double getFactor() const {
        return factor;
    }

    void setFactor(double factor) {
        AutoCenter::factor = factor;
    }

public:
    AutoCenter() {}
    AutoCenter(Mesh const &m) : m(m) { }

    virtual double computeBetterSize()
    {
        double left2 = m.points.at(0).getX();
        double right2 = m.points.at(0).getX();
        double up = m.points.at(0).getY();
        double down = m.points.at(0).getY();
        double far = m.points.at(0).getZ();
        double near = m.points.at(0).getZ();

        //Compute Clipping plan
        for(int i=1;i<m.points.size();++i)
        {
            //Most left negative
            if(m.points.at(i).getX() < left2)
                left2 = m.points.at(i).getX();

            //Most right positive
            if(m.points.at(i).getX() > right2)
                right2 = m.points.at(i).getX();

            if(m.points.at(i).getY() < down)
                down = m.points.at(i).getY();

            if(m.points.at(i).getY() > up)
                up = m.points.at(i).getY();

            if(m.points.at(i).getZ() < near)
                near = m.points.at(i).getZ();

            if(m.points.at(i).getZ() > far)
                far = m.points.at(i).getZ();

        }

        //Center
        double centerX =  (right2 + left2) / 2.0;
        double centerY = (up + down) / 2.0;
        double centerZ = (far + near) / 2.0;
        center.set(centerX,centerY,centerZ);
        std::cout << center << std::endl;
        //Compute the border size of mesh in function of center
        cachedBorderSize = 0;
        prog_3D::Vector v(center.getX(),center.getY(),center.getZ());
        v*=-1.0;
        for(int i=0;i<m.points.size();++i)
        {
            prog_3D::Point p = m.points.at(i).translate(v);
            if(fabs(p.getX()) > cachedBorderSize)
                cachedBorderSize = fabs(p.getX());
            if(fabs(p.getY())> cachedBorderSize)
                cachedBorderSize = fabs(p.getY());
            if(fabs(p.getZ())> cachedBorderSize)
                cachedBorderSize = fabs(p.getZ());
        }

    }

    void placeOrtho()
    {
        glOrtho(-getFactor() * getCachedBorderSize(),getFactor() * getCachedBorderSize(),
                -getFactor() * getCachedBorderSize(),getFactor() * getCachedBorderSize(),
                -getFactor() * getCachedBorderSize(),getFactor() * getCachedBorderSize());
    }


    prog_3D::Point const &getCenter() const {
        return center;
    }
};


#endif //PROGRAMMATION3D_AUTOCENTER_H
