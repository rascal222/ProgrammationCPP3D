//
// Created by beugnon on 22/03/15.
//

#ifndef _PROGRAMMATION3D_DIVIDEADAPTIVEOCTREE_H_
#define _PROGRAMMATION3D_DIVIDEADAPTIVEOCTREE_H_

#include "../core/Point.hpp"
#include "../primitives/Shape.hpp"
#include "AdaptativeOctree.hpp"
#include "TwoShapeAdaptiveOctree.hpp"

class DivideAdaptiveOctree : public virtual TwoShapeAdaptiveOctree {
public:
    DivideAdaptiveOctree(prog_3D::Voxel &voxel, prog_3D::Shape *shape, prog_3D::Shape *shape2, int resolution)
            : TwoShapeAdaptiveOctree(voxel, shape, shape2, resolution), AdaptativeOctree(voxel, shape, resolution) {

    };

    virtual void compute();

    virtual ~DivideAdaptiveOctree() {
    };
};


#endif //_PROGRAMMATION3D_DIVIDEADAPTIVEOCTREE_H_
