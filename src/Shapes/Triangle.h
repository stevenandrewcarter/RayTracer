#ifndef RAYTRACER_TRIANGLE_H
#define RAYTRACER_TRIANGLE_H

#include "Shape.h"

class Triangle : Shape {
    Vector v0, v1, v2;

public:
    Triangle(Vector v0, Vector v1, Vector v2, LightConstants material);

    float Intersect(const Ray *r) override;

    Vector Normal(Vector p) override;

    Vector GetMaterialColour(Vector point) override;

    void Translatef(Vector u) override;

    void Rotatef(float Angle, Vector Axis) override;
};

#endif
