#include "World.h"
#include "LightConstants.h"
#include "Light.h"
#include "Plane.h"
#include "Sphere.h"
#include "../Maths/Matrix4Operations.h"
#include "Triangle.h"
#include <iostream>

float Limit255(float a) {
    if (a < 0.0f) {
        return 0.0f;
    }
    if (a > 255.0f) {
        return 255.0f;
    }
    return a;
}

World::World(Bitmap *image) {
    Vector CameraCenter = Vector(0.0f, 0.0f, 0.0f);
    view_camera = std::unique_ptr<Camera>(new Camera(CameraCenter, Vector(0.0f, 0.0f, 1.0f), Vector(0.0f, 1.0f, 0.0f),
                                                     image->getwidth(), image->getheight()));
    view_camera->CalculatePlaneNormals();

    LightConstants Material = LightConstants(Vector(0.0f, 0.9f, 0.0f), Vector(0.1f, 0.1f, 0.1f),
                                             Vector(0.1f, 0.1f, 0.1f), Vector(), Vector(), Vector(), 8.0f);
    shape_list.push_back(new Plane(Vector(0.0f, 1.0f, 0.0f, 1.0f), Material));

    Material = LightConstants(Vector(1.0f, 0.0f, 0.0f), Vector(0.1f, 0.1f, 0.1f), Vector(0.0f, 0.0f, 0.0f),
                              Vector(),
                              Vector(), Vector(), 8.0f);
    shape_list.push_back(new Plane(Vector(0.0f, -1.0f, 0.0f, 1.0f), Material));

    Material = LightConstants(Vector(0.9f, 0.9f, 0.0f), Vector(0.1f, 0.1f, 0.1f), Vector(0.0f, 0.0f, 0.0f),
                              Vector(),
                              Vector(), Vector(), 8.0f);
    shape_list.push_back(new Plane(Vector(1.0f, 0.0f, 0.0f, 1.0f), Material));

    Material = LightConstants(Vector(0.9f, 0.9f, 0.9f), Vector(0.1f, 0.1f, 0.1f), Vector(0.0f, 0.0f, 0.0f),
                              Vector(),
                              Vector(), Vector(), 8.0f);
    shape_list.push_back(new Plane(Vector(-1.0f, 0.0f, 0.0f, 1.0f), Material));

    Material = LightConstants(Vector(0.0f, 0.0f, 0.7f), Vector(0.3f, 0.3f, 0.3f), Vector(), Vector(),
                              Vector(0.1f, 0.1f, 0.1f), Vector(), 4.0f);
    Shape *sphere1 = new Sphere(0.5f, Material, false);
    sphere1->Translatef(Vector(0.0f, 1.0f, 0.0f));
    shape_list.push_back(sphere1);

    Material = LightConstants(Vector(0.7f, 0.0f, 0.0f), Vector(0.3f, 0.3f, 0.3f), Vector(), Vector(),
                              Vector(0.5f, 0.5f, 0.5f), Vector(), 16.0f);
    Shape *sphere2 = new Sphere(0.5f, Material, false);
    sphere2->Translatef(Vector(-1.0f, 0.0f, 0.0f));
    shape_list.push_back(sphere2);

    Material = LightConstants(Vector(0.1f, 0.1f, 0.1f), Vector(0.9f, 0.9f, 0.9f), Vector(), Vector(),
                              Vector(0.5f, 0.5f, 0.5f), Vector(), 16.0f);
    Shape *sphere3 = new Sphere(0.5f, Material, false);
    sphere3->Translatef(Vector(1.0f, 0.0f, 0.0f));
    shape_list.push_back(sphere3);

    Material = LightConstants(Vector(0.0f, 0.7f, 0.0f), Vector(0.3f, 0.3f, 0.3f), Vector(), Vector(),
                              Vector(0.5f, 0.5f, 0.5f), Vector(), 16.0f);
    Shape *sphere4 = new Sphere(0.5f, Material, false);
    sphere4->Translatef(Vector(0.0f, -1.0f, 0.0f));
    shape_list.push_back(sphere4);

    Material = LightConstants(Vector(0.5f, 0.5f, 0.5f), Vector(0.5f, 0.5f, 0.5f), Vector(), Vector(), Vector(),
                              Vector(0.9f, 0.9f, 0.9f), 16.0f);
    Shape *b = new Triangle(Vector(0.5f, 0.0f, 0.0f), Vector(0.0f, 0.5f, 0.0f), Vector(-0.5f, 0.0f, 0.0f), Material);
    b->Translatef(Vector(0.0f, 0.0f, -0.5f));
//    b->Rotatef(3.0f, Vector(0.0f, 1.0f, 0.0f));
    shape_list.push_back(b);

    LightConstants LightValue = LightConstants(Vector(0.4f, 0.4f, 0.4f), Vector(0.3f, 0.3f, 0.3f),
                                               Vector(0.7f, 0.7f, 0.7f));
    light = std::unique_ptr<Light>(new Light(Ray(Vector(0.5f, 0.5f, -1.0f), Vector(0.0f, 0.0f, 0.0f)), LightValue));
    LightValue = LightConstants(Vector(0.7f, 0.7f, 0.7f), Vector(0.3f, 0.3f, 0.3f), Vector(0.5f, 0.5f, 0.5f));
    light->addLight(Ray(Vector(0.5f, 0.5f, -1.0f), Vector(0.0f, 0.0f, 0.0f)), LightValue);
    cout << "Casting Rays...\n";
    BYTE Red, Green, Blue;

    for (int i = 1; i < image->getwidth(); i++) {
        cout << "Row: " << i;
        float w = image->getwidth();
        float t = i / w;
        Vector Left = Parametric(view_camera->P3(), view_camera->P0(), t);
        Vector Right = Parametric(view_camera->P2(), view_camera->P1(), t);
        for (int j = 1; j < image->getheight(); j++) {
            float h = image->getheight();
            t = j / h;
            Vector RayDir = Parametric(Left, Right, t);
            Matrix4Operations Translate;
            Translate.SetTranslate(RayDir);
            RayDir = Translate.Translate(Vector(0.0f, 0.0f, -3.0f));
            Vector C = view_camera->Position();
            Matrix4Operations TranslateC;
            TranslateC.SetTranslate(C);
            C = TranslateC.Translate(Vector(0.0f, 0.0f, -3.0f));
            RayDir = C - RayDir;
            Ray casted = Ray(C, RayDir.Normalize());
            Vector Colour = RayCast(&casted, 5);
            Red = Limit255(Colour.x * 255);
            Green = Limit255(Colour.y * 255);
            Blue = Limit255(Colour.z * 255);
            image->setcolor(image->getwidth() - i, image->getheight() - j, Red, Green, Blue);
        }
        cout << "\n";
    }
}

