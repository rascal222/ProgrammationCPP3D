#ifndef RULED_SURFACE_HPP_DEFINED
#define RULED_SURFACE_HPP_DEFINED


#include "../core/Axis.hpp"
#include "../core/Curve.hpp"
#include "../core/Point.hpp"
#include "Surface.hpp"
#include <memory>

namespace prog_3D
{

    class RuledSurface: virtual prog_3D::Surface {
    private:
        std::shared_ptr<Curve> curve1;
        std::shared_ptr<Curve> curve2;
    public:
        RuledSurface(std::shared_ptr<Curve>, std::shared_ptr<Curve>);
        RuledSurface(std::shared_ptr<Curve> direct, std::shared_ptr<Curve> g,int nbU);


        virtual ~RuledSurface();

        std::shared_ptr<Curve> getCurve1();

        std::shared_ptr<Curve> getCurve2();

        virtual Point compute(double u, double v);

        virtual std::vector<std::vector<Point>> compute();

        virtual void draw();
        virtual void draw(bool);

    };
}
#endif