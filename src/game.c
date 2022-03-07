#include "game.h"


void initBoard() {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            gBoard[i][j] = NOT_OCCUPIED;
        }
    }
}

void startGame() {
    initBoard();
    printf("[*] Game started.\r\n");
    showBoard();
    placeAndShow(1, 7, 7);
}

int place(int stone, int row, int col) {
    if (row >= HEIGHT) return FALSE;
    if (col >= WIDTH) return FALSE;
    if (gBoard[row][col] != 0) return FALSE;
    if (stone != WHITE && stone != BLACK) return FALSE;
    gBoard[row][col] = stone;
    printf("[*] Placed %d at (%d, %d)\r\n", stone, row, col);
    return TRUE;
}

void printHeaderOrFooter() {
    printf("  ");
    for (int i = 0; i < WIDTH; ++i) {
        printf(" %c ", 'a' + i);
    }
    printf("\r\n");

}

void showBoard() {
    printHeaderOrFooter();
    for (int row = 0; row < HEIGHT; ++row) {
        printf("%2d", HEIGHT - row);
        for (int col = 0; col < WIDTH; ++col) {
            if (gBoard[row][col] == NOT_OCCUPIED) {
                printf(" + ");
                continue;
            }
            if (gBoard[row][col] == BLACK) {
                printf(" @ ");
                continue;
            }
            if (gBoard[row][col] == WHITE) {
                printf(" # ");
                continue;
            }
        }
        printf("%d\r\n", HEIGHT - row);

    }
    printHeaderOrFooter();
}

int placeAndShow(int stone, int row, int col) {
    int ret = place(stone, row, col);
    if (ret == TRUE) {
        showBoard();
        return ret;
    }
    return ret;
}
