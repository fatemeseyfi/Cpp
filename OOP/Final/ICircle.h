#pragma once
#include "Elipse.h"
class ICircle : virtual public IElipse {
public:

	virtual void setRadius(const float& radius) = 0;
	virtual float getRadius() const = 0;

};