//
// Created by Kamil on 21.11.15.
//

#include "../headers/BoundaryCondition.h"

BoundaryCondition::BoundaryCondition(double parameterDependent, double parameterIndependent) {
    this->parameterDependent = parameterDependent;
    this->parameterIndependent = parameterIndependent;
}

double BoundaryCondition::getParameterDependentPart() {
    return parameterDependent;
}

double BoundaryCondition::getParameterIndependentPart() {
    return parameterIndependent;
}