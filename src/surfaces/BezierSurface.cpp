#include "BezierSurface.hpp"
#include <iostream>
#include "../glWrappers/GlCoreRendering.hpp"

namespace prog_3D
{
    BezierSurface::BezierSurface(std::shared_ptr<BezierCurve> direct, std::shared_ptr<BezierCurve> g):prog_3D::Surface(4, 2)
    {
        director =direct;
        generator =(g);
    }

    BezierSurface::BezierSurface(std::shared_ptr<BezierCurve> direct, std::shared_ptr<BezierCurve> g,int nbU,int nbV):prog_3D::Surface(nbU,nbV)
    {
        director =direct;
        generator =(g);
    }

    BezierSurface::~BezierSurface() {
    }

    std::shared_ptr<BezierCurve> BezierSurface::getDirector() {
        return director;
    }

    std::shared_ptr<BezierCurve> BezierSurface::getGenerator() {
        return generator;
    }

    Point BezierSurface::compute(double u, double v)
    {
        Point originOnGenerator = getGenerator()->compute(u);

        Point originOnDirector = getDirector()->compute(0);
        Point next = getDirector()->compute(v);
        Vector translator(originOnDirector, next);
        return originOnGenerator.translate(translator);
    }

    std::vector<std::vector<Point>> BezierSurface::compute() {
        std::vector<std::vector<Point>> mat;
        for (int u = 0; u < getPointNumberForU(); ++u)
        {
            double u2 = u/((double)getPointNumberForU()-1.0);
            std::vector<Point> line;
            for(int v=0; v < getPointNumberForV();++v)
            {
                double v2 = v/((double)getPointNumberForV()-1.0);
                Point p = compute(u2, v2);
                line.push_back(p);
            }
            mat.push_back(line);
        }
        return mat;
    }


    void BezierSurface::draw(bool showPoints)
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

    void BezierSurface::draw()
    {
        draw(false);
    }

}