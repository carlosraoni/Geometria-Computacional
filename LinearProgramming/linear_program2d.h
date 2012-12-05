#ifndef LINEAR_PROGRAM2D_H
#define LINEAR_PROGRAM2D_H

#include <string>
#include <vector>
#include "lp2d_constants.h"
#include "constraint2d.h"

namespace lp2D{

typedef enum{
	MAX, MIN
} LinearProgramType;

class LinearProgram2D{

public:

	LinearProgram2D(double c0, double c1, LinearProgramType type);
	~LinearProgram2D();

	void addConstraint(double a0, double a1, double b, ConstraintType type);
	int getNumberOfConstraints() const;
	Constraint2D * getConstraint(int index) const;

	double getC(int index) const;
	double getCAsMaximization(int index) const;

	double getZValue(double x, double y) const;
	double getZValueAsMaximization(double x, double y) const;

	string toString() const;

private:
	LinearProgramType type;
	vector<Constraint2D *> constr;
	double c[DIM];

};

}

#endif // LINEAR_PROGRAM2D_H
