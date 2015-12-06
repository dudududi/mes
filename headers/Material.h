//
// Created by Kamil on 06.12.15.
//

#ifndef MES_MATERIAL_H
#define MES_MATERIAL_H


struct Material {
    int nh, ne;
    double L, K, S;
    static const int NUMBER_OF_VARS = 5;
};


#endif //MES_MATERIAL_H
