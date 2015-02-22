#ifndef PROG_3D_BERNSTEIN_BEZIER_CURVE_HPP_DEFINED
#define PROG_3D_BERNSTEIN_BEZIER_CURVE_HPP_DEFINED

#include "core-declaration.hpp"
#include "BezierCurve.hpp"
/**
* \namespace This namespace gathers all classes for 3D programming
**/
namespace prog_3D {

    class BernsteinBezierCurve :public virtual BezierCurve
    {

    public:
        BernsteinBezierCurve(std::vector<Point>,int);

        virtual ~BernsteinBezierCurve();
        virtual std::vector<Point> compute();
    };

}

#endif