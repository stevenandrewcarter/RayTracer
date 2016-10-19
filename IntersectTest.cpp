#include "IntersectTests.h"

float RadToDegree(float Radian) {
    const float PI = 3.141592653589793;
    float Theta = (360 * Radian) / (2 * PI);
    return Theta;
}