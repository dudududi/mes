//
// Created by Kamil on 21.11.15.
//

#ifndef MES_FEMGRID_H
#define MES_FEMGRID_H

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include "Element.h"
#include "GlobalData.h"
#include "Solver.h"

using namespace std;

class FEMGrid {
private:
    vector<Element *> *elements;
    vector<Node *> *nodes;
    Matrix *globalMatrixH;
    Matrix *globalMatrixP;
    Matrix *result;
    const string RESULT_FILE = "output.txt";
    double MAX_TAU_ITERATION, dTau;
public:
    FEMGrid();

    void generateFEMGrid(GlobalData *globalData);

    void generateAndSolveGlobalSE();

    ~FEMGrid();
};


#endif //MES_FEMGRID_H
