//
// Created by Qifan Deng on 2022/3/7.
//
#include "stdio.h"

#ifndef FIVEINAROW_GAME_H
#define FIVEINAROW_GAME_H

#define HEIGHT 15
#define WIDTH 15

#define NOT_OCCUPIED 0
#define WHITE -1
#define BLACK 1

#define TRUE 0
#define FALSE 1
#define STONE_B '@'
#define STONE_W '#'
#define BOARD '+'
int gBoard[HEIGHT][WIDTH];
int gLastRound;

void startGame();

int place(int stone, int row, int col);

void showBoard();

int placeAndShow(int stone, int row, int col);

void playerPlace();

#endif //FIVEINAROW_GAME_H
