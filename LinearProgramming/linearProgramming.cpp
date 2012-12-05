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
	if(argc < 2){
		cout << "Error: Please specify the linear program descriptor file" << endl;
		return 1;
	}

	LinearProgram2D * lp = readLinearProgram2D(argv[1]);
	double x, y, z;

	solveLinearProgram2D(lp, x, y, z);

	delete lp;

	return 0;
}

