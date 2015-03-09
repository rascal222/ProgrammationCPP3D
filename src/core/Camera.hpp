#ifndef CAMERA_HPP_DEFINED
#define CAMERA_HPP_DEFINED

#include <cmath>
#include <GL/glut.h>

class Camera {
protected:
    float xEye, yEye, zEye, xTarget, yTarget, zTarget, xViewport, yViewport, zViewport;

public:
    Camera();

    virtual ~Camera();

    virtual void computeEvent(float deltaMove1, float deltaMove2, float deltaAngle1, float deltaAngle2) = 0;

    virtual float getXeye() {
        return xEye;
    }

    virtual float getYeye() {
        return yEye;
    }

    virtual float getZeye() {
        return zEye;
    }

    virtual float getXtarget() {
        return xTarget;
    }

    virtual float getYtarget() {
        return yTarget;
    }

    virtual float getZtarget() {
        return zTarget;
    }

    virtual float getXviewport() {
        return xViewport;
    }

    virtual float getYviewport() {
        return yViewport;
    }

    virtual float getZviewport() {
        return zViewport;
    }

    inline void place() {
        gluLookAt(
                getXeye(), getYeye(), getZeye(),
                getXtarget(), getYtarget(), getZtarget(),
                getXviewport(), getYviewport(), getZviewport());
    }

};

#endif