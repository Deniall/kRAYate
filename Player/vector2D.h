#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cmath>

class Vector2D{
public:
	double x;
	double y;

	Vector2D(double ix,double iy);
	Vector2D(int ix,int iy);
	Vector2D();

	Vector2D normalized();

	double magnitude();

	double distance(Vector2D point);

	Vector2D clampMagnitude(double max);

	Vector2D lerp(Vector2D to, double amount);

};

#endif
