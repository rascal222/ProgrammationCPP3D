#ifndef CAMERA_HPP_DEFINED
#define CAMERA_HPP_DEFINED

#include <cmath>
#include <GL/glut.h>

class Camera {
protected:
    float xEye, yEye, zEye, xTarget, yTarget, zTarget, xViewport, yViewport, zViewport = 0;

public:
    Camera();

    virtual ~Camera();

    virtual void computeEvent(float deltaMove1, float deltaMove2, float deltaAngle1, float deltaAngle2) = 0;

    virtual void setXEye(float xEye) {
        Camera::xEye = xEye;
    }

    virtual void setYEye(float yEye) {
        Camera::yEye = yEye;
    }

    virtual void setZEye(float zEye) {
        Camera::zEye = zEye;
    }

    virtual void setXTarget(float xTarget) {
        Camera::xTarget = xTarget;
    }

    virtual void setYTarget(float yTarget) {
        Camera::yTarget = yTarget;
    }

    virtual void setZTarget(float zTarget) {
        Camera::zTarget = zTarget;
    }

    virtual void setXViewport(float xViewport) {
        Camera::xViewport = xViewport;
    }

    virtual void setYViewport(float yViewport) {
        Camera::yViewport = yViewport;
    }

    virtual void setZViewport(float zViewport) {
        Camera::zViewport = zViewport;
    }

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