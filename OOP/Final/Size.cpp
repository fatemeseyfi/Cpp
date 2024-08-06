#include "Size.h"
#include <exception>

Size::Size()
{
	Size(0, 0);
}

// =============================================================

Size::Size(int h, int w)
{
	setDimension(h, w);
}

Size::Size(const ISize& size) :Size(size.getHeight(), size.getWidth())
{
}

// =============================================================

void Size::setDimension(int h, int w)
{
	validateCoordinate(h, w);
	m_height = h;
	m_width = w;
}

// =============================================================

void Size::setDimension(const ISize& size)
{
	setDimension(size.getHeight(), size.getWidth());
}

// =============================================================

Size::~Size() {}

// =============================================================

int Size::getHeight() const
{
	return m_height;
}

// =============================================================

int Size::getWidth() const
{
	return m_width;
}


void Size::validateCoordinate(float x, float y) const
{
	if (x < 0 || y < 0)
		throw std::exception("Invalid value!");
}
