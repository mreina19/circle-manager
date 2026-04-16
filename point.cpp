#include "point.h"
#include <cmath>

using namespace std;

const Point Point::ORIGIN(0, 0);

Point::Point(float x, float y) {
	this->x = x;
	this->y = y;
}

FloatXY Point::displacementFrom(const Point& p) const {
	return { x - p.x, y - p.y };
}

float Point::distanceTo(const Point& p) const
{
	FloatXY c2d = displacementFrom(p);

	float num = pow(c2d.x, 2) + pow(c2d.y, 2);

	return (float)sqrt(num);
}

FloatXY Point::move(FloatXY displacement)
{
	x += displacement.x;
	y += displacement.y;
	return { x, y };
}

Quadrant Point::quadrant() const
{
	if (x == 0 || y == 0)
		return Quadrant::NONE;

	if (y > 0)
	{
		if (x > 0)
			return Quadrant::Q1;
		return Quadrant::Q2;
	}

	if (x < 0)
		return Quadrant::Q3;

	return Quadrant::Q4;
}

string Point::quadrantStr() const
{
	switch (quadrant())
	{
		case Quadrant::Q1:
			return "Q1";
			break;

		case Quadrant::Q2:
			return "Q2";
			break;

		case Quadrant::Q3:
			return "Q3";
			break;

		case Quadrant::Q4:
			return "Q4";
			break;

		default:
			return "NONE";
			break;
	}
}