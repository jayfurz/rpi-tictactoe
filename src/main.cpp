#include <iostream>

const int ROWS = 3;
const int COLUMNS = 3;

char board[ROWS][COLUMNS];

void initializeBoard() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            board[i][j] = '-';
        }
    }
}

int main() {
    initializeBoard();
    return 0;
}