#ifndef HEADER_H
#define HEADER_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>

void task1(void);
void task1EnterStudents(int);
void task2(void);
float** task2AllocateArr(int, int);
void task2GenerateArr(float**, int, int);
void task2PrintAndSaveArr(float**, int, int);
void task2DeallocateArr(float**, int);
void task3(void);
void task3CopyFile(FILE*);

#endif