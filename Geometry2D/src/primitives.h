#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <cmath>
#include <vector>
#include "point2d.h"

using namespace std;

// Cabeçalho das funções geométricas primitivas utilizadas nas implementações dos algoritmos
// da bibioteca geometry2d.
namespace geometry2d{

// Definição de constante epsilon utilizada na comparação de ponto flutuante
const double EPS = 1e-9;
// Definição da constante PI
const double PI = 2*acos(0.0);

// Enum de orientação de um ponto em relação ao uma reta
typedef enum {LEFT, RIGHT, ON} Orientation;

// Multipliação de escalar por um ponto
const Point2D operator*(double m, const Point2D p);

// Produto escalar entre dois pontos
double operator*(const Point2D & p1, const Point2D & p2);

// Soma de dois pontos
const Point2D operator+(const Point2D & p1, const Point2D & p2);

// Subtração de dois pontos
const Point2D operator-(const Point2D & p1, const Point2D & p2);

// Operador menor (compara coordenada X depois Y)
bool operator<(const Point2D & p1, const Point2D & p2);

// Operador de igualdade de pontos
bool operator==(const Point2D & p1, const Point2D & p2);

// Função que cria um vetor AB a partir dos pontos A e B. AB = B - A.
const Point2D vector2D(const Point2D & A, const Point2D & B);

// Distância entre dois pontos
double distance(const Point2D & p1, const Point2D & p2);

// Ângulo entre dois pontos
double angle(const Point2D & p1, const Point2D & p2);

// Ângulo orientado entre dois pontos
double orientedAngle(const Point2D & p0, const Point2D & p1, const Point2D & p2);

// Pseudo-Ângulo entre dois pontos
double pseudoAngle(const Point2D & p1, const Point2D & p2);

// Duas vezes a área (com sinal) do paralelogramo definido pelos vetores p0p1 e p0p2.
// Equivalente a coordenada z do vetor resultante do produto vetorial entre os vetores p0p1 e p0p2.
double doubleSignedTriangleArea(const Point2D & p0, const Point2D & p1, const Point2D & p2);

// Área (com sinal) do paralelogramo definido pelos vetores p0p1 e p0p2.
double signedTriangleArea(const Point2D & p0, const Point2D & p1, const Point2D & p2);

// Determina orientação do ponto p2 com relação a reta definida pelos pontos p0p1
Orientation orientation(const Point2D & p0, const Point2D & p1, const Point2D & p2);

// Determina se o ponto p2 está a esquerda da reta definida pelos pontos p0p1
bool isLeft(const Point2D & p0, const Point2D & p1, const Point2D & p2);

// Determina se o ponto p está dentro do triângulo definido pelos pontos p0p1p2
bool inTriangle(const Point2D & p0, const Point2D & p1, const Point2D & p2, const Point2D & p);

// Distância entre os pontos p1 e p2 elevada ao quadrado = (p1.x - p2.x)^2 +  (p1.y - p2.y)^2
double squareDistance(const Point2D & p1, const Point2D & p2);

// Determina se os pontos p1, p2 e p3 são colineares
bool collinear(const Point2D & p1, const Point2D & p2, const Point2D & p3);

// Realiza a ordenação polar os pontos p de acordo com o ângulo formado com o ponto mais abaixo e a esquerda
void polarAngleSort(vector<Point2D> & p);

}

#endif

