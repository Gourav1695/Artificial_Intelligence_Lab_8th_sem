#include <bits/stdc++.h>

using namespace std;


//Defines a structure Game to hold the game state, including the game board and a move table.
//board is a vector representing the Tic-Tac-Toe board, initially filled with zeros.
//moveTable is a vector to store pre-calculated moves for each possible board configuration.
//The constructor initializes the board vector with 9 zeros (representing an empty board) and initializes the moveTable vector with a size of 19683, which is 3 to the power of 9, representing all possible combinations of X, O, and empty squares on the board.
struct Game {
    vector<int> board;   
    vector<int> moveTable;

    Game() : board(9, 0), moveTable(19683) {} // 3^9 = 19683
};

// Function to convert ternary number to decimal
int ternaryToDecimal(vector<int>& ternary) {
    int decimal = 0;
    int power = 0;
    
    // Iterate through the ternary vector from right to left
    for (int i = ternary.size() - 1; i >= 0; i--) {
        decimal += ternary[i] * pow(3, power);
        power++;
    }
    
    return decimal;
}
// decimalToTernary:

//This function converts a decimal number to its ternary representation. In the context of the Tic-Tac-Toe game, the decimal number represents the index of a particular board state in the move table. Each index corresponds to a unique board state.
//For example, if we have a board state represented by a decimal number 14, decimalToTernary(14) would return a ternary vector representing the board state.

// used to efficiently access and update the move table, which stores precalculated moves for the Tic-Tac-Toe game.
// Function to convert decimal number to ternary

vector<int> decimalToTernary(int decimal) {
    vector<int> ternary(9, 0); // Initialize ternary vector with zeros
    
    // Convert decimal to ternary
    int index = ternary.size() - 1;
    while (decimal > 0 && index >= 0) {
        ternary[index] = decimal % 3;
        decimal /= 3;
        index--;
    }
    
    return ternary;
}

const int EMPTY = 0;
const int X = 1;
const int O = 2;
const int BOARD_SIZE = 9;


// Check Rows:

//It iterates over the rows of the board.
//For each row, it checks if all three elements are equal (i.e., if the row is filled with either all X's or all O's).
//If all three elements are X's, it returns a score of 10, indicating that X has won.
//If all three elements are O's, it returns a score of -10, indicating that O has won.
//Check Columns:

//It iterates over the columns of the board.
//For each column, it checks if all three elements in that column are equal.
//Same as for rows, if all elements are X's, it returns 10, and if all elements are O's, it returns -10.
//Check Diagonals:

//It checks the two diagonals of the board.
//If either diagonal has all X's, it returns 10.
//If either diagonal has all O's, it returns -10.
//No Winner:

//If none of the above conditions are met, it means there is no winner, so it returns 0.

int evaluate(const vector<int>& board) {
    // Check rows
    for (int i = 0; i < 3; ++i) {
        if (board[i * 3] == board[i * 3 + 1] && board[i * 3 + 1] == board[i * 3 + 2]) {
            if 
            
            
            
            (board[i * 3] == X) return 10;
            else if (board[i * 3] == O) return -10;
        }
    }
    
    // Check columns
    for (int i = 0; i < 3; ++i) {
        if (board[i] == board[i + 3] && board[i + 3] == board[i + 6]) {
            if (board[i] == X) return 10;
            else if (board[i] == O) return -10;
        }
    }
    
    // Check diagonals
    if ((board[0] == board[4] && board[4] == board[8]) || (board[2] == board[4] && board[4] == board[6])) {
        if (board[4] == X) return 10;
        else if (board[4] == O) return -10;
    }
    
    // No winner
    return 0;
}


// function isMovesLeft to check if there are any remaining moves available on the board.
bool isMovesLeft(const vector<int>& board) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (board[i] == EMPTY) return true;
    }
    return false;
}

