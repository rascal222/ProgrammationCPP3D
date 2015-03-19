//
// Created by beugnon on 20/03/15.
//

#ifndef _PROGRAMMATION3D_SHAPE_H_
#define _PROGRAMMATION3D_SHAPE_H_

#include "Voxel.hpp"

namespace prog_3D {
    class Shape {

    public:
        virtual double equation(const Point &point) = 0;

        virtual bool isInVoxel(const Voxel &point);

        virtual bool isVoxelOut(const Voxel &point);

        virtual bool isOnVoxelBorder(const Voxel &point);
    };
}


#endif //_PROGRAMMATION3D_SHAPE_H_
