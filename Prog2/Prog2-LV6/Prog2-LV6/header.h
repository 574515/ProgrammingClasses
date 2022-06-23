#ifndef HEADER_H
#define HEADER_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>

typedef struct tocka {
	int x, y;
} TOCKA;

typedef struct trokut {
	TOCKA* t1, * t2, * t3;
} TROKUT;

typedef struct artikl {
	char itemName[41];
	float price;
	int quantity;
} ARTIKL;

void task1(void);
int* task1EnterLength(void);
TOCKA* task1AllocateVertices(int);
TROKUT* task1AllocateTriangles(int);
void task1FillCoordinates(TOCKA*, int);
void task1SelectVertices(TOCKA*, TROKUT*, int, int);
double task1SidesLength(TOCKA, TOCKA);
int task1FindBiggestPerimeter(TROKUT*, int);
void task1PrintBiggestTriangle(TROKUT*, int, int);
void task2(void);
int task2GetLength(void);
ARTIKL* task2CreateArticles(int);
void task2InputArticles(ARTIKL*, int);
ARTIKL task2FindMostExpesniveArticle(ARTIKL*, int);
void task2PrintArticle(ARTIKL);

#endif