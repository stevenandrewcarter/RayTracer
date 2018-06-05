#include "Vector.h"

float DotProduct(Vector u, Vector v) {
    return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
}

float Norm(Vector u) {
    return sqrt((u.x * u.x) + (u.y * u.y) + (u.z * u.z) + (u.t * u.t));
}

float Distance(Vector p1, Vector p2) {
    double ReturnAnswer;
    double x = p2.x - p1.x;
    double y = p2.y - p1.y;
    double z = p2.z - p1.z;
    ReturnAnswer = sqrt((x * x) + (y * y) + (z * z));
    return (float) ReturnAnswer;
}

Vector Parametric(Vector p0, Vector p1, float t) {
    float d1 = p1.x - p0.x;
    float d2 = p1.y - p0.y;
    float d3 = p1.z - p0.z;
    float X = p0.x + (d1 * t);
    float Y = p0.y + (d2 * t);
    float Z = p0.z + (d3 * t);
    Vector returnPoint = Vector(X, Y, Z);
    return returnPoint;
}
