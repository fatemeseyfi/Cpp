#pragma once;

class ISize {

public:

	virtual void setDimension(int h, int w) = 0;
	virtual void setDimension(const ISize& size) = 0;

	virtual int getHeight() const = 0;
	virtual int getWidth() const = 0;

	virtual bool operator==(const ISize& s) = 0;
};