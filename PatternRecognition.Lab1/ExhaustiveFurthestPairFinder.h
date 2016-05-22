#pragma once

#include "IFurthestPairFinder.h"
#include <utility>
#include <vector>
#include "IDistanceCalculator.h"

template <class T>
class ExhaustiveFurthestPairFinder: public IFurthestPairFinder<T>
{
	public:
		virtual std::pair<T, T> FindFurthestPair(std::vector<T> set, 
			IDictanceCalculator<T>* distanceCalculator, double & distance) const;
};

template <class T>
std::pair<T, T> ExhaustiveFurthestPairFinder<T>::FindFurthestPair(std::vector<T> set, 
	IDictanceCalculator<T>* distanceCalculator, double & distance) const
{
	int n = set.size();
	distance = -1;
	std::pair<T, T> result;
	for (int i = 0; i < n; ++i)
	{
		T t1 = set[i];
		for (int j = i + 1; j < n; ++j)
		{
			T t2 = set[j];
			double dist = distanceCalculator->Distance(t1, t2);
			if (dist > distance)
			{
				result = std::make_pair(t1, t2);
				distance = dist;
			}
		}
	}
	return result;
}