#ifndef PROG_3D_BEZIER_CURVE_HPP_DEFINED
#define PROG_3D_BEZIER_CURVE_HPP_DEFINED

#include "core-declaration.hpp"
#include <ostream>
#include "Curve.hpp"
#include <vector>
/**
* \namespace This namespace gathers all classes for 3D programming
*/
namespace prog_3D {

    class BezierCurve : public virtual Curve{
    private:
        std::vector<Point> controlPoints;
        int pointsNumber;
    public:
        BezierCurve(std::vector<Point>);
        BezierCurve(std::vector<Point>,int);
        virtual ~BezierCurve();

        std::vector<Point>& getControlPoint();
        double fact(double n);
        std::vector<Point> compute()=0;
    };




}

#endif