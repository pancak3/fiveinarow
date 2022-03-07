#include "game.h"


void initBoard() {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            gBoard[i][j] = NOT_OCCUPIED;
        }
    }
    gLastRound = WHITE;
}

void startGame() {
    initBoard();
    printf("[*] Game started.\r\n");
    showBoard();
    while (1) {
        playerPlace();
    }
}

int place(int stone, int row, int col) {
    if (row >= HEIGHT) return FALSE;
    if (col >= WIDTH) return FALSE;
    if (gBoard[row][col] != 0) return FALSE;
    if (stone != WHITE && stone != BLACK) return FALSE;
    gBoard[row][col] = stone;
    printf("[*] Placed %d at (%d, %d)\r\n", stone, row, col);
    if (gLastRound == WHITE) gLastRound = BLACK;
    else gLastRound = WHITE;
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
                printf(" %c ", BOARD);
                continue;
            }
            if (gBoard[row][col] == BLACK) {
                printf(" %c ", STONE_B);
                continue;
            }
            if (gBoard[row][col] == WHITE) {
                printf(" %c ", STONE_W);
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

void playerPlace() {
    char position[3];
    if (gLastRound == WHITE) {
        printf("[*] Black stone round, please place(%c): ", STONE_B);
    } else {
        printf("[*] White stone round, please place(%c): ", STONE_W);
    }
    scanf("%s", position);

    int col = position[0] - 'a';
    if (col < 0 || col >= WIDTH) {
        printf("[!] Incorrect position.\r\n");
        return playerPlace();
    }
    int row = 0;
    if (position[2] - '0' >= 0) {
        row += position[2] - '0';
        row += 10 * (position[2] - '0');
    } else {
        row += position[1] - '0';
    }
    if (row < 0 || row >= HEIGHT) {
        printf("[!] Incorrect position.\r\n");
        return playerPlace();
    }
    row = HEIGHT - row;
    if (gLastRound == WHITE) {
        placeAndShow(BLACK, row, col);
    }
    placeAndShow(WHITE, row, col);
}