//
// Created by beugnon on 19/04/15.
//

#ifndef PROGRAMMATION3D_GRIDPOINT_H
#define PROGRAMMATION3D_GRIDPOINT_H

#include <vector>
#include "Voxel.hpp"

class GridVoxel : public virtual prog_3D::Voxel {

private:
    std::vector<GridPoint*> gridPoints;
public:
    GridPoint *getMasterPoint() const {
        return masterPoint;
    }

    void setMasterPoint(GridPoint *masterPoint) {
        GridPoint::masterPoint = masterPoint;
    }

    const std::vector<GridPoint *>& getGridPoints() const {
        return gridPoints;
    }

    void setGridPoints(std::vector<GridPoint *>& gridPoints) {
        GridPoint::gridPoints = gridPoints;
    }
};


#endif //PROGRAMMATION3D_GRIDPOINT_H
