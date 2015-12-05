//
// Created by Kamil on 21.11.15.
//

#include "../headers/Element.h"

Element::Element(Node *NOP1, Node* NOP2, double K, double L, double S) {
    this->NOP1 = NOP1;
    this->NOP2 = NOP2;
    this->K = K;
    this->L = L;
    this->S = S;
    localMatrixH = new Matrix();
    localMatrixP = new Matrix(2, 1);
}

void Element::calculateLocalMatrixes() {
    calculateLocalMatrixH();
    calculateLocalMatrixP();
}

Element::~Element() {
    delete localMatrixH;
    delete localMatrixP;
    //we cannot delete here the Nodes - we will delete them in FEMGrid
}

void Element::calculateLocalMatrixH() {
    double C = (K*S)/L;
    localMatrixH->setValueAt(0,0, C);
    localMatrixH->setValueAt(0,1,-C);
    localMatrixH->setValueAt(1,0,-C);
    localMatrixH->setValueAt(1,1,C);
    if (NOP1->boundaryCondition != NULL){
        localMatrixH->addValueAt(0,0,NOP1->boundaryCondition->getParameterDependentPart());
    }
    if (NOP2->boundaryCondition != NULL){
        localMatrixH->addValueAt(1,1,NOP2->boundaryCondition->getParameterDependentPart());
    }
}

void Element::calculateLocalMatrixP() {
    if(NOP1->boundaryCondition != NULL){
        localMatrixP->addValueAt(0,0,NOP1->boundaryCondition->getParameterIndependentPart());
    }
    if(NOP2->boundaryCondition != NULL){
        localMatrixP->addValueAt(1,0,NOP2->boundaryCondition->getParameterIndependentPart());
    }
}