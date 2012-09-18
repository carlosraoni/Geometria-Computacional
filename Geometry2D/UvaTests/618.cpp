#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>
#include <cstdio>

using namespace std;

const double EPS = 1e-9;
const double PI = 2*acos(0.0);

class Point2D
{

public:
	Point2D();
	Point2D(double m_x, double m_y);
	~Point2D();

	double getX() const { return m_x; }
	double getY() const { return m_y; }

	double norm() const;

	string toString() const;

private:

	double m_x;
	double m_y;

};

const Point2D operator*(double c, const Point2D p){
	return Point2D(c * p.getX(), c * p.getY());
}

double operator*(const Point2D & p1, const Point2D & p2){
	return p1.getX() * p2.getX() + p1.getY() * p2.getY();
}

const Point2D operator+(const Point2D & p1, const Point2D & p2){
	return Point2D(p1.getX() + p2.getX(), p1.getY() + p2.getY());
}

const Point2D operator-(const Point2D & p1, const Point2D & p2){
	return Point2D(p1.getX() - p2.getX(), p1.getY() - p2.getY());
}

Point2D::Point2D() : m_x(0.0), m_y(0.0)
{

}

Point2D::Point2D(double x, double y) : m_x(x), m_y(y)
{

}

Point2D::~Point2D()
{

}

double Point2D::norm() const{
	return sqrt(m_x * m_x + m_y * m_y);
}

string Point2D::toString() const{
	ostringstream o;
	o << "(" << m_x << "," << m_y << ")";
	return o.str();
}

double doubleSignedTriangleArea(const Point2D & p0, const Point2D & p1, const Point2D & p2){
	return ( (p1.getX() - p0.getX()) * (p2.getY() - p0.getY()) -
			  (p2.getX() - p0.getX()) * (p1.getY() - p0.getY()) );
}

bool isLeft(const Point2D & p0, const Point2D & p1, const Point2D & p2){
	return doubleSignedTriangleArea(p0, p1, p2) > 0.0;
}

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
		if(fabs(p[i].getY() - p[indexLeftBottom].getY()) < EPS){
			if(p[i].getX() < p[indexLeftBottom].getX())
				indexLeftBottom = i;
		}
		else if(p[i].getY() < p[indexLeftBottom].getY()){
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
		while(prevLast >=0 && !isLeft(convHull[prevLast], convHull[last], p[i])){
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

int main( int argc, char** argv )
{
	int n, niter;
	double x, y;
	vector<Point2D> p;
	vector< vector<Point2D> > resp;
	ConvexHullAlgorithm * alg = new GrahamScanAlgorithm();

	cin >> niter;

	for(int iter = 0; iter < niter; iter++){
		if(iter) cin >> n;

		cin >> n;

		p.clear();
		for(int i=0; i<n; i++){
			cin >> x >> y;
			p.push_back(Point2D(x, y));
		}

		vector<Point2D> ch = alg->convexHull(p);
		resp.push_back(ch);
	}

	cout << niter << endl;
	for(int i=0; i<niter; i++){
		if(i) cout << "-1" << endl;
		vector<Point2D> ch = resp[i];
		n = ch.size();
		cout << n << endl;
		for(int j=0; j<n; j++)
			cout << (int) ch[j].getX() << " " << (int) ch[j].getY() << endl;
	}

	delete alg;
	return 0;
}

