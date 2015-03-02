#ifndef VOXEL_HPP_DEFINED
#define VOXEL_HPP_DEFINED
#include "../core/Point.hpp"
class Voxel
{
private:
    Point center;
    double length;
public:
    Voxel(Point&,double);
    ~Voxel();
    std::vector< std::vector<Point> > compute();
};

#endif