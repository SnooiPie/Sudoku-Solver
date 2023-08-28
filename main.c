#include <stdio.h>
#include <stdbool.h>

#define N 9

// Check if placing 'num' at grid[row][col] maintains Sudoku rules
bool is_valid(int grid[N][N], int row, int col, int num) {
    // Check current row and column
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return false;
        }
    }

    // Check 3x3 subgrid
    int start_row = row - row % 3;
    int start_col = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + start_row][j + start_col] == num) {
                return false;
            }
        }
    }

    return true;
}

// Find an empty location (with value 0) in the grid
bool find_empty_location(int grid[N][N], int *row, int *col) {
    for (*row = 0; *row < N; (*row)++) {
        for (*col = 0; *col < N; (*col)++) {
            if (grid[*row][*col] == 0) {
                return true;
            }
        }
    }
    return false;
}

// Solve the Sudoku puzzle using backtracking
bool solve_sudoku(int grid[N][N]) {
    int row, col;

    // If no empty location found, puzzle is solved
    if (!find_empty_location(grid, &row, &col)) {
        return true;
    }

    // Try placing numbers from 1 to 9
    for (int num = 1; num <= N; num++) {
        if (is_valid(grid, row, col, num)) {
            grid[row][col] = num;

            // Recursively solve the remaining puzzle
            if (solve_sudoku(grid)) {
                return true; // Puzzle solved, terminate
            }

            // If current placement doesn't work, backtrack
            grid[row][col] = 0;
        }
    }

    return false; // No valid number found, need to backtrack further
}

// Print the Sudoku grid
void print_grid(int grid[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

// Entry point
int main() {
    int grid[N][N] = {
        // Initial Sudoku puzzle
        {8, 0, 0, 0, 0, 0, 0, 0, 0},//⠀⠀⠀⠀⣀⣤⣤⣶⣾⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣶⣶⣦⣤⣀⠀⠀⠀⠀⠀
        {0, 0, 3, 6, 0, 0, 0, 0, 0},//⣀⣴⣶⣿⣿⣿⣿⣿⣿⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣴⣿⣿⣿⣿⣿⣿⣷⣦⣄⡀
        {0, 7, 0, 0, 9, 0, 2, 0, 0},//⠁⠀⠀⠈⠉⠛⣿⣿⣿⣿⣿⣷⣦⣀⢠⣆⣸⡆⢀⣤⣾⣿⣿⣿⣿⣿⠟⠋⠉⠀⠀⠀⠀
        {0, 5, 0, 0, 0, 7, 0, 0, 0},//⠀⠀⠀⠀⠀⠀⠸⠿⠿⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠿⠿⠿⠏⠀⠀⠀⠀⠀⠀⠀
        {0, 0, 0, 0, 4, 5, 7, 0, 0},//⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠻⣿⣿⣿⣿⠿⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        {0, 0, 0, 1, 0, 0, 0, 3, 0},//⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        {0, 0, 1, 0, 0, 0, 0, 6, 8},// _                         _           _                         
        {0, 0, 8, 5, 0, 0, 0, 1, 0},//| |   __ _ _ __ ___       | |__   __ _| |_ _ __ ___   __ _ _ __  
        {0, 9, 0, 0, 0, 0, 4, 0, 0} //| |  / _` | '_ ` _ \      | '_ \ / _` | __| '_ ` _ \ / _` | '_ \ 
    };                              //| | | (_| | | | | | |     | |_) | (_| | |_| | | | | | (_| | | | |
                                    //|_|  \__,_|_| |_| |_|     |_.__/ \__,_|\__|_| |_| |_|\__,_|_| |_|
    if (solve_sudoku(grid)) {
        printf("Sudoku solved:\n");
        print_grid(grid);
    } else {
        printf("No solution exists.\n");
    }

    return 0;
}
