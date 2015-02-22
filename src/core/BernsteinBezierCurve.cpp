#include "Curve.hpp"
#include "BernsteinBezierCurve.hpp"
#include <cmath>
#include "Point.hpp"

namespace prog_3D
{
    BernsteinBezierCurve::BernsteinBezierCurve(std::vector<Point> ps,int n): BezierCurve(ps,n){   }

    BernsteinBezierCurve::~BernsteinBezierCurve(){   }

    std::vector<Point> BernsteinBezierCurve::compute()
    {
        std::vector<Point> result;

        for(long i=0;i<getControlPoint().size();++i)
        {
            Point p;
            double u = ((double) i) * 1.0 /(double)(getPointsNumber()-1);
            double x=0;
            double y =0;
            double z=0;
            // LA SOMME DES POINTS DE CONTROLES EN FONCTION DE U
            for(long j=0;j<getControlPoint().size();++j)
            {
                double b = (fact(getControlPoint().size()-1) / (fact(j) * fact(getControlPoint().size()-1-j))) * pow(u, j) * pow((1.0-u), getControlPoint().size()-1-j);
                x+= b*(double) getControlPoint()[j].getX();
                y+= b*(double) getControlPoint()[j].getY();
                z+= b*(double) getControlPoint()[j].getZ();
            }

            p.setX(x);
            p.setY(y);
            p.setZ(z);
            result.push_back(p);
        }
        return result;
    }


}