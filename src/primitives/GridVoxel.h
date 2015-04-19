//
// Created by beugnon on 19/04/15.
//

#ifndef PROGRAMMATION3D_GRIDPOINT_H
#define PROGRAMMATION3D_GRIDPOINT_H

#include <vector>
#include "Voxel.hpp"
#include "../meshing/TopoPoint.h"

class GridVoxel : public virtual prog_3D::Voxel {

private:
    std::vector<TopoPoint*> gridPoints;

public:

    GridVoxel(const prog_3D::Point& center, double length) : prog_3D::Voxel(center,length) {};

    const std::vector<TopoPoint *>& getInPoints() const {
        return gridPoints;
    }

    virtual void addTopoPoint(TopoPoint* tp){
        gridPoints.push_back(tp);
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