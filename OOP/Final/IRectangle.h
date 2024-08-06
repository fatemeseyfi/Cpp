#pragma once

#include "ISize.h"
#include "IShape.h"

class IRectangle : virtual public IShape {

public:

	virtual void setSize(const ISize& size) = 0;
	virtual void setRotation(float angle) = 0;
	virtual const ISize& getSize() const = 0;
	virtual float getRotation() const = 0;

};