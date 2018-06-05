#ifndef LIGHTCONSTANTS_H
#define LIGHTCONSTANTS_H

#include "../Maths/Vector.h"

class LightConstants {
public:
    LightConstants() {
        Diffuse = Vector();
        Specular = Vector();
        Ambient = Vector();
        Reflective = Vector();
        Emissive = Vector();
        f = 0.0f;
    };

    // Constructor for Material Light constants
    LightConstants(Vector diffuse, Vector specular, Vector ambient, Vector emissive, Vector reflective,
                   Vector transmission, float F) {
        Diffuse = diffuse;
        Specular = specular;
        Ambient = ambient;
        Reflective = reflective;
        Emissive = emissive;
        Transmission = transmission;
        f = F;
    };

    // Constructor for Light source constants
    LightConstants(Vector diffuse, Vector specular, Vector ambient) {
        Diffuse = diffuse;
        Specular = specular;
        Ambient = ambient;
    };

    Vector Diffuse;
    Vector Specular;
    Vector Ambient;
    Vector Reflective;
    Vector Emissive;
    Vector Transmission;
    float f;
};


#endif
