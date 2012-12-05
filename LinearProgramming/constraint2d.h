#ifndef CONSTRAINT_2D
#define CONSTRAINT_2D

#include <string>
#include "lp2d_constants.h"

using namespace std;

namespace lp2D{

typedef enum{
	LT, LEQ, EQ, GEQ, GT, INVALID
} ConstraintType;

string constrTypeToString(ConstraintType t);

ConstraintType constrTypeFromString(const string & str);

class Constraint2D{

public:

	Constraint2D(double a0, double a1, double b, ConstraintType type);

	double getA(int d) const;
	double getB() const;

	ConstraintType getType() const;

	bool isFeasible(double x, double y) const;

	string toString() const;

private:
	double a[DIM], b;
	ConstraintType type;
};


}

#endif // CONSTRAINT_2D
