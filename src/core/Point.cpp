#include "Point.hpp"
#include "Vector.hpp"

namespace prog_3D {

    Point::Point() : Point(0, 0, 0) {
    }

    Point::Point(double x, double y, double z) : x(x), y(y), z(z) {
    }

    Point::Point(Point& p) : Point(p.getX(), p.getY(), p.getZ()) {
    }

    Point::~Point() {
    }

    void Point::setX(double x) {
        this->x = x;
    }

    void Point::setY(double y) {
        this->y = y;
    }

    void Point::setZ(double z) {
        this->z = z;
    }

    double Point::getX()
    {
        return this->x;
    }

    double Point::getY()
    {
        return this->y;
    }

    double Point::getZ()
    {
        return this->z;
    }

    Point& Point::projectOnLine(Point& p1Line, Point& p2Line)
    {
        Vector ba(p1Line,*this);
        Vector bc(p1Line,p2Line);
        bc.normalize();
        double ba2Norm = ba.scalar(bc)/ bc.norm();
        return *new Point(
                p1Line.getX() + bc.getX()*ba2Norm,
                p1Line.getY() + bc.getY()*ba2Norm,
                p1Line.getZ() + bc.getZ()*ba2Norm
        );
    }

    Point& Point::projectOnLine(Vector& vector)
    {

        //vector bc dans la méthode précédente
        //TODO
        Point origin(0,0,0);
        Vector ba(origin,*this);
        vector.normalize();
        double ba2Norm = ba.scalar(vector)/vector.norm();
       return *new Point(
                vector.getX()*ba2Norm,
                vector.getY()*ba2Norm,
                vector.getZ()*ba2Norm
       );
    }

    Point& Point::projectOnPlan(Point& pointOnPlane, Vector& normalOfPlan)
    {
        Vector ma(*this,pointOnPlane);
        double norm = ma.scalar(normalOfPlan)/normalOfPlan.norm();

        return * new Point(
                getX() - normalOfPlan.getX() * norm,
                getY() - normalOfPlan.getY() * norm,
                getZ() - normalOfPlan.getZ() * norm
        );
    }

    Point& Point::apply(Vector &vector)
    {
        return * new Point
                (
                        getX() + vector.getX(),
                        getY() + vector.getY(),
                        getZ() + vector.getZ()
                );
    }


}