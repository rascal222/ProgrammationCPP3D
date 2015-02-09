#ifndef PROG_3D_DECASTELJAU_BEZIER_CURVE_HPP_DEFINED
#define PROG_3D_DECASTELJAU_BEZIER_CURVE_HPP_DEFINED

#include "core-declaration.hpp"
#include <ostream>
#include "Curve.hpp"
#include <vector>
/**
* \namespace This namespace gathers all classes for 3D programming
*/
namespace prog_3D {

    class DeCasteljauBezierCurve :public virtual Curve
    {
    private:
        std::vector<Point> controlPoints;
        int pointsNumber;
    public:
        DeCasteljauBezierCurve(std::vector<Point>,int);
        void setPointsNumber(int);
        int getPointsNumber();


        virtual ~DeCasteljauBezierCurve();
        virtual std::vector<Point> compute();

        std::vector<Point>& getControlPoint();
    };

}

#endif