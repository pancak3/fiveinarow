//
// Created by Qifan Deng on 2022/3/7.
//
#ifndef FIVEINAROW_GAME_H

#define FIVEINAROW_GAME_H

#include "stdio.h"
#include "stdlib.h"

#define BUFF_SIZE 256
#define HEIGHT 15
#define WIDTH 15
#define END_VALUE 5
#define NOT_OCCUPIED 0
#define WHITE -1
#define BLACK 1

#define TRUE 1
#define FALSE 0
#define STONE_B '@'
#define STONE_W '#'
#define BOARD '+'

int gBoard[HEIGHT][WIDTH];
int gLastRound;

void startGame();

int place(int stone, int row, int col);

void showBoard();

int placeAndShow(int stone, int row, int col);

void playerPlace(int *placedRow, int *placedCol);

int isGameEnd(int row, int col);

#endif //FIVEINAROW_GAME_H
