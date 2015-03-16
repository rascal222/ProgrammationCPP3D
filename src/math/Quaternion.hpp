//
// Created by beugnon on 16/03/15.
//

#ifndef _PROGRAMMATION3D_QUATERNION_HPP_
#define _PROGRAMMATION3D_QUATERNION_HPP_

class Vector3;

class Quaternion {
private:
    double w;
    double x;
    double y;
    double z;

public:
    Quaternion();

    Quaternion(double w, double x, double y, double z);

    Quaternion(Vector3 &axis, double angle);

    virtual ~Quaternion();

    double getW() const {
        return w;
    }

    double getX() const {
        return
    }

    double getY() const;

    double getZ() const;

    //TODO FINISH QUATERNION CLASS
};

#endif //_PROGRAMMATION3D_QUATERNION_HPP_
