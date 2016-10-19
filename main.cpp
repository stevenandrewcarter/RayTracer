#include "Image/Bitmap.h"
#include "Camera.h"
#include "Light.h"
#include "Shapes/Plane.h"
#include "Shapes/Sphere.h"
#include "Matrix4Operations.h"

using namespace std;

vector<Shape*> ShapeList;
Light aLight;
Camera ViewCamera;

float Limit255(float a) {
    if (a < 0.0f) {
        return 0.0f;
    }
    if (a > 255.0f) {
        return 255.0f;
    }
    return a;
}

Vector RayCast(Ray r, int Depth) {
    Vector result = Vector();
    Shape* o;
    int ShapeNum = 0;
    bool Intersect = false;
    //Find nearest intersection between r and objects
    float Dist = -1.0f;
    for (int i = 0; i < ShapeList.size(); i++) {
        // Find Closest intersecting shape
        // - Find t for each shape
        // - if t > 0 for that shape find dst
        // - Smallest Dst is the object
        ShapeList[i]->setT(-1.0f);
        auto t = ShapeList[i]->Intersect(&r);

        if (t > 0.0f) {
            ShapeList[i]->setT(t);
            Intersect = true;
            if (Dist < 0.0f) {
                Dist = ShapeList[i]->getT();
            }
            if (ShapeList[i]->getT() <= Dist) {
                o = ShapeList[i];
                ShapeNum = i;
                Dist = o->getT();
            }
        }
    }
    if (!Intersect) {
        return result;
    }
    Vector p = r.Source + (r.Direction * o->getT());
    Vector n = o->Normal(p);
    Vector v = ViewCamera.Position() - p;
    LightConstants MaterialP = o->getLightConstants();
    if (o->Has_Texture()) {
        Vector Material = o->GetMaterialColour(p);
        MaterialP.Diffuse = Material;
    }
    result = aLight.CalculateLightModel(p, n, v, MaterialP, ShapeList, ShapeNum);

    if (Depth == 0) {
        return result;
    }
    LightConstants P = o->getLightConstants();
    Vector ZERO = Vector(0.0f, 0.0f, 0.0f);
    if ((P.Reflective.x != ZERO.x) || (P.Reflective.y != ZERO.y) || (P.Reflective.z != ZERO.z)) {
        // Reflection Vector = u - 2(u . n)n
        float temp = 2.0f * DotProduct(r.Direction.Normalize(), n.Normalize());
        Vector R = r.Direction.Normalize() - (n.Normalize() * temp);
        Vector ReflectColour = RayCast(Ray(p, R.Normalize()), Depth - 1);
        result = result + Vector(P.Reflective.x * ReflectColour.x, P.Reflective.y * ReflectColour.y,
                                 P.Reflective.z * ReflectColour.z);
    }

    if ((P.Transmission.x != ZERO.x) || (P.Transmission.y != ZERO.y) || (P.Transmission.z != ZERO.z)) {
        Vector u = r.Direction;
        u = u.Normalize() * -1.0f;
        Vector t = aLight.CalcTransmissionDirection((u), n.Normalize(), 1.5f);
        if ((t.x != ZERO.x) && (t.y != ZERO.y) && (t.z != ZERO.z)) {
            Vector T = RayCast(Ray(p, t), Depth - 1);
            result = result + Vector(P.Transmission.x * T.x, P.Transmission.y * T.y, P.Transmission.z * T.z);
        }
    }
    //if ! Transparent
    return result;
}

