#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <float.h>
#define TASK3N 10

void task1(void) {
	system("cls");
	int n, tempIndex;
	TROKUT* triangles;
	do {
		printf("Unesite broj trokutova [1, 10]: ");
		if (scanf("%d", &n) <= 0) exit(EXIT_FAILURE);
	} while (n < 1 || n > 10);
	triangles = malloc(n * sizeof(TROKUT));
	if (!triangles) exit(EXIT_FAILURE);
	task1EnterTriangle(triangles, n);
	task1GetSides(triangles, n);
	tempIndex = task1FindBiggestPerimeter(triangles, n);
	system("cls");
	if (tempIndex != (-1)) printf("Trokut %d ima opseg %.2lf.\n", tempIndex, (triangles + tempIndex)->perimeter);
	else printf("Doslo je do pogreske.\n");
	free(triangles);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	_CrtDumpMemoryLeaks();
	return;
}

void task1EnterTriangle(TROKUT* triangles, int n) {
	for (int i = 0; i < n; i++) {
		do {
			system("cls");
			printf("Unesite prvu tocku [format: x y]: ");
			if (scanf("%f %f", &(triangles + i)->t1.x, &(triangles + i)->t1.y) <= 0) exit(EXIT_FAILURE);
		} while ((triangles + i)->t1.x < 0.0f || (triangles + i)->t1.y < 0.0f);
		do {
			printf("Unesite drugu tocku [format: x y]: ");
			if (scanf("%f %f", &(triangles + i)->t2.x, &(triangles + i)->t2.y) <= 0) exit(EXIT_FAILURE);
		} while ((triangles + i)->t2.x < 0.0f || (triangles + i)->t2.y < 0.0f);
		do {
			printf("Unesite trecu tocku [format: x y]: ");
			if (scanf("%f %f", &(triangles + i)->t3.x, &(triangles + i)->t3.y) <= 0) exit(EXIT_FAILURE);
		} while ((triangles + i)->t3.x < 0.0f || (triangles + i)->t3.y < 0.0f);
	}
}

void task1GetSides(TROKUT* triangles, int n) {
	for (int i = 0; i < n; i++) {
		(triangles + i)->firstSide = sqrt(pow(((double)(triangles + i)->t2.x - (triangles + i)->t1.x), 2) + pow(((double)(triangles + i)->t2.y - (triangles + i)->t1.y), 2));
		(triangles + i)->secondSide = sqrt(pow(((double)(triangles + i)->t3.x - (triangles + i)->t2.x), 2) + pow(((double)(triangles + i)->t3.y - (triangles + i)->t2.y), 2));
		(triangles + i)->thirdSide = sqrt(pow(((double)(triangles + i)->t3.x - (triangles + i)->t1.x), 2) + pow(((double)(triangles + i)->t3.y - (triangles + i)->t1.y), 2));
		(triangles + i)->perimeter = ((triangles + i)->firstSide + (triangles + i)->secondSide + (triangles + i)->thirdSide);
	}
}

int task1FindBiggestPerimeter(TROKUT* triangles, int n) {
	int i, tempIndx = (-1);
	double biggest = DBL_MIN;
	for (i = 0; i < n; i++) {
		if ((triangles + i)->perimeter > biggest) {
			tempIndx = i;
			biggest = (triangles + i)->perimeter;
		}
	}
	return tempIndx;
}

void task2(void) {
	system("cls");
	ARTIKL* arr, max;
	int i, n;
	float maxPrice = FLT_MIN;
	do {
		printf("Unesite broj artikala [1, 50]: ");
		if (scanf("%d", &n) <= 0) exit(EXIT_FAILURE);
	} while (n < 1 || n > 50);
	arr = malloc(n * sizeof(ARTIKL));
	if (!arr) exit(EXIT_FAILURE);
	for (i = 0; i < n; i++) {
		system("cls");
		printf("\tUnos %d. artikla\n\nUnesite naziv: ", (i + 1));
		if (getchar() <= 0) exit(EXIT_FAILURE);
		if (fgets((arr + i)->name, 30, stdin) == NULL) exit(EXIT_FAILURE);
		printf("Unesite cijenu: ");
		if (scanf("%f", &(arr + i)->price) <= 0) exit(EXIT_FAILURE);
		printf("Unesite kolicinu: ");
		if (scanf("%d", &(arr + i)->quantity) <= 0) exit(EXIT_FAILURE);
		if ((arr + i)->price > maxPrice) {
			maxPrice = (arr + i)->price;
			max = *(arr + i);
		}
	}
	system("cls");
	printf("\tNajskuplji artikl\n\nNaziv: %sCijena: %.2f\nKolicina: %d\n", max.name, max.price, max.quantity);
	free(arr);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	_CrtDumpMemoryLeaks();
	return;
}

void task3(void) {
	system("cls");
	TOCKA* arr;
	int i, tmpIndx = 0;
	float maxTocka = FLT_MIN;
	arr = malloc(TASK3N * sizeof(TOCKA));
	if (!arr) exit(EXIT_FAILURE);
	for (i = 0; i < TASK3N; i++) {
		system("cls");
		printf("\tUnos %d. tocke\n\nUnesite x: ", (i + 1));
		if (scanf("%f", &(arr + i)->x) <= 0) exit(EXIT_FAILURE);
		printf("Unesite y: ");
		if (scanf("%f", &(arr + i)->y) <= 0) exit(EXIT_FAILURE);
		printf("Unesite z: ");
		if (scanf("%f", &(arr + i)->z) <= 0) exit(EXIT_FAILURE);
		if ((arr + i)->z > maxTocka) {
			maxTocka = (arr + i)->z;
			tmpIndx = i;
		}
	}
	system("cls");
	printf("Najvisa tocka se nalazi na indexu %d.\n\nKoordinate [x, y, z]: [%.2f, %.2f, %.2f]\n", tmpIndx, (arr + tmpIndx)->x, (arr + tmpIndx)->y, (arr + tmpIndx)->z);
	free(arr);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	_CrtDumpMemoryLeaks();
	return;
}