#ifndef GLCORE_HPP_DEFINED
#define GLCORE_HPP_DEFINED

#include "Vector.hpp"
#include "Axis.hpp"
#include "Point.hpp"
#include "PolarPoint.hpp"
#include "Curve.hpp"
#include <GL/glut.h>
#include <vector>

namespace prog_3D
{

    void glPoint(const Point& p);
    void glPoint(const PolarPoint &p);

    void drawPoint(const Point& p);
    void drawPoint(const PolarPoint& p);
    void drawPoint(Point& p,float r,float g,float b);
    void drawPoint(Point& p,float r,float g,float b, float alpha);
    void drawLine(const Point& p,const Vector& v);
    void drawLine(Point& p, Point& p2);
    void drawLine(const Point& p, const Point& p2);
    void drawLine(const PolarPoint& p, const PolarPoint& p2);
    void drawCurve(std::vector<Point> tabPointsOfCurve,bool showPoint);
    void drawSurface(std::vector< std::vector<Point> > vector,bool showPoint);
}

#endif