#ifndef MATRIX4OPERATIONS_H
#define MATRIX4OPERATIONS_H

#include "Matrix4.h"
#include "Vector.h"

class Matrix4Operations {
public:
    Matrix4Operations() = default;

    /*Matrix4 Translatef(Matrix4 M, Vector u)
      {
          Matrix4 T = Matrix4( Vector(1, 0, 0, u.x), Vector(0 , 1 , 0, u.y), Vector(0, 0, 1, u.z), Vector(0, 0, 0, 1));
          return T * M;//Matrix4(R1 , R2 , R3 , R4);
      };

      Matrix4 Rotatef(Vector u, double Angle)
      {
          return Matrix4();
      };*/

    void SetTranslate(Vector u) {
        Vector R1 = Vector(1, 0, 0, u.x);
        Vector R2 = Vector(0, 1, 0, u.y);
        Vector R3 = Vector(0, 0, 1, u.z);
        Vector R4 = Vector(0, 0, 0, u.t);
        T = Matrix4(R1, R2, R3, R4);
    };

    Vector Translate(Vector u) {
        return T * u;
    };

    Vector Rotate(float angle, Vector Axis, Vector RotateVector) {
        Vector vNewView;
        float x = Axis.x;
        float y = Axis.y;
        float z = Axis.z;
        Vector vView = RotateVector;

        // Calculate the sine and cosine of the angle once
        auto cosTheta = cos(angle);
        auto sinTheta = sin(angle);

        // Find the new x position for the new rotated point
        vNewView.x = (cosTheta + (1 - cosTheta) * x * x) * vView.x;
        vNewView.x += ((1 - cosTheta) * x * y - z * sinTheta) * vView.y;
        vNewView.x += ((1 - cosTheta) * x * z + y * sinTheta) * vView.z;

        // Find the new y position for the new rotated point
        vNewView.y = ((1 - cosTheta) * x * y + z * sinTheta) * vView.x;
        vNewView.y += (cosTheta + (1 - cosTheta) * y * y) * vView.y;
        vNewView.y += ((1 - cosTheta) * y * z - x * sinTheta) * vView.z;

        // Find the new z position for the new rotated point
        vNewView.z = ((1 - cosTheta) * x * z - y * sinTheta) * vView.x;
        vNewView.z += ((1 - cosTheta) * y * z + x * sinTheta) * vView.y;
        vNewView.z += (cosTheta + (1 - cosTheta) * z * z) * vView.z;

        RotateVector = RotateVector + vNewView;
        return RotateVector;
    };

private:
    Matrix4 T;
};

#endif
