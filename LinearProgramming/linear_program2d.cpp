#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include "linear_program2d.h"

using namespace std;

namespace lp2D{

LinearProgram2D::LinearProgram2D(double c0, double c1, LinearProgramType type){
	this->c[0] = c0;
	this->c[1] = c1;
	this->type = type;
}

LinearProgram2D::~LinearProgram2D(){
	int m = getNumberOfConstraints();
	for(int i=0; i<m; i++)
		delete getConstraint(i);
}

void LinearProgram2D::addConstraint(double a0, double a1, double b, ConstraintType type){
	this->constr.push_back(new Constraint2D(a0, a1, b, type));
}

int LinearProgram2D::getNumberOfConstraints() const{
	return this->constr.size();
}

Constraint2D * LinearProgram2D::getConstraint(int index) const{
	return this->constr[index];
}

double LinearProgram2D::getC(int index) const{
	return this->c[index];
}

double LinearProgram2D::getCAsMaximization(int index) const{
	return this->c[index] * ((type == MAX) ? 1.0: -1.0);
}

double LinearProgram2D::getZValue(double x, double y) const{
	return c[0] * x + c[1] * y;
}

double LinearProgram2D::getZValueAsMaximization(double x, double y) const{
	return getCAsMaximization(0) * x + getCAsMaximization(1) * y;
}

string LinearProgram2D::toString() const{
	ostringstream out;
	int m = getNumberOfConstraints();

	out << ((type == MAX) ? "Max.": "Min.") << endl;
	out << "\t";
	out << c[0] << "*x0" << ((c[1] > 0) ? " + " : " - ") << fabs(c[1]) << "*x1 " << endl;
	out << endl << "s.t." << endl;
	for(int i=0; i<m; i++){
		out << "\t" << getConstraint(i)->toString() << endl;
	}

	return out.str();
}

}
