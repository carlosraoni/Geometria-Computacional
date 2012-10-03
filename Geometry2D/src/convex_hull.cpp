#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
#include <string>
#include "geometry2d.h"

using namespace std;

namespace geometry2d{

/**
	Implementação do algoritmo Graham-Scan para determinação do fecho convexo.
**/

// Determina o fecho convexo do conjunto de pontos p utilizando Graham-Scan.
void GrahamScanAlgorithm::convexHull(vector<Point2D> & p){
	// Realiza ordenação polar dos pontos utilizando como ponto de referência o ponto mais abaixo e a esquerda.
	polarAngleSort(p);

	int n = p.size();
	// Inicia o fecho com os 2 primeiros pontos do vetor ordenado polarmente
	int convHullSize = 2;
	for(int i=2; i<n; i++){
		// Enquanto o triângulo formado pelo penúltimo ponto da pilha, último ponto da pilha e o ponto atual
		// não estiver orientado de forma anti-horária então realizar um pop na pilha.
		while(convHullSize >= 2 && !isLeft(p[convHullSize - 2], p[convHullSize - 1], p[i])){
			convHullSize--; // Pop na pilha de pontos, equivalente a remover o último ponto da mesma
		}
		p[convHullSize++] = p[i]; // Push do ponto atual na pilha.
	}
	p.resize(convHullSize); // Remove os pontos residuais que não fazem parte do fecho convexo

}

/**
	Implementação do algoritmo de Dividir para Conquistar para determinação do fecho convexo.
**/

// Comparação utilizada para ordenar os pontos primeiro pela menor coordenada X depois pela menor coordenada Y
bool leftBottomCompare(const Point2D & p1, const Point2D & p2){
	if(p1.getX() < p2.getX())
		return true;
	if(p1.getX() > p2.getX())
		return false;
	return p1.getY() < p2.getY();
}

// Determina o índice do próximo ponto no sentido horário (ClockWise).
// Considerando que os pontos estão ordenados em sentido anti-horário (Counter-ClockWise)
int nextCW(int index, int n){
	return (index == 0) ? n-1: index - 1;
}

// Determina o índice do próximo ponto no sentido anti-horário (Counter-ClockWise).
// Considerando que os pontos estão ordenados em sentido anti-horário (Counter-ClockWise)
int nextCCW(int index, int n){
	return (index + 1) % n;
}

// Determina o índice do ponto que está mais a direita entre os pontos do vetor p.
int findIndexRighMostPoint(const vector<Point2D> & p){
	int n = p.size(), index = 0;
	for(int i=1; i<n; i++){
		if(p[i].getX() > p[index].getX())
			index = i;
	}
	return index;
}

// Determina o índice do ponto que está mais a esquerda entre os pontos do vetor p.
int findIndexLeftMostPoint(const vector<Point2D> & p){
	int n = p.size(), index = 0;
	for(int i=1; i<n; i++){
		if(p[i].getX() < p[index].getX())
			index = i;
	}
	return index;
}

// Teste do algoritmo de determinação das tangentes (superior e inferior) que determina se os pontos do fecho convexo p
// estão a esquerda da reta formada pelo ponto p0 (pertencente ao fecho oposto no merge) e o ponto de índice p1 de p.
bool isLeftOriented(const Point2D & p0, int indexP1, const vector<Point2D> & p){
	int n = p.size();
	return isLeft(p0, p[indexP1], p[nextCCW(indexP1, n)]) && isLeft(p0, p[indexP1], p[nextCW(indexP1, n)]);
}

// Teste do algoritmo de determinação das tangentes (superior e inferior) que determina se os pontos do fecho convexo p
// estão a direita da reta formada pelo ponto p0 (pertencente ao fecho oposto no merge) e o ponto de índice p1 de p.
bool isRightOriented(const Point2D & p0, int indexP1, const vector<Point2D> & p){
	int n = p.size();
	return !isLeft(p0, p[indexP1], p[nextCCW(indexP1, n)]) && !isLeft(p0, p[indexP1], p[nextCW(indexP1, n)]);
}

// Determina a tangente superior dos fechos da esquerda (leftCH) e da direita (rightCH).
// Retorna o par de índices da tangente (índice do ponto do fecho da esquerda, índice do ponto do fecho da direita)
pair<int, int> findUpperTangent(int idxRightMost, int idxLeftMost,
								 const vector<Point2D> & leftCH, const vector<Point2D> &rightCH){
	int nl = leftCH.size();
	int nr = rightCH.size();

	// Inicializa os pontos da busca pela tangente superior dos fechos
	// Inicia o indice do fecho da esquerda com o indice de seu ponto mais a direita
	int indexPLeft = idxRightMost;
	// Inicia o indice do fecho da direita com o indice de seu ponto mais a esquerda
	int indexPRight = idxLeftMost;

	// Enquanto leftCH[indexPLeft] e rightCH[indexPRight] não formarem uma tangente superior dos 2 fechos.
	while(!(isLeftOriented(rightCH[indexPRight], indexPLeft, leftCH) &&
			 isRightOriented(leftCH[indexPLeft], indexPRight, rightCH))){

		// Enquanto leftCH[indexPLeft] e rightCH[indexPRight] não formarem uma tangente superior ao fecho da esquerda.
		while(!isLeftOriented(rightCH[indexPRight], indexPLeft, leftCH)){
			indexPLeft = nextCCW(indexPLeft, nl); // Avança o ponto do fecho da esquerda para o próximo ponto no sentido CCW.
		}
		// Enquanto leftCH[indexPLeft] e rightCH[indexPRight] não formarem uma tangente superior ao fecho da direita.
		while(!isRightOriented(leftCH[indexPLeft], indexPRight, rightCH)){
			indexPRight = nextCW(indexPRight, nr); // Avança o ponto do fecho da direita para o próximo ponto no sentido CW.
		}
	}

	return pair<int, int>(indexPLeft, indexPRight);
}

// Determina a tangente inferior dos fechos da esquerda (leftCH) e da direita (rightCH).
// Retorna o par de índices da tangente (índice do ponto do fecho da esquerda, índice do ponto do fecho da direita)
pair<int, int> findLowerTangent(int idxRightMost, int idxLeftMost,
								 const vector<Point2D> & leftCH, const vector<Point2D> &rightCH){
	int nl = leftCH.size();
	int nr = rightCH.size();

	// Inicializa os pontos da busca pela tangente inferior dos fechos
	// Inicia o indice do fecho da esquerda com o indice de seu ponto mais a direita
	int indexPLeft = idxRightMost;
	// Inicia o indice do fecho da direita com o indice de seu ponto mais a esquerda
	int indexPRight = idxLeftMost;

	// Enquanto leftCH[indexPLeft] e rightCH[indexPRight] não formarem uma tangente inferior dos 2 fechos.
	while(!(isRightOriented(rightCH[indexPRight], indexPLeft, leftCH) &&
			 isLeftOriented(leftCH[indexPLeft], indexPRight, rightCH))){

		// Enquanto leftCH[indexPLeft] e rightCH[indexPRight] não formarem uma tangente inferior ao fecho da esquerda.
		while(!isRightOriented(rightCH[indexPRight], indexPLeft, leftCH)){
			indexPLeft = nextCW(indexPLeft, nl); // Avança o ponto do fecho da esquerda para o próximo ponto no sentido CW.
		}
		// Enquanto leftCH[indexPLeft] e rightCH[indexPRight] não formarem uma tangente inferior ao fecho da direita.
		while(!isLeftOriented(leftCH[indexPLeft], indexPRight, rightCH)){
			indexPRight = nextCCW(indexPRight, nr); // Avança o ponto do fecho da direita para o próximo ponto no sentido CCW.
		}
	}

	return pair<int, int>(indexPLeft, indexPRight);
}

// Insere os pontos entre ini e end de p no sentido CCW ao fecho ch.
void insertPointsInCCW(vector<Point2D> & ch, int ini, int end, const vector<Point2D> & p){
	int n = p.size();
	int index = ini;
	while(index != end){
		ch.push_back(p[index]);
		index = nextCCW(index, n);
	}
	ch.push_back(p[index]);
}

// Efetua o merge dos fechos da esquerda leftCH e da direita rightCH
vector<Point2D> mergeCH(const vector<Point2D> & leftCH, const vector<Point2D> & rightCH){
	vector<Point2D> ch; // Fecho resultante do merge

	int idxLeftMost = findIndexLeftMostPoint(rightCH);
	int idxRightMost = findIndexRighMostPoint(leftCH);

	// Determina as tangentes superior e inferior dos fechos
	pair<int, int> upperTangent = findUpperTangent(idxRightMost, idxLeftMost, leftCH, rightCH);
	pair<int, int> lowerTangent = findLowerTangent(idxRightMost, idxLeftMost, leftCH, rightCH);

	// Insere os pontos de leftCH entre seu ponto da tangente superior e seu ponto da tangente inferior em ch em sentido CCW
	insertPointsInCCW(ch, upperTangent.first, lowerTangent.first, leftCH);
	// Insere os pontos de rightCH entre seu ponto da tangente inferior e seu ponto da tangente superior em ch em sentido CCW
	insertPointsInCCW(ch, lowerTangent.second, upperTangent.second, rightCH);

	return ch;
}

// Procedimento recursivo do algoritmo de dividir para conquistar de fecho convexo
vector<Point2D> divideAndConquerConvexHull(vector<Point2D> p){
	int n = p.size();
	// Casos base da recursão
	if(n <= 2){ // Se p possui apenas 2 pontos retorna o próprio p
		return p;
	}
	else if(n == 3){
		// Se p possui apenas 3 pontos retorna o triângulo formado pelos pontos orientado de forma CCW
		if(!isLeft(p[0], p[1], p[2]))
			swap(p[1], p[2]);
		return p;
	}

	int middle = n / 2;

	// Divide os pontos ordenados por X ao meio
	vector<Point2D> leftP(p.begin(), p.begin() + middle); // Pontos a esquerda
	vector<Point2D> rightP(p.begin() + middle, p.end());  // Pontos a direita

	// Determina o fecho convexo dos pontos da esquerda e da direita
	vector<Point2D> leftCH = divideAndConquerConvexHull(leftP);
	vector<Point2D> rightCH = divideAndConquerConvexHull(rightP);

	// Realiza o merge dos fechos obtidos
	return mergeCH(leftCH, rightCH);
}

// Determina o fecho convexo do conjunto de pontos p utilizando o algoritmo de Dividir para conquistar.
void DivideAndConquerConvexHullAlgorithm::convexHull(vector<Point2D> & p){
	// Ordena os pontos pela coordenada X
	sort(p.begin(), p.end(), leftBottomCompare);

	// Chama procedimento recursivo para determina do fecho convexo de p
	vector<Point2D> ret = divideAndConquerConvexHull(p);

	// Altera p para conter apenas os pontos do fecho convexo
	p.clear();
	p.insert(p.begin(),ret.begin(), ret.end());
}

}
