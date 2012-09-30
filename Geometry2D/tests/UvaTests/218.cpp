#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>

using namespace std;

const double EPS = 1e-7;

typedef pair<double, double> Point2D;

double ccw(const Point2D & p0, const Point2D & p1, const Point2D & p2){
	return ( (p1.first - p0.first) * (p2.second - p0.second) -
			  (p2.first - p0.first) * (p1.second - p0.second) );
}

double squareDist(const Point2D & p1, const Point2D & p2){
	double dx = p2.first - p1.first;
	double dy = p2.second - p1.second;
	return dx * dx + dy * dy;
}

Point2D refPoint;

bool polarAngleCompare(const Point2D & p1, const Point2D & p2){
	double cp = ccw(refPoint, p1, p2);
	return (fabs(cp) < EPS) ? (squareDist(refPoint, p1) < squareDist(refPoint, p2)) : (cp > 0.0);
}

void convexHull(vector<Point2D> & p){
	int n = p.size();

	int indexBottomLeft = 0;
	for(int i=1; i<n; i++){
		if(p[i].second > p[indexBottomLeft].second) continue;
		if(p[i].second < p[indexBottomLeft].second || p[i].first < p[indexBottomLeft].first)
			indexBottomLeft = i;
	}
	swap(p[0], p[indexBottomLeft]);
	refPoint = p[0];
	sort(p.begin(), p.end(), polarAngleCompare);

	int convHullSize = 2;
	for(int i=2; i<n; i++){
		while(convHullSize >= 2 && !(ccw(p[convHullSize - 2], p[convHullSize - 1], p[i]) > 0.0))
			convHullSize--;
		p[convHullSize++] = p[i];
	}
	p.resize(convHullSize);
}

int main( int argc, char** argv )
{
	int n, iter = 0;
	double x, y;
	vector<Point2D> p;

	while(cin >> n){
		if(n == 0) break;
		if(iter) cout << endl;

		p.clear();
		for(int i=0; i<n; i++){
			cin >> x >> y;
			p.push_back(Point2D(x, y));
		}

		convexHull(p);

		printf("Region #%d:\n", ++iter);
		printf("(%.1f,%.1f)", p[0].first, p[0].second);
		double perimeter = 0.0;
		for(int i=p.size() - 1; i >= 0; i--){
			perimeter += sqrt(squareDist(p[(i+1)%p.size()], p[i]));
			printf("-(%.1f,%.1f)", p[i].first, p[i].second);
		}
		printf("\n");
		printf("Perimeter length = %.2f\n", perimeter);
	}

	return 0;
}


