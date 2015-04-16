//
// Created by beugnon on 15/04/15.
//

#ifndef PROGRAMMATION3D_PROPAGATION_H
#define PROGRAMMATION3D_PROPAGATION_H


#include "../meshing/TopoMesh.h"

class Propagation {

private:
    TopoMesh* topoMesh;

public:
    Propagation(TopoMesh* topoMesh) : topoMesh(topoMesh){}
    virtual ~Propagation();


    TopoMesh *getTopoMesh() const {
        return topoMesh;
    }

    void setTopoMesh(TopoMesh *topoMesh) {
        Propagation::topoMesh = topoMesh;
    }

    virtual int* propagation();
};


#endif //PROGRAMMATION3D_PROPAGATION_H
