#pragma once

#include <cmath>
#include "IDistanceCalculator.h"
#include "Geometry\Point2D.h"

class PToPDistanceCalculator: public IDictanceCalculator<Point2D>
{
	public:

		virtual double Distance(const Point2D & p1, const Point2D & p2) const;

		virtual Point2D FindMiddle(const Point2D & p1, const Point2D & p2) const;
};