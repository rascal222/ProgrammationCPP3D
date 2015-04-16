//
// Created by sbeugnon on 30/03/15.
//

#ifndef _PROGRAMMATION3D_TOPOMESH_H_
#define _PROGRAMMATION3D_TOPOMESH_H_
#include "../meshing/Mesh.hpp"
#include "core_declaration.h"

#include <list>
#include "TopoPoint.h"
#include "TopoFace.h"
#include "TopoEdge.h"

class TopoMesh
{
private:
    std::vector<TopoPoint*> points;
    std::vector<TopoEdge*> edges;
    std::vector<TopoFace*> faces;

public:
    TopoMesh(Mesh& mesh);
    virtual ~TopoMesh();
    virtual std::vector<TopoFace*> getFaces(){ return faces; }
    virtual std::vector<TopoEdge*> getEdges(){ return edges; }
    virtual std::vector<TopoPoint*> getPoints(){ return points; }

    virtual int getEdge(TopoPoint* p1,TopoPoint* p2);
    virtual bool haveEdge(TopoPoint* p1, TopoPoint* p2);
    virtual std::vector<prog_3D::Point> computeGaussianPointCloud();

    int* giveNeighboringFaceTab();
    float* getPointNormals();
};


#endif //_PROGRAMMATION3D_TOPOMESH_H_
