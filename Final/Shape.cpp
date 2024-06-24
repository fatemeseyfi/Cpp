#include "Shape.h"
#include "IShape.h"
#include "Point.h"

Shape::Shape()
{
}

// =============================================================

Shape::~Shape()
{
}

// =============================================================

const IPoint& Shape::getCenter() const
{
    return m_center;
}

// =============================================================

void Shape::setCenter(const IPoint& p)
{
    m_center = p;
}

IShape::ShapeType Shape::getType() const
{
    return m_type;
}


