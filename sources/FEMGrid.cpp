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
    int numberOfMaterials = globalData->numberOfMaterials;

    //generating elements with previous generated nodes
    unsigned long idOfNode = 0;
    for (int i=0; i<numberOfMaterials;i++){
        Material* currentMaterial = globalData->materials[i];
        double lengthOfElement = currentMaterial->L/currentMaterial->ne;
        for (int j = 0; j<currentMaterial->ne; j++){
            elements->push_back(new Element(nodes->at(idOfNode), nodes->at(idOfNode+1), currentMaterial->K,
                                            lengthOfElement ,currentMaterial->S));
            idOfNode++;
        }
    }

    //setting boundary conditions
    nodes->front()->setBoundaryCondition(new BoundaryCondition(0,globalData->Q*globalData->materials[0]->S));
    nodes->back()->setBoundaryCondition(new BoundaryCondition(
            globalData->Alfa * globalData->materials[numberOfMaterials-1]->S,
            -(globalData->Alfa*globalData->envT*globalData->materials[numberOfMaterials-1]->S)));

    dR = (globalData->maxR - globalData->minR)/globalData->ne;
    //dTau = (dR * dR)/(0.5*) how ???????????????????
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
    }
    for(unsigned long i = 0; i<elements->size(); i++){
        Element* element = elements->at(i);
        globalMatrixH->insertMatrix((int)i ,(int)i , element->localMatrixH);
        globalMatrixP->insertMatrix((int)i, 0, element->localMatrixP);
    }
}


void FEMGrid::solveGlobalSE() {
    Solver::solve(globalMatrixH, globalMatrixP, result);
    cout<<*result;
}
