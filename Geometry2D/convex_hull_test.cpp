#include <iostream>
#include <cstdio>
#include "geometry2d.h"

using namespace std;
using namespace geometry2d;

int main( int argc, char** argv )
{
	int n, iter = 0;
	double x, y;
	vector<Point2D> p;
	ConvexHullAlgorithm * alg = new GrahamScanAlgorithm();

	while(cin >> n){
		if(n == 0) break;
		if(iter) cout << endl;

		p.clear();
		for(int i=0; i<n; i++){
			cin >> x >> y;
			p.push_back(Point2D(x, y));
		}

		vector<Point2D> ch = alg->convexHull(p);

		printf("Region #%d:\n", ++iter);
		printf("(%.1f,%.1f)", ch[0].getX(), ch[0].getY());
		double perimeter = 0.0;
		for(int i=ch.size() - 1; i >= 0; i--){
			perimeter += (ch[(i+1)%ch.size()] - ch[i]).norm();

			printf("-(%.1f,%.1f)", ch[i].getX(), ch[i].getY());
		}
		printf("\n");
		printf("Perimeter length = %.2f\n", perimeter);
	}

	delete alg;
	return 0;
}