Vector World::RayCast(Ray *r, int Depth) {
    Vector result;
    Shape *o;
    int ShapeNum = 0;
    bool Intersect = false;
    //Find nearest intersection between r and objects
    float Dist = -1.0f;
    for (int i = 0; i < shape_list.size(); i++) {
        // Find Closest intersecting shape
        // - Find t for each shape
        // - if t > 0 for that shape find dst
        // - Smallest Dst is the object
        shape_list[i]->setT(-1.0f);
        auto t = shape_list[i]->Intersect(r);

        if (t > 0.0f) {
            shape_list[i]->setT(t);
            Intersect = true;
            if (Dist < 0.0f) {
                Dist = shape_list[i]->getT();
            }
            if (shape_list[i]->getT() <= Dist) {
                o = shape_list[i];
                ShapeNum = i;
                Dist = o->getT();
            }
        }
    }
    if (!Intersect) {
        return result;
    }
    Vector p = r->Source + (r->Direction * o->getT());
    Vector n = o->Normal(p);
    Vector v = view_camera->Position() - p;
    LightConstants MaterialP = o->getLightConstants();
    if (o->Has_Texture()) {
        Vector Material = o->GetMaterialColour(p);
        MaterialP.Diffuse = Material;
    }
    result = light->CalculateLightModel(p, n, v, MaterialP, shape_list, ShapeNum);

    if (Depth == 0) {
        return result;
    }
    LightConstants P = o->getLightConstants();
    Vector ZERO = Vector(0.0f, 0.0f, 0.0f);
    if ((P.Reflective.x != ZERO.x) || (P.Reflective.y != ZERO.y) || (P.Reflective.z != ZERO.z)) {
        // Reflection Vector = u - 2(u . n)n
        float temp = 2.0f * DotProduct(r->Direction.Normalize(), n.Normalize());
        Vector R = r->Direction.Normalize() - (n.Normalize() * temp);
        std::unique_ptr<Ray> ray = std::unique_ptr<Ray>(new Ray(p, R.Normalize()));
        Vector ReflectColour = RayCast(ray.get(), Depth - 1);
        result = result + Vector(P.Reflective.x * ReflectColour.x, P.Reflective.y * ReflectColour.y,
                                 P.Reflective.z * ReflectColour.z);
    }

    if ((P.Transmission.x != ZERO.x) || (P.Transmission.y != ZERO.y) || (P.Transmission.z != ZERO.z)) {
        Vector u = r->Direction;
        u = u.Normalize() * -1.0f;
        Vector t = light->CalcTransmissionDirection((u), n.Normalize(), 1.5f);
        if ((t.x != ZERO.x) && (t.y != ZERO.y) && (t.z != ZERO.z)) {
            std::unique_ptr<Ray> ray = std::unique_ptr<Ray>(new Ray(p, t));
            Vector T = RayCast(ray.get(), Depth - 1);
            result = result + Vector(P.Transmission.x * T.x, P.Transmission.y * T.y, P.Transmission.z * T.z);
        }
    }
    //if ! Transparent
    return result;
}
