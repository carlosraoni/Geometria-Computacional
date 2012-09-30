#include <iostream>
#include "geometry2d.h"

using namespace std;
using namespace geometry2d;

int main( int argc, char** argv )
{
	int n;
	double x, y;
	vector<Point2D> poly;
	PointInPolygonAlgorithm * alg = new CrossingNumberAlgorithm();
	//PointInPolygonAlgorithm * alg = new WindingNumberAlgorithm();

	while(cin >> n){
		if(n == 0) break;

		poly.clear();
		for(int i=0; i<n; i++){
			cin >> x >> y;
			poly.push_back(Point2D(x, y));
		}

		cin >> x >> y;
		Point2D p(x, y);

		if(alg->pointInPolygon(p, poly) == 1)
			cout << "F" << endl;
		else
			cout << "T" << endl;
	}

	return 0;
}

