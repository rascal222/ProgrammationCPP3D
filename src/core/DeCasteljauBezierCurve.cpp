#include "DeCasteljauBezierCurve.hpp"
#include <cmath>
#include <iostream>


namespace prog_3D
{
    DeCasteljauBezierCurve::DeCasteljauBezierCurve(std::vector<Point> ps,int n): BezierCurve(ps,n){   }

    DeCasteljauBezierCurve::~DeCasteljauBezierCurve(){   }


    std::vector<Point> DeCasteljauBezierCurve::compute()
    {
        std::vector<Point> result;
        for(long i=0;i<getPointsNumber();++i)
        {
            double u = ((double) i) * 1.0 /(double)(getPointsNumber()-1);

            Point p = recursive(getControlPoint(), u);
            result.push_back(p);
        }
        return result;
    }
    //FUNCTION RECURSIVE
    Point DeCasteljauBezierCurve::recursive(std::vector<Point> points,double u)
    {
        if(points.size()==1)
            return points.at(0);
        else
        {
            std::vector<Point> poin2;
            for (int k = 0; k < points.size()-1; ++k)
            {
                double x = points[k].getX()*(1.0-u) + u*points[k+1].getX();

                double y = points[k].getY()*(1.0-u) + u*points[k+1].getY();
                double z = points[k].getZ()*(1.0-u) + u*points[k+1].getZ();

                Point p(x,y,z);
                poin2.push_back(p);
            }
            return recursive(poin2, u);
        }
    }

}