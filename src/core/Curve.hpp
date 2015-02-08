#ifndef PROG_3D_CURVE_HPP_DEFINED
#define PROG_3D_CURVE_HPP_DEFINED

#include "core-declaration.hpp"
#include <vector>

/**
* \namespace This namespace gathers all classes for 3D programming
*/
namespace prog_3D {

    class Curve {
    public:
        Curve();
        virtual ~Curve();
        virtual std::vector<Point> compute()=0;
    };

    inline void drawCurve(Curve& curve)
    {
        std::vector<Point> points = curve.compute();


    }
}

#endif