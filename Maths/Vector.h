#ifndef VECTOR_H
#define VECTOR_H
#include <cmath>

#define ZERO_VECTOR = Vector();

class Vector
{
public:

	Vector()
	{
		x = 0;
		y = 0;
		z = 0;
		t = 1;
	};

	Vector(float nx, float ny, float nz)
	{
		x = nx;
		y = ny;
		z = nz;
		t = 1;
	};

	Vector(float nx, float ny)
	{
		x = nx;
		y = ny;
		z = 0;
	};
	
	Vector(float x1, float x2, float x3, float x4)
	{
		x = x1;
		y = x2;
		z = x3;
		t = x4;
	};
	
	void set(float nx, float ny, float nz)
	{
		x = nx;
		y = ny;
		z = nz;
	};

	void set(float nx, float ny)
	{
		x = nx;
		y = ny;
		z = 0;
	};

	bool operator==(const Vector &a) 
	{
		if((x == a.x) && (y == a.y) && (z == a.z))
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	bool operator!=(const Vector &a)
	{
		if((x != a.x) || (y != a.y) || (z == a.z))
		{
			return true;
		}
		else
		{
			return false;
		}
	};
		

	Vector operator+(const Vector &a) const
	{
		return Vector(x + a.x, y + a.y, z + a.z);
	};

	Vector operator-(const Vector &a) const
	{
		return Vector(x - a.x, y - a.y, z - a.z);
	};

	Vector operator*(const Vector &a) const
	{
		Vector vNormal;	

		// Calculate the cross product with the non communitive equation
		vNormal.x = ((y * a.z) - (z * a.y));
		vNormal.y = ((z * a.x) - (x * a.z));
		vNormal.z = ((x * a.y) - (y * a.x));

		// Return the cross product
		return vNormal;								
	};

	Vector operator*(const float &a) const
	{
		return Vector(x * a, y * a, z * a, t * a);
	};

	Vector operator/(const float &a) const
	{
		return Vector(x / a, y / a, z / a, t / a);
	};
	
	float Magnitude()
	{
		return sqrt( ( x * x ) + ( y * y ) + ( z * z ) );
	};

	Vector Normalize()
	{
		float n = Magnitude();
		return Vector( x / n, y / n, z / n); 
	};

	
	float x;
	float y;
	float z;
	float t;
};

float DotProduct(Vector u, Vector v)
{					
	return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);	
};

float Norm(Vector u)
{
	return sqrt( (u.x * u.x) + (u.y * u.y) + (u.z * u.z) + (u.t * u.t) );
};

float Distance(Vector p1, Vector p2)
{
	double ReturnAnswer;
	double x = p2.x - p1.x;
	double y = p2.y - p1.y;
	double z = p2.z - p1.z;
	ReturnAnswer = sqrt( (x * x) + (y * y) + (z * z) );
	return (float)ReturnAnswer;	
};

Vector Parametric(Vector p0, Vector p1, float t)
{
	float d1 = p1.x - p0.x;
	float d2 = p1.y - p0.y;
	float d3 = p1.z - p0.z;
	float X = p0.x + (d1 * t);
	float Y = p0.y + (d2 * t);
	float Z = p0.z + (d3 * t);
	Vector returnPoint = Vector(X,Y,Z);	
	return returnPoint;
};


#endif