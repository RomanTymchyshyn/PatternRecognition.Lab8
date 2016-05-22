#pragma once

#include <cmath>
#define M_PI 3.141592653589793238462643383279502884

class Point2D
{
	public:

		Point2D(double x = 0.0, double y = 0.0): _x(x), _y(y) {};

		Point2D(const Point2D& p): _x(p.X()), _y(p.Y()) {};
		
		double X() const { return _x; };

		double Y() const { return _y; };

		double Distance(const Point2D & p2) const;

	private:

		double _x;

		double _y;
};

bool operator==(const Point2D & p1, const Point2D & p2);

bool operator!=(const Point2D & p1, const Point2D & p2);