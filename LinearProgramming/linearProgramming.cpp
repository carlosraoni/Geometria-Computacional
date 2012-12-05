#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "lp2d.h"

using namespace std;
using namespace lp2D;

int main(int argc, char ** argv){
	LinearProgram2D * lp;
	string type;
	double c[DIM];
	double a[DIM], b;
	double x, y, z;

	cin >> type >> c[0] >> c[1];
	lp = new LinearProgram2D(c[0], c[1], (type == "MAX") ? MAX: MIN);

	while(cin >> a[0] >> a[1] >> type >> b){
		lp->addConstraint(a[0], a[1], b, constrTypeFromString(type));
	}

	solveLinearProgram2D(lp, x, y, z);

	//cout << lp->toString() << endl;

	delete lp;
	return 0;
}

