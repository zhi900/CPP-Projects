#include <iostream>
using namespace std;

// Size of the Sudoku grid
const int N = 9;

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            cout << grid[row][col] << " ";
        cout << endl;
    }
}

// Function to check if a number can be placed in a particular cell
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check if the number already exists in the current row
    for (int i = 0; i < N; i++)
        if (grid[row][i] == num)
            return false;

    // Check if the number already exists in the current column
    for (int i = 0; i < N; i++)
        if (grid[i][col] == num)
            return false;

    // Check if the number already exists in the current 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Function to solve the Sudoku puzzle
bool solveSudoku(int grid[N][N]) {
    int row, col;

    // Find an unassigned cell
    bool isUnassigned = false;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                isUnassigned = true;
                break;
            }
        }
        if (isUnassigned)
            break;
    }

    // If all cells are assigned, the puzzle is solved
    if (!isUnassigned)
        return true;

    // Try numbers from 1 to 9
    for (int num = 1; num <= 9; num++) {
        // Check if the number can be placed in the current cell
        if (isSafe(grid, row, col, num)) {
            // Place the number in the current cell
            grid[row][col] = num;

            // Recursively solve the rest of the puzzle
            if (solveSudoku(grid))
                return true;

            // If the current number does not lead to a solution, backtrack
            grid[row][col] = 0;
        }
    }

    // No solution found
    return false;
}

int main() {
    int grid[N][N];

    // Input the Sudoku grid (0 represents an empty cell)
    cout << "Enter the Sudoku grid (enter 0 for empty cells):\n";
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cin >> grid[row][col];
        }
    }

    // Solve the Sudoku puzzle
    if (solveSudoku(grid)) {
        cout << "Sudoku solution:\n";
        printGrid(grid);
    } else {
        cout << "No solution exists for the given Sudoku.\n";
    }

    return 0;
}