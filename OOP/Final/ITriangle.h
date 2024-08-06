#pragma once
#include "IPolygon.h"
#include "IPoint.h"

class ITriangle : virtual public IPolygon {

public:
	virtual void setPoint(const IPoint& p, int index) = 0;


};