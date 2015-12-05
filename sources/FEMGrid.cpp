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

    //generating nodes first
    for (int i = 0; i < globalData->nh; i++){
        nodes->push_back(new Node());
    }

    //generating elements with previous generated nodes
    double lengthOfNode = globalData->L / globalData->ne;
    for (unsigned long i = 0; i<globalData->ne; i++){
        elements->push_back(new Element(nodes->at(i), nodes->at(i+1), globalData->K, lengthOfNode ,globalData->S));
    }

    //setting boundary conditions
    nodes->front()->setBoundaryCondition(new BoundaryCondition(0,globalData->Q*globalData->S));
    nodes->back()->setBoundaryCondition(new BoundaryCondition(
            globalData->Alfa * globalData->S,
            -(globalData->Alfa*globalData->envT*globalData->S)));
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
    for(vector<Element*>::iterator element= elements->begin(); element != elements->end(); element++){
        (*element)->calculateLocalMatrixes();
        cout<<(*(*element)->localMatrixH)<<endl;
        cout<<(*(*element)->localMatrixP)<<endl;
    }
    for(unsigned long i = 0; i<elements->size(); i++){
        Element* element = elements->at(i);
        globalMatrixH->insertMatrix((int)i ,(int)i , element->localMatrixH);
        globalMatrixP->insertMatrix((int)i, 0, element->localMatrixP);
    }
    cout<<(*globalMatrixH)<<endl;
    cout<<(*globalMatrixP)<<endl;

}


void FEMGrid::solveGlobalSE() {
    Solver::solve(globalMatrixH, globalMatrixP, result);
    cout<<*result;
}
