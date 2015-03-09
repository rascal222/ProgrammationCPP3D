namespace prog_3D {
    Cone::Cone() {
        this->apex = Point::Origin;
        this->axis.setX(0);
        this->axis.setY(10);
        this->axis.setZ(0);
        this->height = 10;
        this->meridians = 5;
    }

    Cone::Cone(float rayon, float height, int meridians, Point &apex, Vector &axis) {
        this->apex = apex;
        this->axis = axis;
        this->meridians = meridians;
        this->rayon = rayon;
        this->height = height;
    }

    Cone::~Cone() {
    }

    void Cone::draw() {
        draw(false);
    }

    Vector perp(const Vector &v) {
        float min = fabs(v.getX());
        Point cardinalAxis(1, 0, 0);

        if (fabs(v.getY()) < min) {
            min = fabs(v.getY());
            cardinalAxis = Point(0, 1, 0);
        }

        if (fabs(v.getZ()) < min) {
            cardinalAxis = Point(0, 0, 1);
        }
        Vector c(cardinalAxis.getX(), cardinalAxis.getY(), cardinalAxis.getZ());
        Vector cross = v.cross(c);
        return cross;
    }

#define M_PI_DIV180 0.01745329251994329576

    void Cone::draw(bool debug) {
        Point c = apex.translate(axis);
        Vector e0 = perp(axis);

        Vector v3 = e0.cross(axis);

        Point e1(v3.getX(), v3.getY(), v3.getZ());

        std::vector <Point> pts;
        for (int i = 0; i < meridians; ++i) {
            double rad = 2 * M_PI * i / meridians;
            double x = c.getX() + (e0.getX() * cos(rad) + e1.getX() * sin(rad)) * rayon;
            double y = c.getY() + (e0.getY() * cos(rad) + e1.getY() * sin(rad)) * rayon;
            double z = c.getZ() + (e0.getZ() * cos(rad) + e1.getZ() * sin(rad)) * rayon;
            Point p(x, y, z);
            pts.push_back(p);
        }

// draw cone top
        glBegin(GL_TRIANGLE_FAN);
        glPoint(apex);
        for (int i = 0; i < meridians; ++i) {
            glPoint(pts.at(i));
        }
        glPoint(pts.at(0));
        glEnd();

        if (debug) {
            glColor3f(1.0f, 0.0f, 0.0f);
            for (int i = 0; i < meridians; ++i) {
                glBegin(GL_LINES);
                glPoint(apex);
                glPoint(pts.at(i));
                glEnd();
            }
        }

    }

}