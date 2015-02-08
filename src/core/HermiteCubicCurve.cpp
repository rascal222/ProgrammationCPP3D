#include "core-declaration.hpp"
#include <ostream>
#include <vector>
#include <cmath>
#include "HermiteCubicCurve.hpp"

namespace prog_3D {

	HermiteCubicCurve::HermiteCubicCurve(Point& p1,Point& p2,Vector& v1, Vector& v2,int n) : Curve()
	{
		this->pointNumber=n;
		this->p1=p1;
		this->p2=p2;
		this->v1=v1;
		this->v2=v2;
	}

	void HermiteCubicCurve::setPointNumber(int n)
	{
		this->pointNumber=n;
	}

	HermiteCubicCurve::~HermiteCubicCurve()
	{

	}

    Point& HermiteCubicCurve::getPoint1()
    {
        return this->p1;
    }

    Point& HermiteCubicCurve::getPoint2()
    {
        return this->p2;
    }

    Vector& HermiteCubicCurve::getVector1()
    {
        return this->v1;
    }

    Vector& HermiteCubicCurve::getVector2()
    {
        return this->v2;
    }

	std::vector<Point> HermiteCubicCurve::compute()
	{
		std::vector<Point> points;

        for(long i=0;i<n;i++)
        {
            double u = ((double) i) *1.0 /(double)(n);

            double f1 = 2 * pow(u,3) - 3 * pow(u,2) + 1;
            double f2 = -2 * pow(u,3) + 3 * pow(u,2);
            double f3 = pow(u,3) - 2 * pow(u,2) + u;
            double f4 = pow(u,3) - pow(u,2);

            double x = f1*p1.getX() + f2*p2.getX() + f3*v1.getX() + f4*v2.getX();
            double y = f1*p1.getY() + f2*p2.getY() + f3*v1.getY() + f4*v2.getY();
            double z = f1*p1.getZ() + f2*p2.getZ() + f3*v1.getZ() + f4*v2.getZ();
            Point p(x,y,z);
            points.push_back(p);
        }

        return points;
	}


}
