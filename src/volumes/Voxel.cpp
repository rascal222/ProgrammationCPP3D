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

    virtual Point *Voxel::getVertices() const {
        if (_cached != nullptr)
            return _cached;
        else {
            _cached = new Point[8];
            _cached[0].set(
                    (getCenter().getX() - 0.5) * getLength(),
                    (getCenter().getY() - 0.5) * getLength(),
                    (getCenter().getZ() - 0.5) * getLength()
            );
            _cached[1].set(
                    (getCenter().getX() + 0.5) * getLength(),
                    (getCenter().getY() - 0.5) * getLength(),
                    (getCenter().getZ() - 0.5) * getLength()
            );
            _cached[2].set(
                    (getCenter().getX() + 0.5) * getLength(),
                    (getCenter().getY() + 0.5) * getLength(),
                    (getCenter().getZ() - 0.5) * getLength()
            );
            _cached[3].set(
                    (getCenter().getX() - 0.5) * getLength(),
                    (getCenter().getY() + 0.5) * getLength(),
                    (getCenter().getZ() - 0.5) * getLength()
            );
            _cached[4].set(
                    (getCenter().getX() - 0.5) * getLength(),
                    (getCenter().getY() - 0.5) * getLength(),
                    (getCenter().getZ() + 0.5) * getLength()
            );
            _cached[5].set(
                    (getCenter().getX() + 0.5) * getLength(),
                    (getCenter().getY() - 0.5) * getLength(),
                    (getCenter().getZ() + 0.5) * getLength()
            );
            _cached[6].set(
                    (getCenter().getX() + 0.5) * getLength(),
                    (getCenter().getY() + 0.5) * getLength(),
                    (getCenter().getZ() + 0.5) * getLength()
            );
            _cached[7].set(
                    (getCenter().getX() - 0.5) * getLength(),
                    (getCenter().getY() + 0.5) * getLength(),
                    (getCenter().getZ() + 0.5) * getLength()
            );

        }
        return _cached;
    }

    virtual void draw(bool) {

    }
}