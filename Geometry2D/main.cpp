#include <iostream>
#include "geometry2d.h"

using namespace std;
using namespace geometry2d;

int main( int argc, char** argv )
{
	double x, y;

	cin >> x >> y;
	Point2D p1(x, y);

	cin >> x >> y;
	Point2D p2(x, y);

	cout << "p1 * p2 = " << p1 * p2 << endl;

	Point2D p3 = 5 * p1;
	cout << "5 * p1  = " << "(" << p3.getX() << "," << p3.getY()  << ")" << endl;

	p3 = p1 + p2;
	cout << "p1 + p2 = " << "(" << p3.getX() << "," << p3.getY()  << ")" << endl;

	return 0;
}
