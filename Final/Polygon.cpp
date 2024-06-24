
#include "Polygon.h"
#include <stdexcept>
#include "Point.h"
#include "Line.h"
#include <algorithm>
#include <vector>
#include <cmath>

Polygon::Polygon() : m_points(nullptr), m_pointCount(0)
{
}

// ============================================================= 

Polygon::Polygon(const Polygon& polygon)
{
	m_type = ShapeType::Polygon;
	if (polygon.getPointsCount() == 0) {
		m_points = nullptr;
		m_pointCount = 0;
		return;
	}
	m_pointCount = polygon.getPointsCount();
	m_points = new Point[m_pointCount];
	for (int i = 0; i < m_pointCount; i++) {
		m_points[i] = polygon.getPoint(i);
	}
}

// ============================================================= 

Polygon::Polygon(const Point* points, unsigned pointCount, float angle)
{
	m_type = ShapeType::Polygon;

	m_pointCount = pointCount;
	m_points = new Point[m_pointCount];
	std::copy(points, points + pointCount, m_points);

	if (m_pointCount < 3) {
		throw std::exception("Invalid Point Count");
	}
	if (!validateConvexity(points, pointCount)) {
		throw std::exception("Point not belong to a convex polygon");
	}



	m_center = Point(0, 0);
	for (int i = 0; i < pointCount; i++) {
		Point& p = m_points[i];

		m_center += p;

	}
	m_center /= m_pointCount;
}

// ============================================================= 

Polygon::Polygon(const std::vector<Point>& points) : Polygon(points.data(), points.size())

{
}

// ============================================================= 

Polygon::~Polygon()
{
	if (m_points) { delete[] m_points; }

}

// ============================================================= 

unsigned Polygon::getPointsCount() const
{
	return m_pointCount;
}

// ============================================================= 

const IPoint& Polygon::getPoint(unsigned index) const
{
	if (index >= m_pointCount) {
		throw std::exception("Out of Boundery");
	}
	return m_points[index];
}

// ============================================================= 

const IPoint* Polygon::getPoints() const
{
	//to-do: refactor
	return m_points;
}

// ============================================================= 

void Polygon::setCenter(const IPoint& p)
{
	float difX = p.getX() - m_center.getX();
	float difY = p.getY() - m_center.getY();

	for (int i = 0; i < m_pointCount; i++) {
		Point& pp = m_points[i];

		pp.setCoordinate(pp.getX() + difX,
			pp.getY() + difY);
	}
	//todo 
	m_center = p;
}

// ============================================================= 

float Polygon::getArea() const
{
	float a = 0;
	for (int i = 1; i < m_pointCount - 1; i++) {
		a += triangleArea(m_points[0], m_points[i], m_points[i + 1]);
	}
	return a;
}

// ============================================================= 

float Polygon::getPerimeter() const
{
	float p = 0;
	for (int i = 0; i < m_pointCount; i++) {
		int j = (i + 1) % m_pointCount;

		p += distance(m_points[i], m_points[j]);
	}
	return p;
}

// ============================================================= 

float Polygon::getDiameter() const
{
	float d = 0;
	for (int i = 0; i < m_pointCount; i++) {
		for (int j = i + 1; j < m_pointCount; j++) {
			d = std::max(d, distance(m_points[i], m_points[j]));
		}
	}
	return d;
}

// ============================================================= 

bool Polygon::operator==(const IShape& other)
{
	if (other.getType() != m_type && other.getType() != ShapeType::Triangle)
		return false;

	const Polygon* otherPol = nullptr;
	otherPol = dynamic_cast<const Polygon*>(&other);

	if (otherPol) {
		return m_pointCount == otherPol->getPointsCount() &&
			m_points == otherPol->getPoints();
	}
	else
		return false;
}

// ============================================================= 

float Polygon::distance(const Point& p1, const Point& p2) const
{
	return std::sqrt((std::pow(p1.getX() - p2.getX(), 2.0f)) + (std::pow(p1.getY() - p2.getY(), 2.0f)));
}

// ============================================================= 

