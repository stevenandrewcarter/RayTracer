#ifndef MATRIX4_H
#define MATRIX4_H

#include "Maths/Vector.h"

class Matrix4 {
public:
    Matrix4() {
        R1 = Vector();
        R2 = Vector();
        R3 = Vector();
        R4 = Vector();
    };

    //Matrix4(float Matrix4F[])
    Matrix4(Vector RowA, Vector RowB, Vector RowC, Vector RowD) {
        R1 = RowA;
        R2 = RowB;
        R3 = RowC;
        R4 = RowD;
        //matrix4f = Matrix4F;
    };

    //	Matrix4 Translatef(Vector u)
    //	{
    //		Matrix T = Matrix4( Vector(1, 0, 0, u.x), Vector(0 , 1 , 0, u.y), Vector(0, 0, 1, u.z), Vector(0, 0, 0, 1));
    //		return T * Matrix4(R1 , R2 , R3 , R4);
    //	};


    Matrix4 operator*(Matrix4 M1) {
        Matrix4 Ret = Matrix4();
        Ret.R1.x = (R1.x * M1.R1.x) + (R1.y * M1.R2.x) + (R1.z * M1.R3.x) + (R1.t * M1.R4.x);
        Ret.R1.y = (R1.x * M1.R1.y) + (R1.y * M1.R2.y) + (R1.z * M1.R3.y) + (R1.t * M1.R4.y);
        Ret.R1.z = (R1.x * M1.R1.z) + (R1.y * M1.R2.z) + (R1.z * M1.R3.z) + (R1.t * M1.R4.z);
        Ret.R1.t = (R1.x * M1.R1.t) + (R1.y * M1.R2.t) + (R1.z * M1.R3.t) + (R1.t * M1.R4.t);

        Ret.R2.x = (R2.x * M1.R1.x) + (R2.y * M1.R2.x) + (R2.z * M1.R3.x) + (R2.t * M1.R4.x);
        Ret.R2.y = (R2.x * M1.R1.y) + (R2.y * M1.R2.y) + (R2.z * M1.R3.y) + (R2.t * M1.R4.y);
        Ret.R2.z = (R2.x * M1.R1.z) + (R2.y * M1.R2.z) + (R2.z * M1.R3.z) + (R2.t * M1.R4.z);
        Ret.R2.t = (R2.x * M1.R1.t) + (R2.y * M1.R2.t) + (R2.z * M1.R3.t) + (R2.t * M1.R4.t);

        Ret.R3.x = (R3.x * M1.R1.x) + (R3.y * M1.R2.x) + (R3.z * M1.R3.x) + (R3.t * M1.R4.x);
        Ret.R3.y = (R3.x * M1.R1.y) + (R3.y * M1.R2.y) + (R3.z * M1.R3.y) + (R3.t * M1.R4.y);
        Ret.R3.z = (R3.x * M1.R1.z) + (R3.y * M1.R2.z) + (R3.z * M1.R3.z) + (R3.t * M1.R4.z);
        Ret.R3.t = (R3.x * M1.R1.t) + (R3.y * M1.R2.t) + (R3.z * M1.R3.t) + (R3.t * M1.R4.t);

        Ret.R4.x = (R4.x * M1.R1.x) + (R4.y * M1.R2.x) + (R4.z * M1.R3.x) + (R4.t * M1.R4.x);
        Ret.R4.y = (R4.x * M1.R1.y) + (R4.y * M1.R2.y) + (R4.z * M1.R3.y) + (R4.t * M1.R4.y);
        Ret.R4.z = (R4.x * M1.R1.z) + (R4.y * M1.R2.z) + (R4.z * M1.R3.z) + (R4.t * M1.R4.z);
        Ret.R4.t = (R4.x * M1.R1.t) + (R4.y * M1.R2.t) + (R4.z * M1.R3.t) + (R4.t * M1.R4.t);

        return Ret;
    };

    Vector operator*(Vector u) {
        Vector Ret = Vector();
        Ret.x = (R1.x * u.x) + (R1.y * u.y) + (R1.z * u.z) + (R1.t * u.t);
        Ret.y = (R2.x * u.x) + (R2.y * u.y) + (R2.z * u.z) + (R2.t * u.t);
        Ret.z = (R3.x * u.x) + (R3.y * u.y) + (R3.z * u.z) + (R3.t * u.t);
        Ret.t = (R4.x * u.x) + (R4.y * u.y) + (R4.z * u.z) + (R4.t * u.t);

        return Ret;
    };

    Vector R1;
    Vector R2;
    Vector R3;
    Vector R4;
private:
};

#endif
