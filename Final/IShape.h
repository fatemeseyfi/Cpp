#pragma once
#include "IPoint.h"
#include "IDrawable.h"
class IShape : virtual public IDrawable{
public:
	enum ShapeType {
		Rectangle,
		Square,
		Circle,
		Elipse,
		Polygon,
		Triangle
	};

	virtual const IPoint& getCenter() const = 0;
	virtual void setCenter(const IPoint& p) = 0;

	virtual float getArea() const = 0;
	virtual float getPerimeter() const = 0;
	virtual float getDiameter() const = 0;

	virtual bool operator==(const IShape& other) = 0;
	virtual ShapeType getType() const = 0;


};