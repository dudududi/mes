//
// Created by Kamil on 21.11.15.
//

#include "../headers/Element.h"

Element::Element(Node *NOP1, Node* NOP2, double K, double C, double ro, double dTau) {
    this->NOP1 = NOP1;
    this->NOP2 = NOP2;
    this->K = K;
    this->C = C;
    this->ro = ro;
    this->dTau = dTau;
    this->dR = NOP2->r - NOP1->r;
    localMatrixH = new Matrix();
    localMatrixP = new Matrix(2, 1);
}

void Element::calculateLocalMatrixes(int currentTau) {
    calculateLocalMatrixH();
    calculateLocalMatrixP(currentTau);
}

Element::~Element() {
    delete localMatrixH;
    delete localMatrixP;
    //we cannot delete here the Nodes - we will delete them in FEMGrid
}

void Element::calculateLocalMatrixH() {
    double K11 = K * integrals() / dR + C*ro*dR*integrals(N1_SQUARED)/dTau;
    double K12 = -K * integrals() / dR + C*ro*dR*integrals(BOTH)/dTau;
    double K21 = K12;
    double K22 = K * integrals() / dR + C*ro*dR*integrals(N2_SQUARED)/dTau;
    localMatrixH->setValueAt(0,0, K11);
    localMatrixH->setValueAt(0,1,K12);
    localMatrixH->setValueAt(1,0,K21);
    localMatrixH->setValueAt(1,1,K22);
    if (NOP1->boundaryCondition != NULL){
        localMatrixH->addValueAt(0,0,NOP1->boundaryCondition->getParameterDependentPart());
    }
    if (NOP2->boundaryCondition != NULL){
        localMatrixH->addValueAt(1,1,NOP2->boundaryCondition->getParameterDependentPart());
    }
}

void Element::calculateLocalMatrixP(int currentTau) {
    double a = -C*ro*dR/dTau;
    double b = integrals(PREVIOUS_TAU_N1, currentTau);
    double F1 = -C*ro*dR*integrals(PREVIOUS_TAU_N1, currentTau)/dTau;
    double F2 = -C*ro*dR*integrals(PREVIOUS_TAU_N2, currentTau)/dTau;
    localMatrixP->setValueAt(0,0,F1);
    localMatrixP->setValueAt(1,0,F2);
    if(NOP1->boundaryCondition != NULL){
        localMatrixP->addValueAt(0,0,NOP1->boundaryCondition->getParameterIndependentPart());
    }
    if(NOP2->boundaryCondition != NULL){
        localMatrixP->addValueAt(1,0,NOP2->boundaryCondition->getParameterIndependentPart());
    }
}

double Element::N1(double r) {
    return 0.5*(1-r);
}

double Element::N2(double r) {
    return 0.5*(1+r);
}

double Element::integrals(IntegralsType type) {
    double result = 0;
    switch (type){
        case SINGLE:
            for (int i =0; i<SCHEMA; i++){
                double r = N1(points[i])*NOP1->r + N2(points[i])*NOP2->r;
                result += r*weights[i];
            }
            break;
        case N1_SQUARED:
            for (int i =0; i<SCHEMA; i++){
                double r = N1(points[i])*NOP1->r + N2(points[i])*NOP2->r;
                result += N1(points[i])* N1(points[i])*r*weights[i];
            }
            break;
        case N2_SQUARED:
            for (int i =0; i<SCHEMA; i++){
                double r = N1(points[i])*NOP1->r + N2(points[i])*NOP2->r;
                result += N2(points[i])* N2(points[i])*r*weights[i];
            }
            break;

        case BOTH:
            for (int i =0; i<SCHEMA; i++){
                double r = N1(points[i])*NOP1->r + N2(points[i])*NOP2->r;
                result += N1(points[i])* N2(points[i])*r*weights[i];
            }
            break;
        default:
            result = -1;
    }
    return result;
}

double Element::integrals(IntegralsType type, int currentTau) {
    double result = 0;
    switch(type){
        case PREVIOUS_TAU_N1:
            for (int i=0; i<SCHEMA; i++){
                double r = N1(points[i])*NOP1->r + N2(points[i])*NOP2->r;
                result += (N1(points[i])*NOP1->getTempAtIteration(currentTau-1) + N2(points[i])*NOP2->getTempAtIteration(currentTau-1))*N1(points[i])*r*weights[i];
            }
            break;
        case PREVIOUS_TAU_N2:
            for (int i=0; i<SCHEMA; i++){
                double r = N1(points[i])*NOP1->r + N2(points[i])*NOP2->r;
                result += (N1(points[i])*NOP1->getTempAtIteration(currentTau-1) + N2(points[i])*NOP2->getTempAtIteration(currentTau-1))*N2(points[i])*r*weights[i];
            }
            break;
        default:
            result = -1;
    }
    return result;
}
