#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include <vector>
#include "point2d.h"

using namespace std;

namespace geometry2d{

class ConvexHullAlgorithm{

public:
	virtual vector<Point2D> convexHull(vector<Point2D> & p) = 0;

};

class GrahamScanAlgorithm : public ConvexHullAlgorithm{

public:
	vector<Point2D> convexHull(vector<Point2D> & p);

};

class DivideAndConquerConvexHullAlgorithm : public ConvexHullAlgorithm{

public:
	vector<Point2D> convexHull(vector<Point2D> & p);

};

}

#endif // CONVEX_HULL_H

