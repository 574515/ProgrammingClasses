#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <float.h>
#include <stdbool.h>

/*	1. Omogućiti korisniku unos željene veličine polja realnih brojeva. Dinamički zauzeti potrebnu memoriju. Popuniti polje
	pseudo-slučajnim brojevima u [−100, 100]. Pronaći i na ekran ispisati najmanju i najveću vrijednost elemenata u polju.
	2. Generirati pseudo-slučajni cijeli broj u [50, 1000] te zauzeti dinamički memoriju za toliko podataka tipa double.
	Popuniti dobiveno polje pseudo-slučajnim brojevima u [0, 1]. Provjeriti i na ekran ispisati odgovarajuću poruku nalazi
	li se u polju vrijednost 1.
	3. Omogućiti korisniku unos željene duljine stringa (1 ≤ m < 500). Dinamički zauzeti potrebnu memoriju (uzeti u obzir i
	mjesto potrebno za null znak). Potom, omogućiti korisniku unos rečenice od maksimalno m znakova. Odrediti i na ekran
	ispisati koliko se puta pojavljuje razmak.
	4. Napisati funkciju koja računa zbroj dva vektora predstavljena poljima realnih brojeva (uzeti u obzir kako oba polja
	moraju biti iste veličine). Funkcija kao rezultat vraća polje koje je rezultat zbrajanja. Na primjeru u funkciji main()
	pokazati uporabu napisane funkcije. Za sva polja dinamički zauzeti potrebnu memoriju. */

void first(void);
void second(void);
void third(void);
void fourth(void);
float* genArr(int, float, float);
float* allocate(int);
void printArr(float*, int);
float* arrAddition(float*, float*, int);

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
	int n, i;
	float* arr, min = FLT_MAX, max = FLT_MIN;
	do {
		printf("Unesite n: ");
		if (scanf("%d", &n) <= 0) exit(EXIT_FAILURE);
	} while (n < 1);
	arr = malloc(n * sizeof(float));
	if (!arr) exit(EXIT_FAILURE);
	for (i = 0; i < n; i++) {
		*(arr + i) = (-100.0f) + (float)rand() / RAND_MAX * (100.0f - (-100.0f));
		if (max < *(arr + i)) max = *(arr + i);
		if (min > * (arr + i)) min = *(arr + i);
	}
	printf("Najveca vrijednost u polju je %f.\nNajmanja vrijednost u polju je %f.\n", max, min);
	free(arr);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	_CrtDumpMemoryLeaks();
	return;
}

void second(void) {
	system("cls");
	int i, num = 50 + rand() / RAND_MAX * (1000 - 50);
	double* arr = malloc(num * sizeof(double));
	bool flag = false;
	if (!arr) exit(EXIT_FAILURE);
	for (i = 0; i < num; i++) {
		*(arr + i) = 0 + (float)rand() / RAND_MAX * (1 - 0);
		if (*(arr + i) == 1) flag = true;
	}
	if (flag) printf("U polju se nalazi vrijednost 1.\n");
	else printf("U polju se NE NALAZI vrijednost 1.\n");
	free(arr);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	_CrtDumpMemoryLeaks();
	return;
}

void third(void) {
	system("cls");
	int m, i, counter = 0;
	char* arr;
	do {
		printf("Unesite m [1, 500>: ");
		if (scanf("%d", &m) <= 0) exit(EXIT_FAILURE);
	} while (m < 1 || m > 499);
	arr = calloc((m + 1), sizeof(char));
	if (!arr) exit(EXIT_FAILURE);
	printf("Unesite string: ");
	if (getchar() <= 0) exit(EXIT_FAILURE);
	if (fgets(arr, (m + 1), stdin) == NULL) exit(EXIT_FAILURE);
	for (i = 0; *(arr + i) != '\0'; i++) if (*(arr + i) == ' ') counter++;
	printf("\nU stringu se razmak pojavljuje %d puta.\n", counter);
	free(arr);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	_CrtDumpMemoryLeaks();
	return;
}

void fourth(void) {
	system("cls");
	int n = 20;
	float* firstArr, * secondArr, * tempArr = NULL, dg = 20.0f, gg = 40.0f;
	firstArr = genArr(n, dg, gg);
	secondArr = genArr(n, dg, gg);
	printf("Prvo generirano polje:\n");
	printArr(firstArr, n);
	printf("\n\nDrugo generirano polje:\n");
	printArr(secondArr, n);
	tempArr = arrAddition(firstArr, secondArr, n);
	printf("\n\nZbroj polja:\n");
	printArr(tempArr, n);
	free(firstArr);
	free(secondArr);
	free(tempArr);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	_CrtDumpMemoryLeaks();
	return;
}

float* genArr(int n, float dg, float gg) {
	float* tempArr = allocate(n);
	for (int i = 0; i < n; i++) *(tempArr + i) = dg + (float)rand() / RAND_MAX * (gg - dg);
	return tempArr;
}

float* allocate(int n) {
	float* tempArr = malloc(n * sizeof(float));
	if (!tempArr) exit(EXIT_FAILURE);
	return tempArr;
}

void printArr(float* arr, int n) { 
	for (int i = 0; i < n; i++) printf("%f ", *(arr + i)); 
}

float* arrAddition(float* firstArr, float* secondArr, int n) {
	float* retArr = allocate(n);
	for (int i = 0; i < n; i++) *(retArr + i) = *(firstArr + i) + *(secondArr + i);
	return retArr;
}