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
    int row = 0;
    int col = 0;
    while (1) {
        playerPlace(&row, &col);
        if (isGameEnd(row, col) == TRUE)
            break;
    }
    if (gLastRound == WHITE) {
        printf("[*] White stone won!\r\n");
    } else {
        printf("[*] Black stone won!\r\n");
    }
}

int place(int stone, int row, int col) {
    if (row >= HEIGHT) return FALSE;
    if (col >= WIDTH) return FALSE;
    if (gBoard[row][col] != 0) return FALSE;
    if (stone != WHITE && stone != BLACK) return FALSE;
    gBoard[row][col] = stone;
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

char position[BUFF_SIZE];

void playerPlace(int *placedRow, int *placedCol) {

    if (gLastRound == WHITE) {
        printf("[*] Black stone round, please place(%c): ", STONE_B);
    } else {
        printf("[*] White stone round, please place(%c): ", STONE_W);
    }
    scanf("%s", position);
    printf("\r\n");

    int col = position[0] - 'a';
    if (col < 0 || col > WIDTH) {
        printf("[!] Incorrect position.\r\n");
        return playerPlace(placedRow, placedCol);
    }
    int row = 0;
    if (position[2] - '0' >= 0) {
        row += position[2] - '0';
        row += 10 * (position[1] - '0');
    } else {
        row += position[1] - '0';
    }
    if (row < 0 || row > HEIGHT) {
        printf("[!] Incorrect position.\r\n");
        return playerPlace(placedRow, placedCol);
    }
    printf("[*] Placed at (%c, %d)\r\n", 'a' + col, row);
    row = HEIGHT - row;
    if (gLastRound == WHITE) {
        placeAndShow(BLACK, row, col);
    }
    placeAndShow(WHITE, row, col);
    *placedRow = row;
    *placedCol = col;

}

int abs(int value) {
    if (value < 0) {
        return -value;
    }
    return value;
}

int checkLeft(int row, int col) {
    int value = 0;
    if (col < END_VALUE - 1) return FALSE;
    for (int i = 0; i < END_VALUE; ++i) {
        value += gBoard[row][col - i];
    }
    if (abs(value) == END_VALUE) return TRUE;
    return FALSE;
}

int checkRight(int row, int col) {
    int value = 0;
    if (col >= WIDTH - END_VALUE) return FALSE;
    for (int i = 0; i < END_VALUE; ++i) {
        value += gBoard[row][col + i];
    }
    if (abs(value) == END_VALUE) return TRUE;
    return FALSE;
}

int checkUp(int row, int col) {
    int value = 0;
    if (row < END_VALUE - 1) return FALSE;
    for (int i = 0; i < END_VALUE; ++i) {
        value += gBoard[row - i][col];
    }
    if (abs(value) == END_VALUE) return TRUE;
    return FALSE;
}

int checkDown(int row, int col) {
    int value = 0;
    if (row > HEIGHT - END_VALUE) return FALSE;
    for (int i = 0; i < END_VALUE; ++i) {
        value += gBoard[row + i][col];
    }
    if (abs(value) == END_VALUE) return TRUE;
    return FALSE;
}


int checkUpRight(int row, int col) {
    int value = 0;
    if (row < END_VALUE - 1 || col >= WIDTH - END_VALUE)
        return FALSE;
    for (int i = 0; i < END_VALUE; ++i) {
        value += gBoard[row - i][col + i];
    }
    if (abs(value) == END_VALUE) return TRUE;
    return FALSE;
}

int checkUpLeft(int row, int col) {
    int value = 0;
    if (row < END_VALUE - 1 || col < END_VALUE - 1) return FALSE;
    for (int i = 0; i < END_VALUE; ++i) {
        value += gBoard[row - i][col - i];
    }
    if (abs(value) == END_VALUE) return TRUE;
    return FALSE;
}

int checkDownLeft(int row, int col) {
    int value = 0;
    if (row >= HEIGHT - END_VALUE || col < END_VALUE - 1)
        return
                FALSE;
    for (int i = 0; i < END_VALUE; ++i) {
        value += gBoard[row + i][col - i];
    }
    if (abs(value) == END_VALUE) return TRUE;
    return FALSE;
}

int checkDownRight(int row, int col) {
    int value = 0;
    if (row >= HEIGHT - END_VALUE || col >= WIDTH - END_VALUE)
        return FALSE;
    for (int i = 0; i < END_VALUE; ++i) {
        value += gBoard[row + i][col + i];
    }
    if (abs(value) == END_VALUE) return TRUE;
    return FALSE;
}

int isGameEnd(int row, int col) {
    if (checkUp(row, col)) {
        return TRUE;
    }
    if (checkDown(row, col)) {
        return TRUE;
    }
    if (checkLeft(row, col)) {
        return TRUE;
    }
    if (checkRight(row, col)) {
        return TRUE;
    }
    if (checkUpRight(row, col)) {
        return TRUE;
    }
    if (checkUpLeft(row, col)) {
        return TRUE;
    }
    if (checkDownLeft(row, col)) {
        return TRUE;
    }
    if (checkDownRight(row, col)) {
        return TRUE;
    }
    return FALSE;
}