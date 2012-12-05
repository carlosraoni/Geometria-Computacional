#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include "constraint2d.h"

using namespace std;

namespace lp2D{

string constrTypeToString(ConstraintType t){
	return string(ConstraintTypeToStr[t]);
}

ConstraintType constrTypeFromString(const string & str){
	for(int i=0; i<N_CONSTR_TYPE; i++){
		if(str == constrTypeToString((ConstraintType) i))
			return (ConstraintType) i;
	}
	return INVALID;
}

Constraint2D::Constraint2D(double a0, double a1, double b, ConstraintType type){
	this->type = type;
	this->a[0] = a0;
	this->a[1] = a1;
	this->b = b;
}

double Constraint2D::getA(int d) const{
	return a[d];
}

double Constraint2D::getB() const{
	return b;
}

ConstraintType Constraint2D::getType() const{
	return type;
}

bool Constraint2D::isFeasible(double x, double y) const{
	double f = x * getA(0) + y * getA(1);

	switch(this->type){
		case LT:  return f < getB();
		case LEQ: return f <= getB();
		case EQ:  return fabs(f - getB()) < EPS;
		case GEQ: return f >= getB();
		case GT:  return f > getB();
	}
		return false;
}

string Constraint2D::toString() const{
	ostringstream out;

	out << a[0] << "*x0" << ((a[1] > 0) ? " + " : " - ") << fabs(a[1]) << "*x1 ";
	out << constrTypeToString(type) << " " << b;

	return out.str();
}


}
