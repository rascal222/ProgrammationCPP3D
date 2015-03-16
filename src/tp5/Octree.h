//
// Created by sbeugnon on 16/03/15.
//

#ifndef _PROGRAMMATION3D_OCTREE_H_
#define _PROGRAMMATION3D_OCTREE_H_


class Octree
{
    Point center;
    Point halfDimension;

    Octree* children[8];
    OctreePoint* data;
};


#endif //_PROGRAMMATION3D_OCTREE_H_
