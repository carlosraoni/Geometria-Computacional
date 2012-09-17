#ifndef POINT_IN_POLYGON_H
#define POINT_IN_POLYGON_H

#include <vector>
#include "point2d.h"

using namespace std;

namespace geometry2d{

class PointInPolygonAlgorithm{

public:

    virtual int pointInPolygon(const Point2D & p, const vector<Point2D> & polygon) = 0;

};

class CrossingNumberAlgorithm : public PointInPolygonAlgorithm{

public:

    int pointInPolygon(const Point2D & p, const vector<Point2D> & polygon);

};

class WindingNumberAlgorithm : public PointInPolygonAlgorithm{

public:

    int pointInPolygon(const Point2D & p, const vector<Point2D> & polygon);

};

}
#endif // POINT_IN_POLYGON_H

