#include "RuledSurface.hpp"
#include "Surface.hpp"
#include <vector>
#include <GL/glut.h>
#include <iostream>
#include "../core/GlCoreRendering.hpp"

namespace prog_3D
{
    RuledSurface::RuledSurface(std::shared_ptr<Curve> direct, std::shared_ptr<Curve> g):prog_3D::Surface(2, 2)
    {
        curve1 =direct;
        curve2 =(g);
    }

    RuledSurface::RuledSurface(std::shared_ptr<Curve> direct, std::shared_ptr<Curve> g,int nbU):prog_3D::Surface(nbU,nbU)
    {
        curve1 =direct;
        curve2 =(g);
    }

    RuledSurface::~RuledSurface() {
    }

    std::shared_ptr<Curve> RuledSurface::getCurve2() {
        return curve2;
    }

    std::shared_ptr<Curve> RuledSurface::getCurve1() {
        return curve1;
    }

    Point RuledSurface::compute(double u, double v)
    {
        Point p;
        Point p1 = getCurve1()->compute(u);
        Point p2 = getCurve2()->compute(u);
        p.setX((1.0 - v)*p1.getX() + v* p2.getX());
        p.setY((1.0 - v)*p1.getY() + v* p2.getY());
        p.setZ((1.0 - v)*p1.getZ() + v* p2.getZ());
        return p;
    }

    std::vector<std::vector<Point>> RuledSurface::compute() {
        std::vector<std::vector<Point>> mat;


        for (int u = 0; u < getPointNumberForU(); ++u)
        {
            std::vector<Point> line;
            double u2 = (double)u/((double)getPointNumberForU()-1.0);
            for(int v=0; v < getPointNumberForU();++v)
            {
                double v2 = (double) v/((double)getPointNumberForV()-1.0);
                Point p = compute(u2,v2);
                line.push_back(p);
            }
            mat.push_back(line);

        }
        return mat;
    }


    void RuledSurface::draw(bool showPoints)
    {
        std::vector<std::vector<Point>> mat = compute();
        for(int i=0;i<mat.size();++i)
        {
            for(int j=0;j<mat.at(i).size()-1;++j)
            {
                drawLine(mat.at(i).at(j), mat.at(i).at(j+1));
            }

        }

        for(int i=0;i<mat.size()-1;++i)
        {
            for(int j=0;j<mat.at(i).size();++j)
            {
                drawLine(mat.at(i).at(j), mat.at(i+1).at(j));
            }

        }

        if(showPoints)
        {
            for(int i=0;i<mat.size();++i)
            {
                for(int j=0;j<mat.at(i).size();++j)
                {
                    drawPoint(mat.at(i).at(j));
                }

            }
        }
    }

    void RuledSurface::draw()
    {
        draw(false);
    }

}