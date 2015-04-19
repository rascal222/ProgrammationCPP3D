//
// Created by beugnon on 19/04/15.
//

#include "GridVoxel.h"
#include "Voxel.hpp"
#include <algorithm>
#include <iostream>


using namespace prog_3D;


std::vector<GridVoxel*> GridVoxel::cut2() {
    std::vector<Voxel> voxels = Voxel::cut();
    std::vector<GridVoxel*> gvoxels;
    for(Voxel v : voxels){
        GridVoxel* gv = new GridVoxel(v.getCenter(),v.getLength());
        gvoxels.push_back(gv);
    }
    return gvoxels;
}

bool GridVoxel::havePoint() {
    return !gridPoints.empty();
}

prog_3D::Point *GridVoxel::getGridCenter() {
    prog_3D::Point* center = new prog_3D::Point(getCenter());
    return center;
}

bool GridVoxel::isConnected(GridVoxel* v2, GridVoxel* v3) {
    for(TopoPoint* tp : getInPoints()) {
        std::vector<TopoPoint*> tps = tp->getNeighbours();
        for(TopoPoint* tp2 : v2->getInPoints()) {
            if(std::find(tps.begin(),tps.end(),tp2)!=tps.end())
            for(TopoPoint* tp3 : v3->getInPoints()) {
                if(std::find(tps.begin(),tps.end(),tp3)!=tps.end()) {
                    return true;
                }

            }
        }
    }
    return false;
}
