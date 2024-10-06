using namespace std;
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

bool isValid(int row, int column, vector<vector<int>> &grid, int n) {
    // revisar si ya existe el numero en su fila
    for (int i = 0; i < 9; i++) {
        if (grid[row][i] == n) {
            return false;
        }
    }

    // revisar si ya existe el numero en su columna
    for (int i = 0; i < 9; i++) {
        if (grid[i][column] == n) {
            return false;
        }
    }
    // obtener la primera fila y columna del cuadro del numero actual
    int startRow = row - row % 3;
    int starCol = column - column % 3;

    // revisar si existe el numero en su cuadro
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[startRow + i][starCol + j] == n) {
                return false;
            }
        }
    }

    return true;
}

bool solveSudoku(int row, int column, vector<vector<int>> &grid) {

    // caso base sudoku resuelto
    if (column == 9 && row == 8) {
        return true;
    }

    // revisar si la columna ya esta fuera de alcance
    if (column == 9) {
        column = 0;
        row++;
    }

    // revisar si ya existe un numero en la celda actual
    if (grid[row][column] != 0) {
        return solveSudoku(row, column + 1, grid);
    }

    // revisar numeros para el indice actual
    for (int i = 1; i < 10; i++) {
        if (isValid(row, column, grid, i)) {
            grid[row][column] = i;
        
            // revisar si se puede resolver el siguiente elemento
            if (solveSudoku(row, column + 1, grid)) {
                return true;
            }

            // regresar el valor a 0 en caso de que el numero no sea correcto
            grid[row][column] = 0;

        }
    }

    return false;
}

int main(int argc, char *argv[]) {

    ifstream file(argv[1]);
    vector<vector<int>> sudokuGrid;

    string line;
    while (getline(file, line)) {
        vector<int> row;
        stringstream ss(line);
        string num;
        
        while (getline(ss, num, ',')) {
            row.push_back(stoi(num));
        }
        sudokuGrid.push_back(row);
    }
    
    file.close();

    cout << "Original sudoku:" << endl;
    for (int row = 0; row < 9; row++) {
        for (int column = 0; column < 9; column++) {
            cout << sudokuGrid[row][column] << " ";
        }
        cout << endl;
    }

    solveSudoku(0,0,sudokuGrid);

    ofstream outputFile("outputSudoku.txt");

    cout << endl << endl << "Solved sudoku:" << endl;
    for (int row = 0; row < 9; row++) {
        for (int column = 0; column < 9; column++) {
            cout << sudokuGrid[row][column] << " ";
            outputFile << sudokuGrid[row][column] << " ";
        }
        cout << endl;
        outputFile << endl;
    }

    outputFile.close();

    return 0;
}