//
// Created by Kamil on 21.11.15.
//

#ifndef MES_MATRIX_H
#define MES_MATRIX_H

#include <iostream>
using namespace std;

class Matrix {
private:
    int rows, columns;
    double** matrix;
public:
    friend class Solver;
    Matrix(int rows = 2, int columns = 2);
    void setValueAt(int row, int column, double value);
    void addValueAt(int row, int column, double value);
    double getValueAt(int row, int column);
    ~Matrix();
    friend ostream& operator<<(ostream& os, const Matrix& m);
    void insertMatrix(int row, int column, Matrix* matrix);
};


#endif //MES_MATRIX_H