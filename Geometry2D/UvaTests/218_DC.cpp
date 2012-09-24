#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>

using namespace std;

const double EPS = 1e-7;


class Point2D
{

public:

	Point2D() : m_x(0.0), m_y(0.0) {}
	Point2D(double x, double y) : m_x(x) , m_y(y) {}
	~Point2D() {}

	double getX() const { return m_x; }
	double getY() const { return m_y; }

	void translateX(double dx) { m_x += dx; }
	void translateY(double dy) { m_y += dy; }

private:

	double m_x;
	double m_y;

};

double squareDist(const Point2D & p1, const Point2D & p2){
	double dx = p2.getX() - p1.getX();
	double dy = p2.getY() - p1.getY();
	return dx * dx + dy * dy;
}

double ccw(const Point2D & p0, const Point2D & p1, const Point2D & p2){
	return ( (p1.getX() - p0.getX()) * (p2.getY() - p0.getY()) -
			 (p2.getX() - p0.getX()) * (p1.getY() - p0.getY()) );
}

bool isLeft(const Point2D & p0, const Point2D & p1, const Point2D & p2){
	return ccw(p0, p1, p2) > 0.0;
}


bool leftBottomCompare(const Point2D & p1, const Point2D & p2){
	if(p1.getX() < p2.getX())
		return true;
	if(p1.getX() > p2.getX())
		return false;
	return p1.getY() < p2.getY();
}

int nextCW(int index, int n){
	return (index == 0) ? n-1: index - 1;
}

int nextCCW(int index, int n){
	return (index + 1) % n;
}

int findIndexRighMostPoint(const vector<Point2D> & p){
	int n = p.size(), index = 0;
	for(int i=1; i<n; i++){
		if(p[i].getX() > p[index].getX())
			index = i;
	}
	return index;
}

int findIndexLeftMostPoint(const vector<Point2D> & p){
	int n = p.size(), index = 0;
	for(int i=1; i<n; i++){
		if(p[i].getX() < p[index].getX())
			index = i;
	}
	return index;
}

bool isLeftOriented(const Point2D & p0, int indexP1, const vector<Point2D> & p){
	int n = p.size();
	return isLeft(p0, p[indexP1], p[nextCCW(indexP1, n)]) && isLeft(p0, p[indexP1], p[nextCW(indexP1, n)]);
}

bool isRightOriented(const Point2D & p0, int indexP1, const vector<Point2D> & p){
	int n = p.size();
	return !isLeft(p0, p[indexP1], p[nextCCW(indexP1, n)]) && !isLeft(p0, p[indexP1], p[nextCW(indexP1, n)]);
}

pair<int, int> findUpperTangent(int idxRightMost, int idxLeftMost,
								 const vector<Point2D> & leftCH, const vector<Point2D> &rightCH){
	int nl = leftCH.size();
	int nr = rightCH.size();

	int indexPLeft = idxRightMost;
	int indexPRight = idxLeftMost;

	//cout << "FindUT" << endl;
	//cout << "ipl: " << indexPLeft << ", ipr : " << indexPRight << endl;

	while(!(isLeftOriented(rightCH[indexPRight], indexPLeft, leftCH) &&
			 isRightOriented(leftCH[indexPLeft], indexPRight, rightCH))){

		while(!isLeftOriented(rightCH[indexPRight], indexPLeft, leftCH)){
			indexPLeft = nextCCW(indexPLeft, nl);
		//	cout << "nextccwLeft -> ipl: " << indexPLeft << ", ipr : " << indexPRight << endl;
		}
		while(!isRightOriented(leftCH[indexPLeft], indexPRight, rightCH)){
			indexPRight = nextCW(indexPRight, nr);
		//	cout << "nextcwRight -> ipl: " << indexPLeft << ", ipr : " << indexPRight << endl;
		}
	}

	return pair<int, int>(indexPLeft, indexPRight);
}

