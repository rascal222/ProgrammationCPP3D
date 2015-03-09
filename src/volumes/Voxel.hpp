#ifndef VOXEL_HPP_DEFINED
#define VOXEL_HPP_DEFINED
#include "../core/Point.hpp"

namespace prog_3D {
    class Voxel {
    private:
        Point center;
        double length;
    public:
        Voxel(Point &, double);

        ~Voxel();

        virtual Point &getCenter() const;

        virtual double getLength() const;
    };
}
#endif