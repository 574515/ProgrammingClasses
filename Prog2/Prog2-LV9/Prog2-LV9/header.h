#ifndef HEADER_H
#define HEADER_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

void task1(void);
void task1And2FillArray(int*);
void task1And2WriteToFile(int*);
int* task1And2ReadFromFile(int*);
int task1And2SeqSearch(int*, int);
void task2(void);
void task2GetSearchNumbers(int*);
void task2BubbleSort(int*);
void task2Swap(int* const, int* const);
int task2BinSearch(int*, int);
void task2PrintResult(int*, int*);

#endif