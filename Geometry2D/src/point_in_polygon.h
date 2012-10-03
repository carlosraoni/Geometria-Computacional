#ifndef POINT_IN_POLYGON_H
#define POINT_IN_POLYGON_H

#include <vector>
#include "point2d.h"

using namespace std;

namespace geometry2d{

// Classe que encapsula a interface dos algoritmos de ponto no polígono
class PointInPolygonAlgorithm{

public:

	// Método a ser implementado pelos algoritmos de ponto no polígono.
	// O método recebe o ponto e o polígono do teste.
	// Retorna:
	// -1 - Ponto dentro do polígono
	//  0 - Ponto na fronteira do polígono
	//  1 - Ponto fora do polígono
    virtual int pointInPolygon(const Point2D & p, const vector<Point2D> & polygon) = 0;

};

// Classe que encapsula a implementação do algoritmo de ponto no polígono utilizando
// o número de vezes que a linha imaginária que parte do ponto cruza a fronteira do polígono
class CrossingNumberAlgorithm : public PointInPolygonAlgorithm{

public:
    int pointInPolygon(const Point2D & p, const vector<Point2D> & polygon);

};

// Classe que encapsula a implementação do algoritmo de ponto no polígono utilizando
// o índice de rotação do ponto em relação ao polígono
class WindingNumberAlgorithm : public PointInPolygonAlgorithm{

public:
    int pointInPolygon(const Point2D & p, const vector<Point2D> & polygon);

};

}
#endif // POINT_IN_POLYGON_H

