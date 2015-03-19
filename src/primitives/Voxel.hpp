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
        Voxel(const Point &, double);

        virtual ~Voxel();

        virtual Point &getCenter();

        virtual double getLength() const;

        virtual Point* getVertices();

        virtual void draw(bool);

        virtual void notifyChange();

        virtual float equation(const Point&);
    };
}
#endif