int minimax(vector<int>& board, int player) {
    // Initialization:

    //starts by evaluating the current state of the board using the evaluate function, which returns a score indicating if there's a winner or a draw.
    //If the score is 10 or -10 (indicating a win for X or O respectively), it returns the score directly.
    //If there's no winner and the board is not full, it proceeds to the next steps.
    int score = evaluate(board);
    if (score == 10 || score == -10) return score;
    if (!isMovesLeft(board)) return 0;
    
    //Recursive Minimax:

    //If it's X's turn (player == X), it initializes the best score to a very low value (-1000).
    //It then iterates over all possible moves (empty cells) on the board.
    //For each empty cell, it temporarily assigns X to that cell, simulating the move.
    //It then recursively calls minimax with the opponent's turn (O), and retrieves the score of that move.
    //The best score is updated to the maximum of the current best and the score obtained from the recursive call.
    //After simulating all possible moves, it reverts the board to its original state and returns the best score.
    if (player == X) {
        int best = -1000;
        for (int i = 0; i < BOARD_SIZE; ++i) {
            if (board[i] == EMPTY) {
                board[i] = X;
                best = max(best, minimax(board, O));
                board[i] = EMPTY;
            }
        }
        return best;
    } else {
    // Similarly, if it's O's turn (player == O), it initializes the best score to a very high value (1000).
    //It then iterates over all possible moves on the board, simulating each move for O.
    //Instead of updating the best score to the maximum, it updates it to the minimum of the current best and the score obtained from the recursive call.
    //This process of recursively exploring possible moves and updating the best score continues until all possible moves are explored.
        int best = 1000;
        for (int i = 0; i < BOARD_SIZE; ++i) {
            if (board[i] == EMPTY) {
                board[i] = O;
                best = min(best, minimax(board, X));
                board[i] = EMPTY;
            }
        }
        return best;
    }
}


// This findBestMove function is responsible for finding the best move for a given player on the Tic-Tac-Toe board using the Minimax algorithm. Here's a breakdown of each part:

//Function Overview:

//The function takes two parameters: board, which represents the current state of the Tic-Tac-Toe board, and player, which specifies which player's turn it is (1 for X, 2 for O).
//It returns the index of the best move for the given player.
//Initialization:

//If it's X's turn (player == 1), it initializes bestVal to a very low value (-1000) and bestMove to -1.
//If it's O's turn (player == 2), it initializes bestVal to a very high value (1000) and bestMove to -1.
//Iterating Over Possible Moves:

//The function iterates through each cell of the board.
//For each empty cell (where board[i] == EMPTY), it simulates placing the current player's symbol (X or O) in that cell.
//It then calls the minimax function with the opponent's turn (3 - player), which calculates the score for the opponent's best move from the current board state.
//After obtaining the score (moveVal), it restores the board to its original state by setting the cell back to empty.
//For X, it updates bestVal and bestMove if the current move's score (moveVal) is greater than bestVal.
//For O, it updates bestVal and bestMove if the current move's score (moveVal) is less than bestVal.
//Returning the Best Move:

//After iterating through all possible moves, it returns bestMove, which represents the index of the cell where the current player should make their move to maximize their chances of winning.

int findBestMove(vector<int>& board, int player) {
    if(player == 1){
    int bestVal = -1000;
    int bestMove = -1;
    
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (board[i] == EMPTY) {
            board[i] = player;
            int moveVal = minimax(board, 3 - player); // Opponent's turn
            board[i] = EMPTY;
            
            if (moveVal > bestVal) {
                bestMove = i;
                bestVal = moveVal;
            }
        }
    }
    
    return bestMove;
    } else{
        int bestVal = 1000;
        int bestMove = -1;
        
        for (int i = 0; i < BOARD_SIZE; ++i) {
            if (board[i] == EMPTY) {
                board[i] = player;
                int moveVal = minimax(board, 3 - player); // Opponent's turn
                board[i] = EMPTY;
                
                if (moveVal < bestVal) {
                    bestMove = i;
                    bestVal = moveVal;
                }
            }
        }
        
        return bestMove;
    }
}


// preCalculate function recursively generates all possible game states from the current state of the board and stores the best moves for each player in the moveTable of the game object.

void preCalculate(Game& game, vector<int> board){
    // game: A reference to the Game object where the precalculated moves will be stored.
    // board: A vector representing the current state of the game board.
    if(!isMovesLeft(board)) return; // checks if there are any remaining moves left on the board. If there are no remaining moves, the function returns, as there is no need to calculate further moves.

    int tot1=0, tot2=0;
    for(int i=0; i<BOARD_SIZE; i++){
        if(board[i]==1) tot1++;
        else if(board[i]==2) tot2++;
    } // This loop counts the number of occurrences of player X (represented by 1) and player O (represented by 2) on the board.

    if(tot1==tot2){
        int move = findBestMove(board, 1);
        vector<int> newBoard(9);
        for(int i=0; i<9; i++){
            newBoard[i]=board[i];
        }
        newBoard[move]=1;
        game.moveTable[ternaryToDecimal(board)]=ternaryToDecimal(newBoard);
        for(int i=0; i<BOARD_SIZE; i++){
            if(board[i]==EMPTY){
                board[i]=1;
                preCalculate(game, board);
                board[i]=EMPTY;
            }
        } // If the number of occurrences of player X and player O on the board are equal (tot1 == tot2), it means it's currently player X's turn to make a move. 
        //The function then finds the best move for player X using the findBestMove function, which returns the index of the best move for player X. 
        //It then creates a new board configuration newBoard where player X makes the calculated move.
        // The ternaryToDecimal function is used to convert the board configurations from ternary to decimal representation, which is used as an index to store the moves in the moveTable of the game object.
        // After storing the move, the function recursively calls itself for each empty cell on the board with player X's move made on that cell.
    } else if(tot1>tot2){
        int move = findBestMove(board, 2);

        vector<int> newBoard(9);
        for(int i=0; i<9; i++){
            newBoard[i]=board[i];
        }
        newBoard[move]=2;
        game.moveTable[ternaryToDecimal(board)]=ternaryToDecimal(newBoard);
        for(int i=0; i<BOARD_SIZE; i++){
            if(board[i]==EMPTY){
                board[i]=2;
                preCalculate(game, board);
                board[i]=EMPTY;
            }
        }
    } // If there are more occurrences of player X (tot1 > tot2), it means it's player O's turn to make a move.
    // This code is similar to the previous one, except that it calculates the best move for player O using the findBestMove function and updates the newBoard accordingly with player O's move.
}

