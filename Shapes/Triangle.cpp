#include "Triangle.h"
#include "../Matrix4Operations.h"
#include "../IntersectTests.h"
#include "Plane.h"

Triangle::Triangle(Vector n_v0, Vector n_v1, Vector n_v2, LightConstants material) {
    v0 = n_v0;
    v1 = n_v1;
    v2 = n_v2;
    Material = material;
}

float Triangle::Intersect(const Ray *r) {
    Vector e1 = v1 - v0;
    Vector e2 = v2 - v0;
    Vector n = e1 * e2;
    float d = DotProduct(n, v0);
    n.t = d;
    float a = DotProduct(e1, e1);
    float b = DotProduct(e1, e2);
    float c = DotProduct(e2, e2);
    float D = (a * c) - (b * b);
    float A = a / D;
    float B = b / D;
    float C = c / D;
    Vector ub = (e1 * C) - (e2 * B);
    Vector uy = (e2 * A) - (e1 * B);
    // Plane intersection test
    std::unique_ptr<Plane> plane(new Plane(n, Material));
    float t =  plane->Intersect(r);
    if (t < 0.0f) {
        return -1.0f;
    }
    Vector q = r->Source + (r->Direction * t);
    Vector R = q - v0;
    float Beta = DotProduct(ub, R);
    if (Beta < 0.0f) {
        return -1.0f;
    }
    float s = DotProduct(uy, R);
    if (s < 0.0f) {
        return -1.0f;
    }
    float lamda = 1 - Beta - s;
    if (lamda < 0.0f) {
        return -1.0f;
    }
    return t;
}

Vector Triangle::Normal(Vector p) {
    return (v1 - v0) * (v2 - v0);
}

Vector Triangle::GetMaterialColour(Vector point) {
    ObjectTexture.load("TEX2.bmp");
    Vector returnColour = Material.Diffuse;
    return returnColour;
}

void Triangle::Translatef(Vector u) {
    Matrix4Operations Translate;
    // Translate each point
    Translate.SetTranslate(v0);
    v0 = Translate.Translate(u);
    Translate.SetTranslate(v1);
    v1 = Translate.Translate(u);
    Translate.SetTranslate(v2);
    v2 = Translate.Translate(u);
}

void Triangle::Rotatef(float Angle, Vector Axis) {
    Matrix4Operations Rotate;
    v0 = Rotate.Rotate(Angle, Axis, v0);
    v1 = Rotate.Rotate(Angle, Axis, v1);
    v2 = Rotate.Rotate(Angle, Axis, v2);
}
