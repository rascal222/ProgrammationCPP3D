#ifndef GLCORE_HPP_DEFINED
#define GLCORE_HPP_DEFINED

#include "Vector.hpp"
#include "Axis.hpp"
#include "Point.hpp"
#include "Curve.hpp"
#include <GL/glut.h>

namespace prog_3D
{


    void glPoint(const Point& p);
    void drawPoint(const Point& p);
    void drawPoint(Point& p,float r,float g,float b);
    void drawPoint(Point& p,float r,float g,float b, float alpha);
    void drawLine(const Point& p,const Vector& v);
    void drawLine(Point& p, Point& p2);
    void drawCurve(std::vector<Point> tabPointsOfCurve,bool showPoint);
    void drawSurface(std::vector<std::vector<Point>> vector,bool showPoint);
}

#endif