#ifndef LINE_H
#define LINE_H
#include "Point.h"
#include "ILine.h"
#include "IDrawable.h"

class Line : public ILine, public IDrawable
{
	Point m_src;
	Point m_dst;

public:
	Line();
	Line(const Line& line);
	Line(const Point& src, const Point& dst);

	~Line();


	void setLine(const IPoint& src, const IPoint& dst) override;
	const IPoint& getSrc() const override;
	const IPoint& getDst() const override;
	float getLength() const override;

	void draw(SDL_Renderer* renderer) override;
};
#endif

