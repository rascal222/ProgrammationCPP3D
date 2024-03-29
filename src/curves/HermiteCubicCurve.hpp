#ifndef PROG_3D_HERMITE_CUBIC_CURVE_HPP_DEFINED
#define PROG_3D_HERMITE_CUBIC_CURVE_HPP_DEFINED

#include "../core/Vector.hpp"
#include "../core/Curve.hpp"

/**
* \namespace This namespace gathers all classes for 3D programming
*/
namespace prog_3D {

    class HermiteCubicCurve :public virtual Curve {
    private:
        Point p1;
        Point p2;
        Vector v1;
        Vector v2;
    public:
        HermiteCubicCurve(Point& p1,Point& p2,Vector& v1, Vector& v2,int n);

        virtual ~HermiteCubicCurve();

        virtual Point compute(double u);
        virtual std::vector<Point> compute();

        Point& getPoint1();

        Point& getPoint2();

        Vector& getVector1();

        Vector& getVector2();
    };

}

#endif
