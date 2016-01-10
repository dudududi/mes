//
// Created by Kamil on 21.11.15.
//

#ifndef MES_BOUNDARYCONDITION_H
#define MES_BOUNDARYCONDITION_H


class BoundaryCondition {
private:
    double parameterDependent = 0, parameterIndependent = 0;
public:
    BoundaryCondition(double parameterDependent, double parameterIndependent);

    double getParameterDependentPart();

    double getParameterIndependentPart();
};


#endif //MES_BOUNDARYCONDITION_H
