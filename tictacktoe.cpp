
#include <iostream>
#include <limits>
using namespace std;

char board[9] = {'1','2','3','4','5','6','7','8','9'};

// All possible winning combinations
int wins[8][3] = {
    {0,1,2}, {3,4,5}, {6,7,8},
    {0,3,6}, {1,4,7}, {2,5,8},
    {0,4,8}, {2,4,6}
};

void displayBoard() {
    cout << "\n";
    cout << " " << board[0] << " | " << board[1] << " | " << board[2] << "\n";
    cout << "---+---+---\n";
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << "\n";
    cout << "---+---+---\n";
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << "\n\n";
}

char checkWinner() {
    for (int i = 0; i < 8; i++) {
        if (board[wins[i][0]] == board[wins[i][1]] &&
            board[wins[i][1]] == board[wins[i][2]]) {
            return board[wins[i][0]];
        }
    }

    return ' ';
}

bool isDraw() {
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O')
            return false;
    }
    return true;
}

// Minimax: predicts the best possible outcome
int minimax(bool computerTurn) {
    char winner = checkWinner();

    if (winner == 'O') return 10;
    if (winner == 'X') return -10;
    if (isDraw()) return 0;

    if (computerTurn) {
        int bestScore = numeric_limits<int>::min();

        for (int i = 0; i < 9; i++) {
            if (board[i] != 'X' && board[i] != 'O') {
                char old = board[i];
                board[i] = 'O';

                int score = minimax(false);
                board[i] = old;

                if (score > bestScore)
                    bestScore = score;
            }
        }

        return bestScore;
    } else {
        int bestScore = numeric_limits<int>::max();

        for (int i = 0; i < 9; i++) {
            if (board[i] != 'X' && board[i] != 'O') {
                char old = board[i];
                board[i] = 'X';

                int score = minimax(true);
                board[i] = old;

                if (score < bestScore)
                    bestScore = score;
            }
        }

        return bestScore;
    }
}

// Find the computer's best move
int computerMove() {
    int bestScore = numeric_limits<int>::min();
    int bestMove = -1;

    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            char old = board[i];
            board[i] = 'O';

            int score = minimax(false);
            board[i] = old;

            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }

    return bestMove;
}

int main() {
    cout << "=== UNBEATABLE TIC-TAC-TOE ===\n";
    cout << "You are X. Computer is O.\n";
    cout << "Choose a position from 1 to 9.\n";

    while (true) {
        displayBoard();

        // Human player's turn
        int move;
        cout << "Your move (1-9): ";

        if (!(cin >> move)) {
            cout << "Please enter a number!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (move < 1 || move > 9 ||
            board[move - 1] == 'X' || board[move - 1] == 'O') {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        board[move - 1] = 'X';

        if (checkWinner() == 'X') {
            displayBoard();
            cout << "You win! (This should not happen against perfect AI.)\n";
            break;
        }

        if (isDraw()) {
            displayBoard();
            cout << "It's a draw!\n";
            break;
        }

        // Computer's turn
        int aiMove = computerMove();
        board[aiMove] = 'O';

        cout << "Computer chooses position " << aiMove + 1 << ".\n";

        if (checkWinner() == 'O') {
            displayBoard();
            cout << "Computer wins! Better luck next time.\n";
            break;
        }

        if (isDraw()) {
            displayBoard();
            cout << "It's a draw! Nobody wins.\n";
            break;
        }
    }

    return 0;
}
