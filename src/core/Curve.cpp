#include "Curve.hpp"
namespace prog_3D {

    Curve::Curve() : Curve(10) {}

    Curve::Curve(int i) : pointsNumber(i){ }

    Curve::~Curve() {}


    void Curve::setPointsNumber(int n)
    {
        pointsNumber=n;
    };

    inline int Curve::getPointsNumber()
    {
        return pointsNumber;
    };
}
