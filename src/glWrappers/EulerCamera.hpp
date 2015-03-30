#ifndef EULER_CAMERA_HPP_DEFINED
#define EULER_CAMERA_HPP_DEFINED

#include "Camera.hpp"
#include <cmath>
#include <GL/glut.h>

class EulerCamera : public virtual Camera {
private:
    float angleX = 270.f;//Theta
    float angleY = 180.f;//Phi
    float dist = 1;
public:
    EulerCamera(float targetX, float targetY, float targetZ, float dist);

    virtual ~EulerCamera();


    float getDist() const {
        return dist;
    }

    void setDist(float dist) {
        EulerCamera::dist = dist;
    }

    float getAngleY() const {
        return angleY;
    }

    void setAngleY(float angleY) {
        angleY = angleY;
    }

    float getAngleX() const {
        return angleX;
    }

    void setAngleX(float angleX) {
        angleX = angleX;
    }

    virtual void computeEvent(float deltaMove1, float deltaMove2, float deltaAngle1, float deltaAngle2) {
        angleX += deltaAngle1;//
        angleY += deltaAngle2;
        dist += deltaMove1;
        angleX = fmod((double)angleX,360.0);
        angleY = fmod((double)angleY,360.0);

        xEye = getXtarget() + dist * -sinf(angleX * (M_PI / 180)) * cosf((angleY) * (M_PI / 180));
        yEye = getYtarget() + dist * -sinf((angleY) * (M_PI / 180));
        zEye = getZtarget() - dist * cosf((angleX) * (M_PI / 180)) * cosf((angleY) * (M_PI / 180));
    }

    void setXEye(float xEye){
        Camera::setXEye(xEye);
    }

    void setYEye(float yEye) {
        Camera::setYEye(yEye);
    }

    void setZEye(float zEye) {
        Camera::setZEye(zEye);
    }

    void setXTarget(float xTarget) {
        Camera::setXTarget(xTarget);
    }

    void setYTarget(float yTarget) {
        Camera::setYTarget(yTarget);
    }

    void setZTarget(float zTarget) {
        Camera::setZTarget(zTarget);
    }

    void setXViewport(float xViewport) {
        Camera::setXViewport(xViewport);
    }

    void setYViewport(float yViewport) {
        Camera::setYViewport(yViewport);
    }

    void setZViewport(float zViewport) {
        Camera::setZViewport(zViewport);
    }

    float getXeye() {
        return Camera::getXeye();
    }

    float getYeye() {
        return Camera::getYeye();
    }

    float getZeye() {
        return Camera::getZeye();
    }

    float getXtarget() {
        return Camera::getXtarget();
    }

    float getYtarget() {
        return Camera::getYtarget();
    }

    float getZtarget() {
        return Camera::getZtarget();
    }

    float getXviewport() {
        return Camera::getXviewport();
    }

    float getYviewport() {
        return Camera::getYviewport();
    }

    float getZviewport() {
        return Camera::getZviewport();
    }


};

#endif
