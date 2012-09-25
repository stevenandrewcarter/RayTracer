//#include <iostream>
//#include <vector>
#include "image/bitmap.h"
#include "Camera.h"
#include "Light.h"
#include "Matrix4.h"
#include "Ray.h"
#include "Shapes.h"
#include "Maths/Vector.h"

using namespace std;

vector<Shapes> ShapeList;
Light aLight;
Shapes Last;
Camera ViewCamera;


float Limit255(float a)		
{
	if(a < 0.0f) 
	{
		return 0.0f;
	}
	else if(a > 255.0f) 
	{
		return 255.0f;
	}
	else 
	{
		return a;
	}
}


Vector RayCast(Ray r, int Depth)
{	
	Vector result = Vector();		
	Shapes o = Shapes();
	int ShapeNum = 0;
	float t = 0.0f;
	bool Intersect = false;
	//Find nearest intersection between r and objects		
	float Dist = -1.0f;
	for(int i = 0; (unsigned)i < ShapeList.size(); i++)
	{
		// Find Closest intersecting shape
		// - Find t for each shape
		// - if t > 0 for that shape find dst
		// - Smallest Dst is the object		
		ShapeList[i].setT(-1.0f);		
		t = ShapeList[i].Intersect(r);		

		if(t > 0.0f)
		{
			ShapeList[i].setT(t);			
			Intersect = true;			
			Shapes Place = ShapeList[i];
			if(Dist < 0.0f)
			{
				Dist = ShapeList[i].getT();
			}
			if(ShapeList[i].getT() <= Dist)
			{
				o = ShapeList[i];
				ShapeNum = i;
				Dist = o.getT();
			}			
		}		
	}	
	if(!Intersect)
	{
		return result;
	}
	else
	{	
		Vector p = r.Source + (r.Direction * o.getT());				
		Vector n = o.Normal(p);
		Vector v = ViewCamera.Position() - p;		
		//Ray Feeler = Ray(L.Source, l.Normalize());		
		// Shadowing 
		// Write code here
		//for(int i = 0; (unsigned)i < ShapeList.size(); i++)
		//{
		//	t = ShapeList[i].Intersect(Feeler);
		//	if(t > 0.0f)
		//	{
		//		Shadowed = 0.0f;
		//	}			
		//}

		// to here
		LightConstants MaterialP = o.getLightConstants();
		if(o.Has_Texture())
		{
			Vector Material = o.getMaterialColour(p);
			MaterialP.Diffuse = Material;
		}
		result = aLight.CalculateLightModel(p, n, v, MaterialP, ShapeList, ShapeNum);

		if(Depth == 0)
		{
			return result;
		}
		LightConstants P = o.getLightConstants();
		Vector ZERO = Vector(0.0f, 0.0f, 0.0f);
		if( (P.Reflective.x != ZERO.x) || (P.Reflective.y != ZERO.y) || (P.Reflective.z != ZERO.z) )
		{
			// Reflection Vector = u - 2(u . n)n
			float temp = 2.0f * DotProduct(r.Direction.Normalize(), n.Normalize());
			Vector R = r.Direction.Normalize() - (n.Normalize() * temp);
			Vector ReflectColour = RayCast(Ray(p, R.Normalize()), Depth - 1);
			result = result + Vector(P.Reflective.x * ReflectColour.x, P.Reflective.y * ReflectColour.y, P.Reflective.z * ReflectColour.z);  
		}

		if( (P.Transmission.x != ZERO.x) || (P.Transmission.y != ZERO.y) || (P.Transmission.z != ZERO.z) )
		{
			//float temp = 2.0f * DotProduct(r.Direction.Normalize(), n.Normalize());
			//Vector R = r.Direction.Normalize() - (n.Normalize() * temp);
			//R = R * -1.0f;
			//Vector ReflectColour = RayCast(Ray(p, R.Normalize()), Depth - 1);			
			// 1.5 is glass
			//Vector t = aLight.CalcTransmissionDirection((v.Normalize() * -1.0f), n.Normalize(), 1.3);
			//Vector t = aLight.CalcTransmissionDirection((v.Normalize() * -1.0f), n.Normalize(), 0.9f);
			//Vector t = aLight.CalcTransmissionDirection((v.Normalize() * -1.0f), n.Normalize(), 1.5f);
			Vector u = r.Direction;
			u = u.Normalize() * -1.0f;			
			Vector t = aLight.CalcTransmissionDirection((u), n.Normalize(), 1.5f);
			if((t.x != ZERO.x) && (t.y != ZERO.y) && (t.z != ZERO.z))
			{
				Vector T = RayCast(Ray(p, t), Depth - 1);
				result = result + Vector(P.Transmission.x * T.x, P.Transmission.y * T.y, P.Transmission.z * T.z );
			}
		}
		//if ! Transparent
	}
	return result;
}

