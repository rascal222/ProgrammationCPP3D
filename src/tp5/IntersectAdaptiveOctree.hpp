//
// Created by beugnon on 22/03/15.
//

#ifndef _PROGRAMMATION3D_MINUSADAPTIVEOCTREE_H_
#define _PROGRAMMATION3D_MINUSADAPTIVEOCTREE_H_

#include "TwoShapeAdaptiveOctree.hpp"
#include "../core/Point.hpp"
#include "../primitives/Shape.hpp"

class IntersectAdaptiveOctree : public virtual TwoShapeAdaptiveOctree {

public:
    IntersectAdaptiveOctree(prog_3D::Voxel &voxel, prog_3D::Shape *shape, prog_3D::Shape *shape2, int resolution)
            : TwoShapeAdaptiveOctree(voxel, shape, shape2, resolution), AdaptativeOctree(voxel, shape, resolution) {

    };

    virtual ~IntersectAdaptiveOctree() {
    };

    virtual void compute();
};


#endif //_PROGRAMMATION3D_MINUSADAPTIVEOCTREE_H_
