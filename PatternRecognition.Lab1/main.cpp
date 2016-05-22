#include <vector>
#include <iostream>
#include <string>
#include <ctime>
#include "Geometry/Point2D.h"
#include "PToPDistanceCalculator.h"
#include "ExhaustiveFurthestPairFinder.h"
#include "MalandainExhaustiveFurthestPairFinder.h"
#include "MalandainOptimalFurthestPairFinder.h"

void RunAndMeasure(const std::vector<Point2D> & points, IFurthestPairFinder<Point2D>* furthestPairFinder, const std::string & algoName);

std::vector<Point2D> GenRandVertexesInEllipse(const int & number, const double & xC, const double & yC, 
	const double & xAxis, const double & yAxis);

int main()
{
	std::srand(std::time(NULL));

	const int NumberOfPoints = 100000;
	
	std::vector<Point2D> points = GenRandVertexesInEllipse(NumberOfPoints, 0, 0, 1, 0.5);
	
	IFurthestPairFinder<Point2D>* furthestPairFinder = new ExhaustiveFurthestPairFinder<Point2D>();
	
	RunAndMeasure(points, furthestPairFinder, "Exhaustive algorithm");

	delete furthestPairFinder;

	furthestPairFinder = new MalandainExhaustiveFurthestPairFinder<Point2D>();

	RunAndMeasure(points, furthestPairFinder, "Malandain with exhaustive search");

	delete furthestPairFinder;

	furthestPairFinder = new MalandainOptimalFurthestPairFinder<Point2D>();

	RunAndMeasure(points, furthestPairFinder, "Malandain with optimal search");
		
	delete furthestPairFinder;

	std::cout << "Press any key.\n";
	std::cin.get();
	
	return 0;
}

void RunAndMeasure(const std::vector<Point2D> & points, IFurthestPairFinder<Point2D>* furthestPairFinder, const std::string & algoName)
{
	IDictanceCalculator<Point2D>* distCalculator = new PToPDistanceCalculator();

	double distance = 0.0;
	
	clock_t time = clock();
	
	std::pair<Point2D, Point2D> maxPair = furthestPairFinder->FindFurthestPair(points, distCalculator, distance);
	
	time = clock() - time;

	double ms = double(time) / CLOCKS_PER_SEC * 1000;

	std::cout << algoName << std::endl;
	std::cout << "Time elapsed: " << ms << " ms" << std::endl;
	std::cout << "Max Pair: (" << maxPair.first.X() << "," << maxPair.first.Y() << "), (" << maxPair.second.X() << "," << maxPair.second.Y() << ")\n";
	std::cout << "Distance: " << distance << std::endl << std::endl;

	delete distCalculator;
}

std::vector<Point2D> GenRandVertexesInEllipse(const int & number, const double & xC, const double & yC, 
	const double & xAxis, const double & yAxis)
{
	double minX = -xAxis;
	double minY = -yAxis;
	int maxY = yAxis;
	int maxX = xAxis;

	double x = 0.0, y = 0.0;
	std::vector<Point2D> points;
	for (int i = 0; i < number; ++i)
	{
		double phi = ((double)rand() / RAND_MAX) * M_PI;

		x = (maxX - minX) * ((double)std::rand() / RAND_MAX) + minX;
		y = (maxY - minY) * ((double)std::rand() / RAND_MAX) + minY;

		points.push_back(Point2D(x * std::sin(phi) + xC, y * std::cos(phi) + yC));
	}
	return points;
}
