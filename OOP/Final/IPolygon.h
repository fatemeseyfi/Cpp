#pragma once
#include "IShape.h"
#include "IPoint.h"
class IPolygon : virtual public IShape {
public:

	virtual unsigned getPointsCount() const = 0;
	virtual const IPoint& getPoint(unsigned index) const = 0;
	virtual const IPoint* getPoints() const = 0;

};