#pragma once
#include "IPoint.h"

class ILine {


public:
	virtual void setLine(const IPoint& src, const IPoint& dst) = 0;

	virtual const IPoint& getSrc() const = 0;
	virtual const IPoint& getDst() const = 0;

	virtual float getLength() const = 0;
};