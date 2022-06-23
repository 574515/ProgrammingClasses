#ifndef HEADER_H
#define HEADER_H
#define _CRT_SECURE_NO_WARNINGS
#define RED "\033[0;31m"
#define BLU "\033[0;34m"
#define YLW "\033[0;33m"
#define ESC "\033[0m"
#define N 9
#include <stdbool.h>

char board[N];

void checkWinner(void);
void computerMove(void);
void intro(void);
bool isFull(void);
bool isTaken(int);
bool oWin(void);
void play(void);
void playerMove(void);
void printBoard(void);
void printEnd(char);
bool xWin(void);

#endif // HEADER_H