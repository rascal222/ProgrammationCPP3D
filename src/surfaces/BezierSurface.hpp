#ifndef BEZIER_SURFACE_HPP_DEFINED
#define BEZIER_SURFACE_HPP_DEFINED


#include "../core/Axis.hpp"
#include "../core/Curve.hpp"
#include "../core/Point.hpp"
#include "Surface.hpp"
#include "../curves/BezierCurve.hpp"
#include <memory>

namespace prog_3D
{

    class BezierSurface: public virtual prog_3D::Surface {
    private:
        std::shared_ptr<BezierCurve> director;
        std::shared_ptr<BezierCurve> generator;
    public:
        BezierSurface(std::shared_ptr<BezierCurve>, std::shared_ptr<BezierCurve>);
        BezierSurface(std::shared_ptr<BezierCurve> direct, std::shared_ptr<BezierCurve> g,int nbU,int nbV);

        virtual ~BezierSurface();

        std::shared_ptr<BezierCurve> getDirector();

        std::shared_ptr<BezierCurve> getGenerator();

        virtual Point compute(double u, double v);

        virtual std::vector<std::vector<Point>> compute();

        virtual void draw();
        virtual void draw(bool);

    };
}
#endif