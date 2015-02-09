#ifndef PROG_3D_BERNSTEIN_BEZIER_CURVE_HPP_DEFINED
#define PROG_3D_BERNSTEIN_BEZIER_CURVE_HPP_DEFINED

#include "core-declaration.hpp"
#include <ostream>
#include "Curve.hpp"
#include <vector>
/**
* \namespace This namespace gathers all classes for 3D programming
*/
namespace prog_3D {

    class BernsteinBezierCurve :public virtual Curve
    {
    private:
        std::vector<Point> controlPoints;
        int pointsNumber;
    public:
        BernsteinBezierCurve(std::vector<Point>,int);
        void setPointsNumber(int);
        int getPointsNumber();


        virtual ~BernsteinBezierCurve();
        virtual std::vector<Point> compute();

        std::vector<Point> &getControlPoint();
    };

}

#endif