int main()
{
	cout << "RayTracer starting...\n";
	bitmap image1;
	image1.create(256, 256);
	cout << "Image Created...\n";
	// Camera is a ray as well, Source would be the position that the camera exists and
	// Direction would be where it is looking.	
	Vector CameraCenter = Vector(0.0f, 0.0f, 0.0f);		
	ViewCamera = Camera(CameraCenter, Vector(0.0f, 0.0f, 1.0f) , Vector(0.0f, 1.0f, 0.0f), image1.getwidth(), image1.getheight() );
	ViewCamera.CalculatePlaneNormals();	

	Shapes a = Shapes();	
	LightConstants Material = LightConstants(Vector(0.0f,0.9f,0.0f), Vector(0.1f, 0.1f, 0.1f), Vector(0.1f, 0.1f, 0.1f), Vector(), Vector(), Vector(), 8.0f);
	a.setPlane(Vector( 0.0f, 1.0f, 0.0f, 1.0f), Material);	
	ShapeList.push_back(a);

	Material = LightConstants(Vector(1.0f,0.0f,0.0f), Vector(0.1f, 0.1f, 0.1f), Vector(0.0f, 0.0f, 0.0f), Vector(), Vector(), Vector(), 8.0f);
	a.setPlane(Vector( 0.0f,-1.0f, 0.0f, 1.0f), Material);
	ShapeList.push_back(a);

	Material = LightConstants(Vector(0.9f, 0.9f, 0.0f), Vector(0.1f, 0.1f, 0.1f), Vector(0.0f, 0.0f, 0.0f), Vector(), Vector(), Vector(), 8.0f);
	a.setPlane(Vector( 1.0f, 0.0f, 0.0f, 1.0f), Material);
	ShapeList.push_back(a);

	Material = LightConstants(Vector(0.9f,0.9f,0.9f), Vector(0.1f, 0.1f, 0.1f),Vector(0.0f, 0.0f, 0.0f) ,Vector() , Vector(), Vector(), 8.0f);
	a.setPlane(Vector(-1.0f, 0.0f, 0.0f, 1.0f), Material);
	ShapeList.push_back(a);	

	Shapes b = Shapes();
	Material = LightConstants(Vector(0.0f,0.0f,0.7f), Vector(0.3f, 0.3f, 0.3f), Vector(), Vector(), Vector(0.1f, 0.1f, 0.1f), Vector(), 4.0f);
	b.setSphere(0.5f, Material, false);
	b.Translatef(Vector( 0.0f, 1.0f, 0.0f));
	ShapeList.push_back(b);

	Material = LightConstants(Vector(0.7f,0.0f,0.0f), Vector(0.3f, 0.3f, 0.3f), Vector(), Vector(), Vector(0.5f, 0.5f, 0.5f), Vector(), 16.0f);
	b.setSphere(0.5f, Material, false);
	b.Translatef(Vector(-1.0f, 0.0f, 0.0f));
	ShapeList.push_back(b);

	Material = LightConstants(Vector(0.1f,0.1f,0.1f), Vector(0.9f, 0.9f, 0.9f), Vector(), Vector(), Vector(0.5f, 0.5f, 0.5f), Vector(), 16.0f);
	b.setSphere(0.5f, Material, false);
	b.Translatef(Vector( 1.0f, 0.0f, 0.0f));
	ShapeList.push_back(b);

	Material = LightConstants(Vector(0.0f,0.7f,0.0f), Vector(0.3f, 0.3f, 0.3f), Vector(), Vector(), Vector(0.5f, 0.5f, 0.5f), Vector(), 16.0f);
	b.setSphere(0.5f, Material, false);
	b.Translatef(Vector(0.0f, -1.0f, 0.0f));
	ShapeList.push_back(b);	

	Material = LightConstants(Vector(0.5f , 0.5f , 0.5f), Vector(0.5f, 0.5f, 0.5f), Vector(), Vector(), Vector(), Vector(0.9f, 0.9f, 0.9f), 16.0f);
	b.setTriangle(Vector(0.5f, 0.0f, 0.0f), Vector(0.0f, 0.5f, 0.0f), Vector(-0.5f, 0.0f, 0.0f), Material);
	b.Translatef(Vector(0.0f, 0.0f, -0.5f));
	//b.Rotatef(3.0f, Vector(0.0f, 1.0f, 0.0f));
	ShapeList.push_back(b);

	/*Material = LightConstants(Vector(0.7f,0.0f,0.0f), Vector(0.3f, 0.3f, 0.3f), Vector(), Vector(), Vector(), Vector(), 16.0f);
	b.setTriangle(Vector(-1.0f, 1.0f, 0.0f) , Vector(-1.0f, 0.0f, 0.0f),  Vector(0.0f, 1.0f, 0.0f) , Material);
	ShapeList.push_back(b);

	Material = LightConstants(Vector(0.0f,0.7f,0.0f), Vector(0.3f, 0.3f, 0.3f), Vector(), Vector(), Vector(), Vector(), 16.0f);
	b.setTriangle(Vector(0.0f, 1.0f, 0.0f), Vector(1.0f, 0.0f, 0.0f), Vector(1.0f, 1.0f, 0.0f), Material);
	ShapeList.push_back(b);

	Material = LightConstants(Vector(0.0f,0.7f,0.0f), Vector(0.3f, 0.3f, 0.3f), Vector(), Vector(), Vector(), Vector(), 16.0f);
	b.setTriangle(Vector(-1.0f, 0.0f, 0.0f), Vector(0.0f,-1.0f, 0.0f), Vector(-1.0f,-1.0f, 0.0f), Material);
	ShapeList.push_back(b);*/

	LightConstants LightValue = LightConstants(Vector(0.7f, 0.7f, 0.7f), Vector(0.3f, 0.3f, 0.3f), Vector(1.0f, 1.0f, 1.0f));
	aLight = Light(Ray(Vector( 0.5f, 0.5f, -1.0f), Vector(0.0f, 0.0f, 0.0f)) , LightValue);
	LightValue = LightConstants(Vector(0.7f, 0.7f, 0.7f), Vector(0.3f, 0.3f, 0.3f), Vector(0.5f, 0.5f, 0.5f));
	aLight.addLight(Ray(Vector(-0.5f, 0.5f,  -1.0f), Vector(0.0f, 0.0f, 0.0f)), LightValue);
	//aLight.addLight(Ray(Vector(0.0f, 0.0f, 40.0f), Vector(0.0f, 0.0f, 0.0f)), LightValue);
	//aLight.addLight(Ray(Vector(0.0f, 0.0f, 30.0f), Vector(0.0f, 0.0f, 0.0f)), LightValue);
	//aLight.addLight(Ray(Vector(0.0f, 0.0f, -10.0f), Vector(0.0f, 0.0f, 0.0f)), LightValue);
	cout << "Casting Rays...\n";
	BYTE Red, Green, Blue;

	for(int i = 1; i < image1.getwidth(); i++)
	{
		cout << i;
		float w = image1.getwidth();
		float t = i / w;
		Vector Left   = Parametric(ViewCamera.P3(), ViewCamera.P0(), t);
		Vector Right  = Parametric(ViewCamera.P2(), ViewCamera.P1(), t);
		for(int j = 1; j < image1.getheight(); j++)
		{	
			Vector p0 = ViewCamera.P0();
			Vector p1 = ViewCamera.P1();
			Vector p2 = ViewCamera.P2();
			Vector p3 = ViewCamera.P3();
			float z = (p0.z + p1.z + p2.z + p3.z) / 4;
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
			Red = (unsigned)Limit255((Colour.x) * 255);
			Green = (unsigned)Limit255((Colour.y) * 255);
			Blue = (unsigned)Limit255((Colour.z) * 255);
			image1.setcolor((255 - i) , (255 - j), Red, Green, Blue);
		}
	}
	cout << "Saving Image...\n";
	image1.save("image1.bmp");	
	//system("PAUSE");
	return 0;
}