bool Polygon::validateConvexity(const Point* points, unsigned pointCount) const
{
	/*if (pointCount<3)
		return false;

	Point p;
	Point v;
	Point u;
	int res = 0;
	for (int i = 0; i < pointCount; i++) {
		const Point& p = points[i];
		const Point& tmp = points[(i + 1) % pointCount];
		const Point v(tmp.getX() - p.getX(), tmp.getY() - p.getY());
		const Point& u = points[(i + 2) % pointCount];

		if (i == 0)
			res = u.getX() * v.getY() - u.getY() * v.getX() + v.getX() * p.getY() - v.getY() * p.getX();
		else
		{
			int newres = u.getX() * v.getY() - u.getY() * v.getX() + v.getX() * p.getY() - v.getY() * p.getX();
			if ((newres > 0 && res < 0) || (newres < 0 && res > 0))
				return false;
		}
	}*/
	return true;

}

// ============================================================= 

float Polygon::triangleArea(const Point& p1, const Point& p2, const Point& p3) const
{
	return 0.5 * (
		p1.getX() * (p2.getY() - p3.getY()) +
		p2.getX() * (p3.getY() - p1.getY()) +
		p3.getX() * (p1.getY() - p2.getY())
		);
}

void Polygon::draw(SDL_Renderer* renderer)
{

	setLines();

	for (int i = 0; i < crossed.size(); i++) {
		crossed[i]->draw(renderer);
	}
	crossed.clear();
	seen.clear();
	
}

//======================================================================================================================
//======================================================================================================================
//======================================================================================================================



// -- Salesman ------------------------------------------------------------



bool Polygon::HasSeen(std::vector<Point> seen, Point p) {
	bool has = false;

	for (int i = 0; i < seen.size(); i++) {
		if (seen[i].getX() == p.getX() && seen[i].getY() == p.getY()) {
			has = true;
			break;
		}
	}

	return has;



}

bool Polygon::validate(std::vector<Line*> crossed, Line newLine) {
	bool ok = true;

	double new_m, new_c, m, c;
	double x_intersect = 0;
	double y_intersect = 0;
	double new_XDelta, new_YDelta, XDelta, YDelta;

	for (int i = 0; i < crossed.size(); i++) {

		new_XDelta = newLine.getDst().getX() - newLine.getSrc().getX();
		new_YDelta = newLine.getDst().getY() - newLine.getSrc().getY();
		XDelta = (*crossed[i]).getDst().getX() - (*crossed[i]).getSrc().getX();
		YDelta = (*crossed[i]).getDst().getY() - (*crossed[i]).getSrc().getY();

		if ((newLine.getSrc().getX() == (*crossed[i]).getSrc().getX() && newLine.getSrc().getY() == (*crossed[i]).getSrc().getY()) ||
			(newLine.getSrc().getX() == (*crossed[i]).getDst().getX() && newLine.getSrc().getY() == (*crossed[i]).getDst().getY()) ||
			(newLine.getDst().getX() == (*crossed[i]).getSrc().getX() && newLine.getDst().getY() == (*crossed[i]).getSrc().getY()) ||
			(newLine.getDst().getX() == (*crossed[i]).getDst().getX() && newLine.getDst().getY() == (*crossed[i]).getDst().getY()))
			continue;

		if (new_XDelta != 0 && XDelta != 0) {
			if (new_YDelta != 0 && YDelta != 0) {
				new_m = new_YDelta / new_XDelta;
				new_c = newLine.getSrc().getY() - (new_m * newLine.getSrc().getX());
				m = YDelta / XDelta;
				c = (*crossed[i]).getSrc().getY() - (m * (*crossed[i]).getSrc().getX());
				x_intersect = -(new_c - c) / (new_m - m);
				y_intersect = new_m * x_intersect + new_c;

			}
			else if (new_YDelta == 0 && YDelta != 0) {
				m = YDelta / XDelta;
				c = (*crossed[i]).getSrc().getY() - (m * (*crossed[i]).getSrc().getX());

				x_intersect = (newLine.getSrc().getY() - c) / m;
				y_intersect = newLine.getSrc().getY();
			}
			else if (new_YDelta != 0 && YDelta == 0) {
				new_m = new_YDelta / new_XDelta;
				new_c = newLine.getSrc().getY() - (new_m * newLine.getSrc().getX());
				x_intersect = ((*crossed[i]).getSrc().getY() - new_c) / new_m;
				y_intersect = (*crossed[i]).getSrc().getY();
			}
			else {
				if ((newLine.getSrc().getX() > std::min((*crossed[i]).getDst().getX(), (*crossed[i]).getSrc().getX()) && newLine.getSrc().getX() < std::max((*crossed[i]).getDst().getX(), (*crossed[i]).getSrc().getX())) ||
					(newLine.getDst().getX() > std::min((*crossed[i]).getDst().getX(), (*crossed[i]).getSrc().getX()) && newLine.getDst().getX() < std::max((*crossed[i]).getDst().getX(), (*crossed[i]).getSrc().getX()))) {
					ok = false;

				}
			}
		}
		else if (new_XDelta == 0 && XDelta != 0) {
			m = YDelta / XDelta;
			c = (*crossed[i]).getSrc().getY() - (m * (*crossed[i]).getSrc().getX());

			x_intersect = newLine.getSrc().getX();
			y_intersect = m * x_intersect + c;

		}
		else if (new_XDelta == 0 && XDelta == 0) {
			if ((newLine.getSrc().getY() > std::min((*crossed[i]).getDst().getY(), (*crossed[i]).getSrc().getY()) && newLine.getSrc().getY() < std::max((*crossed[i]).getDst().getY(), (*crossed[i]).getSrc().getY())) ||
				(newLine.getDst().getY() > std::min((*crossed[i]).getDst().getY(), (*crossed[i]).getSrc().getY()) && newLine.getDst().getY() < std::max((*crossed[i]).getDst().getY(), (*crossed[i]).getSrc().getY()))) {
				ok = false;
				break;
			}
		}
		else if (new_XDelta != 0 && XDelta == 0) {
			new_m = new_YDelta / new_XDelta;
			new_c = newLine.getSrc().getY() - (new_m * newLine.getSrc().getX());

			x_intersect = (*crossed[i]).getSrc().getX();
			y_intersect = new_m * x_intersect + new_c;
		}

		// Check if the intersection point lies within the range of the existing line segment
		if (ok) {
			if (x_intersect >= std::min((*crossed[i]).getDst().getX(), (*crossed[i]).getSrc().getX()) && x_intersect <= std::max((*crossed[i]).getDst().getX(), (*crossed[i]).getSrc().getX()) &&
				y_intersect >= std::min((*crossed[i]).getDst().getY(), (*crossed[i]).getSrc().getY()) && y_intersect <= std::max((*crossed[i]).getDst().getY(), (*crossed[i]).getSrc().getY()) &&
				x_intersect >= std::min(newLine.getDst().getX(), newLine.getSrc().getX()) && x_intersect <= std::max(newLine.getDst().getX(), newLine.getSrc().getX()) &&
				y_intersect >= std::min(newLine.getDst().getY(), newLine.getSrc().getY()) && y_intersect <= std::max(newLine.getDst().getY(), newLine.getSrc().getY())) {
				ok = false;
				break;
			}
		}
	}

	return ok;

}

