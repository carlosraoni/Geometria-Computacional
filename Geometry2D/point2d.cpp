#include <cmath>
#include "primitives.h"
#include "point2d.h"

namespace geometry2d
{
	const Point2D ei(1,0);
		
	Point2D::Point2D(double x, double y) : m_x(x), m_y(y)
	{
		
	}

	Point2D::~Point2D()
	{
		
	}
	
	double Point2D::norm() const{
		return sqrt(m_x * m_x + m_y * m_y);
	}
	
	double Point2D::angle() const{
		return geometry2d::angle(ei, *this);
	}
	
	double Point2D::orientedAngle() const{
		return (m_x < 0) ? -angle(): angle();
	}
	
}

