#ifndef LP2D_CONSTANTS_H
#define LP2D_CONSTANTS_H

namespace lp2D{

const double EPS = 1e-9;
const double SMALL_CONST = 1.0;
const double M = 10e9;

const int DIM = 2;
const int N_CONSTR_TYPE = 6;

const char ConstraintTypeToStr[N_CONSTR_TYPE][4] = {"<", "<=", "=", ">=", ">", "I"};

}

#endif // LP2D_CONSTANTS_H
