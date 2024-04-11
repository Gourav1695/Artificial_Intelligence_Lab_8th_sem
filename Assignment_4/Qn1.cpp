#include <iostream>
#include <vector>

using namespace std;

class EightQueens {
private:
    const int board_size = 8;
    int solution_count = 0;
    //This is the beginning of a class definition named EightQueens. It encapsulates the functionality related to solving the Eight Queens problem. It has two private data members: board_size, which stores the size of the chessboard (8x8 for this problem), and solution_count, which keeps track of the number of solutions found.

    //It checks whether it's safe to place a queen at a given position on the chessboard
    bool isSafe(vector<vector<int>>& board, int row, int col) {
        // Check if there is a queen in the same column
        for (int i = 0; i < row; ++i) {
            if (board[i][col] == 1)
                return false;
        }

        // Check upper left diagonal
        for (int i = row, j = col; i >= 0 && j >= 0; --i, --j) {
            if (board[i][j] == 1)
                return false;
        }

        // Check upper right diagonal
        for (int i = row, j = col; i >= 0 && j < board_size; --i, ++j) {
            if (board[i][j] == 1)
                return false;
        }

        return true;
    }
// It's a recursive backtracking function to find all solutions for the Eight Queens problem
    void solveQueens(vector<vector<int>>& board, int row) {
        // If all queens are placed successfully (reaching the last row), it prints the solution, increments the solution count, and returns.
        if (row == board_size) {
            printSolution(board);
            solution_count++;
            return;
        }
        // It iterates through each column in the current row and tries to place a queen. If it's safe to place a queen, it marks the position as occupied, moves to the next row recursively, and then backtracks if no solution is found.
        for (int col = 0; col < board_size; ++col) {
            if (isSafe(board, row, col)) {
                board[row][col] = 1;
                solveQueens(board, row + 1);
                board[row][col] = 0; // Backtrack
            }
        }
    }

// It prints the solution number and the chessboard configuration with '1' representing the queen's position and '0' representing an empty cell.

    void printSolution(vector<vector<int>>& board) {
        cout << "Solution " << solution_count + 1 << ":\n";
        for (const auto& row : board) {
            for (int cell : row) {
                cout << cell << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

// It initializes the chessboard and initiates the solving process by calling solveQueens.

public:
    void findSolutions() {
        vector<vector<int>> board(board_size, vector<int>(board_size, 0));
        solveQueens(board, 0);
    }
};

int main() {
    EightQueens eq;
    eq.findSolutions();
    return 0;
}
