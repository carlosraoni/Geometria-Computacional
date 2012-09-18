#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
#include "geometry2d.h"

using namespace std;

namespace geometry2d{

class PolarAngleComparator{
public:
	PolarAngleComparator(Point2D & p){
		referencePoint = p;
	}

	bool operator()(const Point2D & p1, const Point2D & p2){
		double cp = doubleSignedTriangleArea(referencePoint, p1, p2);
		if(fabs(cp) < EPS){
			return squareDistance(referencePoint, p1) < squareDistance(referencePoint, p2);
		}
		return cp > 0.0;
	}

private:
	Point2D referencePoint;
};

vector<Point2D> GrahamScanAlgorithm::convexHull(vector<Point2D> & p){
	int n = p.size();

	int indexBottomLeft = 0;
	for(int i=1; i<n; i++){
		if(p[i].getY() > p[indexBottomLeft].getY()) continue;
		if(p[i].getY() < p[indexBottomLeft].getY() || p[i].getX() < p[indexBottomLeft].getX())
			indexBottomLeft = i;
	}
	swap(p[0], p[indexBottomLeft]);
	sort(p.begin(), p.end(), PolarAngleComparator(p[0]));

	vector<Point2D> convHull;
	convHull.push_back(p[0]);
	convHull.push_back(p[1]);

	for(int i=2; i<n; i++){
		while(convHull.size() >= 2 && !isLeft(*(convHull.end() - 2), *(convHull.end() - 1), p[i])){
			convHull.pop_back();
		}
		convHull.push_back(p[i]);
	}

	return convHull;
}

vector<Point2D> DivideAndConquerConvexHullAlgorithm::convexHull(vector<Point2D> & p){
	vector<Point2D> ch;

	return ch;
}

}
