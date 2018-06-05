#include "Sphere.h"
#include "../Maths/Matrix4Operations.h"
#include "../Maths/Ray.h"

Sphere::Sphere(float R, LightConstants material, bool Textured) {
    Center = Vector();
    r = R;
    Material = material;
    Texture = Textured;
}

void Sphere::Translatef(Vector u) {
    Matrix4Operations Translate;
    Translate.SetTranslate(Center);
    Center = Translate.Translate(u);
}

void Sphere::Rotatef(float Angle, Vector Axis) {
}

Vector Sphere::GetMaterialColour(Vector point) {
    ObjectTexture.load("TEX2.bmp");
    BYTE R, G, B;
    // Get Angles
    auto Theta = (float) atan(point.y / point.x);
    //Theta = RadToDegree(Theta);
    auto Omega = (float) acos(point.z / (sqrt((point.x * point.x) + (point.y * point.y) + (point.z * point.z))));
    //Omega = RadToDegree(Omega);
    double s = Theta / 360;
    double t = (Omega / 180) + 0.5;
    int x = s * ObjectTexture.getwidth();
    int y = t * ObjectTexture.getheight();
    ObjectTexture.getcolor(x, y, R, G, B);
    float r = R / 255.0f;
    float g = G / 255.0f;
    float b = B / 255.0f;
    return {r, g, b};
}

Vector Sphere::Normal(Vector p) {
    return p - Center;
}

float Sphere::Intersect(const Ray *ray) {
    float a = DotProduct(ray->Direction, ray->Direction);
    Vector d2 = ray->Direction * 2;
    float b = DotProduct(d2, (ray->Source - Center));
    float c = DotProduct((ray->Source - Center), (ray->Source - Center)) - (r * r);

    float s1 = (b * b) - (4 * a * c);
    if (s1 < 0) return -1.0f;
    float t1 = ((-1.0f * b) + sqrt(s1)) / (2 * a);
    float t2 = ((-1.0f * b) - sqrt(s1)) / (2 * a);
    if (t1 < t2) {
        return t1;
    } else {
        return t2;
    }
}
