#ifndef EULER_CAMERA_HPP_DEFINED
#define EULER_CAMERA_HPP_DEFINED

#include "Camera.hpp"
#include <cmath>
#include <GL/glut.h>

class EulerCamera : public virtual Camera {
private:
    float angleX = 0.f;
    float angleY = 0.f;
    float dist = 1;
public:
    EulerCamera(float targetX, float targetY, float targetZ, float dist);

    virtual ~EulerCamera();

    virtual void computeEvent(float deltaMove1, float deltaMove2, float deltaAngle1, float deltaAngle2) {
        angleX += deltaAngle1;
        angleY += deltaAngle2;
        dist += deltaMove1;
        dist -= deltaMove2;

        xEye = dist * -sinf(angleX * (M_PI / 180)) * cosf((angleY) * (M_PI / 180));
        yEye = dist * -sinf((angleY) * (M_PI / 180));
        zEye = -dist * cosf((angleX) * (M_PI / 180)) * cosf((angleY) * (M_PI / 180));
    }

};

#endif