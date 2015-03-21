//
// Created by beugnon on 22/03/15.
//

#include "UnionAdaptiveOctree.hpp"
#include <iostream>
#include "../glWrappers/GlCoreRendering.hpp"

void UnionAdaptiveOctree::compute() {
    if (getShape()->isOnVoxelBorder(getCenter()) || getShape2()->isOnVoxelBorder(getCenter())) {
        if (getResolution() > 1) {
            std::vector<prog_3D::Voxel> voxels = getCenter().cut();
            for (int i = 0; i < voxels.size(); ++i) {
                UnionAdaptiveOctree o(voxels.at(i), getShape(), getShape2(), getResolution() - 1);
                o.compute();
                if (getShape()->isOnVoxelBorder(voxels.at(i)) || getShape2()->isOnVoxelBorder(voxels.at(i))) {
                    getChildrens().push_back(o);
                }
            }
        }
    }
}
