#ifndef INTERSECTTEST_H
#define INTERSECTTEST_H

#include "Ray.h"


float PlaneTest(Ray R, Vector n, float d)
{
	float t = 0;
	float u = (DotProduct(n, R.Source) );
	float D = (DotProduct(n, R.Direction));
	float U = (-1.0f * d) - u;
	t = ( U / D);
	return t;
};

float SphereTest(Ray R, Vector C, float r)
{
	float a = DotProduct(R.Direction, R.Direction);
	Vector d2 = R.Direction * 2;
	float b = DotProduct(d2, (R.Source - C));
	float c = DotProduct((R.Source - C), (R.Source - C)) - (r * r);
	
	float s1 = (b * b) - (4 * a * c);
	if(s1 < 0) return -1.0f;
	float t1 = ((-1.0f * b) + sqrt(s1)) / (2 * a);
	float t2 = ((-1.0f * b) - sqrt(s1)) / (2 * a);
	if(t1 < t2) 
	{
		return t1;
	}
	else
	{
		return t2;
	}
};

float TriangleTest(Ray r, Vector v0, Vector v1, Vector v2)
{
	Vector e1 = v1 - v0;
	Vector e2 = v2 - v0;
	Vector n = e1 * e2;
	float d = DotProduct(n, v0);
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
	float t = PlaneTest(r, n, d);
	if(t < 0.0f)
	{
		return -1.0f;
	}
	Vector q = r.Source + (r.Direction * t);
	Vector R = q - v0;
	float Beta = DotProduct(ub, R);
	if(Beta < 0.0f)
	{
		return -1.0f;
	}
	float s = DotProduct(uy, R);
	if(s < 0.0f)
	{
		return -1.0f;
	}
	float lamda = 1 - Beta - s;
	if(lamda < 0.0f)
	{
		return -1.0f;
	}
	return t;
};

float RadToDegree(float Radian)
{
	const float PI = 3.141592653589793;	
	float Theta = (360 * Radian) /( 2 * PI);	
	return Theta;
}

#endif