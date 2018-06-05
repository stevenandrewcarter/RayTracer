#ifndef RAYTRACER_WORLD_H
#define RAYTRACER_WORLD_H

#include <vector>
#include "Light.h"
#include "../Camera.h"

class Bitmap;
class Shape;
class Ray;
class Vector;

class World {
public:
    explicit World(Bitmap *image);

private:
    std::vector<Shape *> shape_list;
    std::unique_ptr<Light> light;
    std::unique_ptr<Camera> view_camera;

    Vector RayCast(Ray *r, int Depth);
};


#endif
