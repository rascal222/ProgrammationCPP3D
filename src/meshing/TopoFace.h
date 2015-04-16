//
// Created by sbeugnon on 30/03/15.
//

#ifndef _PROGRAMMATION3D_TOPOFACE_H_
#define _PROGRAMMATION3D_TOPOFACE_H_
#include "core_declaration.h"
#include <vector>
#include "../core/Vector.hpp"
#include "TopoEdge.h"
#include <cmath>
#include <iostream>

class TopoFace {

private:
    std::vector<TopoEdge*> edges;
    int region = -1;
public:

    TopoFace(TopoEdge* t1,TopoEdge* t2, TopoEdge* t3,prog_3D::Vector normal);
    virtual ~TopoFace();

    virtual std::vector<TopoEdge*>& getEdges(){ return edges; }

    virtual prog_3D::Vector getNormal();

    virtual std::vector<TopoPoint*> getVertices();

    virtual std::vector<TopoFace*> getNeighbours();

    virtual prog_3D::Point getCenter();


    int getRegion() const {
        return region;
    }

    void setRegion(int region) {
        TopoFace::region = region;
    }

    static double computeDihedralAngle(TopoFace* face1, TopoFace* face2)
    {
        prog_3D::Vector n1 = face1->getNormal();
        prog_3D::Vector n2 = face2->getNormal();
        prog_3D::Vector cross = n1.cross(n2);
      //  cross.normalize();
//        return fabs(atan2(cross.scalar(n2),n1.scalar(n2)));
        return n1.getAngle(n2);
    }

    prog_3D::Vector n;
};


#endif //_PROGRAMMATION3D_TOPOFACE_H_
