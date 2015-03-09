#ifndef PROG_3D_CONE_HPP_DEFINED
#define PROG_3D_CONE_HPP_DEFINED

#include "../core/Point.hpp"
#include "../core/Vector.hpp"

namespace prog_3D {

    class Cone {
    private :
        float rayon;
        float height;
        Point apex;
        Vector axis;
        int meridians;
    public:
        Cone();

        Cone(float, float, int, Point &, Vector &);

        ~Cone();

        virtual void draw();

        virtual void draw(bool);
    };
}

#endif