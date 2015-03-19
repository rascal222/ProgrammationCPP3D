#include "EulerCamera.hpp"

EulerCamera::EulerCamera(float targetX, float targetY, float targetZ, float dist) : Camera(), dist(dist) {
    xTarget = targetX;
    yTarget = targetY;
    zTarget = targetZ;
    xEye = dist * -sinf(angleX * (M_PI / 180)) * cosf((angleY) * (M_PI / 180));
    yEye = dist * -sinf((angleY) * (M_PI / 180));
    zEye = -dist * cosf((angleX) * (M_PI / 180)) * cosf((angleY) * (M_PI / 180));
}

EulerCamera::~EulerCamera() {
}