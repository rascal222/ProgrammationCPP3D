//
// Created by beugnon on 15/04/15.
//

#ifndef PROGRAMMATION3D_PROPAGATION_HPP
#define PROGRAMMATION3D_PROPAGATION_HPP


#include "../meshing/TopoMesh.h"
#include <stack>


class Propagation {

private:
    TopoMesh* topoMesh;
    double threshold;

    int step = 0;

public:
   int getStep() const {
        return step;
    }

    void setStep(int step) {
        Propagation::step = step;
    }

    std::stack<TopoEdge *>  &getPassiveHull() {
        return passiveHull;
    }

    Propagation(TopoMesh* topoMesh,double threshold) : topoMesh(topoMesh), threshold(threshold){}
    virtual ~Propagation(){}


    TopoMesh *getTopoMesh() const {
        return topoMesh;
    }

    void setTopoMesh(TopoMesh *topoMesh) {
        Propagation::topoMesh = topoMesh;
    }

    virtual void initPropagation();
    virtual int* fullPropagation();
    virtual void propagationStep();



    double getThreshold() const {
        return threshold;
    }

    void setThreshold(double threshold) {
        Propagation::threshold = threshold;
    }

    std::stack<TopoEdge*> passiveHull;
};


#endif //PROGRAMMATION3D_PROPAGATION_H
