#include <iostream>
#include <string>
#include <fstream>
#include "lp2d_reader.h"
#include "constraint2d.h"

using namespace std;

namespace lp2D{

LinearProgram2D * readLinearProgram2D(const char * file){
	LinearProgram2D * lp;
	string type;
	double c[DIM];
	double a[DIM], b;
	ifstream in(file);

	in >> type >> c[0] >> c[1];
	lp = new LinearProgram2D(c[0], c[1], (type == "MAX") ? MAX: MIN);

	while(in >> a[0] >> a[1] >> type >> b){
		lp->addConstraint(a[0], a[1], b, constrTypeFromString(type));
	}

	return lp;
}

}
