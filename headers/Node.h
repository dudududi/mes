//
// Created by Kamil on 21.11.15.
//

#ifndef MES_NODE_H
#define MES_NODE_H

#include <iostream>
#include "BoundaryCondition.h"

using namespace std;

class Node {
private:
    double t;
    BoundaryCondition* boundaryCondition;
public:
    friend class Element;
    Node();
    double getValue();
    void setBoundaryCondition(BoundaryCondition* boundaryCondition);
    ~Node();
};


#endif //MES_NODE_H
