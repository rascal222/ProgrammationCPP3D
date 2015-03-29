//
// Created by sbeugnon on 23/03/15.
//

#ifndef _PROGRAMMATION3D_MESH_H_
#define _PROGRAMMATION3D_MESH_H_


#include "../core/Point.hpp"
#include "IdTriangle.hpp"
#include <vector>
class Mesh
{
public:
    std::vector<prog_3D::Point> points;
    std::vector<prog_3D::IdTriangle> idTriangles;
    Mesh();
    ~Mesh();
    virtual float* getPointVector();
    virtual unsigned int* getIdVector();
    virtual float* getNormalVector();
};


#endif //_PROGRAMMATION3D_MESH_H_
