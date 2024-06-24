#include "Triangle.h"
#include <vector>

Triangle::Triangle() : Triangle(Point(0, 0), Point(0, 0), Point(0, 0))
{
}

Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3) :Polygon(std::vector<Point>({ p1,p2,p3 }))
{
}

Triangle::Triangle(const std::vector<Point>& points) : Polygon(points)
{
}

Triangle::~Triangle()
{
}

void Triangle::setPoint(const IPoint& p, int index)
{
	m_points[index] = p;
}

const IPoint* Triangle::getPoints() const
{
	return Polygon::getPoints();
}

unsigned Triangle::getPointsCount() const
{
	return Polygon::getPointsCount();
}

const IPoint& Triangle::getPoint(unsigned index) const
{
	return Polygon::getPoint(index);
}


float Triangle::getArea() const
{
	return Polygon::getArea();
}

float Triangle::getPerimeter() const
{
	return Polygon::getPerimeter();
}

float Triangle::getDiameter() const
{
	return Polygon::getDiameter();
}

bool Triangle::operator==(const IShape& other)
{
	if (other.getType() != m_type)
		return false;

	const Triangle* otherTri = nullptr;
	otherTri = dynamic_cast<const Triangle*>(&other);

	/*if (otherTri) {
		return m_pointCount == otherTri->getPointsCount() &&
			m_points == otherTri->getPoints();
	}
	else*/
	return false;
}

void Triangle::draw(SDL_Renderer* renderer)
{
	for (int i = 0; i < 3; ++i) {
		Line l(m_points[i], m_points[(i + 1) % 3]);
		l.draw(renderer);
	}
}
