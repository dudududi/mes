//
// Created by Kamil on 21.11.15.
//

#include "../headers/Node.h"
Node::Node(double r, double beginT) {
    boundaryCondition = NULL;
    this->r = r;
    this->beginT = beginT;
    tempInTime = new vector<double>();
}

void Node::setBoundaryCondition(BoundaryCondition* boundaryCondition ) {
    this->boundaryCondition = boundaryCondition;
}

Node::~Node() {
    if (boundaryCondition != NULL)
        delete boundaryCondition;
    delete (tempInTime);
}

double Node::getTempAtIteration(int iteration) {
    if (iteration == -1) return beginT;
    else return tempInTime->at((unsigned)iteration);
}

void Node::insertTempForNextIteration(double value) {
    this->tempInTime->push_back(value);
}