#include "Point.h"
#include <exception>
#include "Constants.h"

Point::Point() : Point(0, 0) {}

// =============================================================

Point::Point(float x, float y) {
	setCoordinate(x, y);
}

// =============================================================

Point::~Point() {}

// =============================================================

Point::Point(const IPoint& p) : Point(p.getX(), p.getY()) {}

// =============================================================

void Point::setCoordinate(float x, float y) {
	//validateCoordinate(x, y);
	m_x = x;
	m_y = y;
}

// =============================================================

void Point::setCoordinate(const IPoint& p) {
	setCoordinate(p.getX(), p.getY());
}

// =============================================================

float Point::getX() const
{
	return m_x;
}

// =============================================================

float Point::getY() const
{
	return m_y;
}

// =============================================================

void Point::draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set color to white
	int size = 3; // Size of the square
	SDL_Rect pointRect = { m_x - size / 2, m_y - size / 2, size, size }; // Center the square around the point
	SDL_RenderFillRect(renderer, &pointRect);
}

// =============================================================

IPoint& Point::operator+=(const IPoint& p)
{
	m_x += p.getX();
	m_y += p.getY();

	return *this;
}

// =============================================================

IPoint& Point::operator/=(float v)
{
	m_x /= v;
	m_y /= v;

	return *this;
}


// =============================================================

void Point::validateCoordinate(float x, float y) const
{
	if (x > WORLD_SIZE || y > WORLD_SIZE || x < 0 || y < 0)
		throw std::exception("Invalid value!");
}
