#ifndef PROG_3D_POINT_HPP_DEFINED
#define PROG_3D_POINT_HPP_DEFINED



namespace prog_3D {
    class Vector;


    class Point {
    private:
        double x;
        double y;
        double z;

    public:
        Point();

        Point(double x, double y, double z);

        Point(Point& p);

        virtual ~Point();

        void setX(double x);

        void setY(double y);

        void setZ(double z);

        double getX();

        double getY();

        double getZ();

        Point projectOnLine(Point& p1Line, Point& p2Line);

        Point projectOnLine(Vector& vector);

        Point projectOnPlan(Point& pointOnPlane, Vector& normalOfPlan);

    };
}

#endif