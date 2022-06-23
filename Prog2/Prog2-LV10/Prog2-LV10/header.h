#ifndef HEADER_H
#define HEADER_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>

void task1(void);
int task1FindSumOfDigits(int);
void task2(void);
int* task2AllocateArr(int);
void task2GenerateArr(int*, int, int, int);
int task2FindBiggestInArr(int*, int, int);
void task2PrintBiggest(int);
void task3(void);
char* task3AllocateArr(int);
void task3GetString(char*);
void task3PrintString(char*);
void task3ReverseString(char*, FILE*);

#endif