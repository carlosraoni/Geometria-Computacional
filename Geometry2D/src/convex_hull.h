#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include <vector>
#include "point2d.h"

using namespace std;

namespace geometry2d{

// Classe que encapsula a interface dos algoritmos de convex hull
class ConvexHullAlgorithm{

public:

	// Método a ser implementado pelos algoritmos de convex hull.
	// O método recebe o vetor do conjunto de pontos para determinação do convex hull,
	// o algoritmo deve alterar o vetor deixando apenas os pontos pertencentes ao convex hull.
	virtual void convexHull(vector<Point2D> & p) = 0;

};

// Classe que encapsula a implementação do algoritmo de Graham-Scan
class GrahamScanAlgorithm : public ConvexHullAlgorithm{

public:
	void convexHull(vector<Point2D> & p);

};

// Classe que encapsula a implementação do algoritmo de dividir para conquistar para determinação do convex hulll.
class DivideAndConquerConvexHullAlgorithm : public ConvexHullAlgorithm{

public:
	void convexHull(vector<Point2D> & p);

};

}

#endif // CONVEX_HULL_H

