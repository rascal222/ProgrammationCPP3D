//
// Created by beugnon on 22/03/15.
//

#include "DivideAdaptiveOctree.hpp"
#include <iostream>
#include "../glWrappers/GlCoreRendering.hpp"

void DivideAdaptiveOctree::compute() {
    if (!getShape()->isVoxelOut(getCenter())) {
        if (getResolution() > 1) {
            std::vector<prog_3D::Voxel> voxels = getCenter().cut();
            int cpt = 0;
            for (int i = 0; i < voxels.size(); ++i) {
                DivideAdaptiveOctree o(voxels.at(i), getShape(), getShape2(), getResolution() - 1);
                o.compute();
                if ((!getShape()->isVoxelOut(voxels.at(i))) && !getShape()->isInVoxel(voxels.at(i))
                        && !(getShape2()->isInVoxel(voxels.at(i))
                        || getShape2()->isOnVoxelBorderCenterIn(voxels.at(i)))) {
                    getChildrens().push_back(o);
                }
                else cpt++;
            }
            std::cout << cpt << " discarded" << std::endl;
        }
    }

}

