#ifndef  POLYGAN_H
#define POLYGAN_H
#include <vector>
#include "Point.h"
#include "Shape.h"
#include "Line.h"
#include "IPolygon.h"
#include "IDrawable.h"
#include <vector>

class Polygon : public Shape, public IPolygon, IDrawable
{
protected:
	Point* m_points;
	unsigned m_pointCount;
	std::vector<Point> seen;
	//std::vector<Line*> crossed;




public:
	std::vector<Line*> crossed;

	Polygon();
	Polygon(const Polygon& polygon);
	Polygon(const Point* points, unsigned pointCount, float angle=0);
	Polygon(const std::vector<Point>& points);

	~Polygon();

	// Implement pure virtual functions from IPolygon
	unsigned getPointsCount() const override;
	const IPoint& getPoint(unsigned index) const override;
	const IPoint* getPoints() const override;


	// Implement pure virtual functions from IShape
	void setCenter(const IPoint& p) override;
	virtual float getArea() const override;
	virtual float getPerimeter() const override;
	virtual float getDiameter() const override;
	virtual bool operator==(const IShape& other) override;

	// Implement pure virtual functions from IDrawable
	virtual void draw(SDL_Renderer* renderer) override;


private:

	bool HasSeen(std::vector<Point> seen, Point p);
	bool validate(std::vector<Line*> crossed, Line newLine);
	bool Salesman(std::vector<Line*>& crossed, Point* cities, Point srcCity, Point currentCity);
	void setLines();




private:
	float distance(const Point& p1, const Point& p2) const;
	bool validateConvexity(const Point* points, unsigned pointCount) const;
	float triangleArea(const Point& p1, const Point& p2, const Point& p3) const;
};
#endif 


