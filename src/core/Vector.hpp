#ifndef PROG_3D_VECTOR_HPP_DEFINED
#define PROG_3D_VECTOR_HPP_DEFINED
#include <ostream>
#include "core-declaration.hpp"
/**
* \namespace This namespace gathers all classes for 3D programming
*/
namespace prog_3D {

    /**
        \class Vector
        \brief Implementation of class Vector
     */
    class Vector {
    private:
        /// \brief coordinate in X axis
        double x;
        /// \brief coordinate in Y axis
        double y;
        /// \brief coordinate in Z axis
        double z;

    public:
        /// \brief Shorthand for writing Vector(0, 0, 0).
        static const Vector ZERO;
        /// \brief Shorthand for writing Vector(1, 1, 1).
        static const Vector ONE;
        /// \brief Shorthand for writing Vector(0, 1, 0).
        static const Vector UP;
        /// \brief Shorthand for writing Vector(0, -1, 0).
        static const Vector DOWN;
        /// \brief Shorthand for writing Vector(0, 0, 1).
        static const Vector FORWARD;
        /// \brief Shorthand for writing Vector(0, 0, -1).
        static const Vector BACK;
        /// \brief Shorthand for writing Vector(-1, 0, 0).
        static const Vector LEFT;
        /// \brief Shorthand for writing Vector(1, 0, 0).
        static const Vector RIGHT;

        /// \brief Empty Constructor.
        Vector();

        /**
        *  \brief Constructor.
        *  @param x Coordinate in X axis
        *  @param y Coordinate in Y axis
        *  @param z Coordinate in Z axis
        */
        Vector(double x, double y, double z);

        /**
        *  \brief Constructor by points.
        *  @param p1 First point
        *  @param p2 Second point
        */
        Vector(const Point& p1,const Point& p2);

        /**
        *  \brief Constructor by copy.
        *  @param p Vector to copy
        */
        Vector(Vector& p);

        Vector(const Vector& p);

        /// \brief Destructor
        virtual ~Vector();

        /**
        * \brief Setter.
        * @param x new coordinate in X axis
        */
        void setX(double x);

        /**
        * \brief Setter.
        * @param y new coordinate in Y axis
        */
        void setY(double y);

        /**
        * \brief Setter.
        * @param z new coordinate in Z axis
        */
        void setZ(double z);

        /**
        * \brief Getter.
        * \return coordinate in X axis
        */
        double getX() const;

        /**
        * \brief Getter.
        * \return coordinate in Y axis
        */
        double getY() const;

        /**
        * \brief Getter.
        * \return coordinate in Z axis
        */
        double getZ() const;

        /**
        * \brief Return the length of this vector.
        * \return the norm of vector
        */
        double norm() const;

        /**
        * \brief Normalize this vector.
        * \return the previous norm of this vector
        */
        double normalize();

        /**
        * \brief Return the scalar value between this vector and another one.
        * @param vector the second vector
        * \return the scalar value
        */
        double scalar(const Vector& vector) const;

        /**
        * \brief Return the vectorial product between this vector and another one.
        * @param vector the second vector
        * \return the vectorial product which is perpendicular with this vector and the other one.
        */
        Vector cross(const Vector& vector) const;

        /**
        * \brief Return the angle between this vector and another one.
        * @param vector the second vector
        * \return the angle between two vector
        */
        double getAngle(const Vector& vector) const;

        /**
        * \brief Print this vector in the stream.
        * @param stream the stream where we print this instance
        */
        void print(std::ostream& stream) const;

        /**
        * \brief Operator *= double.
        * @param d a scalar value
        * \return this vector multiplied by the scalar value
        */
        Vector& operator*= (double d);
        /**
        * \brief Operator /= double.
        * @param d a scalar value
        * \return this vector divided by the scalar value
        */
        Vector& operator/= (double d);
    };

    //SPECIFIC OVERRIDE FUNCTIONS

    /**
    * \brief Override the operator << for an instance of ostream and a vector
    * @param stream a stream
    * @param vector a vector to show
    * \return the stream
    */
    std::ostream& operator<<( std::ostream &stream,const Vector& vector);


    /**
    * \brief Override the operator * (for multiplication with a scalar for an instance of vector
    * @param d a scalar value
    * @param vector a vector
    * \return the vector multiplied with the scalar
    */
    Vector operator* (double d,Vector const& vector);
    /**
    * \brief Override the operator * (for multiplication with a scalar for an instance of vector
    * @param vector a vector
    * @param d a scalar value
    * \return the vector multiplied with the scalar
    */
    Vector operator* (Vector const& vector,double d);

    /**
    * \brief Override the operator / (to divide an instance of vector with a scalar
    * @param d a scalar value
    * @param vector a vector
    * \return the vector divided with the scalar
    */
    Vector operator/ (double d,Vector const& vector);
    /**
    * \brief Override the operator * (to divide an instance of vector with a scalar
    * @param vector a vector
    * @param d a scalar value
    * \return the vector divided with the scalar
    */
    Vector operator/ (Vector const& vector,double d);


}

#endif