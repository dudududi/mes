//
// Created by Kamil on 22.11.15.
//

#ifndef MES_SOLVER_H
#define MES_SOLVER_H

#include <cmath>
#include "Matrix.h"

class Solver {
public:
    static void solve(Matrix* matrixH, Matrix* vectorP, Matrix* result);
private:
    static void solveUsingGauss(Matrix* joinedMatrix, Matrix* result);
};


#endif //MES_SOLVER_H
