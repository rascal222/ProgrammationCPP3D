//
// Created by beugnon on 19/04/15.
//

#include "Grid.h"

using namespace prog_3D;

std::vector<GridVoxel*> recursive_grid(GridVoxel* v, int nb);
std::vector<GridVoxel*> recursive_grid(GridVoxel* v, int nb) {

    if(nb<=0) {
        return v->cut2();
    }
    std::vector<GridVoxel*> voxels;

    std::vector<GridVoxel*> cut = v->cut2();
    for(int i=0;i<cut.size();++i) {
        GridVoxel* c = cut.at(i);
        int b = nb-1;
        std::vector<GridVoxel*> r = recursive_grid(c,b);
        voxels.insert(voxels.end(),r.begin(),r.end());
    }
    return voxels;
}

double Grid::computeBetterSize() {
    double value =  AutoCenter::computeBetterSize();
    AutoCenter::getM();
    double min = getM().points.at(0).getX();
    double max = getM().points.at(0).getX();
    for(Point p : getM().points){
        if(p.getX()< min)
            min = p.getX();
        if(p.getY()< min)
            min = p.getY();
        if(p.getZ()< min)
            min = p.getZ();

        if(p.getX() > max)
            max = p.getX();
        if(p.getY() > max)
            max = p.getY();
        if(p.getZ() > max)
            max = p.getZ();
    }

    if(v== nullptr)
        v = new GridVoxel(AutoCenter::getCenter(),(max-min));

    voxels = recursive_grid(v,nb);

    return value;
}

void Grid::draw() {
    for(Voxel* vox : voxels) {
        vox->draw(false,false);
    }
}

std::vector<GridVoxel *> Grid::extract() {

    std::vector<GridVoxel*> extract;
    std::cout << voxels.size() << std::endl;
    extract.insert(extract.end(),voxels.begin(),voxels.end());
    std::remove_if(extract.begin(),extract.end(),[](GridVoxel* gv){return !gv->havePoint();});
    return extract;
}
