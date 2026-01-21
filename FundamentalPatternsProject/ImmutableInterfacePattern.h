#pragma once
#include <iostream>

class IImmutablePoint2D
{
public:
	virtual int GetX() const = 0;
	virtual int GetY() const = 0;
};

class Point2D : public IImmutablePoint2D
{
	int x;
	int y;
public:
	Point2D(int x = 0, int y = 0)
		: x{ x }, y { y }{}
	
	int GetX() const override { return x; }
	int GetY() const override { return y; }

	void SetX(int x) { this->x = x; }
	void SetY(int y) { this->y = y; }

	friend std::ostream& operator<<(std::ostream& out, const Point2D* point)
	{
		out << "(" << point->x << "," << point->y << ")";
		return out;
	}
};
