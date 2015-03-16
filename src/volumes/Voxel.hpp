#ifndef VOXEL_HPP_DEFINED
#define VOXEL_HPP_DEFINED
#include "../core/Point.hpp"
#include <vector>
namespace prog_3D {
    class Voxel {
    private:
        Point center;
        double length;
        Point *_cached;
    public:
        Voxel(Point &, double);

        ~Voxel();

        virtual Point &getCenter() const;

        virtual double getLength() const;

        virtual std::vector<Point> etVertices() const;

        virtual void draw(bool);
    };
}
#endif