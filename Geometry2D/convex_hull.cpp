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
		return isLeft(referencePoint, p1, p2);
	}

private:
	Point2D referencePoint;
};

vector<Point2D> GrahamScanAlgorithm::convexHull(vector<Point2D> & p){
	int n = p.size();
	int indexLeftBottom = 0;

	for(int i=1; i<n; i++){
		if(fabs(p[i].getX() - p[indexLeftBottom].getX()) < EPS){
			if(p[i].getY() < p[indexLeftBottom].getY())
				indexLeftBottom = i;
		}
		else if(p[i].getX() < p[indexLeftBottom].getX()){
			indexLeftBottom = i;
		}
	}
	//cout << "LeftBottom: " << p[indexLeftBottom].toString() << endl;
	swap(p[0], p[indexLeftBottom]);
	sort(p.begin() + 1, p.end(), PolarAngleComparator(p[indexLeftBottom]));
	//for(int i=0; i<n; i++){
	//	cout << "p[" << i << "] = " << p[i].toString() << endl;
	//}

	vector<Point2D> convHull;
	convHull.push_back(p[0]);
	convHull.push_back(p[1]);
	convHull.push_back(p[2]);

	for(int i=3; i<n; i++){
		int last = convHull.size() - 1;
		int prevLast = last - 1;
		while(!isLeft(convHull[prevLast], convHull[last], p[i])){
			convHull.pop_back();
			last = convHull.size() - 1;
			prevLast = last - 1;
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
