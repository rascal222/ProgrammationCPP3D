//
// Created by sbeugnon on 16/03/15.
//

#ifndef _PROGRAMMATION3D_OCTREE_H_
#define _PROGRAMMATION3D_OCTREE_H_

#include "../primitives/Voxel.hpp"
#include "../primitives/Shape.hpp"

class AdaptativeOctree {
private:
    prog_3D::Voxel center;
    prog_3D::Shape *shape;
    int resolution;
    std::vector<AdaptativeOctree> children;
public:
    AdaptativeOctree(prog_3D::Voxel &voxel, prog_3D::Shape *shape, int resolution)
            : center(voxel), shape(shape), resolution(resolution) {

    };

    virtual ~AdaptativeOctree();

    bool isLeaf() {
        return children.empty();
    };

    virtual prog_3D::Voxel getCenter() {
        return center;
    }


    prog_3D::Shape *getShape() const {
        return shape;
    }

    virtual std::vector<AdaptativeOctree> &getChildrens() {
        return children;
    }


    int getResolution() const {
        return resolution;
    }

    virtual void compute();

    virtual void draw(bool debug, bool fillLeaves);

};


#endif //_PROGRAMMATION3D_OCTREE_H_
