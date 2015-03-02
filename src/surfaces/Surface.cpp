#include "Surface.hpp"
namespace prog_3D {
    Surface::Surface(int nbU, int nbV) : nbPointU(nbU), nbPointV(nbV) {
    }

    Surface::~Surface() {
    }

    void Surface::setPointNumberForU(int nb) {
        nbPointU = nb;
    }

    void Surface::setPointNumberForV(int nb) {
        nbPointV = nb;
    }

    int Surface::getPointNumberForU() {
        return nbPointU;
    }

    int Surface::getPointNumberForV() {
        return nbPointV;
    }
}