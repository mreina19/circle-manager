#ifndef circle_h
#define circle_h

#include "point.h"

class Circle
{
	Point center;
	float radius;

	public:
		Circle(float r, const Point& center = Point::ORIGIN);
		Circle(float r, float x, float y);
		float perimeter() const;
		float area() const;
		FloatXY move(FloatXY displacement);
		float resize(float zoom);
		bool contains(const Point& p) const;
		float perimetersDistance(const Circle& c) const;
		FloatXY position() const;
		float size() const;
		Quadrant quadrant() const;
		std::string quadrantStr() const;
};
#endif