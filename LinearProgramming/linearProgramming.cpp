#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

#define VERBOSE

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

typedef enum{
	OPT_FOUND, UNFEASIBLE, UNBOUNDED
} LinearProgramResult;

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

	double getCAsMaximization(int index) const{
		return this->c[index] * ((type == MAX) ? 1.0: -1.0);
	}

	double getZValue(double x, double y) const{
		return c[0] * x + c[1] * y;
	}

	double getZValueAsMaximization(double x, double y) const{
		return getCAsMaximization(0) * x + getCAsMaximization(1) * y;
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

bool calcConstraintIntersection(const Constraint2D * c1, const Constraint2D * c2, double & xInter, double & yInter){
	double a0 = c1->getA(0);
	double a1 = c1->getA(1);
	double a2 = c2->getA(0);
	double a3 = c2->getA(1);

	double denominatorXInter = a1 * a2 - a0 * a3;

	// Determina se restrições são paralelas
	if(fabs(denominatorXInter) < EPS){
		return false;
	}

	double b1 = c1->getB();
	double b2 = c2->getB();
	xInter = (a1 * b2 - a3 * b1) / denominatorXInter;
	yInter = (b1 - a0 * xInter) / a1;

	cout << "Intersection " << c1->toString() << " && " << c2->toString() << endl;
	cout << "(" << xInter << ", " << yInter << ")" << endl << endl;

	return true;
}

bool calcBoundConstraintIntersection(const Constraint2D * c, const Constraint2D * bound, bool isBoundingX, double & xInter, double & yInter){
	double a0 = c->getA(0);
	double a1 = c->getA(1);
	double b = c->getB();

	if(isBoundingX){
		xInter = bound->getB();
		if(fabs(a1) < EPS)
			return false;
		yInter = (b - a0 * xInter) / a1;
	}
	else{
		yInter = bound->getB();
		if(fabs(a0) < EPS)
			return false;
		xInter = (b - a1 * yInter) / a0;
	}

	return true;
}

const double SMALL_CONST = 1.0;

double calcY(double x, double a0, double a1, double b){
	return (b - (a0 * x)) / a1;
}


double calcX(double y, double a0, double a1, double b){
	return (b - (a1 * y)) / a0;
}

bool updateLimits(const Constraint2D * c, const Constraint2D * test, double xInter, double yInter, double & xLeft, double & xRight){
	double yLeftPoint = calcY(xInter - SMALL_CONST, c->getA(0), c->getA(1), c->getB());
	bool isBoundedRight = test->isFeasible(xInter - SMALL_CONST, yLeftPoint);

	if(isBoundedRight){
		cout << "Update Right Bound" << endl;
		xRight = (xRight < xInter) ? xRight: xInter;
	}
	else{
		cout << "Update Left Bound" << endl;
		xLeft = (xLeft > xInter) ? xLeft: xInter;
	}

	return xLeft < xRight;
}

void initializeBounds(const Constraint2D * bx, const Constraint2D * by, const Constraint2D * c, double & xLeft, double & xRight){
	xLeft = -2*M;
	xRight = 2*M;

	double xInter, yInter;
	calcBoundConstraintIntersection(c, bx, true, xInter, yInter);
	printf("bx inter %lf %lf\n", xInter, yInter);
	updateLimits(c, bx, xInter, yInter, xLeft, xRight);

	calcBoundConstraintIntersection(c, by, false, xInter, yInter);
	printf("by inter %lf %lf\n", xInter, yInter);
	updateLimits(c, by, xInter, yInter, xLeft, xRight);
}

bool updateCurrentOptSolution(const LinearProgram2D * lp, const Constraint2D * bx, const Constraint2D * by, int currConstr, double & currX, double & currY){
	const Constraint2D * c = lp->getConstraint(currConstr);

	double xLeft, xRight;
	initializeBounds(bx, by, c, xLeft, xRight);
	printf("Bounds Initialized -> %lf %lf \n\n", xLeft, xRight);

	double xInter, yInter;
	int nc = lp->getNumberOfConstraints();
	for(int i=0; i<currConstr; i++){
		cout << "Calculating intersection " << currConstr << " and " << i << endl;
		if(!calcConstraintIntersection(c, lp->getConstraint(i), xInter, yInter))
			continue;
		if(!updateLimits(c, lp->getConstraint(i), xInter, yInter, xLeft, xRight))
			return false;
	}

	double yLeft = calcY(xLeft, c->getA(0), c->getA(1), c->getB());
	double yRight = calcY(xRight, c->getA(0), c->getA(1), c->getB());

	double zLeft = lp->getZValueAsMaximization(xLeft, yLeft);
	double zRight = lp->getZValueAsMaximization(xRight, yRight);

	printf("Left -> (%lf, %lf) = %lf\n", xLeft, yLeft, zLeft);
	printf("Right -> (%lf, %lf) = %lf\n", xRight, yRight, zRight);

	if(zRight > zLeft){
		cout << "Update Solution to Right" << endl;
		currX = xRight;
		currY = yRight;
	}
	else{
		cout << "Update Solution to Left" << endl;
		currX = xLeft;
		currY = yLeft;
	}

	return true;
}

LinearProgramResult solveLinearProgram2D(const LinearProgram2D * lp, double & optX, double & optY, double & opt){
	double currX = 0.0, currY = 0.0;
	double cx = lp->getCAsMaximization(0);
	double cy = lp->getCAsMaximization(1);
	cout << cx << " " << cy << endl;
	Constraint2D * boundXConstr;
	if(cx > 0.0){
		boundXConstr = new Constraint2D(1.0, 0.0, M, LEQ);
		currX = M;
	}
	else{
		boundXConstr = new Constraint2D(1.0, 0.0, M, GEQ);
		currX = -M;
	}

	Constraint2D * boundYConstr;
	if(cy > 0.0){
		boundYConstr = new Constraint2D(0.0, 1.0, M, LEQ);
		currY = M;
	}
	else{
		boundYConstr = new Constraint2D(0.0, 1.0, M, GEQ);
		currY = -M;
	}
	opt = lp->getZValue(currX, currY);

	cout << "Starting to Solve LP: " << endl << lp->toString() << endl;

	int nc = lp->getNumberOfConstraints();
	for(int i=0; i<nc; i++){
		const Constraint2D * c = lp->getConstraint(i);
		cout << "Insert constraint " << i << " : " << c->toString() << endl;
		if(c->isFeasible(currX, currY)){
			printf("Current Solution (%lf, %lf) = %lf is Feasible, insert next Constraint\n", currX, currY, opt);
			continue;
		}
		cout << "---->Updating Current Solution" << endl;
		if(!updateCurrentOptSolution(lp, boundXConstr, boundYConstr, i, currX, currY)){
			cout << "The Linear Program is Unfeasible" << endl;

			delete boundXConstr;
			delete boundYConstr;

			return UNFEASIBLE;
		}
		opt = lp->getZValue(currX, currY);
		printf("---->Current Solution Updated (%lf, %lf) = %lf\n\n", currX, currY, opt);
	}

	printf("\n\t\tOptimum Found (%lf, %lf) = %lf\n", currX, currY, opt);

	delete boundXConstr;
	delete boundYConstr;

	return OPT_FOUND;
}

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

