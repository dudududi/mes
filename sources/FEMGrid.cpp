//
// Created by Kamil on 21.11.15.
//

#include "../headers/FEMGrid.h"

FEMGrid::FEMGrid() {
    elements = new vector<Element *>();
    nodes = new vector<Node *>();
}

void FEMGrid::generateFEMGrid(GlobalData *globalData) {
    globalMatrixH = new Matrix(globalData->nh, globalData->nh);
    globalMatrixP = new Matrix(globalData->nh, 1);
    result = new Matrix(1, globalData->nh);

    int numberOfMaterials = globalData->numberOfMaterials;

    //calculating time-step for all materials
    double currentR = globalData->minR;
    for (int i = 0; i < numberOfMaterials; i++) {
        Material *currentMaterial = globalData->materials[i];
        //generating nodes first
        double interval = currentMaterial->R / (currentMaterial->nh - 1);
        for (int j = 0; j < currentMaterial->nh; j++) {
            if (i != 0 && j == 0) continue; //first node of 1st material and last node od 2nd material are the same!
            nodes->push_back(new Node(currentR + interval * j, globalData->beginT));
        }
        currentR += currentMaterial->R;
        double dR = currentMaterial->R / currentMaterial->ne;
        double a = currentMaterial->K / (currentMaterial->C * currentMaterial->ro);
        dTau += dR * dR / (0.5 * a);
    }
    dTau = dTau / numberOfMaterials;
    MAX_TAU_ITERATION = globalData->maxTau / dTau;

    //generating elements with previous generated nodes
    unsigned long idOfNode = 0;
    for (int i = 0; i < numberOfMaterials; i++) {
        Material *currentMaterial = globalData->materials[i];
        for (int j = 0; j < currentMaterial->ne; j++) {
            elements->push_back(new Element(nodes->at(idOfNode), nodes->at(idOfNode + 1), currentMaterial->K,
                                            currentMaterial->C, currentMaterial->ro, dTau));
            idOfNode++;
        }
    }

    //setting boundary conditions
    nodes->back()->setBoundaryCondition(new BoundaryCondition(
            2 * globalData->Alfa * globalData->maxR,
            -2 * globalData->Alfa * globalData->maxR * globalData->envT));
}

FEMGrid::~FEMGrid() {
    for (vector<Element *>::iterator element = elements->begin(); element != elements->end(); element++) {
        delete (*element);
    }

    for (vector<Node *>::iterator node = nodes->begin(); node != nodes->end(); node++) {
        delete (*node);
    }
    delete globalMatrixH;
    delete globalMatrixP;
    delete result;
}

void FEMGrid::generateAndSolveGlobalSE() {
    ofstream file(RESULT_FILE, ofstream::trunc);
    ostream *output;
    if (file.is_open()) {
        cout << "Results will be saved in: " << RESULT_FILE;
        output = &file;
    }
    else {
        cout << "Cannot create output file, results will be printed here." << endl;
        output = &cout;
    }
    (*output) << setw(12) << "tau";
    for (int i = 0; i < nodes->size(); i++) {
        (*output) << setw(12) << "t" + std::to_string(i);
    }
    (*output) << endl;

    for (int tauIterator = 0; tauIterator < MAX_TAU_ITERATION; tauIterator++) {
        for (vector<Element *>::iterator element = elements->begin(); element != elements->end(); element++) {
            (*element)->calculateLocalMatrixes(tauIterator);
        }
        for (unsigned long i = 0; i < elements->size(); i++) {
            Element *element = elements->at(i);
            globalMatrixH->insertMatrix((int) i, (int) i, element->localMatrixH);
            globalMatrixP->insertMatrix((int) i, 0, element->localMatrixP);
        }
        Solver::solve(globalMatrixH, globalMatrixP, result);
        for (vector<Node *>::iterator node = nodes->begin(); node != nodes->end(); node++) {
            int i = node - nodes->begin();
            (*node)->insertTempForNextIteration(result->getValueAt(0, i));
        }
        (*output) << setiosflags(ios::fixed) << setprecision(2) << setw(12) << (tauIterator + 1) * dTau << (*result);
        (*result) = 0;
        (*globalMatrixH) = 0;
        (*globalMatrixP) = 0;
    }
    file.close();
}
