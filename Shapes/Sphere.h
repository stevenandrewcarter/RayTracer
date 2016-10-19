#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "Shape.h"
#include "../LightConstants.h"

class Sphere : public Shape {
    Vector Center;
    float r;

public:
    Sphere(float R, LightConstants material, bool Textured);

    float Intersect(const Ray *r) override;

    Vector Normal(Vector p) override;

    Vector GetMaterialColour(Vector point) override;

    void Translatef(Vector u) override;

    void Rotatef(float Angle, Vector Axis) override;
};

#endif
