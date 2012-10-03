#ifndef POINT2D_H
#define POINT2D_H

#include <string>

using namespace std;

namespace geometry2d
{

// Classe que encapsula a representação de um ponto 2D.
class Point2D
{

public:
	Point2D();
	Point2D(double m_x, double m_y);
	~Point2D();

	double getX() const { return m_x; } // Retorna a coordenada X do ponto
	double getY() const { return m_y; } // Retorna a coordenada Y do ponto

	double norm() const; // Retorna a norma do vetor
	double angle() const; // Retorna o ângulo do vetor com o eixo X
	double orientedAngle() const; // // Retorna o ângulo orientado do vetor com o eixo X

	string toString() const;

private:

	double m_x; // Propriedade membro que armazena a coordenada X do ponto
	double m_y; // Propriedade membro que armazena a coordenada X do ponto

};

}

#endif // POINT2D_H

