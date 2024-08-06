#ifndef SHAPE_H
#define SHAPE_H
#include "Point.h"
#include "IPoint.h"
#include "IShape.h"
#include "IDrawable.h"

class Shape : virtual public IShape, public IDrawable
{


protected:
	Point m_center;
	ShapeType m_type;

public:
	Shape();
	virtual ~Shape();

	virtual const IPoint& getCenter() const override;
	virtual void setCenter(const IPoint& p) override;

	virtual ShapeType getType() const override;
};
#endif