int main() {
    Game game;

    preCalculate(game, game.board);

    cout << "Do you want to play as X or O. X plays first: ";
    char c;
    cin >> c;

    cout << "You will play as " << c << " & computer will play as " << (c=='X' ? "O" : "X") << ".\n"; 

    if(c=='O'){
        while(true){
            int player = 1; // Player X's turn
            int score = evaluate(game.board);

            if(score==10){
                cout << "Computer won!\n";
                break;
            } else if(score==-10){
                cout << "You won!\n";
                break;
            }

            if(!isMovesLeft(game.board)){
                cout << "Draw!\n";
                break;
            }

            vector<int> newBoard = decimalToTernary(game.moveTable[ternaryToDecimal(game.board)]);
            
            for(int i=0; i<BOARD_SIZE; i++){
                game.board[i]=newBoard[i];
            }
            
            // Output the updated board
            cout << "Updated Board: \n";
            for (int i = 0; i < BOARD_SIZE; ++i) {
                cout << (game.board[i] == 0 ? "." : game.board[i]==1 ? "X" : "O") << " ";
                if ((i + 1) % 3 == 0) cout << endl;
            }

            score = evaluate(game.board);

            if(score==10){
                cout << "Computer won!\n";
                break;
            } else if(score==-10){
                cout << "You won!\n";
                break;
            }

            if(!isMovesLeft(game.board)){
                cout << "Draw!\n";
                break;
            }

            player = 3-player;

            int move;
            while(true){
                cout << "Enter your move![1-9]\n";
                cin >> move;
                if(move<1 || move>9 || game.board[move-1]!=0){
                    cout << "Invalid move!\n";
                } else break;
            }
            game.board[move-1]=player;
            // Output the updated board
            cout << "Updated Board: \n";
            for (int i = 0; i < BOARD_SIZE; ++i) {
                cout << (game.board[i] == 0 ? "." : game.board[i]==1 ? "X" : "O") << " ";
                if ((i + 1) % 3 == 0) cout << endl;
            }
        }
    } else{
        while(true){
            int player = 1; // Player X's turn
            int score = evaluate(game.board);

            if(score==10){
                cout << "You won!\n";
                break;
            } else if(score==-10){
                cout << "Computer won!\n";
                break;
            }

            if(!isMovesLeft(game.board)){
                cout << "Draw!\n";
                break;
            }

            int move;
            while(true){
                cout << "Enter your move![1-9]\n";
                cin >> move;
                if(move<1 || move>9 || game.board[move-1]!=0){
                    cout << "Invalid move!\n";
                } else break;
            }
            game.board[move-1]=player;
            // Output the updated board
            cout << "Updated Board: \n";
            for (int i = 0; i < BOARD_SIZE; ++i) {
                cout << (game.board[i] == 0 ? "." : game.board[i]==1 ? "X" : "O") << " ";
                if ((i + 1) % 3 == 0) cout << endl;
            }

            player = 3-player;

            if(score==10){
                cout << "You won!\n";
                break;
            } else if(score==-10){
                cout << "computer won!\n";
                break;
            }

            if(!isMovesLeft(game.board)){
                cout << "Draw!\n";
                break;
            }

            vector<int> newBoard = decimalToTernary(game.moveTable[ternaryToDecimal(game.board)]);
            
            for(int i=0; i<BOARD_SIZE; i++){
                game.board[i]=newBoard[i];
            }
            
            // Output the updated board
            cout << "Updated Board: \n";
            for (int i = 0; i < BOARD_SIZE; ++i) {
                cout << (game.board[i] == 0 ? "." : game.board[i]==1 ? "X" : "O") << " ";
                if ((i + 1) % 3 == 0) cout << endl;
            }

            score = evaluate(game.board);
        }
    }

    return 0;
}