bool Polygon::Salesman(std::vector<Line*>& crossed, Point* cities, Point srcCity, Point currentCity) {

	//first condition 
	if (seen.size() == m_pointCount) {
		Line newLine(Point(currentCity.getX(), currentCity.getY()), Point(srcCity.getX(), srcCity.getY()));


		if (validate(crossed, newLine)) {
			crossed.push_back(&newLine);
			//drawWalk(renderer, crossed, cities);
			return true;
		}
	}



	for (int i = 0; i < m_pointCount; i++) {

		Point p = { cities[i].getX(), cities[i].getY() };

		if ((currentCity.getX() == cities[i].getX() && currentCity.getY() == cities[i].getY()) || HasSeen(seen, p)) continue;

		Line newLine(Point(currentCity.getX(), currentCity.getY()), Point(cities[i].getX(), cities[i].getY()));

		if (crossed.empty()) {
			crossed.push_back(&newLine);
			seen.push_back(p);
			//drawWalk(renderer, crossed, cities);
			if (Salesman(crossed, cities, srcCity, p)) return true;

		}
		else if (validate(crossed, newLine)) {
			crossed.push_back(&newLine);
			seen.push_back(p);
			//drawWalk(renderer, crossed, cities);
			if (Salesman(crossed, cities, srcCity, p)) return true;
		}
	}
	if (!crossed.empty()) {
		crossed.pop_back();
	}
	if (!seen.empty()) {
		seen.pop_back();
	}
	return false;


}

void Polygon::setLines()
{
	seen.push_back(m_points[0]);
	Salesman(crossed, m_points, m_points[0], m_points[0]);
}





