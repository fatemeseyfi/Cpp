#pragma once
#include "Polygon.h"
#include "ITriangle.h"

#include <vector>
class Triangle : public Polygon, public ITriangle
{
public:
	Triangle();
	Triangle(const Point& p1, const Point& p2, const Point& p3);
	Triangle(const std::vector<Point>& points);
	~Triangle();

	// Implement pure virtual functions from IPolygon
	void setPoint(const IPoint& p, int index) override;
	const IPoint* getPoints() const override;
	unsigned getPointsCount() const override;
	const IPoint& getPoint(unsigned index) const override;



	// Implement pure virtual functions from IShape

	float getArea() const override;
	float getPerimeter() const override;
	float getDiameter() const override;
	bool operator==(const IShape& other) override;

	// Implement pure virtual functions from Polygon
	void draw(SDL_Renderer* renderer) override;
};

