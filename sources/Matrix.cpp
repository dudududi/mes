//
// Created by Kamil on 21.11.15.
//

#include "../headers/Matrix.h"

Matrix::Matrix(int rows, int columns) {
    this->rows = rows;
    this->columns = columns;
    matrix = new double*[rows];
    for (int i = 0; i < rows; i++){
        matrix[i]=new double[columns];
    }
    for (int i = 0; i<rows; i++){
        for (int j = 0; j< columns; j++){
            matrix[i][j] = 0;
        }
    }
}

Matrix::~Matrix() {
    for (int i =0; i<rows; i++){
        delete[] matrix[i];
    }
    delete [] matrix;
}

void Matrix::setValueAt(int row, int column, double value) {
    matrix[row][column] = value;
}

void Matrix::addValueAt(int row, int column, double value) {
    matrix[row][column] += value;
}

ostream &operator<<(ostream &os, const Matrix &m) {
    for (int i = 0; i<m.rows; i++){
        for (int j = 0; j<m.columns; j++){
            os<<m.matrix[i][j]<<"\t\t";
        }
        os<<endl;
    }
    return os;
}


void Matrix::insertMatrix(int row, int column, Matrix *matrix) {
    for (int i = 0; i<matrix->rows; i++){
        for (int j = 0; j<matrix->columns; j++){
            this->matrix[row+i][column+j]+=matrix->matrix[i][j];
        }
    }
}

double Matrix::getValueAt(int row, int column) {
    return matrix[row][column];
}