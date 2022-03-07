#include "game.h"


void initBoard() {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            gBoard[i][j] = 0;
        }
    }
}

void startGame() {
    initBoard();
    printf("[*] Game started.");
}