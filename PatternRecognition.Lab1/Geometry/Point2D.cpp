#include "Point2D.h"

double Point2D::Distance(const Point2D & p2) const
{
	return std::sqrt((p2.X() - this->X()) * (p2.X() - this->X()) + 
		(p2.Y() - this->Y()) * (p2.Y() - this->Y()));
}

bool operator==(const Point2D & p1, const Point2D & p2)
{
	const double eps = 0.0001;
	return (std::fabs(p1.X() - p2.X()) < eps && std::fabs(p1.Y() - p2.Y()) < eps);
}

bool operator!=(const Point2D & p1, const Point2D & p2)
{
	return !(p1 == p2);
}