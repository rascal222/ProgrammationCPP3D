#ifndef PROG_3D_HERMITE_CUBIC_CURVE_HPP_DEFINED
#define PROG_3D_HERMITE_CUBIC_CURVE_HPP_DEFINED

#include "core-declaration.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "Curve.hpp"

/**
* \namespace This namespace gathers all classes for 3D programming
*/
namespace prog_3D {

    class HermiteCubicCurve :public virtual Curve {
    private:
        int pointNumber;
        Point p1;
        Point p2;
        Vector v1;
        Vector v2;
    public:
        HermiteCubicCurve(Point& p1,Point& p2,Vector& v1, Vector& v2,int n);

        void setPointNumber(int n);

        int getPointNumber();

        virtual ~HermiteCubicCurve();

        virtual std::vector<Point> compute();

        Point& getPoint1();

        Point& getPoint2();

        Vector& getVector1();

        Vector& getVector2();
    };

}

#endif
