#pragma once

#include "MalandainFurthestPairFinder.h"
#include <utility>
#include <vector>
#include "IDistanceCalculator.h"

template<class T>
class MalandainExhaustiveFurthestPairFinder: public MalandainFurthestPairFinder<T>
{
	public:
		virtual std::pair<T, T> SearchMaxPair(const std::vector<T> & P, const std::vector<T> & Q, 
			std::vector<std::pair<T, T>> & DNs, std::vector<double> & distances, 
			IDictanceCalculator<T>* distanceCalculator, double & distance) const;
};

template <class T>
std::pair<T, T> MalandainExhaustiveFurthestPairFinder<T>::SearchMaxPair(const std::vector<T> & P, const std::vector<T> & Q, 
	std::vector<std::pair<T, T>> & DNs, std::vector<double> & distances, 
	IDictanceCalculator<T>* distanceCalculator, double & distance) const
{
	bool found = false;

	double prevMaxDist = distances[distances.size() - 2];
	std::pair<T, T> prevMaxPair = DNs[DNs.size() - 2];

	std::pair<T, T> res = SearchInCarthesian(P, Q, distanceCalculator, distance);
	
	if (distance < prevMaxDist)
	{
		distance = prevMaxDist;
		res = prevMaxPair;
	}

	return res;
}