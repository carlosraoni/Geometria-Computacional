#include <cmath>
#include "primitives.h"

namespace geometry2d{

const Point2D operator*(double c, const Point2D p){
	return Point2D(c * p.getX(), c * p.getY());
}

double operator*(const Point2D & p1, const Point2D & p2){
	return p1.getX() * p2.getX() + p1.getY() * p2.getY();
}

const Point2D operator+(const Point2D & p1, const Point2D & p2){
	return Point2D(p1.getX() + p2.getX(), p1.getY() + p2.getY());
}

const Point2D operator-(const Point2D & p1, const Point2D & p2){
	return Point2D(p1.getX() - p2.getX(), p1.getY() - p2.getY());
}

bool operator<(const Point2D & p1, const Point2D & p2){
	if(p1.getY() < p2.getY())
		return true;
	if(p2.getY() < p1.getY())
		return false;
	return p1.getX() < p2.getX();
}

bool operator==(const Point2D & p1, const Point2D & p2){
	return fabs(p1.getX() - p2.getX()) < EPS && fabs(p1.getY() - p2.getY()) < EPS;
}


const Point2D vector2D(const Point2D & A, const Point2D & B){
	return (B - A);
}

double distance(const Point2D & p1, const Point2D & p2){
	return (p2-p1).norm();
}

double angle(const Point2D & p1, const Point2D & p2){
	return acos((p1 * p2) / (p1.norm() * p2.norm()));
}

double orientedAngle(const Point2D & p0, const Point2D & p1, const Point2D & p2){
	double unsignedAngle = angle(vector2D(p0, p1), vector2D(p0, p2));
	double area = doubleSignedTriangleArea(p0, p1, p2);

	return (area < 0) ? -unsignedAngle: unsignedAngle;
}

double pseudoAngle(const Point2D & p1, const Point2D & p2){
	return (1.0 - (p1 * p2)/(p1.norm() * p2.norm()));
}

double doubleSignedTriangleArea(const Point2D & p0, const Point2D & p1, const Point2D & p2){
	return ( (p1.getX() - p0.getX()) * (p2.getY() - p0.getY()) -
			  (p2.getX() - p0.getX()) * (p1.getY() - p0.getY()) );
}

double signedTriangleArea(const Point2D & p0, const Point2D & p1, const Point2D & p2){
	return doubleSignedTriangleArea(p0, p1, p2) / 2.0;
}

Orientation orientation(const Point2D & p0, const Point2D & p1, const Point2D & p2){
	double area = doubleSignedTriangleArea(p0, p1, p2);
	if(fabs(area) < EPS)
		return ON;
	return (area > 0) ? LEFT: RIGHT;
}

bool isLeft(const Point2D & p0, const Point2D & p1, const Point2D & p2){
	return doubleSignedTriangleArea(p0, p1, p2) > 0.0;
}

double squareDistance(const Point2D & p1, const Point2D & p2){
	double dx = p2.getX() - p1.getX();
	double dy = p2.getY() - p1.getY();
	return dx * dx + dy * dy;
}

bool collinear(const Point2D & p1, const Point2D & p2, const Point2D & p3){
	return fabs(doubleSignedTriangleArea(p1, p2, p3)) < EPS;
}


}

