#ifndef SHAPES_H
#define SHAPES_H

#include "LightConstants.h"
#include "../Image/Bitmap.h"

class Ray;

class Shape {
public:
    void setT(float i_T) {
        t = i_T;
    };

    float getT() {
        return t;
    };

    virtual float Intersect(const Ray *r) = 0;

    LightConstants getLightConstants() {
        return Material;
    };

    virtual Vector Normal(Vector p) = 0;

    virtual Vector GetMaterialColour(Vector Point) = 0;

    bool Has_Texture() {
        return Texture;
    };

    virtual void Translatef(Vector u) = 0;

    virtual void Rotatef(float Angle, Vector Axis) = 0;

    Bitmap ObjectTexture;

protected:
    LightConstants Material;
    bool Texture;
    float t;
};

#endif
