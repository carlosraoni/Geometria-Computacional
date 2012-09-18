#ifndef POINT2D_H
#define POINT2D_H

#include <string>

using namespace std;

namespace geometry2d
{

class Point2D
{

public:
	Point2D();
	Point2D(double m_x, double m_y);
	~Point2D();

	double getX() const { return m_x; }
	double getY() const { return m_y; }

	double norm() const;
	double angle() const;
	double orientedAngle() const;

	string toString() const;

private:

	double m_x;
	double m_y;

};

}

#endif // POINT2D_H

