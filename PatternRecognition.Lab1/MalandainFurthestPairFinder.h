#pragma once

#include <utility>
#include <vector>
#include "IFurthestPairFinder.h"
#include "IDistanceCalculator.h"

template<class T>
class MalandainFurthestPairFinder: public IFurthestPairFinder<T>
{
	public:
		virtual std::pair<T, T> FindFurthestPair(std::vector<T> set, 
			IDictanceCalculator<T>* distanceCalculator, double & distance) const;

	protected:
		//A4-A5 (depends on overload in derived class)
		virtual std::pair<T, T> SearchMaxPair(const std::vector<T> & P, const std::vector<T> & Q, 
			std::vector<std::pair<T, T>> & DNs, std::vector<double> & distances, 
			IDictanceCalculator<T>* distanceCalculator, double & distance) const = 0;

		std::pair<T, T> SearchInCarthesian(const std::vector<T> & P1, const std::vector<T> & P2,
			IDictanceCalculator<T>* distanceCalculator, double & distance) const;

	private:
		//A1
		std::pair<T, T> DoubleNormal(int numberInSet, std::vector<T> & P, 
			IDictanceCalculator<T>* distanceCalculator, double & distance) const;

		// return number of furthest point in set P
		int FP(const T & p, const std::vector<T> & P, 
			IDictanceCalculator<T>* distanceCalculator, double & distance) const;

		//A2
		std::pair<T, T> DNScan(std::vector<T> & P, 
			IDictanceCalculator<T>* distanceCalculator, double & distance,
			std::vector<std::pair<T, T>> & DNs, std::vector<double> & distances) const;
		
		std::pair<T, T> MalandainAlgo(std::vector<T> P, 
			IDictanceCalculator<T>* distanceCalculator, double & distance) const;

		//finds difference P\B[pq] by given P, p, q
		std::vector<T> FindQ(const std::vector<T> & P, const T & p, const T & q, 
			IDictanceCalculator<T>* distanceCalculator) const;
};

template<class T>
std::pair<T, T> MalandainFurthestPairFinder<T>::FindFurthestPair(std::vector<T> P, 
	IDictanceCalculator<T>* distanceCalculator, double & distance) const 
{
	std::vector<std::pair<T, T>> DNs;
	std::vector<double> distances;
	//A2
	std::pair<T, T> DN = DNScan(P, distanceCalculator, distance, DNs, distances);

	if (distances.size() <= 1 || distances[distances.size() - 1] > distances[distances.size() - 2])
	{
		return DN;
	}

	std::pair<T, T> pq = DNs[DNs.size() - 2];
	double maxDist = distances[distances.size() - 2];

	//A3
	std::vector<T> Q = FindQ(P, pq.first, pq.second, distanceCalculator);

	if (Q.size() == 0)
	{
		distance = distances[distances.size() - 2];
		return pq;
	}
	
	//A4-A5
	return SearchMaxPair(P, Q, DNs, distances, distanceCalculator, distance);
}

template<class T>
int MalandainFurthestPairFinder<T>::FP(const T & p, const std::vector<T> & P, 
	IDictanceCalculator<T>* distanceCalculator, double & distance) const
{
	distance = -1.0;
	int result = -1;
	int n = P.size();
	for (int i = 0; i < n; ++i)
	{
		double dist = distanceCalculator->Distance(p, P[i]);
		if (dist > distance)
		{
			distance = dist;
			result = i;
		}
	}
	return result;
}

template<class T>
std::pair<T, T> MalandainFurthestPairFinder<T>::DoubleNormal(int numberInSet, std::vector<T> & P, 
	IDictanceCalculator<T>* distanceCalculator, double & distance) const
{
	distance = -1.0;
	double newDistance = 0.0;
	T p = P[numberInSet];

	std::pair<T, T> DN;

	while (newDistance - distance > 0.0)
	{
		distance = newDistance;
		P.erase(P.begin() + numberInSet);
		double tempDist ;
		numberInSet = FP(p, P, distanceCalculator, tempDist);
		T q = P[numberInSet];
		if (tempDist > distance)
		{
			newDistance = tempDist;
			DN = std::make_pair(p, q);
			p = q;
		}
	}

	return DN;
}

template<class T>
std::pair<T, T> MalandainFurthestPairFinder<T>::DNScan(std::vector<T> & P, 
	IDictanceCalculator<T>* distanceCalculator, double & distance, 
	std::vector<std::pair<T, T>> & DNs, std::vector<double> & distances) const
{
	distance = -1.0;
	bool stop = false;

	int numberInSet = 0;
	T p = P[numberInSet];
	std::vector<T> Q;
	std::pair<T, T> DN;

	do
	{
		double newDist;
		//A1
		std::pair<T, T> pq = DoubleNormal(numberInSet, P, distanceCalculator, newDist);
		DNs.push_back(pq);
		distances.push_back(newDist);
		if (distance < newDist)
		{
			distance = newDist;
			DN = pq;
			Q = FindQ(P, DN.first, DN.second, distanceCalculator);
			if (Q.size() > 0)
			{
				double tempDist;
				numberInSet = FP(distanceCalculator->FindMiddle(DN.first, DN.second), P, distanceCalculator, tempDist);
			}
		}
		else
		{
			stop = true;
		}
	}
	while(Q.size() > 0 && !stop);

	return DN;
}

template<class T>
std::vector<T> MalandainFurthestPairFinder<T>::FindQ(const std::vector<T> & P, const T & p, const T & q, 
	IDictanceCalculator<T>* distanceCalculator) const
{
	int n = P.size();

	T mid = distanceCalculator->FindMiddle(p, q);
	double r = distanceCalculator->Distance(mid, p);
	
	std::vector<T> Q;
	Q.reserve(n / 2.0);

	for (int i = 0; i < n; ++i)
	{
		double dev = (P[i].X() - mid.X())*(P[i].X() - mid.X()) + (P[i].Y() - mid.Y())*(P[i].Y() - mid.Y());
		if (std::sqrt(dev) > r + 0.0001)
		{
			Q.push_back(P[i]);
		}
	}

	return Q;
}

template<class T>
std::pair<T, T> MalandainFurthestPairFinder<T>::SearchInCarthesian(const std::vector<T> & P1, const std::vector<T> & P2,
	IDictanceCalculator<T>* distanceCalculator, double & distance) const
{
	distance = -1.0;
		
	int n = P1.size();
	int m = P2.size();
	std::pair<T, T> max;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			double dist = distanceCalculator->Distance(P1[i], P2[j]);
			if (dist > distance)
			{
				distance = dist;
				max = std::make_pair(P1[i], P2[j]);
			}
		}
	}

	return max;
}