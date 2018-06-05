#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H

#include "Shape.h"

class Plane : public Shape {
    Vector plane;

public:
    Plane(Vector Normal, LightConstants material);

    float Intersect(const Ray *r) override;

    Vector Normal(Vector p) override;

    Vector GetMaterialColour(Vector point) override;

    void Translatef(Vector u) override;

    void Rotatef(float Angle, Vector Axis) override;
};

#endif
