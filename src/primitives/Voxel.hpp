#ifndef VOXEL_HPP_DEFINED
#define VOXEL_HPP_DEFINED
#include "../core/Point.hpp"
#include <vector>
#include <array>

namespace prog_3D {
    class Voxel {
    private:
        Point center;
        double length;
    public:

        Voxel(const Point &, double);

        virtual ~Voxel();

        virtual const Point &getCenter() const;

        virtual double getLength() const;

        virtual std::vector<Point> getVertices() const;

        virtual void draw(bool, bool);

        virtual std::vector<Voxel> cut();

        virtual bool inVoxel(Point* point);
    };
}
#endif
