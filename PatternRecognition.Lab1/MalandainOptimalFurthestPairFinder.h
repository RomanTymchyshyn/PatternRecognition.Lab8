#pragma once

#include "IFurthestPairFinder.h"
#include <utility>
#include <vector>
#include "IDistanceCalculator.h"

template<class T>
class MalandainOptimalFurthestPairFinder: public MalandainFurthestPairFinder<T>
{
	public:
		virtual std::pair<T, T> SearchMaxPair(const std::vector<T> & P, const std::vector<T> & Q, 
			std::vector<std::pair<T, T>> & DNs, std::vector<double> & distances, 
			IDictanceCalculator<T>* distanceCalculator, double & distance) const;
};

template <class T>
std::pair<T, T> MalandainOptimalFurthestPairFinder<T>::SearchMaxPair(const std::vector<T> & P, const std::vector<T> & Q, 
	std::vector<std::pair<T, T>> & DNs, std::vector<double> & distances, 
	IDictanceCalculator<T>* distanceCalculator, double & distance) const
{
	int size= DNs.size();
	std::vector<T> qSet = Q;

	std::pair<T, T> maxPair = DNs[DNs.size() - 2];

	for (int i = 0; i < size && qSet.size() > 0; ++i)
	{
		T p = DNs[i].first;
		T q = DNs[i].second;
		T mid = distanceCalculator->FindMiddle(p, q);
		double r = distances[i] / 2.0;

		std::vector<T> intersection, difference;

		int n = qSet.size();
		for (int j = 0; j < n; ++j)
		{
			double dev = (qSet[j].X() - mid.X())*(qSet[j].X() - mid.X()) + (qSet[j].Y() - mid.Y())*(qSet[j].Y() - mid.Y());
			if (std::sqrt(dev) > r + 0.0001)
			{
				difference.push_back(qSet[j]);
			}
			else
			{
				intersection.push_back(qSet[j]);
			}
		}

		int m = P.size();
		std::vector<T> P2;
		for (int j = 0; j < m; ++j)
		{
			bool found = false;
			for (int k = 0; k < difference.size() && !found; ++k)
			{
				if (P[j] == difference[k])
					found = true;
			}
			if (!found)
				P2.push_back(P[j]);
		}

		double d;
		std::pair<T, T> pq = SearchInCarthesian(intersection, P2, distanceCalculator, d);

		if (d > distance)
		{
			distance = d;
			maxPair = pq;
			DNs.push_back(pq);
			distances.push_back(d);
		}

		qSet = difference;
	}

	return maxPair;
}