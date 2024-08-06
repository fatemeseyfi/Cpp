#include "Elipse.h"
#include "Point.h"
#include "Size.h"
#include "Line.h"
#include "Constants.h"
#include <exception>
#include <algorithm>
#include <iostream>
#include <cmath>

Elipse::Elipse() : Elipse(Size(), Point(), 0) {

}

// =============================================================

Elipse::Elipse(const ISize& size, const IPoint& center, float angle) 
{
    m_type = ShapeType::Elipse;
	m_size = size;
    m_center = center;
	setRotation(angle);
}

// =============================================================

Elipse::~Elipse() {}

// =============================================================

void Elipse::setSize(const ISize& size) {
	m_size.setDimension(size.getHeight(), size.getWidth());
}

// =============================================================

void Elipse::setRotation(float angle) {
	if (angle < 0)
		throw std::exception("Invalid value");
	m_angle = angle;
}

// =============================================================

const ISize& Elipse::getSize() const {
	return m_size;
}

// =============================================================

float Elipse::getRotation() const {
	return m_angle;
}

// =============================================================
float Elipse::getArea() const
{
	return PI * m_size.getHeight() * m_size.getHeight();
}

// =============================================================

float Elipse::getPerimeter() const
{
	return 2 * (m_size.getHeight() + m_size.getWidth());
}

// =============================================================


float Elipse::getDiameter() const
{
	float a = m_size.getWidth() / 2;
	float b = m_size.getHeight() / 2;

	float h = std::pow((a - b) / (a + b), 2.0);
	float p = PI * (a + b) * (1 + (3 * h / (10 + std::sqrt(4 - 3 * h))));

	return p;
}

bool Elipse::operator==(const IShape& other)
{
	if (other.getType() != m_type && other.getType() != ShapeType::Circle)
		return false;

	const Elipse* otherElip = nullptr;
	otherElip = dynamic_cast<const Elipse*>(&other);

	if (otherElip) {
		return m_angle == otherElip->getRotation() &&
			m_center == otherElip->getCenter() &&
			m_size == otherElip->getSize();
	}
	else
		return false;
}

const IPoint& Elipse::getCenter() const
{
    return Shape::getCenter();
}

void Elipse::setCenter(const IPoint& p)
{
    Shape::setCenter(p);
}

// =============================================================

void Elipse::draw(SDL_Renderer* renderer)
{

    Point center = m_center;
    int numSegments = 100; // Increase for a smoother ellipse
    float rad = m_angle * M_PI / 180.0;
    float majorAxis = std::max(m_size.getHeight(), m_size.getWidth()) / 2.0f;
    float minorAxis = std::min(m_size.getHeight(), m_size.getWidth()) / 2.0f;

    Point* points = new Point[numSegments];

    for (int i = 0; i < numSegments; ++i) {
        float theta = 2.0f * M_PI * float(i) / float(numSegments);
        float x = majorAxis * cosf(theta);
        float y = minorAxis * sinf(theta);

        // Apply rotation
        float xr = x * cos(rad) - y * sin(rad);
        float yr = x * sin(rad) + y * cos(rad);

        points[i].setCoordinate(xr + center.getX(), yr + center.getY());
    }


    for (int i = 0; i < numSegments; ++i) {
        int next = (i + 1) % numSegments;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		Line l(points[i], points[(i + 1) % numSegments]);
		l.draw(renderer);
    }

    delete[] points;
    }



