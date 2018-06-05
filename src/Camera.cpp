#include "Camera.h"

float lm_radians(float Angle) {
    const float PI = 3.141592653589793f;
    return ((2.0f * PI) * Angle) / 360.0f;
}

Camera::Camera() {
    m_vPosition = Vector();
    m_vView = Vector();
    m_vUpVector = Vector();
    h = 0;
    w = 0;
}

Camera::Camera(Vector aEye, Vector aCenter, Vector aUp, double Height, double Width) {
    m_vPosition = aEye; // The camera's position
    m_vView = aCenter; // The camera's view
    m_vUpVector = aUp; // The camera's up vector
    h = Height;
    w = Width;
}

void Camera::CalculatePlaneNormals() {
    Vector vd = m_vPosition - m_vView;
    vd = vd.Normalize();
    Vector vAxis = (m_vView - m_vPosition) * m_vUpVector;
    vAxis = vAxis.Normalize();
    Vector vu = vAxis;
    Vector right = vd * vAxis;
    float thetah = lm_radians(60);
    auto thetav = static_cast<float>(2 * atan(h * tan(thetah / 2) / w));

    p0 = m_vPosition;
    p0.x += vd.x - (right.x * tan(thetah / 2)) - (vu.x * tan(thetav / 2));
    p0.y += vd.y - (right.y * tan(thetah / 2)) - (vu.y * tan(thetav / 2));
    p0.z += vd.z - (right.z * tan(thetah / 2)) - (vu.z * tan(thetav / 2));
    p1 = m_vPosition;
    p1.x += vd.x + (right.x * tan(thetah / 2)) - (vu.x * tan(thetav / 2));
    p1.y += vd.y + (right.y * tan(thetah / 2)) - (vu.y * tan(thetav / 2));
    p1.z += vd.z + (right.z * tan(thetah / 2)) - (vu.z * tan(thetav / 2));
    p2 = m_vPosition;
    p2.x += vd.x + (right.x * tan(thetah / 2)) + (vu.x * tan(thetav / 2));
    p2.y += vd.y + (right.y * tan(thetah / 2)) + (vu.y * tan(thetav / 2));
    p2.z += vd.z + (right.z * tan(thetah / 2)) + (vu.z * tan(thetav / 2));
    p3 = m_vPosition;
    p3.x += vd.x - (right.x * tan(thetah / 2)) + (vu.x * tan(thetav / 2));
    p3.y += vd.y - (right.y * tan(thetah / 2)) + (vu.y * tan(thetav / 2));
    p3.z += vd.z - (right.z * tan(thetah / 2)) + (vu.z * tan(thetav / 2));
    // Left Normal
    //PlaneNormals[0] = p0 * p3;
    // Right Normal
    //PlaneNormals[1] = p1 * p2;
    // Up Normal
    //PlaneNormals[2] = p3 * p2;
    // Down Normal
    //PlaneNormals[3] = p0 * p1;
    // Near Normal
    //PlaneNormals[4] = vp1;
};