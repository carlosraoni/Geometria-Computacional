#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <vector>
#include "point2d.h"

using namespace std;

namespace geometry2d{

// Classe que encapsula a estrutura de dados para representação de uma triangulação de um polígono
class PolygonTriangulation{

public:

	PolygonTriangulation();
	// Construtor que receve os pontos do polígono a ser triangulado
	PolygonTriangulation(const vector<Point2D> & polygon);

	int getNumberOfTriangles(); // Retorna o número de triangulos da triangulação
	vector<Point2D> getTriangle(int index); // Obtém o triângulo de índice index
	void addTriangle(int indexP0, int indexP1, int indexP2); // Adiciona o triângulo formado pelos pontos de índice p0, p1 e p2.
	void clearTriangles(); // Remove os triângulos da estrutura

private:

	vector<Point2D> m_p; // Pontos do polígono a ser triangulado
	vector<int> m_he; // Estrutura half-edge que guarda o índice para cada edge do ponto inicial da mesma

};

// Classe que encapsula a interface dos algoritmos de triangulação de polígonos
class PolygonTriangulationAlgorithm{

public:

	// Método a ser implementado pelos algoritmos de triangulação de polígonos.
	// O método recebe o polígono a ser triangulado e retorna a estrutura de dados com a triangulação do mesmo.
	virtual PolygonTriangulation triangulate(const vector<Point2D> & polygon) = 0;

};

// Classe que encapsula a implementação de remoção de orelhas para triangulação de polígonos
class EarRemovalAlgorithm : public PolygonTriangulationAlgorithm{

public:
	PolygonTriangulation triangulate(const vector<Point2D> & polygon);

};


}

#endif // TRIANGULATION_H
