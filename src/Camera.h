#ifndef CAMERA_H
#define CAMERA_H

#include "Maths/Vector.h"

class Camera {
public:
    Camera();

    Camera(Vector aEye, Vector aCenter, Vector aUp, double Height, double Width);

    void CalculatePlaneNormals();

    Vector Position() {
        return m_vPosition;
    };

    Vector View() {
        return m_vView;
    };

    Vector UpVector() {
        return m_vUpVector;
    };

    Vector P0() {
        return p0;
    };

    Vector P1() {
        return p1;
    };

    Vector P2() {
        return p2;
    };

    Vector P3() {
        return p3;
    };

private:
    Vector p0;
    Vector p1;
    Vector p2;
    Vector p3;

    double h, w;

    Vector m_vPosition; // The camera's position
    Vector m_vView; // The camera's view
    Vector m_vUpVector; // The camera's up vector
};

#endif
