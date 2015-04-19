//
// Created by beugnon on 19/04/15.
//

#ifndef PROGRAMMATION3D_GRID_H
#define PROGRAMMATION3D_GRID_H


#include "../meshing/AutoCenter.h"
#include "../primitives/Voxel.hpp"
#include <vector>
#include <map>
#include <algorithm>
#include "GridVoxel.h"

class Grid : public virtual AutoCenter {
private:
    GridVoxel* v=nullptr;
    std::vector<GridVoxel*> voxels;
    int nb;


public:
    Grid() : AutoCenter(), nb(1) {};
    virtual double computeBetterSize() override;
    virtual ~Grid(){
        delete v;
    };
    void draw();

    std::vector<GridVoxel*> const &getVoxels() const {
        return voxels;
    }

    int getNb() const {
        return nb;
    }

    void setNb(int nb) {
        Grid::nb = nb;
        computeBetterSize();
    }

    virtual std::vector<GridVoxel*> extract();
};


#endif //PROGRAMMATION3D_GRID_H


