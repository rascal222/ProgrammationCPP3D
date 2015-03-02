#include "../core/Curve.hpp"
#include "BezierCurve.hpp"

namespace prog_3D {
    BezierCurve::BezierCurve(std::vector<Point> points) : Curve(), controlPoints(points){}
    BezierCurve::BezierCurve(std::vector<Point> points,int n) : Curve(n), controlPoints(points){}
    BezierCurve::~BezierCurve(){}

    std::vector<Point>& BezierCurve::getControlPoint()
    {
        return this->controlPoints;
    }

    double BezierCurve::fact(double n)
    {
        return (n == 1.0 || n == 0.0) ? 1.0 : fact(n - 1.0) * n;
    };
}
