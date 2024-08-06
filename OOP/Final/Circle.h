#pragma once
#include "Elipse.h"
#include "ICircle.h"

class Circle : public Elipse, public ICircle
{
public:

	Circle();
	Circle(const IPoint& center, const float& radius, float angle=0);
	Circle(const ISize& size, const IPoint& center, float angle = 0);
	~Circle();

	void setRadius(const float& radius) override;
	float getRadius() const override;

	void setSize(const ISize& size)override;
	void setRotation(float angle) override;

	const ISize& getSize() const override;
	float getRotation() const override;

	virtual float getArea() const override;
	virtual float getPerimeter() const override;
	virtual float getDiameter() const override;
};

