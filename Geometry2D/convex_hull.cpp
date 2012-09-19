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

void GrahamScanAlgorithm::convexHull(vector<Point2D> & p){
	int n = p.size();

	int indexBottomLeft = 0;
	for(int i=1; i<n; i++){
		if(p[i].getY() > p[indexBottomLeft].getY()) continue;
		if(p[i].getY() < p[indexBottomLeft].getY() || p[i].getX() < p[indexBottomLeft].getX())
			indexBottomLeft = i;
	}
	swap(p[0], p[indexBottomLeft]);
	sort(p.begin(), p.end(), PolarAngleComparator(p[0]));

	int convHullSize = 2;
	for(int i=2; i<n; i++){
		while(convHullSize >= 2 && !isLeft(p[convHullSize - 2], p[convHullSize - 1], p[i])){
			convHullSize--;
		}
		p[convHullSize++] = p[i];
	}
	p.resize(convHullSize);
}

void DivideAndConquerConvexHullAlgorithm::convexHull(vector<Point2D> & p){
}

}
