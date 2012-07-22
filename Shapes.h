#ifndef SHAPES_H
#define SHAPES_H

#include "IntersectTests.h"
#include "LightConstants.h"
#include "Matrix4Operations.h"

enum Shape_Type
{
	SPHERE = 0,
	PLANE  = 1,	
	TRIANGLE = 2,
};

struct Triangle
{
	Vector v0, v1, v2;
};

struct Sphere
{
	Vector Center;
	float r;
};

class Shapes
{
public:
	Shapes(){};

	void setSphere(float R, LightConstants material, bool Textured)
	{	
		sphere.Center = Vector();
		sphere.r = R;
		CurrentShape = SPHERE;
		Material = material;
		Texture = Textured;		
	};

	void Cube()
	{
	};

	void setTriangle(Vector v0, Vector v1, Vector v2, LightConstants material)
	{
		triangle.v0 = v0;
		triangle.v1 = v1;
		triangle.v2 = v2;
		CurrentShape = TRIANGLE;
		Material = material;
	};

	void setPlane(Vector Normal, LightConstants material)
	{
		plane = Normal;
		CurrentShape = PLANE;
		Material = material;
		Texture = false;
	};

	Shape_Type getShapeType()
	{
		return CurrentShape;
	};

	void setT(float i_T)
	{
		t = i_T;
	};

	float getT()
	{
		return t;
	};

	float Intersect(Ray r)
	{
		float t = 0.0f;
		if(CurrentShape == PLANE)
		{
			t = PlaneTest(r, Vector(plane.x, plane.y, plane.z) , plane.t);
		}
		else if(CurrentShape == SPHERE)
		{
			t = SphereTest(r, sphere.Center, sphere.r);
		}
		else if(CurrentShape == TRIANGLE)
		{
			t = TriangleTest(r, triangle.v0, triangle.v1, triangle.v2);
		}
		return t;
	};

	LightConstants getLightConstants()
	{
		return Material;
	};

	Vector Normal(Vector p)
	{
		Vector n = Vector();
		if(CurrentShape == SPHERE)
		{
			n = p - sphere.Center;
		}
		else if(CurrentShape == PLANE)
		{
			n = plane;						
		}
		else if(CurrentShape == TRIANGLE)
		{
			n = (triangle.v1 - triangle.v0) * (triangle.v2 - triangle.v0);
		}
		return n;
	};

	Vector getMaterialColour(Vector Point)
	{
		ObjectTexture.load("TEX2.bmp");
		Vector returnColour = Material.Diffuse;
		BYTE R, G, B;		
		if(CurrentShape == SPHERE)
		{			
			
			// Get Angles
			float Theta = atan( Point.y / Point.x);
			//Theta = RadToDegree(Theta);
			float Omega = acos( Point.z / (sqrt( (Point.x * Point.x) + (Point.y * Point.y) + (Point.z * Point.z) )) );
			//Omega = RadToDegree(Omega);
			double s = Theta / 360;
			double t = (Omega / 180) + 0.5;
			int x = s * ObjectTexture.getwidth();
			int y = t * ObjectTexture.getheight();
			ObjectTexture.getcolor(x, y, R, G, B);
			float r = (float)R / 255.0f;
			float g = (float)G / 255.0f;
			float b = (float)B / 255.0f;
			returnColour = Vector(r , g , b );
		}
		else if(CurrentShape == TRIANGLE)
		{
			
		}
		else if(CurrentShape == PLANE)
		{
			// Need two vectors
		}
		return returnColour;
	};
	
	bool Has_Texture()
	{	
		return Texture;
	};

	void Translatef(Vector u)
	{
		Matrix4Operations Translate;
		if(CurrentShape == SPHERE)
		{			
			Translate.SetTranslate(sphere.Center);
			sphere.Center = Translate.Translate(u);
		}
		else if(CurrentShape == TRIANGLE)
		{
			//Translate each point
			Translate.SetTranslate(triangle.v0);
			triangle.v0 = Translate.Translate(u);

			Translate.SetTranslate(triangle.v1);
			triangle.v1 = Translate.Translate(u);

			Translate.SetTranslate(triangle.v2);
			triangle.v2 = Translate.Translate(u);
		}
	};

	void Rotatef(float Angle, Vector Axis)
	{
		Matrix4Operations Rotate;
		if(CurrentShape == SPHERE)
		{
		}
		else if(CurrentShape == TRIANGLE)
		{
			triangle.v0 = Rotate.Rotate(Angle, Axis, triangle.v0);
			triangle.v1 = Rotate.Rotate(Angle, Axis, triangle.v1);
			triangle.v2 = Rotate.Rotate(Angle, Axis, triangle.v2);
		}
		else if(CurrentShape == PLANE)
		{
			plane = Rotate.Rotate(Angle, Axis, plane);
		}

	};

	Vector plane;
	Sphere sphere;
	Triangle triangle;
	bitmap ObjectTexture;

private:	
	Shape_Type CurrentShape;	
	LightConstants Material;
	bool Texture;
	float f;
	float t;	
};

#endif