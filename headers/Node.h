//
// Created by Kamil on 21.11.15.
//

#ifndef MES_NODE_H
#define MES_NODE_H

#include <iostream>
#include <vector>
#include "BoundaryCondition.h"

using namespace std;

class Node {
private:
    double beginT, r;
    vector<double> *tempInTime;
    BoundaryCondition *boundaryCondition;
public:
    friend class Element;

    Node(double r, double beginT);

    void setBoundaryCondition(BoundaryCondition *boundaryCondition);

    double getTempAtIteration(int iteration);

    void insertTempForNextIteration(double value);

    ~Node();
};


#endif //MES_NODE_H
