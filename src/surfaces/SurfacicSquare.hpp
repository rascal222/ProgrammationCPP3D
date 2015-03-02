#ifndef SURFACE_SQUARE_HPP_DEFINED
#define SURFACE_SQUARE_HPP_DEFINED
#include "../core/Point.hpp"
#include "Surface.hpp"
#include "../curves/DeCasteljauBezierCurve.hpp"
#include <vector>
namespace prog_3D {

    class SurfacicSquare : public virtual Surface {
    private:
        std::vector<DeCasteljauBezierCurve> curves;

    public:
        SurfacicSquare(int, int);

        std::vector<DeCasteljauBezierCurve>& getControlCurves();

        virtual ~SurfacicSquare();

        virtual Point compute(double u, double v) ;
        virtual Point recursive(std::vector<std::vector<Point>> poins2,double u, double v);


        virtual std::vector<std::vector<Point>> compute();

        virtual std::vector<DeCasteljauBezierCurve> compute2();

        virtual void draw(bool);
        virtual void draw();
        void drawIntermediate(bool showPoints);
        void drawIntermediateRecursive(int step,std::vector<std::vector<Point>>& poins2,
                double u,double v, bool showPoints);
    };
}
#endif