namespace prog_3D {
    Voxel::Voxel(Point &center, double rayon) : center(center), length(rayon) {
    }

    Voxel::~Voxel() {
    }

    Point &Voxel::getCenter() const {
        return center;
    }

    double Voxel::getLength() const {
        return length;
    }
}