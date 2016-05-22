#pragma once

template<class T>
class IDictanceCalculator
{
	public:
		virtual double Distance(const T & o1, const T & o2) const = 0;

		virtual T FindMiddle(const T & o1, const T & o2) const = 0;
};