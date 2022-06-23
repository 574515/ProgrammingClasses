#ifndef HEADER_H
#define HEADER_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

typedef struct kompleks {
	float realni, imaginarni;
} k;

// functionsOneToTen.c
void task1(void);
int task1FindFirst(int);
int task1FindMiddle(int);
void task2(void);
void task3(void);
void task4(void);
void task5(void);
void task6(void);
void task7(void);
int getLength(char*);
void task8(void);
void task9(void);
void task10(void);

// functionsElevenToTwenty.c
void task11(void);
void task12(void);
void task13(void);
void task14(void);
void task15(void);
void task16(void);
void task17(void);
void task18(void);
void task19(void);
void task20(void);

// functionsTwentyOneToTwentySix.c
void task21(void);
void task22(void);
k task22ProductComplex(k, k);
void task23(void);
int task23Prime(int);
void task24(void);
int task24Perfect(int);
void task25(void);
int task25SumMN(int, int);
void task26(void);
int task26MiddleDigit(int);

#endif // HEADER_H