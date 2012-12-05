#ifndef LP2D_SOLVER_H
#define LP2D_SOLVER_H

#include "linear_program2d.h"

namespace lp2D{

typedef enum{
	OPT_FOUND, UNFEASIBLE, UNBOUNDED
} LinearProgramResult;

LinearProgramResult solveLinearProgram2D(const LinearProgram2D * lp, double & optX, double & optY, double & opt);

}

#endif // LP2D_SOLVER_H
