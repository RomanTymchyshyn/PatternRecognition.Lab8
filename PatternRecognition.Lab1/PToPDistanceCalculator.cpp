#include "PToPDistanceCalculator.h"

double PToPDistanceCalculator::Distance(const Point2D & p1, const Point2D & p2) const
{
	return p1.Distance(p2);
}

Point2D PToPDistanceCalculator::FindMiddle(const Point2D & p1, const Point2D & p2) const
{
	return Point2D((p1.X() + p2.X())/2.0, (p1.Y() + p2.Y())/2.0);
}