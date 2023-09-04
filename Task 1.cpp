#include <iostream>
#include <vector>
using namespace std;
const int BOARD_SIZE = 3;
// Define the Tic-Tac-Toe board
vector<vector<char>> board(BOARD_SIZE, vector<char>(BOARD_SIZE, ' '));
// Define the winning combinations
const vector<vector<int>> winning_combinations = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
    {0, 4, 8}, {2, 4, 6}             // Diagonals
};
// Function to print the Tic-Tac-Toe board
void printBoard() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            cout << board[i][j];
            if (j < BOARD_SIZE - 1)
                cout << " | ";
        }
        cout << endl;
        if (i < BOARD_SIZE - 1)
            cout << "---------" << endl;
    }
    cout << endl;
}
// Function to check if the board is full
bool isBoardFull() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}
// Function to check if the game is over
bool isGameOver() {
    for (const vector<int>& combo : winning_combinations) {
        char a = board[combo[0] / BOARD_SIZE][combo[0] % BOARD_SIZE];
        char b = board[combo[1] / BOARD_SIZE][combo[1] % BOARD_SIZE];
        char c = board[combo[2] / BOARD_SIZE][combo[2] % BOARD_SIZE];
        if (a != ' ' && a == b && b == c)
            return true;
    }
    return isBoardFull();
}
// Function to evaluate the board for the Minimax algorithm
int evaluateBoard() {
    for (const vector<int>& combo : winning_combinations) {
        char a = board[combo[0] / BOARD_SIZE][combo[0] % BOARD_SIZE];
        char b = board[combo[1] / BOARD_SIZE][combo[1] % BOARD_SIZE];
        char c = board[combo[2] / BOARD_SIZE][combo[2] % BOARD_SIZE];
        if (a == 'X' && b == 'X' && c == 'X')
            return 1; // AI wins
        else if (a == 'O' && b == 'O' && c == 'O')
            return -1; // Human wins
    }
    return 0; // It's a draw
}
// Minimax algorithm with Alpha-Beta Pruning
pair<int, int> minimax(int depth, bool isMaximizing, int alpha, int beta) {
    if (isGameOver()) {
        int score = evaluateBoard();
        return { score, -1 };
    }
    int bestScore = isMaximizing ? -INT_MAX : INT_MAX;
    pair<int, int> bestMove = { -1, -1 };

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == ' ') {
                char currentPlayer = isMaximizing ? 'X' : 'O';
                board[i][j] = currentPlayer;
                int score = minimax(depth + 1, !isMaximizing, alpha, beta).first;
                board[i][j] = ' ';

                if (isMaximizing) {
                    if (score > bestScore) {
                        bestScore = score;
                        bestMove = { i, j };
                        alpha = max(alpha, score);
                    }
                }
                else {
                    if (score < bestScore) {
                        bestScore = score;
                        bestMove = { i, j };
                        beta = min(beta, score);
                    }
                }

                if (beta <= alpha)
                    break;
            }
        }
    }

    return bestMove;
}

int main() {
    cout << "Welcome to Tic-Tac-Toe!" << endl;
    cout << "You are 'O', and the AI is 'X'." << endl;
    cout << "The board positions are numbered from 0 to 8 as follows:" << endl;
    cout << "0 | 1 | 2" << endl;
    cout << "---------" << endl;
    cout << "3 | 4 | 5" << endl;
    cout << "---------" << endl;
    cout << "6 | 7 | 8" << endl;

    bool humanTurn = true; // true for human, false for AI

    while (!isGameOver()) {
        if (humanTurn) {
            cout << "Your turn. Enter your move (0-8): ";
            int move;
            cin >> move;

            if (move < 0 || move >= BOARD_SIZE * BOARD_SIZE || board[move / BOARD_SIZE][move % BOARD_SIZE] != ' ') {
                cout << "Invalid move. Try again." << endl;
                continue;
            }

            board[move / BOARD_SIZE][move % BOARD_SIZE] = 'O';
        }
        else {
            cout << "AI's turn:" << endl;
            pair<int, int> bestMove = minimax(0, true, -INT_MAX, INT_MAX);
            board[bestMove.first][bestMove.second] = 'X';
            cout << "AI placed 'X' at position " << bestMove.first * BOARD_SIZE + bestMove.second << endl;
        }

        printBoard();
        humanTurn = !humanTurn;
    }

    if (evaluateBoard() == 1)
        cout << "AI wins!" << endl;
    else if (evaluateBoard() == -1)
        cout << "You win!" << endl;
    else
        cout << "It's a draw!" << endl;

    return 0;
}
