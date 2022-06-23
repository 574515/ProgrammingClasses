#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <float.h>

void task1(void) {
	system("cls");
	int* arr, m, n, tempIndex;
	arr = task1EnterLength();
	m = *(arr + 0), n = *(arr + 1);
	TOCKA* vertices = task1AllocateVertices(m);
	TROKUT* triangles = task1AllocateTriangles(n);
	task1FillCoordinates(vertices, m);
	task1SelectVertices(vertices, triangles, m, n);
	tempIndex = task1FindBiggestPerimeter(triangles, n);
	task1PrintBiggestTriangle(triangles, n, tempIndex);
	free(arr);
	free(vertices);
	free(triangles);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	_CrtDumpMemoryLeaks();
	return;
}

int* task1EnterLength(void) {
	int* arr;
	arr = malloc(2 * sizeof(int));
	if (!arr) exit(EXIT_FAILURE);
	do {
		printf("Unesite m [5, 100]: ");
		if (scanf("%d", &(*(arr + 0))) <= 0) exit(EXIT_FAILURE);
	} while (*(arr + 0) < 5 || *(arr + 0) > 100);
	do {
		printf("Unesite n [3, 15]: ");
		if (scanf("%d", &(*(arr + 1))) <= 0) exit(EXIT_FAILURE);
	} while (*(arr + 1) < 3 || *(arr + 1) > 15);
	return arr;
}

TOCKA* task1AllocateVertices(int m) {
	TOCKA* vertices;
	vertices = malloc(m * sizeof(TOCKA));
	if (!vertices) exit(EXIT_FAILURE);
	return vertices;
}

TROKUT* task1AllocateTriangles(int n) {
	TROKUT* triangles;
	triangles = malloc(n * sizeof(TROKUT));
	if (!triangles) exit(EXIT_FAILURE);
	return triangles;
}

void task1FillCoordinates(TOCKA* vertices, int m) {
	for (int i = 0; i < m; i++) {
		(vertices + i)->x = (rand() % (m - 0 + 1)) + 0;
		(vertices + i)->y = (rand() % (m - 0 + 1)) + 0;
	}
}

void task1SelectVertices(TOCKA* vertices, TROKUT* triangles, int m, int n) {
	for (int i = 0; i < n; i++) {
		(triangles + i)->t1 = (vertices + (rand() % ((m - 1) - 0 + 1)) + 0);
		do {
			(triangles + i)->t2 = (vertices + (rand() % ((m - 1) - 0 + 1)) + 0);
		} while ((triangles + i)->t2 == (triangles + i)->t1);
		do {
			(triangles + i)->t3 = (vertices + (rand() % ((m - 1) - 0 + 1)) + 0);
		} while (((triangles + i)->t3 == (triangles + i)->t1) || ((triangles + i)->t3 == (triangles + i)->t2));
	}
}

double task1SidesLength(TOCKA tempT1, TOCKA tempT2) {
	return sqrt(pow(((double)tempT2.x - tempT1.x), 2) + pow(((double)tempT2.y - tempT1.y), 2));
}

int task1FindBiggestPerimeter(TROKUT* triangles, int n) {
	int i, tempIndex = (-1);
	double perimeter = 0.0, biggest = DBL_MIN;
	for (i = 0; i < n; i++) {
		perimeter += task1SidesLength(*(triangles + i)->t2, *(triangles + i)->t1);
		perimeter += task1SidesLength(*(triangles + i)->t3, *(triangles + i)->t2);
		perimeter += task1SidesLength(*(triangles + i)->t3, *(triangles + i)->t1);
		if (perimeter > biggest) {
			biggest = perimeter;
			tempIndex = i;
		}
		perimeter = 0.0;
	}
	return tempIndex;
}

void task1PrintBiggestTriangle(TROKUT* triangles, int n, int index) {
	double side1, side2, side3;
	printf("\n\tNajveci je trokut na indeksu %d.\n\n", index);
	printf("TOCKA\t[ X,  Y]\n");
	printf("1\t[%2d, %2d]\n", (triangles + index)->t1->x, (triangles + index)->t1->y);
	printf("2\t[%2d, %2d]\n", (triangles + index)->t2->x, (triangles + index)->t2->y);
	printf("3\t[%2d, %2d]\n\n", (triangles + index)->t3->x, (triangles + index)->t3->y);
	side1 = task1SidesLength(*(triangles + index)->t2, *(triangles + index)->t1);
	side2 = task1SidesLength(*(triangles + index)->t3, *(triangles + index)->t2);
	side3 = task1SidesLength(*(triangles + index)->t3, *(triangles + index)->t1);
	printf("STRANICA\tVELICINA\n");
	printf("d(t1, t2)\t[%lf]\n", side1);
	printf("d(t2, t3)\t[%lf]\n", side2);
	printf("d(t3, t1)\t[%lf]\n\n", side3);
	printf("Ukupan opseg: [%lf].\n", (side1 + side2 + side3));
}

void task2(void) {
	system("cls");
	ARTIKL* articles;
	int m = task2GetLength();
	articles = task2CreateArticles(m);
	task2InputArticles(articles, m);
	task2PrintArticle(task2FindMostExpesniveArticle(articles, m));
	free(articles);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

int task2GetLength(void) {
	int m;
	do {
		printf("Unesite m [1, 60]: ");
		if (scanf("%d", &m) <= 0)exit(EXIT_FAILURE);
	} while (m < 1 || m > 60);
	return m;
}

ARTIKL* task2CreateArticles(int m) {
	ARTIKL* temp;
	temp = malloc(m * sizeof(ARTIKL));
	if (!temp) exit(EXIT_FAILURE);
	return temp;
}

void task2InputArticles(ARTIKL* articles, int m) {
	for (int i = 0; i < m; i++) {
		system("cls");
		printf("[%d artikl] Naziv: ", (i + 1));
		if (getchar() <= 0) exit(EXIT_FAILURE);
		if (fgets((articles + i)->itemName, 40, stdin) == NULL) exit(EXIT_FAILURE);
		printf("[%d artikl] Cijena: ", (i + 1));
		if (scanf("%f", &(articles + i)->price) <= 0) exit(EXIT_FAILURE);
		printf("[%d artikl] Kolicina: ", (i + 1));
		if (scanf("%d", &(articles + i)->quantity) <= 0) exit(EXIT_FAILURE);
	}
}

ARTIKL task2FindMostExpesniveArticle(ARTIKL* articles, int m) {
	int i, tempIndex = (-1);
	float biggest = FLT_MIN;
	for (i = 0; i < m; i++) {
		if ((articles + i)->price > biggest) {
			biggest = (articles + i)->price;
			tempIndex = i;
		}
	}
	return *(articles + tempIndex);
}

void task2PrintArticle(ARTIKL article) {
	system("cls");
	printf("\n\tNajskuplji artikl\n\n");
	printf("Naziv: %s", article.itemName);
	printf("Cijena: %f\n", article.price);
	printf("Kolicina: %d\n", article.quantity);
}