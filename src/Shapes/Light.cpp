#include "Light.h"

LightValues::LightValues(Ray lightray, LightConstants lightvalue) {
    LightRay = lightray;
    LightValue = lightvalue;
}

Light::Light() {
    LightValues a = LightValues(Ray(), LightConstants());
    Lights.push_back(a);
}

Light::Light(Ray light, LightConstants lightvalue) {
    LightValues a = LightValues(light, lightvalue);
    Lights.push_back(a);
}

Ray Light::getLightRay(int Light) {
    return Lights[Light].LightRay;
}

LightConstants Light::getLightConstants(int Light) {
    return Lights[Light].LightValue;
}

Vector Light::CalculateLightModel(Vector Point, Vector n, Vector v, LightConstants Material, vector<Shape *> &ShapeList,
                           int CurrentShape) {
    Vector Pd = Material.Diffuse;
    Vector Ps = Material.Specular;
    Vector Pa = Material.Ambient;
    Vector Pdt = Material.Transmission;
    Vector Ia = Lights[0].LightValue.Ambient;
    Vector Ambcomp = Vector(Pa.x * Ia.x, Pa.y * Ia.y, Pa.z * Ia.z);
    Vector Specularcomp = Vector();
    Vector SpecularTcomp = Vector();
    Vector Diffusecomp = Vector();
    Vector DiffuseTcomp = Vector();

    for (int i = 0; (unsigned) i < Lights.size(); i++) {
        float Shadowed = 1.0f;
        Vector LightsSource = Lights[i].LightRay.Source;
        //Vector l =  Point - LightsSource;//Lights[i].LightRay.Source - Point;
        Vector l = Lights[i].LightRay.Source - Point;
        // Shadowing
        // Write code here
        Ray Feeler = Ray(Point, l.Normalize());
        for (int j = 0; (unsigned) j < ShapeList.size(); j++) {
            if (j != CurrentShape) {
                auto t = (double) ShapeList[j]->Intersect(&Feeler);
                auto ShapeT = (double) Distance(Point, LightsSource);
                if ((t > 0) && (t < ShapeT)) {
                    Shadowed = 0.0f;
                    break;
                }
            }
        }
        // to here

        //l = Point - Lights[i].LightRay.Source;
        Vector Id = Lights[i].LightValue.Diffuse;
        Vector Is = Lights[i].LightValue.Specular;
        float ln = DotProduct(l.Normalize(), n.Normalize());
        float CTIs = Cook_Torrance(n.Normalize(), l.Normalize(), v.Normalize());
        //float CTIs = Phong_Model(v.Normalize(), l.Normalize(), n.Normalize(), Material.f);
        float hnf = CTIs;
        Vector CIs = Is * CTIs;
        //CIs = CIs + Vector(0.1f, 0.1f, 0.1f);
        float mln = DotProduct(l.Normalize(), (n.Normalize() * -1.0f));
        Vector DiffuseT = Id * mln;
        Vector t = CalcTransmissionDirection((v * -1.0f).Normalize(), n.Normalize(), 1.5f);
        float CTIst = Cook_Torrance(n.Normalize(), l.Normalize(), t.Normalize());
        Vector SpecularT = Is * CTIst;
        Specularcomp = Specularcomp + (Vector(Ps.x * CIs.x, Ps.y * CIs.y, Ps.z * CIs.z) * Shadowed);
        Diffusecomp = Diffusecomp + (Vector(Pd.x * (Id.x * ln), Pd.y * (Id.y * ln), Pd.z * (Id.z * ln)) * Shadowed);
        SpecularTcomp = SpecularTcomp + Vector(SpecularT.x * Pdt.x, SpecularT.y * Pdt.y, SpecularT.z * Pdt.z);
        DiffuseTcomp = Vector(DiffuseT.x * Pdt.x, DiffuseT.y * Pdt.y, DiffuseT.z * Pdt.z);
    }
    return Ambcomp + (Diffusecomp) + (Specularcomp) + DiffuseTcomp + SpecularTcomp;
}

float Light::Phong_Model(Vector v, Vector l, Vector n, float f) {
    Vector r = (n * (2 * DotProduct(l, n))) - l;
    float vr = DotProduct(v, r.Normalize());
    return pow(vr, f);
}

float Light::Cook_Torrance(Vector n, Vector l, Vector v) {
    float ndl = DotProduct(n, l);
    float ndv = DotProduct(n, v);
    float a = ndl / ndv;
    float s = 50.0f;
    float G = Geometric(n, l, v);
    float F = 0.5f;
    float D = MicroFacet(l, v, n, 0.5f);
    return a * s * F * G * D;
    // Is = (n.l)/(n.v)sFGD.Is
}

float Light::MicroFacet(Vector l, Vector v, Vector n, float m) {
    Vector h = (l + v) / Norm(l + v);
    float J = acos(DotProduct(h, n));
    auto Beckmann = static_cast<float>((1 / (4.0f * (m * m) * pow((cos(J)), 4))) * exp((-1.0f * (tan(J) * tan(J))) / (m * m)));
    return Beckmann;
}

float Light::Geometric(Vector n, Vector l, Vector v) {
    Vector m = Vector();
    float G = 0.0f;
    if (Norm(l + v) == 0) {
        G = 1.0f;
        return G;
    }
    Vector h = (l + v) / Norm(l + v);
    Vector n0 = (l * DotProduct(n, l)) + (v * DotProduct(n, v)) - (l * (DotProduct(v, l) * DotProduct(v, n))) -
                (v * (DotProduct(v, l) * DotProduct(l, n)));
    if (Norm(n0) != 0) {
        m = n0 / Norm(n0);
    } else {
        m = h;
    }
    Vector hp = (m * (2 * DotProduct(m, h))) - h;
    if ((DotProduct(v, hp) >= 0) || (DotProduct(m, v) >= DotProduct(m, l))) {
        G = 1.0f;
    } else if ((DotProduct(v, hp) < 0) && (DotProduct(l, hp) >= 0)) {
        G = (2 * DotProduct(m, h) * DotProduct(m, v)) / DotProduct(h, v);
    } else {
        G = DotProduct(m, v) / DotProduct(m, l);
    }
    return G;
}

Vector Light::CalcTransmissionDirection(Vector v, Vector n, float ior) {
    Vector tlat = ((n * DotProduct(v, n)) - v) / ior;
    float ntlat = Norm(tlat);
    float sinSq = ntlat * ntlat;
    if (sinSq > 1) {
        return {};
    }
    Vector t = tlat - (n * (sqrt(1 - sinSq)));
    return t;
}

void Light::addLight(Ray light, LightConstants lightvalue) {
    LightValues a = LightValues(light, lightvalue);
    Lights.push_back(a);
}