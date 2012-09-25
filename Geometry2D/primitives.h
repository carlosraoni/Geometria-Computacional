#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <cmath>
#include <vector>
#include "point2d.h"

using namespace std;

namespace geometry2d{

const double EPS = 1e-9;
const double PI = 2*acos(0.0);

typedef enum {LEFT, RIGHT, ON} Orientation;

const Point2D operator*(double m, const Point2D p);

double operator*(const Point2D & p1, const Point2D & p2);

const Point2D operator+(const Point2D & p1, const Point2D & p2);

const Point2D operator-(const Point2D & p1, const Point2D & p2);

bool operator<(const Point2D & p1, const Point2D & p2);

bool operator==(const Point2D & p1, const Point2D & p2);

const Point2D vector2D(const Point2D & A, const Point2D & B);

double distance(const Point2D & p1, const Point2D & p2);

double angle(const Point2D & p1, const Point2D & p2);

double orientedAngle(const Point2D & p0, const Point2D & p1, const Point2D & p2);

double pseudoAngle(const Point2D & p1, const Point2D & p2);

double doubleSignedTriangleArea(const Point2D & p0, const Point2D & p1, const Point2D & p2);

double signedTriangleArea(const Point2D & p0, const Point2D & p1, const Point2D & p2);

Orientation orientation(const Point2D & p0, const Point2D & p1, const Point2D & p2);

bool isLeft(const Point2D & p0, const Point2D & p1, const Point2D & p2);

double squareDistance(const Point2D & p1, const Point2D & p2);

bool collinear(const Point2D & p1, const Point2D & p2, const Point2D & p3);

void polarAngleSort(vector<Point2D> & p);

}

#endif

