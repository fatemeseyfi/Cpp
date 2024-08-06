#ifndef ELIPSE_H
#define ELIPSE_H
#include "Point.h"
#include "Size.h"
#include "Shape.h"
#include "IElipse.h"
#include "IDrawable.h"

class Elipse : public Shape, public IElipse, public IDrawable
{
protected:
	Size m_size;
	Point m_center;
	float m_angle;

public:
	Elipse();
	Elipse(const ISize& size, const IPoint& center, float angle = 0);
	~Elipse();

	// Implement pure virtual functions fro IElipse 
	void setSize(const ISize& size) override;
	void setRotation(float angle) override;
	const ISize& getSize() const override;
	float getRotation() const override;

	// Implement pure virtual functions fro IShape
	virtual float getArea() const override;
	virtual float getPerimeter() const override;
	virtual float getDiameter() const override;
	virtual bool operator==(const IShape& other) override;
	virtual const IPoint& getCenter() const override;
	virtual void setCenter(const IPoint& p) override;

	// Implement pure virtual functions fro IDrawable
	void draw(SDL_Renderer* renderer) override;

};
#endif
