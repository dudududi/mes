//
// Created by Kamil on 21.11.15.
//

#ifndef MES_GLOBALDATA_H
#define MES_GLOBALDATA_H
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class GlobalData {
private:
    int nh, ne;
    double L, K, S, Q, C, ro, Alfa, envT, beginT, minR, maxR, maxTau;
    int numberOfVars = 12;
public:
    friend class FEMGrid;
    void loadFromFile(string const location = "input.txt");
};


#endif //MES_GLOBALDATA_H
