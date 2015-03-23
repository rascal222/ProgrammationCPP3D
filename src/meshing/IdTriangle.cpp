//
// Created by sbeugnon on 23/03/15.
//

#include "IdTriangle.hpp"
namespace prog_3D {

    IdTriangle::~IdTriangle() {
    }

    std::array <std::pair<int, int>, 3> IdTriangle::getEdges() {
        std::array <std::pair<int, int>, 3> edges;
        edges[0] = std::make_pair<int, int>(getPointId(0), getPointId(1));
        edges[1] = std::make_pair<int, int>(getPointId(1), getPointId(2));
        edges[2] = std::make_pair<int, int>(getPointId(2), getPointId(0));
        return edges;
    };

    bool IdTriangle::isNeighbours(IdTriangle& triangle)
    {
        bool found = false;
        for(int i=0;i<3 && !found;++i)
        {
            for(int j=i+1;j<3 && !found;++j)
            {
                for(int k=0;k<3 && !found;++k)
                {
                    for(int h=k+1;h<3 && !found;++h)
                    {
                        if(getPointId(i)==getPointId(k) && getPointId(j)==getPointId(h))
                        {
                            found=true;
                        }
                    }
                }
            }
        }

        return found;
    }
}