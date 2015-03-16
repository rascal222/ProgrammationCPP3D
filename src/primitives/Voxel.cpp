#include "Voxel.hpp"
#include <GL/gl.h>
#include "../core/GlCoreRendering.hpp"
#include <iostream>

namespace prog_3D
{
    Voxel::Voxel(const Point &center, double rayon) : center(center), length(rayon)
    {
        _cached= nullptr;
    }

    Voxel::~Voxel() {
        if(_cached != nullptr)
            delete _cached;
    }

    Point& Voxel::getCenter() {
        return center;
    }

    double Voxel::getLength() const {
        return length;
    }

    void Voxel::notifyChange()
    {
        if(_cached!= nullptr)
            delete _cached;
    }

    Point *Voxel::getVertices() {
        if (_cached != nullptr)
            return _cached;
        else {
            _cached = new Point[8];
            _cached[0].set(
                    (getCenter().getX() - 0.5) * getLength(),
                    (getCenter().getY() - 0.5) * getLength(),
                    (getCenter().getZ() - 0.5) * getLength()
            );
            _cached[1].set(
                    (getCenter().getX() + 0.5) * getLength(),
                    (getCenter().getY() - 0.5) * getLength(),
                    (getCenter().getZ() - 0.5) * getLength()
            );
            _cached[2].set(
                    (getCenter().getX() + 0.5) * getLength(),
                    (getCenter().getY() + 0.5) * getLength(),
                    (getCenter().getZ() - 0.5) * getLength()
            );
            _cached[3].set(
                    (getCenter().getX() - 0.5) * getLength(),
                    (getCenter().getY() + 0.5) * getLength(),
                    (getCenter().getZ() - 0.5) * getLength()
            );
            _cached[4].set(
                    (getCenter().getX() - 0.5) * getLength(),
                    (getCenter().getY() - 0.5) * getLength(),
                    (getCenter().getZ() + 0.5) * getLength()
            );
            _cached[5].set(
                    (getCenter().getX() + 0.5) * getLength(),
                    (getCenter().getY() - 0.5) * getLength(),
                    (getCenter().getZ() + 0.5) * getLength()
            );
            _cached[6].set(
                    (getCenter().getX() + 0.5) * getLength(),
                    (getCenter().getY() + 0.5) * getLength(),
                    (getCenter().getZ() + 0.5) * getLength()
            );
            _cached[7].set(
                    (getCenter().getX() - 0.5) * getLength(),
                    (getCenter().getY() + 0.5) * getLength(),
                    (getCenter().getZ() + 0.5) * getLength()
            );
        }
        return _cached;
    }


    void Voxel::draw(bool debug)
    {
        if(_cached== nullptr)
            getVertices();
        //LEFT FACE


        glColor3f(1.0f,0.0f,.0f);
        glBegin(GL_TRIANGLES);
        {
            glPoint(_cached[3]);
            glPoint(_cached[0]);
            glPoint(_cached[4]);
        }
        glEnd();
        glBegin(GL_TRIANGLES);
        {
            glPoint(_cached[7]);
            glPoint(_cached[3]);
            glPoint(_cached[4]);
        }
        glEnd();

        //BACK FACE            //draw/write 310 321
        glColor3f(1.0f,1.0f,.0f);

        glBegin(GL_TRIANGLES);
        {
            glPoint(_cached[3]);
            glPoint(_cached[1]);
            glPoint(_cached[0]);
        }
        glEnd();
        glBegin(GL_TRIANGLES);
        {
            glPoint(_cached[3]);
            glPoint(_cached[2]);
            glPoint(_cached[1]);
        }
        glEnd();

        //TOP (z+1)
        //draw/write 723 762
        glColor3f(1.0f,1.0f,1.0f);

        glBegin(GL_TRIANGLES);
        {
            glPoint(_cached[7]);
            glPoint(_cached[2]);
            glPoint(_cached[3]);
        }
        glEnd();
        glBegin(GL_TRIANGLES);
        {
            glPoint(_cached[7]);
            glPoint(_cached[6]);
            glPoint(_cached[2]);
        }
        glEnd();

        //BOTTOM OK

        glColor3f(1.0f,0.0f,1.0f);

        glBegin(GL_TRIANGLES);
        {
            glPoint(_cached[0]);
            glPoint(_cached[1]);
            glPoint(_cached[4]);
        }
        glEnd();
        glBegin(GL_TRIANGLES);
        {
            glPoint(_cached[1]);
            glPoint(_cached[5]);
            glPoint(_cached[4]);
        }
        glEnd();

        //RIGHT OK

        glColor3f(.0f,1.0f,.0f);
        glBegin(GL_TRIANGLES);
        {
            glPoint(_cached[1]);
            glPoint(_cached[2]);
            glPoint(_cached[5]);
        }
        glEnd();
        glBegin(GL_TRIANGLES);
        {
            glPoint(_cached[2]);
            glPoint(_cached[6]);
            glPoint(_cached[5]);
        }
        glEnd();

        //TOP (WRONG FACE x-1)
        glColor3f(.0f,1.0f,1.0f);
        glBegin(GL_TRIANGLES);
        {
            glPoint(_cached[4]);
            glPoint(_cached[5]);
            glPoint(_cached[6]);
        }
        glEnd();
        glBegin(GL_TRIANGLES);
        {
            glPoint(_cached[6]);
            glPoint(_cached[7]);
            glPoint(_cached[4]);
        }
        glEnd();

    }
}