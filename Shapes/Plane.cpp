#include "Plane.h"
#include "../IntersectTests.h"
#include "../Matrix4Operations.h"

Plane::Plane(Vector Normal, LightConstants material) {
    plane = Normal;
    Material = material;
    Texture = false;
}

float Plane::Intersect(const Ray *r) {
    float t = 0;
    float u = (DotProduct(plane, r->Source));
    float D = (DotProduct(plane, r->Direction));
    float U = (-1.0f * plane.t) - u;
    t = (U / D);
    return t;
}

Vector Plane::Normal(Vector p) {
    return plane;
}

Vector Plane::GetMaterialColour(Vector point) {
    ObjectTexture.load("TEX2.bmp");
    Vector returnColour = Material.Diffuse;
    return returnColour;
}

void Plane::Translatef(Vector u) {

}

void Plane::Rotatef(float Angle, Vector Axis) {
    Matrix4Operations Rotate;
    plane = Rotate.Rotate(Angle, Axis, plane);
}
