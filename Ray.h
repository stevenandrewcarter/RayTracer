#ifndef RAY_H
#define RAY_H
#include "Maths/Vector.h"

class Ray
{
public:
	Ray()
	{
		Source = Vector();
		Direction = Vector();
	};

	Ray(Vector ASource, Vector ADirection)
	{
		Source = ASource;
		Direction = ADirection;
	};

	

	Vector Source;
	Vector Direction;	

private:
};

#endif