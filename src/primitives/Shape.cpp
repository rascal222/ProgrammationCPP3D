//
// Created by beugnon on 20/03/15.
//

#include <iostream>
#include "Shape.hpp"

bool prog_3D::Shape::isInVoxel(prog_3D::Voxel const &voxel) {
    int cpt = 0;
    for (int i = 0; i < 8; ++i)
        if (equation(voxel.getVertices()[i]) < 0)
            cpt++;

    if (equation(voxel.getCenter()) < 0)
        cpt++;
    return cpt == 9;
}

bool prog_3D::Shape::isVoxelOut(prog_3D::Voxel const &voxel) {
    int cpt = 0;
    for (int i = 0; i < 8; ++i)
        if (equation(voxel.getVertices()[i]) > 0)
            cpt++;

    if (equation(voxel.getCenter()) > 0)
        cpt++;
    return cpt == 9;
}

bool prog_3D::Shape::isOnVoxelBorder(prog_3D::Voxel const &voxel) {

    //return !isInVoxel(voxel)&& !isVoxelOut(voxel);
    //return intersect(voxel.getCenter(), voxel.getLength()*2);
    int cptOut = 0;
    int cptIn = 0;
    for (int i = 0; i < 8; ++i) {
        double equaSolve = equation(voxel.getVertices()[i]);
        if (equaSolve < 0)
            cptIn++;
        else if (equaSolve > 0)
            cptOut++;
    }
    if (equation(voxel.getCenter()) < 0)
        cptIn++;
    else
        cptOut++;
    return cptIn != 0 && cptOut != 0;
}
