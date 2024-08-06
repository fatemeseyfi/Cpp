#include "Line.h"
#include "Point.h"
#include <cmath>

Line::Line() : Line(Point(), Point())
{
}

// ============================================================= 

Line::Line(const Line& line) : Line(line.getSrc(), line.getDst())
{
}

// ============================================================= 

Line::Line(const Point& src, const Point& dst)
{
	setLine(src, dst);

}

// ============================================================= 

Line::~Line() {}

// ============================================================= 

void Line::setLine(const IPoint& src, const IPoint& dst)
{
	m_src.setCoordinate(src);
	m_dst.setCoordinate(dst);
}

// ============================================================= 

const IPoint& Line::getSrc() const
{
	return m_src;
}

// ============================================================= 

const IPoint& Line::getDst() const
{
	return m_dst;
}

float Line::getLength() const
{
	return std::sqrt((std::pow(m_dst.getX() - m_src.getX(), 2.0f)) + (std::pow(m_dst.getY() - m_src.getY(), 2.0f)));
}

void Line::draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set color to white
	SDL_RenderDrawLine(renderer, m_src.getX(), m_src.getY(), m_dst.getX(), m_dst.getY());
}


