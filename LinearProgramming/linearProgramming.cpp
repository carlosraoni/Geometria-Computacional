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

LinearProgram2D * lp;

int main(int argc, char ** argv){

	string inputFile;
	if(argc < 2){
		cout << "Please specify the linear program descriptor file: " << endl;
		cin >> inputFile;
	}
	else{
		inputFile = string(argv[1]);
	}

	lp = readLinearProgram2D(inputFile.c_str());

	if(lp == NULL){
		cout << "Error: impossible to read file '" << inputFile << "'"<< endl;
		return 1;
	}

	double x, y, z;

	solveLinearProgram2D(lp, x, y, z);

	delete lp;

	return 0;
}

