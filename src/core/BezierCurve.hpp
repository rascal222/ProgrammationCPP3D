#ifndef PROG_3D_CURVE_HPP_DEFINED
#define PROG_3D_CURVE_HPP_DEFINED

#include "core-declaration.hpp"
#include <ostream>
#include "Curve.hpp"
#include <vector>
/**
* \namespace This namespace gathers all classes for 3D programming
*/
namespace prog_3D {

    class BezierCurve {
    private:
        std::vector<Point> controlPoints;
    public:
        BezierCurve(std::vector<Point>);
        virtual ~BezierCurve();
    };

}

#endif