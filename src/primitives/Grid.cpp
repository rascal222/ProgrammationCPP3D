//
// Created by beugnon on 19/04/15.
//

#include "Grid.h"
#include <algorithm>
using namespace prog_3D;

std::vector<Voxel> recursive_grid(Voxel& v, int nb) {
    if(nb==0) {
        return v.cut();
    }
    std::vector<Voxel> voxels;
    std::vector<Voxel> cut = v.cut();
    for(int i=0;i<cut.size();++i) {
        std::vector<Voxel> r = recursive_grid(cut.at(i),nb-1);
        voxels.insert(voxels.end(),r.begin(),r.end());
    }
    return voxels;
}

double Grid::computeBetterSize() {
    double value =  AutoCenter::computeBetterSize();
    if(v== nullptr)
        v = new prog_3D::Voxel(AutoCenter::getCenter(),value);
    voxels = recursive_grid(*v,nb);
    return value;
}

void Grid::draw() {
    for(Voxel vox : voxels) {
        vox.draw(false,false);
    }
}
