#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

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
	int n, niter;
	double x, y;
	vector<Point2D> p;
	vector< vector<Point2D> > resp;

	cin >> niter;
	for(int iter = 0; iter < niter; iter++){
		if(iter) cin >> n;
		cin >> n;

		p.clear();
		for(int i=0; i<n; i++){
			cin >> x >> y;
			p.push_back(Point2D(x, y));
		}

		convexHull(p);
		resp.push_back(p);
	}

	cout << niter << endl;
	for(int i=0; i<niter; i++){
		if(i) cout << "-1" << endl;
		vector<Point2D> ch = resp[i];
		n = ch.size();
		cout << n + 1<< endl;
		for(int j=0; j<n; j++)
			cout << (int) ch[j].first << " " << (int) ch[j].second << endl;
		cout << (int) ch[0].first << " " << (int) ch[0].second << endl;
	}

	return 0;
}

