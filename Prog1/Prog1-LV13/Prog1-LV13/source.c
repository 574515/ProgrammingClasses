#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <float.h>
#define FIRSTN 1000
#define SECONDN 20
#define FOURTHN 150

/*	1. Deklarirati polje od 1000 cijelih brojeva i popuniti ga pseudo-slučajnim brojevima iz [0, 10] iz Z. Potom izračunati i
	na ekran ispisati srednju vrijednost elemenata tog polja.
	2. Deklarirati matricu (2-D polje) realnih brojeva dimenzija 20 x 20 i popuniti ju pseudo-slučajnim brojevima iz [-5, 5]
	iz R. Pronaći i na ekran ispisati najveću i najmanju vrijednost u polju.
	3. Napisati funkciju koja popunjava cjelobrojno polje pseudo-slučajnim brojevima. Generirani brojevi trebaju biti unutar
	zadanog intervala. Na primjeru u funkciji main() pokazati uporabu napisane funkcije.
	4. Deklarirati polje od 150 cijelih brojeva. Popuniti polje vrijednostima 1 i 0 na sljedeći način: za svaki element posebno
	generirani pseudo-slučajni broj iz [0, 1] iz R, te ako je manji od 0.5 spremiti vrijednost 0, a u suprotnom spremiti
	vrijednost 1 u trenutni element. */

void first(void);
void second(void);
void third(void);
void generiraj(int*, int, int, int);
void fourth(void);

int main(void) {
	srand((unsigned)time(NULL));
	int choice;
	while (1) {
		do {
			system("cls");
			printf("[1] Prvi zadatak\n[2] Drugi zadatak\n[3] Treci zadatak\n[4] Cetvrti zadatak\n[5] Izlaz\n\nIzbor: ");
			if (scanf("%d", &choice) <= 0) exit(EXIT_FAILURE);
		} while (choice < 1 || choice > 5);
		switch (choice) {
		case 1: first(); break;
		case 2: second(); break;
		case 3: third(); break;
		case 4: fourth(); break;
		case 5: exit(EXIT_SUCCESS);
		}
	}
	return 0;
}

void first(void) {
	system("cls");
	int i, arr[FIRSTN] = { 0 };
	float average = 0.0f;
	for (i = 0; i < FIRSTN; i++) {
		*(arr + i) = rand() % 11;
		average += *(arr + i);
	}
	printf("\nSrednja vrijednost polja je %.2f.\n", (average / FIRSTN));
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

void second(void) {
	system("cls");
	float min = FLT_MAX, max = FLT_MIN, dg = (-5.0f), gg = 5.0f, arr[SECONDN][SECONDN] = { 0.0f };
	for (int i = 0; i < SECONDN; i++) {
		for (int j = 0; j < SECONDN; j++) {
			*(*(arr + i) + j) = dg + (float)rand() / RAND_MAX * (gg - dg);
			if (min > * (*(arr + i) + j)) min = *(*(arr + i) + j);
			if (max < *(*(arr + i) + j)) max = *(*(arr + i) + j);
		}
	}
	printf("Najveca vrijednost u polju je %f.\nNajmanja vrijednost u polju je %f.\n", max, min);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

void third(void) {
	system("cls");
	int* arr, n, i, dg = 10, gg = 20;
	do {
		printf("Unesite n: ");
		if (scanf("%d", &n) <= 0) exit(EXIT_FAILURE);
	} while (n < 1);
	arr = malloc(n * sizeof(int));
	if (!arr) exit(EXIT_FAILURE);
	generiraj(arr, dg, gg, n);
	printf("\nGenerirano polje u granicama [%d, %d]:\n\n", dg, gg);
	for (i = 0; i < n; i++) printf("%d ", *(arr + i));
	free(arr);
	_CrtDumpMemoryLeaks();
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

void generiraj(int* arr, int dg, int gg, int n) {
	for (int i = 0; i < n; i++) *(arr + i) = dg + (float)rand() / RAND_MAX * (gg - dg);
}

void fourth(void) {
	system("cls");
	int arr[FOURTHN] = { 0 }, i;
	for (i = 0; i < FOURTHN; i++) {
		if ((0 + (float)rand() / RAND_MAX * (1 - 0)) < 0.5f) *(arr + i) = 0;
		else *(arr + i) = 1;
	}
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}