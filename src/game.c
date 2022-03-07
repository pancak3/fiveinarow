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
        printf("%2d", row);
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
        printf("%d\r\n", row);

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

    int row = position[0] - 'a';
    if (row < 0 || row > WIDTH) {
        printf("[!] Incorrect position.\r\n");
        return playerPlace(placedRow, placedCol);
    }
    int col = 0;
    if (position[2] - '0' >= 0) {
        col += position[2] - '0';
        col += 10 * (position[1] - '0');
    } else {
        col += position[1] - '0';
    }
    if (col < 0 || col > HEIGHT) {
        printf("[!] Incorrect position.\r\n");
        return playerPlace(placedRow, placedCol);
    }
    printf("[*] Placed at (%c, %d)\r\n", 'a' + row, col);
    if (gLastRound == WHITE) {
        placeAndShow(BLACK, col, row);
    }
    placeAndShow(WHITE, col, row);
    *placedRow = col;
    *placedCol = row;
}

int abs(int value) {
    if (value < 0) {
        return -value;
    }
    return value;
}

int checkVertical(int row, int col) {
    int stone = gBoard[row][col];
    int offset = 0;
    for (; offset < END_VALUE - 1 && row > 0; ++offset) {
        --row;
    }
    for (int i = 0, count = 0; i < END_VALUE + offset && row + i < HEIGHT;
         ++i) {
        if (stone == gBoard[row + i][col]) ++count;
        if (i < END_VALUE) continue;
        if (count == END_VALUE) return TRUE;
        if (stone == gBoard[row + i - END_VALUE][col]) --count;
    }
    return FALSE;
}

int checkHorizon(int row, int col) {
    int stone = gBoard[row][col];
    int offset = 0;
    for (; offset < END_VALUE && col > 0; ++offset) {
        --col;
    }
    for (int i = 0, count = 0; i < END_VALUE + offset && col + i < WIDTH; ++i) {
        if (stone == gBoard[row][col + i]) ++count;
        if (i < END_VALUE) continue;
        if (count == END_VALUE) return TRUE;
        if (stone == gBoard[row][col + i - END_VALUE]) --count;
    }
    return FALSE;
}

int checkRightOblique(int row, int col) {
    int stone = gBoard[row][col];
    int offset = 0;
    for (; offset < END_VALUE && row > 0 && col > 0; ++offset) {
        --row;
        --col;
    }
    for (int i = 0, count = 0;
         i < END_VALUE + offset && row + i < HEIGHT && col + i < WIDTH;
         ++i) {
        if (stone == gBoard[row + i][col + i]) ++count;
        if (i < END_VALUE) continue;
        if (count == END_VALUE) return TRUE;
        if (stone == gBoard[row + i - END_VALUE][col + i - END_VALUE]) --count;
    }
    return FALSE;
}

int checkLeftOblique(int row, int col) {
    int stone = gBoard[row][col];
    int offset = 0;
    for (; offset < END_VALUE && row > 0 && col < HEIGHT; ++offset) {
        ++row;
        --col;
    }
    for (int i = 0, count = 0;
         i < END_VALUE + offset && row + i < HEIGHT && col > 0;
         ++i) {
        if (stone == gBoard[row + i][col - i]) ++count;
        if (i < END_VALUE) continue;
        if (count == END_VALUE) return TRUE;
        if (stone == gBoard[row + i - END_VALUE][col - i + END_VALUE]) --count;
    }
    return FALSE;
}

int isGameEnd(int row, int col) {
    if (checkHorizon(row, col)) {
        return TRUE;
    }
    if (checkVertical(row, col)) {
        return TRUE;
    }
    if (checkRightOblique(row, col)) {
        return TRUE;
    }
    if (checkLeftOblique(row, col)) {
        return TRUE;
    }
    return FALSE;
}