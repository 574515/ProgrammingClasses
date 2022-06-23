#ifndef HEADER_H
#define HEADER_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

typedef struct trokTocka {
	float x, y;
}TTOCKA;

typedef struct trokut {
	double firstSide, secondSide, thirdSide, perimeter;
	TTOCKA t1, t2, t3;
}TROKUT;

typedef struct artikl {
	char name[31];
	float price;
	int quantity;
}ARTIKL;

typedef struct tocka {
	float x, y, z;
}TOCKA;

void task1(void);
void task1EnterTriangle(TROKUT*, int);
void task1GetSides(TROKUT*, int);
int task1FindBiggestPerimeter(TROKUT*, int);
void task2(void);
void task3(void);

#endif