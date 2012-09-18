#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const double EPS = 1e-7;

class Point2D
{
public:
	Point2D() : m_x(0.0), m_y(0.0){}
	Point2D(double x, double y): m_x(x), m_y(y){}
	~Point2D(){}

	double getX() const { return m_x; }
	double getY() const { return m_y; }

private:
	double m_x;
	double m_y;
};

double doubleSignedTriangleArea(const Point2D & p0, const Point2D & p1, const Point2D & p2){
	return ( (p1.getX() - p0.getX()) * (p2.getY() - p0.getY()) -
			 (p2.getX() - p0.getX()) * (p1.getY() - p0.getY()) );
}

bool isLeft(const Point2D & p0, const Point2D & p1, const Point2D & p2){
	return doubleSignedTriangleArea(p0, p1, p2) > 0.0;
}

double squareDistance(const Point2D & p1, const Point2D & p2){
	double dx = p2.getX() - p1.getX();
	double dy = p2.getY() - p1.getY();
	return dx * dx + dy * dy;
}

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

vector<Point2D> convexHull(vector<Point2D> & p){
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
		vector<Point2D> ch = convexHull(p);
		resp.push_back(ch);
	}

	cout << niter << endl;
	for(int i=0; i<niter; i++){
		if(i) cout << "-1" << endl;
		vector<Point2D> ch = resp[i];
		n = ch.size();
		cout << n + 1<< endl;
		for(int j=0; j<n; j++)
			cout << (int) ch[j].getX() << " " << (int) ch[j].getY() << endl;
		cout << (int) ch[0].getX() << " " << (int) ch[0].getY() << endl;
	}

	return 0;
}

