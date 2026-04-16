#include "circle.h"
#include <cmath>
#include <limits>
#include <stdexcept>

using namespace std;

const float PI = acosf(-1);

Circle::Circle(float r, const Point& center) : center(center) 
{
	if (r <= 0)
		throw invalid_argument("Radius value must be bigger than 0.");

	this->radius = r;
}

//Equivalent to center(Point(x, y))
Circle::Circle(float r, float x, float y) : center(x, y) 
{
	if (r <= 0)
		throw invalid_argument("Radius value must be bigger than 0.");

	this->radius = r;
}

//Returns perimeter
float Circle::perimeter() const {
	return 2 * PI * radius;
}

//Returns area
float Circle::area() const {
	return PI * (float)powf(radius, 2);
}

//Deslocates the circle
FloatXY Circle::move(FloatXY displacement) {
	return center.move(displacement);
}

//Changes the size of the circle and returns its radius
float Circle::resize(float zoom)
{
	if(zoom <= 0)
		throw invalid_argument("Zoom value must be bigger than 0.");

	float new_radius = radius * zoom;
	radius = new_radius;
	return radius;
}

//Checks if a point is inside of the circle
bool Circle::contains(const Point& p) const
{
	return center.distanceTo(p) <= radius;
}

//Calculates the distance between two circles
float Circle::perimetersDistance(const Circle& c) const
{
	float cd = center.distanceTo(c.center);
	return cd - this->radius - c.radius;
}

//Returns the coordinates of the center of the circle
FloatXY Circle::position() const {
	return center.displacementFrom(Point::ORIGIN);
}

//Returns the size of the circle
float Circle::size() const {
	return radius;
}

//Returns the quadrant that the circle is in
Quadrant Circle::quadrant() const {
	return center.quadrant();
}

//Returns a string that indicates the quadrant that the circle is in
string Circle::quadrantStr() const {
	return center.quadrantStr();
}