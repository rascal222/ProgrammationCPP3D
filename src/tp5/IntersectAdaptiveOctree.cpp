//
// Created by sbeugnon on 16/03/15.
//

#include <iostream>
#include "IntersectAdaptiveOctree.hpp"
#include "../glWrappers/GlCoreRendering.hpp"

void IntersectAdaptiveOctree::compute() {
    if (!getShape()->isVoxelOut(getCenter()) && !getShape2()->isVoxelOut(getCenter())) {
        if (getResolution() > 1) {
            std::vector<prog_3D::Voxel> voxels = getCenter().cut();
            for (int i = 0; i < voxels.size(); ++i) {
                if (!getShape()->isVoxelOut(voxels.at(i)) && !getShape2()->isVoxelOut(voxels.at(i))) {
                    IntersectAdaptiveOctree o(voxels.at(i), getShape(), getShape2(), getResolution() - 1);
                    o.compute();
                    getChildrens().push_back(o);
                }
            }
        }
    }
}
