#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

const double EPS = 1e-9;
const double PI = 2*acos(0.0);

typedef enum {LEFT, RIGHT, ON} Orientation;

class Point2D
{

public:
	Point2D(double m_x, double m_y);
	~Point2D();

	double getX() const { return m_x; }
	double getY() const { return m_y; }

	double norm() const;

private:

	double m_x;
	double m_y;

};

const Point2D ei(1,0);

Point2D::Point2D(double x, double y) : m_x(x), m_y(y)
{

}

Point2D::~Point2D()
{

}


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

const Point2D vector2D(const Point2D & A, const Point2D & B){
	return (B - A);
}

double distance(const Point2D & p1, const Point2D & p2){
	return (p2-p1).norm();
}

double angle(const Point2D & p1, const Point2D & p2){
	return acos((p1 * p2) / (p1.norm() * p2.norm()));
}

double doubleSignedTriangleArea(const Point2D & p0, const Point2D & p1, const Point2D & p2){
	return ( (p1.getX() - p0.getX()) * (p2.getY() - p0.getY()) -
			  (p2.getX() - p0.getX()) * (p1.getY() - p0.getY()) );
}

double orientedAngle(const Point2D & p0, const Point2D & p1, const Point2D & p2){
	double unsignedAngle = angle(vector2D(p0, p1), vector2D(p0, p2));
	double area = doubleSignedTriangleArea(p0, p1, p2);

	return (area < 0) ? -unsignedAngle: unsignedAngle;
}

double pseudoAngle(const Point2D & p1, const Point2D & p2){
	return (1.0 - (p1 * p2)/(p1.norm() * p2.norm()));
}

double signedTriangleArea(const Point2D & p0, const Point2D & p1, const Point2D & p2){
	return doubleSignedTriangleArea(p0, p1, p2) / 2.0;
}

Orientation orientation(const Point2D & p0, const Point2D & p1, const Point2D & p2){
	double area = doubleSignedTriangleArea(p0, p1, p2);
	if(fabs(area) < EPS)
		return ON;
	return (area > 0) ? LEFT: RIGHT;
}

bool isLeft(const Point2D & p0, const Point2D & p1, const Point2D & p2){
	return doubleSignedTriangleArea(p0, p1, p2) > 0.0;
}


double Point2D::norm() const{
	return sqrt(m_x * m_x + m_y * m_y);
}

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

int CrossingNumberAlgorithm::pointInPolygon(const Point2D & p, const vector<Point2D> & polygon){
	int n = polygon.size();
	int crossing = 0;

	for(int i=0; i<n; i++){
		int next = (i + 1) % n;

		// Verfica se a aresta eh uma linha horizontal
		if(fabs(polygon[i].getY() - polygon[next].getY()) < EPS){
			double maxX = max(polygon[i].getX(),  polygon[next].getX());
			double minX = min(polygon[i].getX(),  polygon[next].getX());

			// Verifica se o ponto p pertence a aresta, i.e. p.y == poly[i].y && minX <= p.x <= maxX
			if(fabs(polygon[i].getY() - p.getY()) < EPS && (p.getX() >= minX && p.getX() <= maxX) ){
				return 0; // Ponto esta na fronteira
			}
			continue;
		}
		// Determinar intersecção
		// s = p + s(1,0) - linha infinita horizontal partindo do ponto p
		// t = poly[i] + t (poly[next] - poly[i]) - segmento da aresta do poligono
 		double deltaX = polygon[next].getX() - polygon[i].getX();
		double deltaY = polygon[next].getY() - polygon[i].getY();
		// t = (p.y - poly[i].y) / deltaY
		double t = (p.getY() - polygon[i].getY()) / deltaY;
		// checando se 0 <= t <= 1 para determinar se os segmentos se cruzam
		if(t < 0.0 || t > 1.0)
			continue;
		// s = poly[i].x - p.x + t * deltaX
		double s = polygon[i].getX() - p.getX() + t * deltaX;
		// Verifica se p está na fronteira, i.e. s == 0
		if(fabs(s) < EPS)
			return 0;

		// verifica se interseção ocorre e incrementa crossing se a mesma não ocorreu no ponto de mínimo
		double minY = min(polygon[i].getY(),  polygon[next].getY());
		if(s > 0.0 && p.getY() > minY)
			crossing++;
	}

	// se N é ímpar, retorne que p0 é interior a P, senão retorne que p0 é exterior a P.
    return (crossing % 2) ? -1: 1;
}

int WindingNumberAlgorithm::pointInPolygon(const Point2D & p, const vector<Point2D> & polygon){
	int n = polygon.size();
	double wn = 0.0;

	for(int i=0; i<n; i++){
		int next = (i + 1) % n;
		wn += orientedAngle(p, polygon[i], polygon[next]);
	}
	wn /= (2.0 * PI);

	if(fabs(wn) < EPS)
		return 1;

    return -1;
}

int main( int argc, char** argv )
{
	int n;
	double x, y;
	vector<Point2D> poly;
	//PointInPolygonAlgorithm * alg = new CrossingNumberAlgorithm();
	PointInPolygonAlgorithm * alg = new WindingNumberAlgorithm();

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
