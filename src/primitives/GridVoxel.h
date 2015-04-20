//
// Created by beugnon on 19/04/15.
//

#ifndef PROGRAMMATION3D_GRIDPOINT_H
#define PROGRAMMATION3D_GRIDPOINT_H

#include <vector>
#include <set>
#include <iostream>
#include "Voxel.hpp"
#include "../meshing/TopoPoint.h"

class GridVoxel : public virtual prog_3D::Voxel {

private:
    std::vector<int> gridPoints;

public:

    GridVoxel(const prog_3D::Point& center, double length) : prog_3D::Voxel(center,length) {};

    const std::vector<int>& getInPoints() const {
        return gridPoints;
    }

    virtual void addPoint(int id){
        gridPoints.push_back(id);
    }


    std::vector<GridVoxel*> cut2();

    virtual bool havePoint();

    prog_3D::Point *getGridCenter();

    bool isConnected(GridVoxel* v2, GridVoxel* v3);

    bool operator<(const GridVoxel& voxel) const {
        return getCenter() < voxel.getCenter();
    }
};


#endif //PROGRAMMATION3D_GRIDPOINT_H