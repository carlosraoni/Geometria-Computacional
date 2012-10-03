#include <vector>
#include <algorithm>
#include <list>
#include <iostream>
#include "geometry2d.h"

using namespace std;

namespace geometry2d{

PolygonTriangulation::PolygonTriangulation(){
}

PolygonTriangulation::PolygonTriangulation(const vector<Point2D> & polygon) : m_p(polygon){
}

int PolygonTriangulation::getNumberOfTriangles(){
	return m_he.size() / 3;
}

vector<Point2D> PolygonTriangulation::getTriangle(int index){
	vector<Point2D> t;
	if(index >= getNumberOfTriangles())
		return t;

	t.push_back(m_p[m_he[index * 3]]);
	t.push_back(m_p[m_he[index * 3 + 1]]);
	t.push_back(m_p[m_he[index * 3 + 2]]);

	return t;
}

void PolygonTriangulation::addTriangle(int indexP0, int indexP1, int indexP2){
	m_he.push_back(indexP0);
	m_he.push_back(indexP1);
	m_he.push_back(indexP2);
}

void PolygonTriangulation::clearTriangles(){
	m_he.clear();
}

// Retorna o iterador da lista (de forma circular) anterior ao iterador passado por parâmetro
list<int>::iterator getPrevIterator(list<int> & l, list<int>::iterator & it){
	list<int>::iterator prevIterator = (it == l.begin()) ? l.end(): it;
	prevIterator--;
	return prevIterator;
}

// Retorna o iterador da lista (de forma circular) seguinte ao iterador passado por parâmetro
list<int>::iterator getNextIterator(list<int> & l, list<int>::iterator & it){
	if(it == l.end())
		return l.begin();

	list<int>::iterator nextIt = it;
	nextIt++;
	return (nextIt == l.end()) ? l.begin(): nextIt;
}

// Determina se no ponto p do polígono o triangulo formado com os vértices vizinhos é uma orelha
int checkEar(list<int> & currPoly, list<int>::iterator & pIterator, const vector<Point2D> & p){
	// Obtém ponto anterior a p no polígono atual
	list<int>::iterator prevIterator = getPrevIterator(currPoly, pIterator);
	// Obtém ponto seguinte a p no polígono atual
	list<int>::iterator nextIterator = getNextIterator(currPoly, pIterator);

	// Determina índice dos pontos do triângulo do teste de orelha
	int p0 = *prevIterator;
	int p1 = *pIterator;
	int p2 = *nextIterator;

	// Se p2 está a direita de p0p1 então a diagonal p0p2 é externa a currPoly, portanto não é uma orelha
	if(!isLeft(p[p0], p[p1], p[p2]))
		return 0;

	// Determina se algum ponto do polígono diferente de p0, p1 e p2 é interno ao triângulo formado por estes pontos
	list<int>::iterator currIterator = getNextIterator(currPoly, nextIterator);
	while(currIterator != prevIterator){
		int currP = *currIterator;
		// Se o ponto atual está dentro do triângulo p0p1p2 então o mesmo não é uma orelha
		if(inTriangle(p[p0], p[p1], p[p2], p[currP])){
			return 0;
		}
		currIterator = getNextIterator(currPoly, currIterator);
	}

	// Se não existiu nenhum ponto dentro do triầngulo p0p1p2 então o mesmo é uma orelha
	return 1;
}

PolygonTriangulation EarRemovalAlgorithm::triangulate(const vector<Point2D> & polygon){
	int n = polygon.size();
	PolygonTriangulation t(polygon);
	if(n < 3) return t;

	list<int> currPoly; // Lista que armazena os índices do polígono atual do algoritmo de remoção de orelhas
	vector<int> isEar(n, 0); // Vetor que armazena indicador de formação de orelha nos pontos do polígono

	// Adiciona todos os pontos do polígono na lista de pontos do polígono atual do algoritmo
	for(int i=0; i<n; i++){
		currPoly.push_back(i);
	}

	// Determina para cada ponto se no mesmo se forma uma orelha no triângulo formado com seus vizinhos
	for(list<int>::iterator it = currPoly.begin(); it != currPoly.end(); it++){
		int p = *it;
		isEar[p] = checkEar(currPoly, it, polygon);
	}

	// Equanto não tivermos apenas um triângulo, então removemos ums orelha
	while(currPoly.size() > 3){
		// Procura uma orelha no polígono atual
		for(list<int>::iterator it = currPoly.begin(); it != currPoly.end(); it++){
			int p = *it;
			if(isEar[p]){
				list<int>::iterator prevIt = getPrevIterator(currPoly, it);
				list<int>::iterator nextIt = getNextIterator(currPoly, it);
				// Determina índice dos pontos da orelha
				int p0 = *prevIt;
				int p1 = *it;
				int p2 = *nextIt;
				// Adicioa orelha a triangulação do polígono
				t.addTriangle(p0, p1, p2);
				// Remove o ponto central do triângulo do polígono
				currPoly.erase(it);
				// Atualiza o indicador de orelha nos pontos vizinhos de p1 no novo polígono formado após a remoção de p1
				isEar[p0] = checkEar(currPoly, prevIt, polygon);
				isEar[p2] = checkEar(currPoly, nextIt, polygon);
				break;
			}
		}
	}
	// Adiciona o triângulo final na triangulação
	list<int>::iterator it = currPoly.begin();
	int p0 = *it; it++;
	int p1 = *it; it++;
	int p2 = *it;

	t.addTriangle(p0, p1, p2);

	return t;
}


}
