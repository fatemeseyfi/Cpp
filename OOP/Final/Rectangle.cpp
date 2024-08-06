#include "Rectangle.h"
#include "Point.h"
#include "Line.h"
#include "Size.h"
#include "ISize.h"
#include "Shape.h"
#include <exception>
#include <cmath>

Rectangle::Rectangle() : Rectangle(Size(), Point(), 0) {

}

// =============================================================

Rectangle::Rectangle(const ISize& size, const IPoint& center, float angle) {
	m_type = ShapeType::Rectangle;
	m_size = size;
	m_center = center;
	setRotation(angle);

}

// =============================================================

Rectangle::~Rectangle() {}

// =============================================================

void Rectangle::setSize(const ISize& size) {
	m_size.setDimension(size.getHeight(), size.getWidth());
}

// =============================================================

void Rectangle::setRotation(float angle) {
	if (angle < 0)
		throw std::exception("Invalid value");
	m_angle = angle;
}

// =============================================================

const ISize& Rectangle::getSize() const {
	return m_size;
}

// =============================================================

float Rectangle::getRotation() const {
	return m_angle;
}

// =============================================================

float Rectangle::getArea() const
{
	return m_size.getHeight() * m_size.getWidth();
}

// =============================================================

float Rectangle::getPerimeter() const
{
	return 2 * (m_size.getHeight() + m_size.getWidth());
}

// =============================================================

float Rectangle::getDiameter() const
{
	return std::sqrt((std::pow(m_size.getHeight(), 2.0f)) +
		(std::pow(m_size.getWidth(), 2.0f)));
}

// =============================================================

bool Rectangle::operator==(const IShape& other)
{
	if (other.getType() != m_type && other.getType() != ShapeType::Square)
		return false;

	const Rectangle* otherRect = nullptr;
	otherRect = dynamic_cast<const Rectangle*>(&other);

	if (otherRect) {
		return m_angle == otherRect->getRotation() &&
			m_center == otherRect->getCenter() &&
			m_size == otherRect->getSize();
	}
	else
		return false;



}

// =============================================================

void Rectangle::draw(SDL_Renderer* renderer) 
{
	float rad = m_angle * M_PI / 180.0;

	float halfW = m_size.getWidth() / 2.0f;
	float halfH = m_size.getHeight() / 2.0f;

	Point corners[4] = {
		Point(-halfW, -halfH),
		Point(halfW, -halfH),
		Point(halfW, halfH),
		Point(-halfW, halfH)
	};

	Point rotatedCorners[4];
	for (int i = 0; i < 4; ++i) {
		float x = corners[i].getX() * cos(rad) - corners[i].getY() * sin(rad);
		float y = corners[i].getX() * sin(rad) + corners[i].getY() * cos(rad);
		rotatedCorners[i].setCoordinate(x + m_center.getX(), y + m_center.getY());
	}

	for (int i = 0; i < 4; ++i) {
		Line l(rotatedCorners[i], rotatedCorners[(i + 1) % 4]);
		l.draw(renderer);
	}
	
}



// =============================================================


