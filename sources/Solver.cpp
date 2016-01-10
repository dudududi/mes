//
// Created by Kamil on 22.11.15.
//

#include "../headers/Solver.h"

void Solver::solve(Matrix *matrixH, Matrix *vectorP, Matrix *result) {
    Matrix *matrix = new Matrix(matrixH->rows, matrixH->columns + 1);
    for (int i = 0; i < matrixH->rows; i++) {
        for (int j = 0; j < matrixH->columns; j++) {
            matrix->matrix[i][j] = matrixH->matrix[i][j];
        }
    }
    for (int i = 0; i < vectorP->rows; i++) {
        matrix->matrix[i][matrix->columns - 1] = -vectorP->matrix[i][0];
    }
    solveUsingGauss(matrix, result);
}

void Solver::solveUsingGauss(Matrix *joinedMatrix, Matrix *result) {

    for (int i = 0; i < joinedMatrix->rows; i++) {
        double maxValue = abs(joinedMatrix->matrix[i][i]);
        int maxRow = i;
        for (int j = i + 1; j < joinedMatrix->rows; j++) {
            if (abs(joinedMatrix->matrix[j][i]) > maxValue) {
                maxValue = abs(joinedMatrix->matrix[j][i]);
                maxRow = j;
            }
        }
        for (int j = i; j < joinedMatrix->columns; j++) {
            double tmp = joinedMatrix->matrix[maxRow][j];
            joinedMatrix->matrix[maxRow][j] = joinedMatrix->matrix[i][j];
            joinedMatrix->matrix[i][j] = tmp;
        }

        for (int k = i + 1; k < joinedMatrix->rows; k++) {
            double zm = -joinedMatrix->matrix[k][i] / joinedMatrix->matrix[i][i];
            for (int j = i; j < joinedMatrix->columns; j++) {
                if (i == j) {
                    joinedMatrix->matrix[k][j] = 0;
                }
                else {
                    joinedMatrix->matrix[k][j] += zm * joinedMatrix->matrix[i][j];
                }
            }
        }
    }

    for (int i = joinedMatrix->rows - 1; i >= 0; i--) {
        result->matrix[0][i] = joinedMatrix->matrix[i][joinedMatrix->rows] / joinedMatrix->matrix[i][i];
        for (int k = i - 1; k >= 0; k--) {
            joinedMatrix->matrix[k][joinedMatrix->rows] -= joinedMatrix->matrix[k][i] * result->matrix[0][i];
        }
    }
}