pair<int, int> findLowerTangent(int idxRightMost, int idxLeftMost,
								 const vector<Point2D> & leftCH, const vector<Point2D> &rightCH){
	int nl = leftCH.size();
	int nr = rightCH.size();

	int indexPLeft = idxRightMost;
	int indexPRight = idxLeftMost;

	while(!(isRightOriented(rightCH[indexPRight], indexPLeft, leftCH) &&
			 isLeftOriented(leftCH[indexPLeft], indexPRight, rightCH))){

		while(!isRightOriented(rightCH[indexPRight], indexPLeft, leftCH)){
			indexPLeft = nextCW(indexPLeft, nl);
		}
		while(!isLeftOriented(leftCH[indexPLeft], indexPRight, rightCH)){
			indexPRight = nextCCW(indexPRight, nr);
		}
	}

	return pair<int, int>(indexPLeft, indexPRight);
}

void insertPointsInCCW(vector<Point2D> & ch, int ini, int end, const vector<Point2D> & p){
	int n = p.size();
	int index = ini;
	while(index != end){
		ch.push_back(p[index]);
		index = nextCCW(index, n);
	}
	ch.push_back(p[index]);
}

void printVector(const string & name, const vector<Point2D> & v){
	cout << name << " = ";
	for(int i=0; i<v.size(); i++)
		cout << " (" << v[i].getX() << "," << v[i].getY() << ")";
	cout << endl;
}

vector<Point2D> mergeCH(const vector<Point2D> & leftCH, const vector<Point2D> & rightCH){
	vector<Point2D> ch;

	int idxLeftMost = findIndexLeftMostPoint(rightCH);
	int idxRightMost = findIndexRighMostPoint(leftCH);

	//printVector("leftCH", leftCH);
	//printVector("rightCH", rightCH);

	pair<int, int> upperTangent = findUpperTangent(idxRightMost, idxLeftMost, leftCH, rightCH);
	pair<int, int> lowerTangent = findLowerTangent(idxRightMost, idxLeftMost, leftCH, rightCH);

	//cout << "ut: " << upperTangent.getX() << ", " << upperTangent.getY() << endl;
	//cout << "lt: " << lowerTangent.getX() << ", " << lowerTangent.getY() << endl;

	insertPointsInCCW(ch, upperTangent.first, lowerTangent.first, leftCH);
	insertPointsInCCW(ch, lowerTangent.second, upperTangent.second, rightCH);

	//printVector("CH" , ch);

	return ch;
}

vector<Point2D> divideAndConquerConvexHull(vector<Point2D> p){
	int n = p.size();
	if(n <= 2){
		return p;
	}
	else if(n == 3){
		if(!isLeft(p[0], p[1], p[2]))
			swap(p[1], p[2]);
		return p;
	}

	int middle = n / 2;

	vector<Point2D> leftP(p.begin(), p.begin() + middle);
	vector<Point2D> rightP(p.begin() + middle, p.end());

	//cout << "n = " << n << ", nl = " << leftP.size() << ", nr = " << rightP.size() << endl;

	vector<Point2D> leftCH = divideAndConquerConvexHull(leftP);
	vector<Point2D> rightCH = divideAndConquerConvexHull(rightP);

	return mergeCH(leftCH, rightCH);
}

void convexHull(vector<Point2D> & p){
	sort(p.begin(), p.end(), leftBottomCompare);

	vector<Point2D> ret = divideAndConquerConvexHull(p);

	p.clear();
	p.insert(p.begin(),ret.begin(), ret.end());
}

const long long NOISE_MIN = 10e7;
const long long NOISE_MAX = 10e9;

double getNoise(){
	long long n = ((rand() + NOISE_MIN) % NOISE_MAX) + 1;
	return (1.0) / n;
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
			double noise = getNoise();
			p.push_back(Point2D(x + noise, y + noise));
		}

		convexHull(p);

		printf("Region #%d:\n", ++iter);
		printf("(%.1f,%.1f)", p[0].getX(), p[0].getY());
		double perimeter = 0.0;
		for(int i=p.size() - 1; i >= 0; i--){
			perimeter += sqrt(squareDist(p[(i+1)%p.size()], p[i]));
			printf("-(%.1f,%.1f)", p[i].getX(), p[i].getY());
		}
		printf("\n");
		printf("Perimeter length = %.2f\n", perimeter);
	}

	return 0;
}


