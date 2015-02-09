#include "DeCasteljauBezierCurve.hpp"
#include <cmath>


#ifndef fact_func
#define fact_func
double fact(double n)
{
    return (n == 1.0 || n == 0.0) ? 1.0 : fact(n - 1.0) * n;
}

#endif
namespace prog_3D
{
    DeCasteljauBezierCurve::DeCasteljauBezierCurve(std::vector<Point> ps,int n): controlPoints(ps),pointsNumber(n){   }

    DeCasteljauBezierCurve::~DeCasteljauBezierCurve(){   }

    void DeCasteljauBezierCurve::setPointsNumber(int n)
    {
        this->pointsNumber=n;
    }

    int DeCasteljauBezierCurve::getPointsNumber()
    {
        return this->pointsNumber;
    }

    std::vector<Point> DeCasteljauBezierCurve::compute()
    {
        std::vector<Point> result;
        for(long i=0;i<getControlPoint().size();++i)
        {
            double u = ((double) i) * 1.0 /(double)(getPointsNumber()-1);

            //result.push_back();
        }
        return result;
    }
    //FUNCTION RECURSIVE
    Point DeCasteljauBezierCurve(std::vector<Point> points,double u)
    {
        if(points.size()==1)
            return points.at(0);
        else
        {
            std::vector<Point> poin2;
            for (int k = 0; k < points.size() - 1; ++k)
            {

                double x = points[k].getX()*(1.0-u) + u*points[k+1].getX();
                double y = points[k].getY()*(1.0-u) + u*points[k+1].getY();
                double z = points[k].getZ()*(1.0-u) + u*points[k+1].getZ();
                Point p;(x,y,z);
                poin2.push_back(p);
            }
            return DeCasteljauBezierCurve(poin2, u);
        }
    }

    std::vector<Point> &DeCasteljauBezierCurve::getControlPoint()
    {
        return this->controlPoints;
    }
}