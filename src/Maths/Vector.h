#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

class Vector {
public:

    Vector() {
        x = 0;
        y = 0;
        z = 0;
        t = 1;
    };

    Vector(float nx, float ny, float nz) {
        x = nx;
        y = ny;
        z = nz;
        t = 1;
    };

    Vector(float nx, float ny) {
        x = nx;
        y = ny;
        z = 0;
    };

    Vector(float x1, float x2, float x3, float x4) {
        x = x1;
        y = x2;
        z = x3;
        t = x4;
    };

    void set(float nx, float ny, float nz) {
        x = nx;
        y = ny;
        z = nz;
    };

    void set(float nx, float ny) {
        x = nx;
        y = ny;
        z = 0;
    };

    bool operator==(const Vector &a) {
        return (x == a.x) && (y == a.y) && (z == a.z);
    };

    bool operator!=(const Vector &a) {
        return (x != a.x) || (y != a.y) || (z == a.z);
    };


    Vector operator+(const Vector &a) const {
        return {x + a.x, y + a.y, z + a.z};
    };

    Vector operator-(const Vector &a) const {
        return {x - a.x, y - a.y, z - a.z};
    };

    Vector operator*(const Vector &a) const {
        Vector vNormal;

        // Calculate the cross product with the non communitive equation
        vNormal.x = ((y * a.z) - (z * a.y));
        vNormal.y = ((z * a.x) - (x * a.z));
        vNormal.z = ((x * a.y) - (y * a.x));

        // Return the cross product
        return vNormal;
    };

    Vector operator*(const float &a) const {
        return {x * a, y * a, z * a, t * a};
    };

    Vector operator/(const float &a) const {
        return {x / a, y / a, z / a, t / a};
    };

    float Magnitude() {
        return sqrt((x * x) + (y * y) + (z * z));
    };

    Vector Normalize() {
        float n = Magnitude();
        return {x / n, y / n, z / n};
    };


    float x;
    float y;
    float z;
    float t;
};

extern float DotProduct(Vector u, Vector v);

extern float Norm(Vector u);

extern float Distance(Vector p1, Vector p2);

extern Vector Parametric(Vector p0, Vector p1, float t);

#endif
