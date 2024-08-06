#pragma once

class IPoint {
public:

	virtual void setCoordinate(float x, float y) = 0;
	virtual void setCoordinate(const IPoint& p) = 0;

	virtual float getX() const = 0;
	virtual float getY() const = 0;

	virtual IPoint& operator+=(const IPoint& p) = 0;
	virtual IPoint& operator/=(float v) = 0;
	virtual bool operator==(const IPoint& p) = 0;
};