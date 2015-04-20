//
// Created by beugnon on 19/04/15.
//

#ifndef PROGRAMMATION3D_GRIDDECIMER_H
#define PROGRAMMATION3D_GRIDDECIMER_H
#include <vector>
#include <map>

#include "GridVoxel.h"
#include "Grid.h"
#include "../octree/AdaptativeOctree.hpp"
#include "../meshing/Mesh.hpp"

class GridDecimer {

private:
    Grid* grid;
    Mesh* tm;

    std::vector<GridVoxel*> points;

public:
    GridDecimer(Grid* grid,Mesh* tm) {
        this->grid = grid;
        this->tm = tm;
    }

    Mesh* reduceMesh() {
        std::map<int,GridVoxel*> attr;
        std::map<GridVoxel*,int> index;
        std::map<GridVoxel*,int> index2;

        for(int i=0;i<tm->points.size();++i) {
            prog_3D::Point p = tm->points.at(i);

            for(GridVoxel* gv : grid->getVoxels()) {
                if(gv->inVoxel(&p)) {
                    attr[i] = gv;

                    gv->addPoint(i);
                    break;
                }
            }
        }
        std::vector<GridVoxel*> extract = grid->extract();
        Mesh* newMesh = new Mesh();
        for(int i=0;i<extract.size();++i) {
            newMesh->points.push_back(extract.at(i)->getCenter());
            index[extract.at(i)] =i;
        }



        for(int i = 0; i< tm->idTriangles.size();++i) {
            newMesh->idTriangles.push_back(tm->idTriangles.at(i));
        }

        for(int i=0;extract.size();++i) {
            for(int j=0;j < extract.at(i)->getInPoints().size();++i) {
                for(int k=0;k<tm->idTriangles.size(); ++k) {
                    if(tm->idTriangles.at(k).havePoint(extract.at(i)->getInPoints().at(j))) {
                        tm->idTriangles.at(k).replace(extract.at(i)->getInPoints().at(j),index[extract.at(i)]);
                    }
                }
            }
        }

        return newMesh;
    }
};


#endif //PROGRAMMATION3D_GRIDDECIMER_H
