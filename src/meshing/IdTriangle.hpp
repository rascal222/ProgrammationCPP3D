//
// Created by sbeugnon on 23/03/15.
//

#ifndef _PROGRAMMATION3D_IDTRIANGLE_H_
#define _PROGRAMMATION3D_IDTRIANGLE_H_

#include <array>
#include <utility>


namespace prog_3D {

    class IdTriangle {
    private:
        std::array<int, 3> points;

    public:
        IdTriangle(std::array<int, 3> &points) : points(points) {
        };

        ~IdTriangle();

        int getPointId(int id)
        {
            return points[id];
        }
        std::array<int,3>& getIndices()
        {
            return points;
        }

        int* getIndicesC()
        {
            return &points[0];
        }

        std::array <std::pair<int, int>, 3> getEdges();

        bool isNeighbours(IdTriangle& triangle);

    };
}

#endif //_PROGRAMMATION3D_IDTRIANGLE_H_
