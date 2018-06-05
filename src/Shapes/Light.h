#ifndef LIGHT_H
#define LIGHT_H

#include "LightConstants.h"
#include "../Maths/Ray.h"
#include "Shape.h"
#include <vector>

using namespace std;

class LightValues {
public:
    LightValues(Ray lightray, LightConstants lightvalue);

    Ray LightRay;
    LightConstants LightValue;
};

class Light {
public:
    Light();
    Light(Ray light, LightConstants lightvalue);

    Ray getLightRay(int Light);

    LightConstants getLightConstants(int Light);

    Vector CalculateLightModel(Vector Point, Vector n, Vector v, LightConstants Material, vector<Shape *> &ShapeList,
                               int CurrentShape);

    float Phong_Model(Vector v, Vector l, Vector n, float f);

    float Cook_Torrance(Vector n, Vector l, Vector v);

    float MicroFacet(Vector l, Vector v, Vector n, float m);

    float Geometric(Vector n, Vector l, Vector v);

    Vector CalcTransmissionDirection(Vector v, Vector n, float ior);

    void addLight(Ray light, LightConstants lightvalue);

private:
    vector<LightValues> Lights;
};

#endif
