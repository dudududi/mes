//
// Created by Kamil on 06.12.15.
//

#ifndef MES_MATERIAL_H
#define MES_MATERIAL_H


struct Material {
    int nh, ne;
    double L, K, S, C, ro, R;
    static const int NUMBER_OF_VARS = 8;
};


#endif //MES_MATERIAL_H
