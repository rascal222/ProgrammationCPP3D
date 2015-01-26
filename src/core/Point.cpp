#include "Point.hpp"
#include "Vector.hpp"
#include <ostream>

namespace prog_3D {

	Point::Point() : Point(0, 0, 0) {
	}

	Point::Point(double x, double y, double z) : x(x), y(y), z(z) {
	}

	Point::Point(Point& p) : Point(p.getX(), p.getY(), p.getZ()) {
	}
    Point::Point(const Point& p) : Point(p.getX(), p.getY(), p.getZ()) {
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

	double Point::getX() const
	{
		return this->x;
	}
	double Point::getY() const
	{
		return this->y;
	}

	double Point::getZ() const
	{
		return this->z;
	}

	Point Point::projectOnLine(const Point& p1Line,const Point& p2Line)
	{
		Vector ba(p1Line,*this);
		Vector bc(p1Line,p2Line);
		bc.normalize();
		double ba2Norm = ba.scalar(bc)/ bc.norm();
		Point p(
				p1Line.getX() + bc.getX()*ba2Norm,
				p1Line.getY() + bc.getY()*ba2Norm,
				p1Line.getZ() + bc.getZ()*ba2Norm
		);
		return p;
	}

	Point Point::projectOnLine(const Vector& vector,const Point& point)
	{
        Point p(0,0,0);
        p.setX(point.getX()+vector.getX());
        p.setY(point.getY()+vector.getY());
        p.setZ(point.getZ()+vector.getZ());
        return projectOnLine(point,p);
	}

	Point Point::projectOnPlan(const Point& pointOnPlane,Vector& normalOfPlan)
	{
		Vector ma(*this,pointOnPlane);
        normalOfPlan.normalize();
		double norm = ma.scalar(normalOfPlan)/normalOfPlan.norm();
		Point p(
				getX() - normalOfPlan.getX() * norm,
				getY() - normalOfPlan.getY() * norm,
				getZ() - normalOfPlan.getZ() * norm
		);
		return p;
	}

	Point Point::translate(const Vector &vector)
	{
		Point p(
				getX() + vector.getX(),
				getY() + vector.getY(),
				getZ() + vector.getZ()
        );
		return p;
	}

	std::ostream& operator<<( std::ostream &stream,const Point& point)
	{
		stream <<"Point{"<< point.getX()<<";"<<point.getY()<<";"<<point.getZ()<<"}";
		return stream;
	}

}