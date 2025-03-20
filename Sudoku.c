#include <stdio.h>
#include <stdbool.h>

#define N 9  //sudoku grid 9*9

// Print the Sudoku grid 
void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", board[i][j]);
            if ((j + 1) % 3 == 0 && j < N - 1) {
                printf("| ");
            }
        }
        printf("\n");
        
        if ((i + 1) % 3 == 0 && i < N - 1) {
            printf("---------------------\n");
        }
    }
}

// To place number
bool isSafe(int board[N][N], int row, int col, int num) {
    // Check if the number already exists in the current row
    for (int x = 0; x < N; x++) {
        if (board[row][x] == num) {
            return false;
        }
    }
    
    // Check if the number already exists in the current column
    for (int x = 0; x < N; x++) {
        if (board[x][col] == num) {
            return false;
        }
    }
    
    // Check if the number exists in the 3*3 subgrid
    int startRow = row - row % 3, startCol = col - col % 3;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }
    
    return true;  // If that number is not exist in row, col, in the 3*3 grid
}

// Sudoku puzzle using backtracking
bool solveSudoku(int board[N][N]) {
    int row, col;
    bool empty = false;

    // Find the first empty space (denoted by 0)
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (board[row][col] == 0) {
                empty = true;  // There's an empty cell
                break;
            }
        }
        if (empty) break;
    }
    
    // If there are no empty cells, we have solved the Sudoku
    if (!empty) {
        return true;
    }

    // Try placing digits 1-9 in the empty cell
    for (int num = 1; num <= N; num++) {
        // Check if placing the number is safe
        if (isSafe(board, row, col, num)) {
            // Place the number
            board[row][col] = num;

            // Recursively try to solve the rest of the grid
            if (solveSudoku(board)) {
                return true;  // If successful, return true
            }

            // If placing num didn't lead to a solution, backtrack
            board[row][col] = 0;
        }
    }

    return false;  // Trigger backtracking if no number can be placed
}

int main() {
    int board[N][N];
    printf("Enter sudoku grid to be solved [Enter 0 for empty place]: \n\n");
    for(int i=0;i<N;i++){
    	for(int j=0;j<N;j++){
    		scanf("%d", &board[i][j]);
		}
	}

    // Sudoku board before solving
    printf("\n\nUnsolved Sudoku Puzzle from User:\n");
    printBoard(board);

    // After solving Sudoku puzzle
    if (solveSudoku(board)) {
        printf("\nSolved Sudoku:\n");
        printBoard(board);
    } else {
        printf("\nNo solution exists.\n");
    }

    return 0;
}
