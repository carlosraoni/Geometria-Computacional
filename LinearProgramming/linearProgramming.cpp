#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

const double EPS = 1e-9;
const double M = 10e9;

const int DIM = 2;
const int N_CONSTR_TYPE = 6;

const char ConstraintTypeToStr[N_CONSTR_TYPE][4] = {"<", "<=", "=", ">=", ">", "I"};

typedef enum{
	LT, LEQ, EQ, GEQ, GT, INVALID
} ConstraintType;

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

class Constraint2D{

public:

	Constraint2D(double a0, double a1, double b, ConstraintType type){
		this->type = type;
		this->a[0] = a0;
		this->a[1] = a1;
		this->b = b;
	}

	double getA(int d) const{
		return a[d];
	}

	double getB() const{
		return b;
	}

	ConstraintType getType() const{
		return type;
	}

	bool isFeasible(double x, double y) const{
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

	string toString() const{
		ostringstream out;

		out << a[0] << "*x0" << ((a[1] > 0) ? " + " : " - ") << fabs(a[1]) << "*x1 ";
		out << constrTypeToString(type) << " " << b;

		return out.str();
	}

private:

	double a[DIM], b;
	ConstraintType type;
};

typedef enum{
	MAX, MIN
} LinearProgramType;

class LinearProgram2D{

public:

	LinearProgram2D(double c0, double c1, LinearProgramType type){
		this->c[0] = c0;
		this->c[1] = c1;
		this->type = type;
	}

	~LinearProgram2D(){
		int m = getNumberOfConstraints();
		for(int i=0; i<m; i++)
			delete getConstraint(i);
	}

	void addConstraint(double a0, double a1, double b, ConstraintType type){
		this->constr.push_back(new Constraint2D(a0, a1, b, type));
	}

	int getNumberOfConstraints() const{
		return this->constr.size();
	}

	Constraint2D * getConstraint(int index) const{
		return this->constr[index];
	}

	double getC(int index) const{
		return this->c[index];
	}

	string toString() const{
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

private:

	LinearProgramType type;
	vector<Constraint2D *> constr;
	double c[DIM];

};

bool calcConstraintIntersection(const Constraint2D & c1, const Constraint2D & c2, double & xInter, double & yInter){
	double a0 = c1.getA(0);
	double a1 = c1.getA(1);
	double a2 = c2.getA(0);
	double a3 = c2.getA(1);

	double denominatorXInter = a1 * a2 - a0 * a3;

	// Determina se restrições são paralelas
	if(fabs(denominatorXInter) < EPS){
		return false;
	}

	double b1 = c1.getB();
	double b2 = c2.getB();
	xInter = (a1 * b2 - a3 * b1) / denominatorXInter;
	yInter = (b1 - a0 * xInter) / a1;

	return true;
}



int main(int argc, char ** argv){
	LinearProgram2D * lp;
	string type;
	double c[DIM];
	double a[DIM], b;

	cin >> type >> c[0] >> c[1];
	lp = new LinearProgram2D(c[0], c[1], (type == "MAX") ? MAX: MIN);

	while(cin >> a[0] >> a[1] >> type >> b){
		lp->addConstraint(a[0], a[1], b, constrTypeFromString(type));
	}

	cout << lp->toString() << endl;

	delete lp;
	return 0;
}

