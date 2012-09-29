#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <vector>
#include "point2d.h"

using namespace std;

namespace geometry2d{

class PolygonTriangulation{

public:

	PolygonTriangulation();
	PolygonTriangulation(const vector<Point2D> & polygon);

	int getNumberOfTriangles();
	vector<Point2D> getTriangle(int index);
	void addTriangle(int indexP0, int indexP1, int indexP2);
	void clearTriangles();

private:

	vector<Point2D> m_p;
	vector<int> m_he;

};

class PolygonTriangulationAlgorithm{

public:
	virtual PolygonTriangulation triangulate(const vector<Point2D> & polygon) = 0;

};

class EarRemovalAlgorithm : public PolygonTriangulationAlgorithm{

public:
	PolygonTriangulation triangulate(const vector<Point2D> & polygon);

};


}

#endif // TRIANGULATION_H
