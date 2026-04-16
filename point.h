#ifndef point_h
#define point_h

#include <string>

struct FloatXY {
	float x, y;
};

enum class Quadrant {
	Q1, Q2, Q3, Q4, NONE
};

class Point
{
	float x, y;

	public:
		static const Point ORIGIN;
		Point(float x, float y);
		FloatXY displacementFrom(const Point& p) const;
		float distanceTo(const Point& p) const;
		FloatXY move(FloatXY displacement);
		Quadrant quadrant() const;
		std::string quadrantStr() const;
};
#endif