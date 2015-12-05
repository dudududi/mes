//
// Created by Kamil on 21.11.15.
//

#ifndef MES_ELEMENT_H
#define MES_ELEMENT_H


#include "Matrix.h"
#include "Node.h"

class Element {
private:
    Node *NOP1, *NOP2;
    double K, L, S;
    Matrix* localMatrixH;
    Matrix* localMatrixP;
    void calculateLocalMatrixH();
    void calculateLocalMatrixP();
public:
    friend class FEMGrid;
    Element(Node* NOP1, Node* NOP2, double K, double L, double S);
    void calculateLocalMatrixes();
    ~Element();
};



#endif //MES_ELEMENT_H