int main() {
    cout << "RayTracer starting...\n";
    Bitmap image1;
    if (image1.create(1980, 1080)) {
        cout << "Image Created. [W:" << image1.getwidth() << " H:" << image1.getheight() << "]\n";
        // Camera is a ray as well, Source would be the position that the camera exists and
        // Direction would be where it is looking.
        Vector CameraCenter = Vector(0.0f, 0.0f, 0.0f);
        ViewCamera = Camera(CameraCenter, Vector(0.0f, 0.0f, 1.0f), Vector(0.0f, 1.0f, 0.0f), image1.getwidth(),
                            image1.getheight());
        ViewCamera.CalculatePlaneNormals();

        LightConstants Material = LightConstants(Vector(0.0f, 0.9f, 0.0f), Vector(0.1f, 0.1f, 0.1f),
                                                 Vector(0.1f, 0.1f, 0.1f), Vector(), Vector(), Vector(), 8.0f);
        ShapeList.push_back(new Plane(Vector(0.0f, 1.0f, 0.0f, 1.0f), Material));

        Material = LightConstants(Vector(1.0f, 0.0f, 0.0f), Vector(0.1f, 0.1f, 0.1f), Vector(0.0f, 0.0f, 0.0f),
                                  Vector(),
                                  Vector(), Vector(), 8.0f);
        ShapeList.push_back(new Plane(Vector(0.0f, -1.0f, 0.0f, 1.0f), Material));

        Material = LightConstants(Vector(0.9f, 0.9f, 0.0f), Vector(0.1f, 0.1f, 0.1f), Vector(0.0f, 0.0f, 0.0f),
                                  Vector(),
                                  Vector(), Vector(), 8.0f);
        ShapeList.push_back(new Plane(Vector(1.0f, 0.0f, 0.0f, 1.0f), Material));

        Material = LightConstants(Vector(0.9f, 0.9f, 0.9f), Vector(0.1f, 0.1f, 0.1f), Vector(0.0f, 0.0f, 0.0f),
                                  Vector(),
                                  Vector(), Vector(), 8.0f);
        ShapeList.push_back(new Plane(Vector(-1.0f, 0.0f, 0.0f, 1.0f), Material));

        Material = LightConstants(Vector(0.0f, 0.0f, 0.7f), Vector(0.3f, 0.3f, 0.3f), Vector(), Vector(),
                                  Vector(0.1f, 0.1f, 0.1f), Vector(), 4.0f);
        Shape *sphere1 = new Sphere(0.5f, Material, false);
        sphere1->Translatef(Vector(0.0f, 1.0f, 0.0f));
        ShapeList.push_back(sphere1);

        Material = LightConstants(Vector(0.7f, 0.0f, 0.0f), Vector(0.3f, 0.3f, 0.3f), Vector(), Vector(),
                                  Vector(0.5f, 0.5f, 0.5f), Vector(), 16.0f);
        Shape *sphere2 = new Sphere(0.5f, Material, false);
        sphere2->Translatef(Vector(-1.0f, 0.0f, 0.0f));
        ShapeList.push_back(sphere2);

        Material = LightConstants(Vector(0.1f, 0.1f, 0.1f), Vector(0.9f, 0.9f, 0.9f), Vector(), Vector(),
                                  Vector(0.5f, 0.5f, 0.5f), Vector(), 16.0f);
        Shape *sphere3 = new Sphere(0.5f, Material, false);
        sphere3->Translatef(Vector(1.0f, 0.0f, 0.0f));
        ShapeList.push_back(sphere3);

        Material = LightConstants(Vector(0.0f, 0.7f, 0.0f), Vector(0.3f, 0.3f, 0.3f), Vector(), Vector(),
                                  Vector(0.5f, 0.5f, 0.5f), Vector(), 16.0f);
        Shape *sphere4 = new Sphere(0.5f, Material, false);
        sphere4->Translatef(Vector(0.0f, -1.0f, 0.0f));
        ShapeList.push_back(sphere4);

//        Material = LightConstants(Vector(0.5f, 0.5f, 0.5f), Vector(0.5f, 0.5f, 0.5f), Vector(), Vector(), Vector(),
//                                  Vector(0.9f, 0.9f, 0.9f), 16.0f);
//        b.setTriangle(Vector(0.5f, 0.0f, 0.0f), Vector(0.0f, 0.5f, 0.0f), Vector(-0.5f, 0.0f, 0.0f), Material);
//        b.Translatef(Vector(0.0f, 0.0f, -0.5f));
        //b.Rotatef(3.0f, Vector(0.0f, 1.0f, 0.0f));
        // ShapeList.push_back(b);

        LightConstants LightValue = LightConstants(Vector(0.4f, 0.4f, 0.4f), Vector(0.3f, 0.3f, 0.3f),
                                                   Vector(0.7f, 0.7f, 0.7f));
        aLight = Light(Ray(Vector(0.5f, 0.5f, -1.0f), Vector(0.0f, 0.0f, 0.0f)), LightValue);
        LightValue = LightConstants(Vector(0.7f, 0.7f, 0.7f), Vector(0.3f, 0.3f, 0.3f), Vector(0.5f, 0.5f, 0.5f));
        aLight.addLight(Ray(Vector(0.5f, 0.5f, -1.0f), Vector(0.0f, 0.0f, 0.0f)), LightValue);
        cout << "Casting Rays...\n";
        BYTE Red, Green, Blue;

        for (int i = 1; i < image1.getwidth(); i++) {
            cout << "Row: " << i;
            float w = image1.getwidth();
            float t = i / w;
            Vector Left = Parametric(ViewCamera.P3(), ViewCamera.P0(), t);
            Vector Right = Parametric(ViewCamera.P2(), ViewCamera.P1(), t);
            for (int j = 1; j < image1.getheight(); j++) {
                cout << j;
                float h = image1.getheight();
                t = j / h;
                Vector RayDir = Parametric(Left, Right, t);
                Matrix4Operations Translate;
                Matrix4Operations TranslateC;
                Translate.SetTranslate(RayDir);
                RayDir = Translate.Translate(Vector(0.0f, 0.0f, -3.0f));
                Vector C = ViewCamera.Position();
                TranslateC.SetTranslate(C);
                C = TranslateC.Translate(Vector(0.0f, 0.0f, -3.0f));
                RayDir = C - RayDir;
                Ray casted = Ray(C, RayDir.Normalize());
                Vector Colour = RayCast(casted, 5);
                Red = Limit255(Colour.x * 255);
                Green = Limit255(Colour.y * 255);
                Blue = Limit255(Colour.z * 255);
                image1.setcolor(image1.getwidth() - i, image1.getheight() - j, Red, Green, Blue);
            }
            cout << "\n";
        }
        cout << "Saving Image...\n";
        image1.save("image1.bmp");
    }
    //system("PAUSE");
    return 0;
}