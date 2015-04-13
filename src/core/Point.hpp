#ifndef PROG_3D_POINT_HPP_DEFINED
#define PROG_3D_POINT_HPP_DEFINED


#include <ostream>


/**
* \namespace This namespace gathers all classes for 3D programming
*/
namespace prog_3D {

    class Vector;
    class Point {
    private:
        double x;
        double y;
        double z;

    public:
        static const Point Origin;
        Point();

        Point(double x, double y, double z);

        Point(Point&);

        Point(const Point&);

        virtual ~Point();

        void set(double x, double y, double z);

        void setX(double x);

        void setY(double y);

        void setZ(double z);

        double getX() const;

        double getY() const;

        double getZ() const;

        Point projectOnLine(const Point& p1Line,const Point& p2Line);

        Point projectOnLine(const Vector& vector,Point& point);

        Point projectOnPlan(const Point& pointOnPlane,Vector& normalOfPlan);

        Point translate(const Vector& vector) const;

        bool operator==(const Point& point) const;

    };
    /**
    * \brief Override the operator << for an instance of ostream and a point
    * @param stream a stream
    * @param vector a point to show
    * \return the stream
    */
    std::ostream &operator<<( std::ostream &stream, const Point& point);
    std::ostream &operator<<( std::ostream &stream, const Point* point);
}

#endif