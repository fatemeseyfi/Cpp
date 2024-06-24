#ifndef POINT_H
#define POINT_H
#include "IPoint.h"
#include "IDrawable.h"

class Point : public IPoint, public IDrawable
{
private:

	float m_x;
	float m_y;

public:

	Point();
	Point(const IPoint& p);
	Point(float x, float y);

	~Point();

	// Implement pure virtual functions fro IPoint
	void setCoordinate(float x, float y) override;
	void setCoordinate(const IPoint& p) override;
	float getX() const override;
	float getY() const override;

	// Implement pure virtual functions fro IDrawable
	void draw(SDL_Renderer* renderer) override;

public:

	IPoint& operator+=(const IPoint& p)  override;
	IPoint& operator/=(float v)  override;
	bool operator==(const IPoint& p) override {
		return m_x == p.getX() && m_y == p.getY();
	}

protected:

	virtual void validateCoordinate(float x, float y) const;
};

#endif
