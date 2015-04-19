//
// Created by beugnon on 19/04/15.
//

#ifndef PROGRAMMATION3D_GRID_H
#define PROGRAMMATION3D_GRID_H


#include "../meshing/AutoCenter.h"
#include "../primitives/Voxel.hpp"
#include <vector>

class Grid : public virtual AutoCenter {
private:
    prog_3D::Voxel* v=nullptr;
    std::vector<prog_3D::Voxel> voxels;
    int nb;


public:
    Grid() : AutoCenter(), nb(10) {};
    virtual double computeBetterSize() override;
    virtual ~Grid(){
        delete v;
    };
    void draw();

    std::vector<prog_3D::Voxel> const &getVoxels() const {
        return voxels;
    }

    int getNb() const {
        return nb;
    }

    void setNb(int nb) {
        Grid::nb = nb;
        computeBetterSize();
    }
};


#endif //PROGRAMMATION3D_GRID_H


