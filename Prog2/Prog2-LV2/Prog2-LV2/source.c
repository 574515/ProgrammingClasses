#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#define CONDITION *(*(arr + i) + j) != 'a' && *(*(arr + i) + j) != 'e' && *(*(arr + i) + j) != 'i' && *(*(arr + i) + j) != 'o' && *(*(arr + i) + j) != 'u'
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <float.h>

/*	1. Napisati C program koji omogućava unos broja n, (1 ≤ 𝑛 ≤ 7) koji predstavlja dane u tjednu. Ukoliko je unesen broj
	koji ne odgovara broju dana u tjednu, ispisati poruku "Krivo uneseni broj za dan" i zatražiti novi unosa broja n. Za
	inicijalizaciju imena dana koristiti polje pokazivača. Ispisati traženi dan. Koristiti isključivo pokazivačku notaciju!
	2. Nadovezujući se na prvi zadatak, proširiti ga tako da se provjerio koji dan ima najviše suglasnika, te ispisati
	naopako dan s najvećim brojem suglasnika.
	3. Napisati C program koji omogućava unos broja n (2 ≤ 𝑛 ≤ 8), ponavljati sve dok unos ne odgovara traženom intervalu.
	Dinamički zauzeti memorijski prostor za realnu matricu M, te ju popuniti pseudo-slučajnim vrijednostima iz intervala
	[-1.25, 5,75], popunjavanje matrice obaviti pomoću funkcije. Ispisati matricu M u matričnom obliku, ispis matrice
	obaviti pomoću funkcije. Pronaći najveći element matrice M iznad sporedne dijagonale i ispisati rezultat na standardnom
	izlazu, pronalaženje najvećeg elementa obaviti pomoću funkcije koja će ujedno vratiti najveći pronađeni element, te
	povratnu vrijednost funkcije ispisati u glavnom dijelu programa. Na kraju programa osloboditi dinamički zauzetu
	memoriju. Koristiti isključivo pokazivački notaciju! */

void task1And2(void);
int task1And2FindConsonants(char*[]);
void task1And2PrintBackwards(char*[], int);
void task3(void);
float** task3FillMatrix(float**, int, float, float);
void task3PrintMatrix(float**, int);
float task3FindBiggest(float**, int);

int main(void) {
	int choice;
	srand((unsigned)time(NULL));
	while (1) {
		do {
			system("cls");
			printf("Unesite broj zadatka [1, 3] ili [0] za izlaz: ");
			if (scanf("%d", &choice) <= 0) exit(EXIT_FAILURE);
		} while (choice < 0 || choice > 3);
		switch (choice) {
		case 0: exit(EXIT_SUCCESS);
		case 1: task1And2(); break;
		case 2: task1And2(); break;
		case 3: task3(); break;
		}
	}
	return 0;
}

void task1And2(void) {
	system("cls");
	int n;	
	do {
		printf("Unesite broj dana u tjednu [1, 7]: ");
		if (scanf("%d", &n) <= 0) exit(EXIT_FAILURE);
		if (n < 1 || n > 7) printf("Krivo uneseni broj za dan.\n");
	} while (n < 1 || n > 7);
	char* daysInWeek[] = { "ponedjeljak", "utorak", "srijeda", "cetvrtak", "petak", "subota", "nedjelja" };
	printf("\n%d. dan u tjednu je %s.", n, *(daysInWeek + (n - 1)));
	printf("\nDan s najvise suglasnika je ");
	task1And2PrintBackwards(daysInWeek, task1And2FindConsonants(daysInWeek));
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

int task1And2FindConsonants(char* arr[]) {
	int i, j, index, tempSum = 0, sum;
	for (i = 0; i < 7; i++) {
		sum = 0;
		for (j = 0; *(*(arr + i) + j) != '\0'; j++) if(CONDITION) sum++;
		if (sum > tempSum) {
			tempSum = sum;
			index = i;
		}
	}
	return index;
}

void task1And2PrintBackwards(char* arr[], int n) {
	int i, count = 0;
	for (i = 0; *(*(arr + n) + i) != '\0'; i++) count++;
	for (i = (count - 1); i >= 0; i--) printf("%c", *(*(arr + n) + i));
	printf(".");
}

void task3(void) {
	system("cls");
	int n, i;
	do {
		printf("Unesite n [2, 8]: ");
		if (scanf("%d", &n) <= 0) exit(EXIT_FAILURE);
	} while (n < 2 || n > 8);
	float** M, dg = (-1.25f), gg = 5.75f;
	M = malloc(n * sizeof(float*));
	if (!M) exit(EXIT_FAILURE);
	for (i = 0; i < n; i++) {
		*(M + i) = malloc(n * sizeof(float));
		if (!*(M + i)) exit(EXIT_FAILURE);
	}
	M = task3FillMatrix(M, n, dg, gg);
	printf("\n");
	task3PrintMatrix(M, n);
	printf("\nNajveci broj iznad sporedne dijagonale je %.2f.\n", task3FindBiggest(M, n));
	for (i = 0; i < n; i++) free(*(M + i));
	free(M);
	_CrtDumpMemoryLeaks();
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

float** task3FillMatrix(float** M, int n, float dg, float gg) {
	for (int i = 0; i < n; i++) for(int j = 0; j < n; j++) *(*(M + i) + j) = dg + (float)rand() / RAND_MAX * (gg - dg);
	return M;
}

void task3PrintMatrix(float** M, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) printf("%5.2f ", *(*(M + i) + j));
		printf("\n");
	}
}

float task3FindBiggest(float** M, int n) {
	float max = FLT_MIN;
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (((i + j) < (n - 1)) && (*(*(M + i) + j) > max)) max = *(*(M + i) + j);
	return max;
}