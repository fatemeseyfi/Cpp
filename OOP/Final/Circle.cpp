#include "Circle.h"
#include <exception>

Circle::Circle() : Elipse() {}

Circle::Circle(const IPoint& center, const float& radius, float angle) : Elipse(Size(radius, radius), center) {

}

Circle::Circle(const ISize& size, const IPoint& center, float angle) :  Elipse(Size(size.getWidth(), size.getWidth()), center)
{
}

// ============================================================= 

Circle::~Circle()
{
}

// ============================================================= 

void Circle::setRadius(const float& radius)
{
	Elipse::setSize(Size(radius * 2.0, radius * 2.0));
}

// ============================================================= 

float Circle::getRadius() const
{
	return Elipse::getSize().getWidth() / 2.0;

}

void Circle::setSize(const ISize& size)
{
	Elipse::setSize(Size(size.getWidth(), size.getWidth()));
}

void Circle::setRotation(float angle)
{
	m_angle = 0;
}

const ISize& Circle::getSize() const
{
	return Elipse::getSize();
}

float Circle::getRotation() const
{
	return 0.0f;
}

// ============================================================= 

float Circle::getArea() const
{
	return Elipse::getArea();
}

// ============================================================= 

float Circle::getPerimeter() const
{
	return Elipse::getPerimeter();
}

// ============================================================= 

float Circle::getDiameter() const
{
	return Elipse::getDiameter();
}

