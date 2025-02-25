#include <iostream>
#include <vector>
#include <limits>

using namespace std;

void initializeBoard(vector<vector<char>>& board) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            board[i][j] = ' ';
        }
    }
}

void printBoard(const vector<vector<char>>& board) {
    cout << "  0 1 2 3\n";
    for (int i = 0; i < 4; ++i) {
        cout << i << " ";
        for (int j = 0; j < 4; ++j) {
            cout << board[i][j];
            if (j < 3) cout << "|";
        }
        cout << "\n";
        if (i < 3) cout << "  -+-+-+-\n";
    }
}

bool isWinner(const vector<vector<char>>& board, char player) {
    // Check rows and columns
    for (int i = 0; i < 4; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player && board[i][3] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player && board[3][i] == player)) {
            return true;
        }
    }
    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player && board[3][3] == player) ||
        (board[0][3] == player && board[1][2] == player && board[2][1] == player && board[3][0] == player)) {
        return true;
    }
    return false;
}

bool isBoardFull(const vector<vector<char>>& board) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] == ' ') return false;
        }
    }
    return true;
}

void playTicTacToe() {
    vector<vector<char>> board(4, vector<char>(4));
    char currentPlayer = 'X';
    bool gameEnded = false;
    int xWins = 0, oWins = 0, ties = 0;

    while (true) {
        initializeBoard(board);
        gameEnded = false;

        while (!gameEnded) {
            printBoard(board);
            int row, col;
            cout << "Player " << currentPlayer << ", enter your move (row and column): ";
            cin >> row >> col;

            if (row >= 0 && row < 4 && col >= 0 && col < 4 && board[row][col] == ' ') {
                board[row][col] = currentPlayer;
                if (isWinner(board, currentPlayer)) {
                    printBoard(board);
                    cout << "Player " << currentPlayer << " wins!\n";
                    if (currentPlayer == 'X') xWins++;
                    else oWins++;
                    gameEnded = true;
                } else if (isBoardFull(board)) {
                    printBoard(board);
                    cout << "The game is a tie!\n";
                    ties++;
                    gameEnded = true;
                } else {
                    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                }
            } else {
                cout << "Invalid move. Try again.\n";
            }
        }

        cout << "Score: Player X - " << xWins << ", Player O - " << oWins << ", Ties - " << ties << "\n";
        cout << "Do you want to play again? (y/n): ";
        char playAgain;
        cin >> playAgain;
        if (playAgain != 'y') break;
    }
}

int main() {
    playTicTacToe();
    return 0;
}
