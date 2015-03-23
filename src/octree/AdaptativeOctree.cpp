//
// Created by sbeugnon on 16/03/15.
//

#include <iostream>
#include "AdaptativeOctree.hpp"
#include "../glWrappers/GlCoreRendering.hpp"

void AdaptativeOctree::compute() {
    if (shape->isOnVoxelBorder(center)) {
        if (resolution > 1) {
            std::vector<prog_3D::Voxel> voxels = center.cut();
            for (int i = 0; i < voxels.size(); ++i) {

                if (!shape->isVoxelOut(voxels.at(i))) {
                    AdaptativeOctree o(voxels.at(i), shape, resolution - 1);
                    o.compute();
                    children.push_back(o);
                }

            }

        }
    } else if (shape->isInVoxel(center)) {
        // std::cout << "is In"<<std::endl;
    } else {
        // std::cout << "is Out" << std::endl;
    }

}

void AdaptativeOctree::draw(bool debug, bool fillLeaves) {
    bool light = glIsEnabled(GL_LIGHTING);
    if (debug) {
        glDisable(GL_LIGHTING);
        drawPoint(getCenter().getCenter());
    }
    if (isLeaf()) {
        getCenter().draw(debug, fillLeaves);
    }
    else {
        if (debug)
            getCenter().draw(debug, false);
        for (int i = 0; i < getChildrens().size(); ++i) {
            getChildrens().at(i).draw(debug, fillLeaves);
        }
    }

    if (light && !glIsEnabled(GL_LIGHTING))
        glEnable(GL_LIGHTING);


}

AdaptativeOctree::~AdaptativeOctree() {

}
