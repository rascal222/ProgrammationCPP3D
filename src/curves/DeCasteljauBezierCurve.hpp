#ifndef PROG_3D_DECASTELJAU_BEZIER_CURVE_HPP_DEFINED
#define PROG_3D_DECASTELJAU_BEZIER_CURVE_HPP_DEFINED

#include "BezierCurve.hpp"

/**
* \namespace This namespace gathers all classes for 3D programming
*/
namespace prog_3D {

    class DeCasteljauBezierCurve :public virtual BezierCurve
    {
    private:
        virtual Point recursive(std::vector<Point>,double);
    public:
        DeCasteljauBezierCurve(std::vector<Point>,int);
        virtual ~DeCasteljauBezierCurve();
        virtual Point compute(double u);
        virtual std::vector<Point> compute();



    };

}

#endif