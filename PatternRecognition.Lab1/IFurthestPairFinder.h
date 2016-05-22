#pragma once

#include <utility>
#include <vector>
#include "IDistanceCalculator.h"

template <class T>
class IFurthestPairFinder
{
	public:
		virtual std::pair<T, T> FindFurthestPair(std::vector<T> set, 
			IDictanceCalculator<T>* distanceCalculator, double & distance) const  = 0;
};