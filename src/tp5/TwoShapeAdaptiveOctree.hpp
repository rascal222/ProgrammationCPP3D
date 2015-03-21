//
// Created by beugnon on 22/03/15.
//

#ifndef _PROGRAMMATION3D_TWOSHAPEADAPTIVEOCTREE_H_
#define _PROGRAMMATION3D_TWOSHAPEADAPTIVEOCTREE_H_


#include "AdaptativeOctree.hpp"

class TwoShapeAdaptiveOctree : public virtual AdaptativeOctree {
private:
    prog_3D::Shape *shape2;
public:
    TwoShapeAdaptiveOctree(prog_3D::Voxel &voxel, prog_3D::Shape *shape, prog_3D::Shape *shape_2, int resolution) :
            AdaptativeOctree(voxel, shape, resolution), shape2(shape_2) {

    };

    virtual ~TwoShapeAdaptiveOctree() {
    };

    prog_3D::Shape *getShape2() const {
        return shape2;
    };

    virtual void compute() = 0;
};


#endif //_PROGRAMMATION3D_TWOSHAPEADAPTIVEOCTREE_H_
