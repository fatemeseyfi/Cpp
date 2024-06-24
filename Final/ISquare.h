#pragma once
#include "IRectangle.h"
#include "ISize.h"
class ISquare : virtual public IRectangle {
public:
	virtual void setSize(float size) = 0;
	virtual void setRotation(float angle) = 0;

	virtual const ISize& getSize() const = 0;
	virtual float getRotation() const = 0;



};