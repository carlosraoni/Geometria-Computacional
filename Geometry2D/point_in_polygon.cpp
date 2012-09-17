#include <vector>
#include <cmath>
#include "geometry2d.h"

using namespace std;

namespace geometry2d{

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
		// Determinar intersec��o
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
		// Verifica se p est� na fronteira, i.e. s == 0
		if(fabs(s) < EPS)
			return 0;

		// verifica se interse��o ocorre e incrementa crossing se a mesma n�o ocorreu no ponto de m�nimo
		double minY = min(polygon[i].getY(),  polygon[next].getY());
		if(s > 0.0 && p.getY() > minY)
			crossing++;
	}

	// se N � �mpar, retorne que p0 � interior a P, sen�o retorne que p0 � exterior a P.
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

}























