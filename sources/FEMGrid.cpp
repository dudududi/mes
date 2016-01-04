//
// Created by Kamil on 21.11.15.
//

#include "../headers/FEMGrid.h"

FEMGrid::FEMGrid() {
    elements = new vector<Element*>();
    nodes = new vector<Node*>();
}

void FEMGrid::generateFEMGrid(GlobalData *globalData) {
    globalMatrixH = new Matrix(globalData->nh, globalData->nh);
    globalMatrixP = new Matrix(globalData->nh, 1);
    result = new Matrix(1, globalData->nh);

    //calculating time-step
    double a = globalData->K/(globalData->C*globalData->ro);
    dR = (globalData->maxR - globalData->minR)/globalData->ne;
    dTau = (dR*dR)/(0.5*a);
    MAX_TAU_ITERATION = (int)(globalData->maxTau/dTau);

    //generating nodes first
    double interval = (globalData->maxR - globalData->minR) / (globalData->nh-1);
    for (int i = 0; i < globalData->nh; i++){
        nodes->push_back(new Node(i*interval, globalData->beginT));
    }

    //generating elements with previous generated nodes
    for (unsigned long i = 0; i<globalData->ne; i++){
        elements->push_back(new Element(nodes->at(i), nodes->at(i+1), globalData->K ,globalData->C, globalData->ro, dTau));
    }

    //setting boundary conditions
    nodes->back()->setBoundaryCondition(new BoundaryCondition(
            2*globalData->Alfa * globalData->maxR,
            -2*globalData->Alfa*globalData->maxR*globalData->envT));
}

FEMGrid::~FEMGrid() {
    for(vector<Element*>::iterator element= elements->begin(); element != elements->end(); element++){
        delete (*element);
    }

    for(vector<Node*>::iterator node= nodes->begin(); node != nodes->end(); node++){
        delete (*node);
    }
    delete globalMatrixH;
    delete globalMatrixP;
    delete result;
}

void FEMGrid::generateGlobalSE() {
    for (int tauIterator=0; tauIterator<MAX_TAU_ITERATION; tauIterator++) {
        for (vector<Element *>::iterator element = elements->begin(); element != elements->end(); element++) {
            (*element)->calculateLocalMatrixes(tauIterator);
            //cout << (*(*element)->localMatrixH) << endl;
            //cout << (*(*element)->localMatrixP) << endl;
        }
        for (unsigned long i = 0; i < elements->size(); i++) {
            Element *element = elements->at(i);
            globalMatrixH->insertMatrix((int) i, (int) i, element->localMatrixH);
            globalMatrixP->insertMatrix((int) i, 0, element->localMatrixP);
        }
        solveGlobalSE();
        for(vector<Node*>::iterator node= nodes->begin(); node != nodes->end(); node++){
            int i = node - nodes->begin();
            (*node)->insertTempForNextIteration(result->getValueAt(0, i));
        }
        cout<<"tau iteration = "<< tauIterator<< ": " << nodes->at(0)->getTempAtIteration(tauIterator)<<endl;
    }
}

void FEMGrid::solveGlobalSE() {
    Solver::solve(globalMatrixH, globalMatrixP, result);
    cout<<*result;
}
