//
// Created by Kamil on 21.11.15.
//

#ifndef MES_ELEMENT_H
#define MES_ELEMENT_H


#include "Matrix.h"
#include "Node.h"

enum IntegralsType {
    SINGLE = 0,
    N1_SQUARED,
    N2_SQUARED,
    BOTH,
    PREVIOUS_TAU_N1,
    PREVIOUS_TAU_N2
};

class Element {
private:
    Node *NOP1, *NOP2;
    double K, dR, C, ro, dTau;
    Matrix *localMatrixH;
    Matrix *localMatrixP;

    void calculateLocalMatrixH();

    void calculateLocalMatrixP(int currentTau);

    static const int SCHEMA = 2;
    double weights[SCHEMA] = {1, 1};
    double points[SCHEMA] = {-0.5773502692, 0.5773502692};

    double N1(double r);

    double N2(double r);

    double integrals(IntegralsType type = IntegralsType::SINGLE);

    double integrals(IntegralsType type, int currentTau);

public:
    friend class FEMGrid;

    Element(Node *NOP1, Node *NOP2, double K, double C, double ro, double dTau);

    void calculateLocalMatrixes(int currentTau);

    ~Element();
};

#endif //MES_ELEMENT_H