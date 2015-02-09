#include <GL/gl.h>
#include "../core/Point.hpp"
#include "../core/Vector.hpp"

#ifndef GLRENDERABLE_HPP
#define GLRENDERABLE_HPP

//EN COURS DE DEFINITION

class GLRenderable
{
public:
    double r;
    double g;
    double b;
    double a;

    virtual void draw()=0;
};


class GLPoint : GLRenderable, virtual Point
{
public:
    float size;

    inline virtual void draw()
    {
        glPointSize(size);
        glColor4d(r, g, b, a);
        glBegin(GL_POINTS);
        {
            glVertex3d(this->getX(),this->getY(),this->getZ());
        }
        glEnd();
    }
};

class GLVector : GLRenderable, virtual Vector
{
public:
    GLPoint point;
    float size;

    inline virtual void draw()
    {
        glColor4d(r, g, b, a);
        glBegin(GL_Line);
        {
            glVertex3d(point.getX(), point.getY(), point.getZ());
            glVertex3d(point.getX()+this->getX(),point.getX()+this->getY(),point.getX()+this->getZ());
        }
        glEnd();
        point.draw();
    }
};

#endif
