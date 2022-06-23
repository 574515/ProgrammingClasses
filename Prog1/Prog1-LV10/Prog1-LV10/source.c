#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <float.h>

/*	1. Omogućiti korisniku unos elemenata matrice A dimenzija 2 x 4. Potom, na ekran ispisati transponiranu matricu,
	matrice A [(𝐴𝑇)𝑖,𝑗 = (𝐴)𝑗,𝑖].
	2. Omogućiti korisniku unos dimenzija matrice realnih brojeva m x n (1 < m < 11 i 5 < n < 9) i njeno popunjavanje.
	Pronaći i na ekran ispisati element matrice s najmanjom vrijednosti.
	3. Omogućiti korisniku unos dimenzija dvije matrice realnih brojeva m x n (1 < m ≤ 5 i 2 < n ≤ 10) kao i njihovo
	popunjavanje te izračunati i na ekran ispisati zbroj i razliku tih matrica [(A ± B)i,j = (A)i,j±(B)i,j].
	4. Omogućiti korisniku unos dimenzija kvadratne matrice m x m (2 ≤ m ≤ 10) i njeno popunjavanje. Odrediti i na ekran
	ispisati najmanju vrijednost na glavnoj te najveću vrijednost na sporednoj dijagonali. */

void first(void);
void second(void);
void third(void);
void printMatrix(float**, int, int);
void fourth(void);
float** zauzmi(int, int);

int main(void) {
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
		case 5: _CrtDumpMemoryLeaks(); exit(EXIT_SUCCESS);
		}
	}
	return 0;
}

void first(void) {
	system("cls");
	int i, j, arr[2][4], transArr[4][2];
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 4; j++) {
			printf("Unos [%d, %d]: ", i, j);
			if (scanf("%d", &arr[i][j]) <= 0) exit(EXIT_FAILURE);
			transArr[j][i] = arr[i][j];
		}
	}
	printf("\nTransponirana matrica:\n");
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 2; j++) printf("%d ", transArr[i][j]);
		printf("\n");
	}
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

void second(void) {
	system("cls");
	float** arr = NULL, min = FLT_MAX;
	int i, j, m, n;
	do {
		printf("Unesite m <1, 11>: ");
		if (scanf("%d", &m) <= 0) exit(EXIT_FAILURE);
	} while (m < 2 || m > 10);
	do {
		printf("Unesite n <5, 9>: ");
		if (scanf("%d", &n) <= 0) exit(EXIT_FAILURE);
	} while (n < 6 || n > 8);
	arr = zauzmi(m, n);
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			printf("Unos [%d, %d]: ", i, j);
			if (scanf("%f", &arr[i][j]) <= 0) exit(EXIT_FAILURE);
			if (arr[i][j] < min) min = arr[i][j];
		}
	}
	printf("\nNajmanji broj u polju je %f.\n", min);
	for (i = 0; i < m; i++) free(arr[i]);
	free(arr);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

void third(void) {
	system("cls");
	float** firstArr = NULL, **secondArr = NULL, **tempArr = NULL;
	int i, j, m, n;
	do {
		printf("Unesite m <1, 5]: ");
		if (scanf("%d", &m) <= 0) exit(EXIT_FAILURE);
	} while (m < 2 || m > 5);
	do {
		printf("Unesite n <2, 10]: ");
		if (scanf("%d", &n) <= 0) exit(EXIT_FAILURE);
	} while (n < 3 || n > 8);
	firstArr = zauzmi(m, n);
	secondArr = zauzmi(m, n);
	tempArr = zauzmi(m, n);
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			printf("1. matrica -> Unos [%d, %d]: ", i, j);
			if (scanf("%f", &firstArr[i][j]) <= 0) exit(EXIT_FAILURE);
		}
	}
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			printf("2. matrica -> Unos [%d, %d]: ", i, j);
			if (scanf("%f", &secondArr[i][j]) <= 0) exit(EXIT_FAILURE);
			tempArr[i][j] = firstArr[i][j] + secondArr[i][j];
		}
	}
	printf("\nZbroj matrica:\n");
	printMatrix(tempArr, m, n);
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) tempArr[i][j] = firstArr[i][j] - secondArr[i][j];
	}
	printf("\nRazlika matrica:\n");
	printMatrix(tempArr, m, n);
	for (i = 0; i < m; i++) free(firstArr[i]);
	for (i = 0; i < m; i++) free(secondArr[i]);
	for (i = 0; i < m; i++) free(tempArr[i]);
	free(firstArr);
	free(secondArr);
	free(tempArr);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

void printMatrix(float** arr, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) printf("%10f ", arr[i][j]);
		printf("\n");
	}
}

void fourth(void) {
	system("cls");
	float** arr = NULL, max = FLT_MIN;
	int i, j, m;
	do {
		printf("Unesite m [2, 10]: ");
		if (scanf("%d", &m) <= 0) exit(EXIT_FAILURE);
	} while (m < 2 || m > 10);
	arr = zauzmi(m, m);
	for (i = 0; i < m; i++) {
		for (j = 0; j < m; j++) {
			printf("Unos [%d, %d]: ", i, j);
			if (scanf("%f", &arr[i][j]) <= 0) exit(EXIT_FAILURE);
		}
	}
	for (i = 0; i < m; i++) {
		for (j = 0; j < m; j++) if (i == j && arr[i][j] > max) max = arr[i][j];
	}
	printf("\nUnesena matrica:\n");
	printMatrix(arr, m, m);
	printf("\nNajveca vrijednost glavne dijagonale je %f.\n", max);
	max = FLT_MIN;
	for (i = 0; i < m; i++) {
		for (j = 0; j < m; j++) if (((i + j) == (m - 1)) && arr[i][j] > max) max = arr[i][j];
	}
	printf("Najveca vrijednost sporedne dijagonale je %f.\n", max);
	for (i = 0; i < m; i++) free(arr[i]);
	free(arr);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

float** zauzmi(int m, int n) {
	float** arr = malloc(m * sizeof(float*));
	if (!arr) exit(EXIT_FAILURE);
	for (int i = 0; i < m; i++) {
		arr[i] = malloc(n * sizeof(float));
		if (!arr[i]) exit(EXIT_FAILURE);
	}
	return arr;
}