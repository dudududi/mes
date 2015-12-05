//
// Created by Kamil on 21.11.15.
//

#include "../headers/Node.h"
Node::Node() {
    boundaryCondition = NULL;
}

double Node::getValue() {
    return t;
}

void Node::setBoundaryCondition(BoundaryCondition* boundaryCondition ) {
    this->boundaryCondition = boundaryCondition;
}

Node::~Node() {
    if (boundaryCondition != NULL)
        delete boundaryCondition;
}