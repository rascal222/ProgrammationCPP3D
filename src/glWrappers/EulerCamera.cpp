#include "EulerCamera.hpp"

EulerCamera::EulerCamera(float targetX, float targetY, float targetZ, float dist) : Camera(), dist(dist) {
    xTarget = targetX;
    yTarget = targetY;
    zTarget = targetZ;
    xEye = getXtarget() + dist * -sinf(angleX * (M_PI / 180)) * cosf((angleY) * (M_PI / 180));
    yEye = getYtarget() + dist * -sinf((angleY) * (M_PI / 180));
    zEye = getZtarget() - dist * cosf((angleX) * (M_PI / 180)) * cosf((angleY) * (M_PI / 180));

}

EulerCamera::~EulerCamera() {
}