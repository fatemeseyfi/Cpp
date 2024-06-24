#ifndef SIZE_H
#define SIZE_H
#include "ISize.h"
class Size : public ISize
{
	int m_height;
	int m_width;

public:
	Size();
	Size(int h, int w);
	Size(const ISize& size);
	~Size();

	void setDimension(int h, int w) override;
	void setDimension(const ISize& size) override;

	int getHeight() const override;
	int getWidth() const override;

	bool operator==(const ISize& s) override {
		return m_height == s.getHeight() && m_width == s.getWidth();
	}

protected:
	virtual void validateCoordinate(float x, float y) const;
};
#endif
