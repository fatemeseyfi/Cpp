#ifndef SQUARE_H
#define SQUARE_H

#include "Rectangle.h"
#include "ISquare.h"
#include "ISize.h"
class Square : public Rectangle, public ISquare
{
public:

	Square();
	Square(float size, const Point& center, float angle = 0);
	Square(const ISize& size, const IPoint& center, float angle = 0);
	~Square();

	// Implement pure virtual functions from ISquare and IRectangle
	void setSize(const ISize& size) override;
	void setSize(float size) override;
	void setRotation(float angle) override;

	const ISize& getSize() const override;
	float getRotation() const override;


	// Implement pure virtual functions from IShape
	float getArea() const override;
	float getPerimeter() const override;
	float getDiameter() const override;

	bool operator==(const IShape& other) override;


};
#endif // !SQUARE_H

