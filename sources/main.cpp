#include <iostream>
#include "../headers/GlobalData.h"
#include "../headers/Exception.h"
#include "../headers/FEMGrid.h"

using namespace std;

int main() {
    try {
        GlobalData *globalData = new GlobalData();
        globalData->loadFromFile("/home/Kamil/ClionProjects/mes/input.txt");
        FEMGrid *grid = new FEMGrid();
        grid->generateFEMGrid(globalData);
        grid->generateAndSolveGlobalSE();
        delete (grid);
        delete (globalData);
        return 0;
    } catch (Exception e) {
        cout << e.getMessage();
        return 1;
    }
}