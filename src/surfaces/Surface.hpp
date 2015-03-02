#ifndef SURFACE_HPP_DEFINED
#define SURFACE_HPP_DEFINED
#include "../core/Point.hpp"
#include <vector>
namespace prog_3D {

    class Surface {
    private:
        int nbPointU;
        int nbPointV;

    public:
        Surface(int, int);

        virtual ~Surface();

        virtual void setPointNumberForU(int nb);

        virtual void setPointNumberForV(int nb);

        virtual int getPointNumberForU();

        virtual int getPointNumberForV();

        virtual Point compute(double u, double v) = 0;

        virtual std::vector<std::vector<Point>> compute() = 0;
    };
}
#endif