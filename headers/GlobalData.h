//
// Created by Kamil on 21.11.15.
//

#ifndef MES_GLOBALDATA_H
#define MES_GLOBALDATA_H
#include <iostream>
#include <string>
#include <fstream>
#include "Material.h"

using namespace std;

class GlobalData {
private:
    int nh, ne, numberOfMaterials;
    double Q, Alfa, envT;
    int numberOfCommonVars = 4;
    Material** materials;
public:
    friend class FEMGrid;
    void loadFromFile(string const location = "input.txt");
    ~GlobalData();
};


#endif //MES_GLOBALDATA_H
