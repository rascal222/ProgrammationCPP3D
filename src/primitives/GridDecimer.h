//
// Created by beugnon on 19/04/15.
//

#ifndef PROGRAMMATION3D_GRIDDECIMER_H
#define PROGRAMMATION3D_GRIDDECIMER_H
#include <vector>
#include <map>

#include "GridVoxel.h"
#include "Grid.h"
#include "../meshing/TopoMesh.h"

class GridDecimer {

private:
    Grid* grid;
    TopoMesh* tm;

    std::vector<GridVoxel*> points;

public:
    GridDecimer(Grid* grid,TopoMesh* tm) {
        this->grid = grid;
        this->tm = tm;
    }

    Mesh reduceMesh() {

        std::cout << "before adding in gridvoxel" <<std::endl;
        for(TopoPoint* p : tm->getPoints()) {
            for(GridVoxel* gv : grid->getVoxels()) {
                if(gv->inVoxel(*p)) {
                    gv->addTopoPoint(p);
                    break;
                }
            }
        }
        std::cout << "before new mesh"<<std::endl;
        Mesh newMesh;
        std::map<GridVoxel*,int> assoc;
        std::cout << "before extract" << std::endl;
        std::vector<GridVoxel*> ex = grid->extract();
        std::cout << ex.size() << std::endl;
        std::cout << "after extract"<<std::endl;

        for(GridVoxel* gv : ex) {
            newMesh.points.push_back(gv->getCenter());
        }
        std::cout << "end new mesh"<<std::endl;

        for(int i=0;i<ex.size();++i) {
            std::cout <<"i:"<< i << std::endl;
            for(int j=i+1; j<ex.size();++j) {
                std::cout << "j:"<<j << std::endl;

                for(int z =j+1;z<ex.size();++z) {
                    if(ex.at(i)->isConnected(ex.at(j),ex.at(z))){
                        prog_3D::IdTriangle triangle(assoc[ex.at(i)],assoc[ex.at(j)],assoc[ex.at(z)]);
                        newMesh.idTriangles.push_back(triangle);
                    }
                }
            }
            std::cout << i << std::endl;
        }
        std::cout << "end reducing" << std::endl;

        return newMesh;
    }
};


#endif //PROGRAMMATION3D_GRIDDECIMER_H
