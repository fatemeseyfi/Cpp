#include "Square.h"
#include <cmath>
#include <exception>

Square::Square() : Square(0, Point(0, 0), 0)
{
}

// =============================================================

Square::Square(float size, const Point& center, float angle) : Rectangle(Size(size, size), center, angle)
{
	m_type = ShapeType::Square;
}

Square::Square(const ISize& size, const IPoint& center, float angle) : Rectangle(Size(size.getWidth(), size.getWidth()), center, angle)
{
}

// ============================================================= 

Square::~Square()
{
}

// ============================================================= 

void Square::setRotation(float angle)
{
	Rectangle::setRotation(angle);
}

void Square::setSize(float size)
{
	Rectangle::setSize(Size(size, size));
}

// ============================================================= 

const ISize& Square::getSize() const
{
	return Rectangle::getSize();
}

float Square::getRotation() const
{
	return Rectangle::getRotation();
}

// ============================================================= 

float Square::getArea() const
{
	return Rectangle::getArea();
}

// ============================================================= 

float Square::getPerimeter() const
{
	return Rectangle::getPerimeter();
}

// ============================================================= 

float Square::getDiameter() const {
	return Rectangle::getDiameter();
}

// ============================================================= 

bool Square::operator==(const IShape& other)
{
	if (other.getType() != m_type && other.getType() != ShapeType::Rectangle)
		return false;

	const Square* otherSqr = nullptr;
	otherSqr = dynamic_cast<const Square*>(&other);

	if (otherSqr) {
		return m_angle == otherSqr->getRotation() &&
			m_center == otherSqr->getCenter() &&
			m_size == otherSqr->getSize();
	}
	else
		return false;
}

void Square::setSize(const ISize& size)
{
	Rectangle::setSize(Size(size.getWidth(), size.getWidth()));

}

// ============================================================= 


