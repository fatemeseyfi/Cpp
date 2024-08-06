#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Size.h"
#include "ISize.h"
#include "Point.h"
#include "IPoint.h"
#include "Shape.h"
#include "IRectangle.h"

class Rectangle : public Shape, public IRectangle
{
protected:
	Size m_size;
	float m_angle;

public:
	Rectangle();
	Rectangle(const ISize& size, const IPoint& center, float angle = 0);
	~Rectangle();

	// Implement pure virtual functions fro ISquare and IRectangle
	void setSize(const ISize& size) override;
	void setRotation(float angle)  override;
	const ISize& getSize() const override;
	float getRotation() const override;

	// Implement pure virtual functions from IShape
	virtual float getArea() const override;
	virtual float getPerimeter() const override;
	virtual float getDiameter() const override;
	virtual bool operator==(const IShape& other) override;

	// Implement pure virtual functions from Shape
	void draw(SDL_Renderer* renderer) override;

};
#endif
